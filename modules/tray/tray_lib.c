#include "tray.h"

DEFINE_LUA_F(new_tray) {
  mbarL_check_global_app(L, app);
  Tray* tray = tray_new();
  if (!tray) {
    luaL_error(L, "failed to create new Tray\n");
    return 0;
  }
  fprintf(stdout, "appending tray widget\n");
  mbar_append_left(app, tray->box);

  lua_pushlightuserdata(L, tray);
  luaL_getmetatable(L, kTrayMetatableName);
  lua_setmetatable(L, -2);
  return 1;
}

// clang-format off
static const luaL_Reg kLibFuncs[] = {
  {"new", new_tray},
  {nullptr, nullptr},
};
// clang-format on

extern int luaopen_moonbar_tray(lua_State* L) {
  trayL_initmetatable(L);
  LUA_NEW_LIB_TABLE(kLibFuncs);
  return 1;
}
