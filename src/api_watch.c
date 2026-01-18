#include "moonbar.h"
#include "state_lua.h"
#include "app.h"
#include "state_gtk.h"
#include "uv_gsource.h"
#include "log.h"
#include "hypr_client.h"
#include "util.h"
#include "file_watcher.h"
#include "api.h"

int mbarL_api_watch(lua_State* L) {
  ASSERT(L);
  const int num_args = lua_gettop(L);
  mbarL_check_global_app(L, app);
  luaL_checkstring(L, 1);
  const char* filename = lua_tostring(L, 1);

  FileWatcher* ctx = (FileWatcher*)malloc(sizeof(FileWatcher));
  if(!ctx) {
    luaL_error(L, "failed to alloc memory for FileWatcher");
    return 0;
  }

  LOG_F("watching: %s\n", filename);
  mbar_file_watcher_init(app, ctx, filename, 2); // TODO(@s0cks): prolly should get the reference and pass it as an arg instead
  mbar_file_watcher_start(ctx);
  return 0;
}
