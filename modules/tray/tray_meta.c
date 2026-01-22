#include "tray.h"

// clang-format off
static const luaL_Reg kTrayFuncs[] = {
  {nullptr, nullptr},
};
// clang-format on

void trayL_initmetatable(lua_State* L) {
  luaL_newmetatable(L, kTrayMetatableName);
  luaL_setfuncs(L, kTrayFuncs, 0);
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
}
