#ifndef MBAR_LSTATE_H
#define MBAR_LSTATE_H

#include "app.h"
#include "moonbar.h"

#define LUA_GLOBAL_MBAR_STATE "mbar_state"

void mbarL_init(BarApp* app);
void mbarL_doinit(BarApp* app);
void mbarL_close(BarApp* app);
void mbarL_init_config_ref(BarApp* app);
void mbarL_call_config_init(BarApp* app);

static inline void mbarL_push_config_ref(BarApp* app) {
  ASSERT(app);
  ASSERT(app->config_ref != LUA_NOREF);
#define L app->L
  lua_rawgeti(L, LUA_REGISTRYINDEX, app->config_ref);
#undef L
}

void mbarL_init_api(lua_State* L);

#define DECLARE_INITMETATABLE(Name) void mbarL_initmetatable_##Name(lua_State* L);
DECLARE_INITMETATABLE(widget);
DECLARE_INITMETATABLE(label);
DECLARE_INITMETATABLE(button);
DECLARE_INITMETATABLE(event_route);
DECLARE_INITMETATABLE(box);
#undef DECLARE_INITMETATABLE

#define DECLARE_INITLIB(Name) void mbarL_initlib_##Name(lua_State* L);
DECLARE_INITLIB(label);
DECLARE_INITLIB(button);
DECLARE_INITLIB(event_route);
DECLARE_INITLIB(box);
#undef DECLARE_INITLIB

static inline void mbarL_hello_world(BarApp* app) {
  static const char* kHelloWorld = "print('Hello World')";
  mbarL_dostring(app, kHelloWorld);
}

#endif  // MBAR_LSTATE_H
