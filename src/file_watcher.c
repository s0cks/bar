#include "moonbar.h"
#include "app.h"
#include "file_watcher.h"

#define OWNER ctx->owner
#define HANDLE ctx->handle
#define APP_LOOP app->loop

void mbar_file_watcher_init(BarApp* app, FileWatcher* ctx, const char* filename, const int index) {
  ASSERT(app);
  ASSERT(ctx);
  ASSERT(filename);
  OWNER = app;
  uv_fs_event_init(APP_LOOP, &HANDLE);
  HANDLE.data = ctx;
  ctx->filename = strdup(filename);
#define L app->L
  luaL_checktype(L, index, LUA_TFUNCTION);
  lua_pushvalue(L, index);
  ctx->callback = luaL_ref(L, LUA_REGISTRYINDEX);
  ASSERT(ctx->callback != LUA_NOREF);
#undef L
}

MBAR_INLINE void
on_changed(uv_fs_event_t* handle, const char* filename, int events, int status) {
  //TODO(@s0cks): implement
  LOG("file changed");
  FileWatcher* ctx = (FileWatcher*)handle->data;
  mbar_file_watcher_stop(ctx);
  //TODO(@s0cks): need to reinit file watcher
  mbar_file_watcher_start(ctx);

  if(ctx->callback != LUA_NOREF) {
    LOG("executing lua callback");
#define L OWNER->L
    lua_rawgeti(L, LUA_REGISTRYINDEX, ctx->callback);
    const int status = lua_pcall(L, 0, 0, 0);
    if(status != LUA_OK) {
      luaL_error(L, "failed to execute callback");
      return;
    }
#undef L
  }
}

void mbar_file_watcher_start(FileWatcher* ctx) {
  ASSERT(ctx);
  ASSERT(ctx->callback != LUA_NOREF);
  if(mbar_file_watcher_is_running(ctx))
    return;
  LOG_F("starting file watcher for: %s...\n", ctx->filename);
  const int status = uv_fs_event_start(&HANDLE, &on_changed, ctx->filename, 0);
  if(status != UV_OK)
    mbar_error(OWNER, "failed to start file watcher");
}

void mbar_file_watcher_stop(FileWatcher* ctx) {
  ASSERT(ctx);
  if(!mbar_file_watcher_is_running(ctx))
    return;
  LOG("stopping file watcher");
  const int status = uv_fs_event_stop(&HANDLE);
  if(status != UV_OK)
    mbar_error(OWNER, "failed to stop file watcher");
}

void mbar_file_watcher_free(FileWatcher* ctx) {
  ASSERT(ctx);
  if(ctx->filename)
    free(ctx->filename);
  //TODO(@s0cks): implement
}
