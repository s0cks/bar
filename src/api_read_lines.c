#include "moonbar.h"
#include "state_lua.h"
#include "app.h"
#include "state_gtk.h"
#include "uv_gsource.h"
#include "log.h"
#include "hypr_client.h"
#include "util.h"
#include "file_line_reader.h"
#include "api.h"

int mbarL_api_read_lines(lua_State* L) {
  ASSERT(L);
  const int num_args = lua_gettop(L);
  mbarL_check_global_app(L, app);
  luaL_checkstring(L, 1);
  const char* filename = lua_tostring(L, 1);
  FileLineReader* reader = (FileLineReader*)malloc(sizeof(FileLineReader));
  if(!reader) {
    luaL_error(L, "failed to alloc memory for FileLineReader");
    return 0;
  }

  int on_next = LUA_NOREF;
  luaL_checktype(L, 2, LUA_TFUNCTION);
  lua_pushvalue(L, 2);
  on_next = luaL_ref(L, LUA_REGISTRYINDEX);
  ASSERT(on_next != LUA_NOREF);

  int on_err = LUA_NOREF;
  if(num_args >= 3) {
    luaL_checktype(L, 3, LUA_TFUNCTION);
    lua_pushvalue(L, 3);
    on_err = luaL_ref(L, LUA_REGISTRYINDEX);
    ASSERT(on_err != LUA_NOREF);
  }

  int on_finished = LUA_NOREF;
  if(num_args >= 4) {
    luaL_checktype(L, 4, LUA_TFUNCTION);
    lua_pushvalue(L, 4);
    on_finished = luaL_ref(L, LUA_REGISTRYINDEX);
    ASSERT(on_finished != LUA_NOREF);
  }

  line_reader_init(app, reader, on_next, on_err, on_finished);
  line_reader_read(reader, filename);
  return 0;
}
