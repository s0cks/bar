#include "moonbar.h"
#include "box.h"
#include "app.h"
#include "state_lua.h"

Box* mbar_create_box(BarApp* app, const int orientation) {
  ASSERT(app);
  fprintf(stdout, "creating box\n");
  GtkWidget* widget = gtk_box_new(orientation, 1);
  if(!widget) {
    mbar_error(app, "failed to create Box");
    return NULL;
  }
  Box* box = (Box*)malloc(sizeof(Box));
  box->owner = app;
  box->events = NULL;
  box->handle = widget;
  g_object_ref(box->handle);
  return box;
}

void mbar_free_box(Box* value) {
  if(!value)
    return;
  //TODO(@s0cks): implement
  free(value);
}
