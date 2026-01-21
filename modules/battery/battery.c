#include "battery.h"

#include <dirent.h>
#include <stdio.h>
#include <string.h>

#include "moonbar.h"

char* get_sys_battery_dir() {
  return "/sys/class/power_supply";
}

uint16_t get_number_of_system_batteries() {
  char* batt_dir = get_sys_battery_dir();
  uint16_t count = 0;
  DIR* dir = opendir(batt_dir);
  if (!dir) {
    fprintf(stderr, "failed to open system battery dir: %s\n", batt_dir);
    return count;
  }

  struct dirent* ent = nullptr;
  while ((ent = readdir(dir)) != nullptr) {
    if (strncmp(ent->d_name, "BAT", 3) == 0)
      count++;
  }
  closedir(dir);
  return count;
}

static constexpr const size_t kBufferMaxLength = 8192;
static inline bool read_file_str(Battery* batt, const char* filename, char** result, size_t* num_read) {
  ASSERT(batt);

  char path[PATH_MAX];
  snprintf(path, PATH_MAX, "%s/%s", batt->path, filename);
  FILE* file = fopen(path, "r");
  if (!file) {
    fprintf(stderr, "failed to open: %s\n", path);
    goto failed_to_open;
  }

  char data[kBufferMaxLength];
  memset(data, 0, sizeof(data));
  size_t nread = fread(data, sizeof(char), kBufferMaxLength, file);
  if (nread <= 0) {
    fprintf(stderr, "failed to read battery file\n");
    goto finished_reading;
  }

  (*result) = strdup(data);
  (*num_read) = nread;
finished_reading:
  fclose(file);
failed_to_open:
  return nread > 0;
}

#define DEFINE_READ_BATTERY_FILE_TYPE(Name, Type, ParseFunc)                               \
  static inline bool read_file_##Name(Battery* batt, const char* filename, Type* result) { \
    ASSERT(batt);                                                                          \
    char path[PATH_MAX];                                                                   \
    snprintf(path, PATH_MAX, "%s/%s", batt->path, filename);                               \
    FILE* file = fopen(path, "r");                                                         \
    if (!file) {                                                                           \
      fprintf(stderr, "failed to open: %s\n", path);                                       \
      goto failed_to_open;                                                                 \
    }                                                                                      \
    char data[kBufferMaxLength];                                                           \
    memset(data, 0, sizeof(data));                                                         \
    size_t nread = fread(data, sizeof(char), kBufferMaxLength, file);                      \
    if (nread <= 0) {                                                                      \
      fprintf(stderr, "failed to read battery file\n");                                    \
      goto finished_reading;                                                               \
    }                                                                                      \
    (*result) = ParseFunc(data);                                                           \
  finished_reading:                                                                        \
    fclose(file);                                                                          \
  failed_to_open:                                                                          \
    return nread > 0;                                                                      \
  }

DEFINE_READ_BATTERY_FILE_TYPE(uint32, uint32_t, atoi);
DEFINE_READ_BATTERY_FILE_TYPE(uint64, uint64_t, atoll);
DEFINE_READ_BATTERY_FILE_TYPE(double, double, atof);

#define DEFINE_READ_BATTERY_TYPE(Battery, Type, Name)    \
  if (!read_file_##Type(Battery, #Name, &Battery->Name)) \
    fprintf(stderr, "failed to read battery %s\n", #Name);

// clang-format off
#define read_battery_uint32(Battery, Name)          \
  DEFINE_READ_BATTERY_TYPE(Battery, uint32, Name)
// clang-format on

// clang-format off
#define read_battery_uint64(Battery, Name)          \
  DEFINE_READ_BATTERY_TYPE(Battery, uint64, Name)
// clang-format on

#define read_battery_str(Battery, Name)                                   \
  size_t Name##_length = 0;                                               \
  if (!read_file_str((Battery), #Name, &(Battery)->Name, &Name##_length)) \
    fprintf(stderr, "failed to read battery %s\n", #Name);

void batt_init(Battery* batt, const uint16_t index) {
  batt->index = index;
  char* sys_battery_dir = get_sys_battery_dir();
  snprintf(batt->path, PATH_MAX, "%s/BAT%d", sys_battery_dir, index);

  read_battery_str(batt, type);
  read_battery_str(batt, status);
  read_battery_str(batt, health);
  read_battery_str(batt, manufacturer);
  read_battery_str(batt, model_name);
  read_battery_str(batt, serial_number);
  read_battery_str(batt, technology);
  read_battery_uint64(batt, temp);
  read_battery_uint64(batt, voltage_now);
  read_battery_uint64(batt, alarm);
  read_battery_uint64(batt, capacity);
  read_battery_uint64(batt, charge_full);
  read_battery_uint64(batt, charge_now);
  read_battery_uint64(batt, current_now);
  read_battery_uint64(batt, cycle_count);
  read_battery_uint64(batt, manufacture_day);
  read_battery_uint64(batt, manufacture_month);
}

void batt_free(Battery* batt) {
  if (!batt)
    return;
  if (batt->status)
    free(batt->status);
  if (batt->type)
    free(batt->type);
  if (batt->health)
    free(batt->health);
  if (batt->manufacturer)
    free(batt->manufacturer);
  if (batt->model_name)
    free(batt->model_name);
  if (batt->serial_number)
    free(batt->serial_number);
  if (batt->technology)
    free(batt->technology);
}
