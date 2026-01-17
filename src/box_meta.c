#include "moonbar.h"
#include "box.h"
#include "state_lua.h"

DEFINE_LUA_F(box_append) {
  fprintf(stdout, "appending\n");
  Box* box = (Box*)lua_touserdata(L, 1);
  if(box == NULL) {
    luaL_error(L, "invalid Box userdata");
    return 0;
  }
  fprintf(stdout, "adding userdata at 2 to box\n");
  const void* data = lua_touserdata(L, 2);
  if(!data) {
    luaL_error(L, "invalid widget for param 1");
    return 0;
  }
  fprintf(stdout, "appending widget to gtk box\n");
  GtkWidget* widget = mbar_widget_get_handle(data);
  gtk_box_append(GTK_BOX(box->handle), widget);
  return 1;
}

DEFINE_LUA_F(box_prepend) {
  Box* box = (Box*)lua_touserdata(L, 1);
  if(box == NULL) {
    luaL_error(L, "invalid Box userdata");
    return 0;
  }
  const void* data = lua_touserdata(L, 2);
  if(!data) {
    luaL_error(L, "invalid widget for param 1");
    return 0;
  }
  GtkWidget* widget = mbar_widget_get_handle(data);
  gtk_box_append(GTK_BOX(box->handle), widget);
  return 1;
}

DECLARE_LUA_METATABLE(Box) {
  { "append", box_append },
  { "prepend", box_prepend },
  { NULL, NULL },
};
DEFINE_LUA_INITWIDGETMETATABLE(box, Box);
