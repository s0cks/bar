#include <lua.h>

#include "battery.h"

static inline int get_number_of_batteries(lua_State* L) {
  uint16_t num_batteries = get_number_of_system_batteries();
  lua_pushnumber(L, (lua_Number)num_batteries);
  return 1;
}

DEFINE_LUA_F(batt_new) {
  const lua_Number index = luaL_checknumber(L, 1);
  Battery* batt = (Battery*)malloc(sizeof(Battery));
  if (!batt) {
    luaL_error(L, "failed to alloc memory for Battery\n");
    return 0;
  }
  batt_init(batt, (uint16_t)index);
  lua_pushlightuserdata(L, batt);
  luaL_getmetatable(L, kBatteryMetatableName);
  lua_setmetatable(L, -2);
  return 1;
}

static const luaL_Reg kBatteryLibFuncs[] = {
    {"get_number_of_batteries", get_number_of_batteries},
    {"new", batt_new},
    {nullptr, nullptr},
};

extern int luaopen_moonbar_battery(lua_State* L) {
  fprintf(stdout, "opening battery lib...\n");
  mbarL_initmetatable_battery(L);
  LUA_NEW_LIB_TABLE(kBatteryLibFuncs);
  return 1;
}
