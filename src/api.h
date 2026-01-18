#ifndef MOONBAR_API_H
#define MOONBAR_API_H

#include "moonbar.h"

int mbarL_api_spawn(lua_State* L);
int mbarL_api_read_lines(lua_State* L);
int mbarL_api_watch(lua_State* L);

#endif // MOONBAR_API_H
