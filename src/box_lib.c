#include "moonbar.h"
#include "box.h"
#include "state_lua.h"

DEFINE_LUA_TYPE_LIB(box, Box);

DEFINE_LUA_TYPE_INIT_F(box) {
  BarApp* app = mbarL_get_mbar_app(L);
  if(!app) {
    luaL_error(L, "failed to get global bar state");
    return 0;
  }
  const int orientation = lua_tonumber(L, 1);
  mbarL_push_box(app, orientation);
  return 1;
}
