#include "moonbar.h"
#include "label.h"
#include "state_lua.h"

DEFINE_LUA_TYPE_LIB(label, Label);

DEFINE_LUA_TYPE_INIT_F(label) {
  const char* text =  lua_tostring(L, 1);
  BarApp* app = mbarL_get_mbar_app(L);
  if(!app) {
    luaL_error(L, "failed to get global bar state");
    return 0;
  }
  mbarL_push_new_label(app, text);
  return 1;
}
