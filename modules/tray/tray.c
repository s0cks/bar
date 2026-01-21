#include "tray.h"

extern int luaopen_moonbar_tray(lua_State* L) {
  fprintf(stdout, "opening tray lib...\n");
  return 0;
}
