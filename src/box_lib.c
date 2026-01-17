#include "moonbar.h"
#include "box.h"
#include "state_lua.h"

DEFINE_LUA_F(box_new) {
  BarApp* app = mbarL_get_mbar_app(L);
  if(!app) {
    luaL_error(L, "failed to get global bar state");
    return 0;
  }

  const int orientation = lua_tonumber(L, 1);
  fprintf(stdout, "creating box w/ orientation %d\n", orientation);
  Box* value = mbar_create_box(app, orientation);
  if(!value) {
    luaL_error(L, "failed to create gtk box.");
    return 0;
  }
  fprintf(stdout, "pushing box\n");
  mbarL_pushbox(L, value);
  return 1;
}

DECLARE_LUA_LIB(Box) {
  { "new", box_new },
  { NULL, NULL },
};

DEFINE_LUA_INITLIB(box);
