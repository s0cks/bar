#ifndef BAR_UTIL_H
#define BAR_UTIL_H

#include <unistd.h>

bool file_exists(const char* filename);
char* bar_get_config_dir();
char* bar_get_cwd();

#endif // BAR_UTIL_H
