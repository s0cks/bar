#include "moonbar.h"
#include "state_lua.h"

DEFINE_LUA_TYPE_LIB(event_route, EventRoute);

DEFINE_LUA_TYPE_INIT_F(event_route) {
  BarApp* app = mbarL_get_mbar_app(L);
  if(!app) {
    luaL_error(L, "failed to get global bar state");
    return 0;
  }
  mbarL_push_new_event_route(app);
  return 1;
}
