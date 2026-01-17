#include "moonbar.h"
#include "button.h"
#include "state_lua.h"

DEFINE_LUA_TYPE_LIB(button, Button);

DEFINE_LUA_TYPE_INIT_F(button) {
  const char* text = NULL;
  if(lua_isnoneornil(L, -1)) {
    text = NULL;
  } else {
    text = lua_tostring(L, -1);
  }

  BarApp* app = mbarL_get_mbar_app(L);
  if(!app) {
    luaL_error(L, "failed to get global bar state");
    return 0;
  }
  mbarL_push_button(app, text);
  return 1;
}
