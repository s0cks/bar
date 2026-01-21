#include "battery.h"
#include "moonbar.h"

#define DEFINE_GET_BATTERY_STR_F(Name)   \
  DEFINE_LUA_F(batt_get_##Name) {        \
    Battery* batt = check_battery(L, 1); \
    ASSERT(batt);                        \
    lua_pushstring(L, batt->Name);       \
    return 1;                            \
  }

DEFINE_GET_BATTERY_STR_F(type);
DEFINE_GET_BATTERY_STR_F(status);
DEFINE_GET_BATTERY_STR_F(health);
DEFINE_GET_BATTERY_STR_F(manufacturer);
DEFINE_GET_BATTERY_STR_F(model_name);
DEFINE_GET_BATTERY_STR_F(serial_number);
DEFINE_GET_BATTERY_STR_F(technology);

#undef DEFINE_GET_BATTERY_STR_F

#define DEFINE_GET_BATTERY_UINT64_F(Name) \
  DEFINE_LUA_F(batt_get_##Name) {         \
    Battery* batt = check_battery(L, 1);  \
    ASSERT(batt);                         \
    lua_pushnumber(L, batt->Name);        \
    return 1;                             \
  }

DEFINE_GET_BATTERY_UINT64_F(temp);
DEFINE_GET_BATTERY_UINT64_F(voltage_now);
DEFINE_GET_BATTERY_UINT64_F(alarm);
DEFINE_GET_BATTERY_UINT64_F(capacity);
DEFINE_GET_BATTERY_UINT64_F(charge_full);
DEFINE_GET_BATTERY_UINT64_F(charge_now);
DEFINE_GET_BATTERY_UINT64_F(current_now);
DEFINE_GET_BATTERY_UINT64_F(cycle_count);
DEFINE_GET_BATTERY_UINT64_F(manufacture_day);
DEFINE_GET_BATTERY_UINT64_F(manufacture_month);

#undef DEFINE_GET_BATTERY_UINT64_F

#define DEFINE_LUA_STATUS_CHECK_F(Name)       \
  DEFINE_LUA_F(is_##Name) {                   \
    Battery* batt = check_battery(L, 1);      \
    ASSERT(batt);                             \
    lua_pushboolean(L, batt_is_##Name(batt)); \
    return 1;                                 \
  }

DEFINE_LUA_STATUS_CHECK_F(full);
DEFINE_LUA_STATUS_CHECK_F(charging);
DEFINE_LUA_STATUS_CHECK_F(discharging);
#undef DEFINE_LUA_STATUS_CHECK_F

DEFINE_LUA_F(batt_close) {
  Battery* batt = check_battery(L, 1);
  ASSERT(batt);
  batt_free(batt);
  return 0;
}

// clang-format off
DECLARE_LUA_METATABLE(Battery){
#define DEFINE_GETTER(Name) \
  {"get_" #Name, batt_get_##Name}

  DEFINE_GETTER(type),
  DEFINE_GETTER(status),
  DEFINE_GETTER(health),
  DEFINE_GETTER(manufacturer),
  DEFINE_GETTER(model_name),
  DEFINE_GETTER(serial_number),
  DEFINE_GETTER(technology),
  DEFINE_GETTER(temp),
  DEFINE_GETTER(voltage_now),
  DEFINE_GETTER(alarm),
  DEFINE_GETTER(capacity),
  DEFINE_GETTER(charge_full),
  DEFINE_GETTER(charge_now),
  DEFINE_GETTER(current_now),
  DEFINE_GETTER(cycle_count),
  DEFINE_GETTER(manufacture_day),
  DEFINE_GETTER(manufacture_month),
#undef DEFINE_GETTER

#define DEFINE_STATUS_CHECK(Name) \
  { "is_" #Name, is_##Name }

  DEFINE_STATUS_CHECK(full),
  DEFINE_STATUS_CHECK(charging),
  DEFINE_STATUS_CHECK(discharging),
#undef DEFINE_STATUS_CHECK

  {"close", batt_close},
  {nullptr, nullptr},
};
// clang-format on
DEFINE_LUA_INITMETATABLE(battery, Battery);
