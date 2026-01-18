#include "file_line_reader.h"
#include "log.h"

void line_reader_init(BarApp* owner, FileLineReader* ctx, const int on_next, const int on_error, const int on_finished) {
  ASSERT(owner);
  ASSERT(ctx);
  memset(ctx, 0, sizeof(FileLineReader));
  ctx->owner = owner;
  ctx->open_handle.data = ctx;
  ctx->read_handle.data = ctx;
  ctx->on_next = on_next;
  ASSERT(ctx->on_next != LUA_NOREF);
  ctx->on_error = on_error;
  ctx->on_finished = on_finished;
}

MBAR_INLINE void
on_finished(FileLineReader* ctx) {
  ASSERT(ctx);
  if(ctx->on_finished != LUA_NOREF) {
#define L ctx->owner->L
    lua_rawgeti(L, LUA_REGISTRYINDEX, ctx->on_finished);
    const int status = lua_pcall(L, 0, 0, 0);
    if(status != LUA_OK) {
      luaL_error(L, "failed to execute callback");
      return;
    }
#undef L
  }

  uv_fs_close(ctx->owner->loop, &ctx->open_handle, ctx->open_handle.result, NULL);
  free(ctx->buf.base);
  free(ctx->remainder);
  free(ctx);
}

MBAR_INLINE void
on_read(uv_fs_t* handle) {
  ASSERT(handle);
  FileLineReader* ctx = (FileLineReader*)handle->data;
  if(handle->result < 0) {
    fprintf(stderr, "read error: %s\n", uv_strerror(handle->result));
    exit(handle->result);
    return;
  } else if(handle->result == 0) {
#define L ctx->owner->L
    if(ctx->remainder_len > 0) {
      ASSERT(ctx->on_next != LUA_NOREF);
      lua_pushstring(L, ctx->remainder);
      lua_rawgeti(L, LUA_REGISTRYINDEX, ctx->on_next);
      const int status = lua_pcall(L, 1, 0, 0);
      if(status != LUA_OK) {
        luaL_error(L, "failed to execute callback");
        return;
      }
    }
#undef L
    on_finished(ctx);
  } else {
    uint64_t total_len = ctx->remainder_len + handle->result;
    char* working = malloc(total_len);
    memcpy(working, ctx->remainder, ctx->remainder_len);
    memcpy(working + ctx->remainder_len, ctx->buf.base, handle->result);

    char* start = working;
    char* newline;
    while((newline = memchr(start, '\n', (working + total_len) - start))) {
      (*newline) = '\0';
#define L ctx->owner->L
      ASSERT(ctx->on_next != LUA_NOREF);
      lua_rawgeti(L, LUA_REGISTRYINDEX, ctx->on_next);
      lua_pushstring(L, start);
      const int status = lua_pcall(L, 1, 0, 0);
      if(status != LUA_OK) {
        luaL_error(L, "failed to execute callback");
        return;
      }
#undef L
      start = newline + 1;
    }

    size_t new_remainder_len = (working + total_len) - start;
    ctx->remainder = realloc(ctx->remainder, new_remainder_len);
    memcpy(ctx->remainder, start, new_remainder_len);
    ctx->remainder_len = new_remainder_len;

    free(working);
    uv_fs_req_cleanup(handle);

    const int status = uv_fs_read(ctx->owner->loop, &ctx->read_handle, ctx->open_handle.result, &ctx->buf, 1, -1, &on_read);
    if(status != UV_OK) {
      fprintf(stderr, "uv_fs_read failed: %s\n", uv_strerror(status));
      exit(status);
      return;
    }
  }
}

MBAR_INLINE void
on_open(uv_fs_t* handle) {
  ASSERT(handle);
  FileLineReader* ctx = (FileLineReader*)handle->data;
#define L ctx->owner->L
  if(handle->result < 0) {
    fprintf(stderr, "uv_fs_open failed: %s\n", uv_strerror(handle->result));
    if(ctx->on_finished == LUA_NOREF) {
      return;
    }

    lua_rawgeti(L, LUA_REGISTRYINDEX, ctx->on_error);
    lua_pushstring(L, "uv_fs_open failed");
    const int status = lua_pcall(L, 1, 0, 0);
    if(status != LUA_OK) {
      luaL_error(L, "failed to execute callback");
      return;
    }
    return;
  }

  ctx->buf = uv_buf_init(malloc(4096), 4096);
  const int status = uv_fs_read(ctx->owner->loop, &ctx->read_handle, (uv_file)handle->result, &ctx->buf, 1, -1, &on_read);
  if(status != UV_OK) {
    fprintf(stderr, "uv_fs_read failed: %s\n", uv_strerror(status));
    if(ctx->on_finished == LUA_NOREF) {
      return;
    }

    lua_rawgeti(L, LUA_REGISTRYINDEX, ctx->on_error);
    lua_pushstring(L, "uv_fs_read failed");
    const int status = lua_pcall(L, 1, 0, 0);
    if(status != LUA_OK) {
      luaL_error(L, "failed to execute callback");
      return;
    }
  }
#undef L
}

void line_reader_read(FileLineReader* ctx, const char* filename) {
  ASSERT(ctx);
  ASSERT(filename);
  const int status = uv_fs_open(ctx->owner->loop, &ctx->open_handle, filename, O_RDONLY, 0, &on_open);
  if(status != UV_OK) {
    fprintf(stderr, "failed to open %s: %s\n", filename, uv_strerror(status));
    exit(status);
    return;
  }
}

void line_reader_free(FileLineReader* ctx) {
  if(!ctx)
    return;
  //TODO(@s0cks): implement
  free(ctx);
}
