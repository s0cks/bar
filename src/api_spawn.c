#include "moonbar.h"
#include "state_lua.h"
#include "app.h"
#include "state_gtk.h"
#include "uv_gsource.h"
#include "util.h"
#include "log.h"
#include "hypr_client.h"
#include "api.h"

int mbarL_api_spawn(lua_State* L) {
  ASSERT(L);
  const int num_args = lua_gettop(L) - 1;
  mbarL_check_global_app(L, app);
  int argc = 0;
  char** argv = NULL;
  if(lua_isstring(L, 1)) {
    argc = 1;
    argv = (char**)malloc(sizeof(char*) * (argc + 1));
    argv[0] = strdup(lua_tostring(L, 1));
    argv[1] = NULL;
  } else if(lua_istable(L, 1)) {
    argc = lua_objlen(L, 1);
    argv = (char**)malloc(sizeof(char*) * (argc + 1));
    for(int i = 0; i < argc; i++) {
      lua_rawgeti(L, 1, i + 1);
      luaL_checkstring(L, -1);
      argv[i] = strdup(lua_tostring(L, -1));
    }
    argv[argc + 1] = NULL;
  } else {
    luaL_error(L, "invalid value for argument 1");
    return 0;
  }

  ASSERT(argv != NULL);
  ASSERT(argc > 0);
  Process* proc = mbar_proc_new(app, argv, argc);
  if(!proc) {
    luaL_error(L, "failed to spawn new process");
    return 0;
  }

  // on_success
  if(num_args >= 2)
    mbar_proc_set_on_success(proc, L, 2);

  // on_failure
  if(num_args >= 3)
    mbar_proc_set_on_failure(proc, L, 3);

  // on_finished
  if(num_args >= 4)
    mbar_proc_set_on_finished(proc, L, 4);

  mbar_proc_spawn(proc);
  return 0;
}
