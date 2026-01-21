#ifndef MOONBAR_BATTERY_H
#define MOONBAR_BATTERY_H

#include "moonbar.h"

char* get_sys_battery_dir();
uint16_t get_number_of_system_batteries();

typedef struct _Battery {
  char path[PATH_MAX];
  uint16_t index;
  char* status;
  char* type;
  char* health;
  char* manufacturer;
  char* model_name;
  char* serial_number;
  char* technology;
  uint64_t temp;
  uint64_t voltage_now;
  uint64_t alarm;
  uint64_t charge_full;
  uint64_t charge_now;
  uint64_t current_now;
  uint64_t cycle_count;
  uint64_t capacity;
  uint64_t manufacture_day;
  uint64_t manufacture_month;
  uint64_t manufacture_year;
} Battery;

void batt_init(Battery* batt, const uint16_t index);
void batt_free(Battery* batt);

static inline bool batt_is_status(Battery* batt, const char* status) {
  if (!batt)
    return false;
  return strncasecmp(batt->status, status, strlen(status)) == 0;
}

#define DEFINE_BATTERY_STATUS_CHECK(Name)            \
  static inline bool batt_is_##Name(Battery* batt) { \
    return batt_is_status(batt, #Name);              \
  }

DEFINE_BATTERY_STATUS_CHECK(full);
DEFINE_BATTERY_STATUS_CHECK(charging);
DEFINE_BATTERY_STATUS_CHECK(discharging);
#undef DEFINE_BATTERY_STATUS_CHECK

static const char* kBatteryMetatableName = "Battery";
static inline Battery* check_battery(lua_State* L, const int index) {
  // TODO(@s0cks): check userdata
  return (Battery*)lua_touserdata(L, index);
}

void mbarL_initmetatable_battery(lua_State* L);

#endif  // MOONBAR_BATTERY_H
