#include "moonbar.h"
#include "widget.h"

#define BUTTON_USERDATA(Name, Index)                    \
  Button* Name = (Button*)lua_touserdata(L, (Index));   \
  if((Name) == NULL)                                    \
    INVALID_BUTTON_USERDATA;

DEFINE_LUA_F(widget_on) {
  const void* data = lua_touserdata(L, 1);
  if(!data) {
    luaL_error(L, "invalid widget for param 1");
    return 0;
  }
  const char* event = lua_tostring(L, 2);
  mbar_widget_onl(data, event, L, 3);
  return 0;
}

static const luaL_Reg kWidgetFuncs[] = {
  { "on", widget_on },
  { NULL, NULL },
};

void mbarL_initmetatable_widget(lua_State* L) {
  luaL_newmetatable(L, kWidgetMetatableName);
  luaL_setfuncs(L, kWidgetFuncs, 0);
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "__index");
}
