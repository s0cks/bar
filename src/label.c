#include "label.h"
#include "app.h"

Label* mbar_create_label(BarApp* app, const char* text) {
  GtkWidget* widget = gtk_label_new(text);
  if(!widget) {
    mbar_error(app, "failed to create Label");
    return NULL;
  }
  gtk_label_set_single_line_mode(GTK_LABEL(widget), TRUE);
  gtk_label_set_xalign(GTK_LABEL(widget), 0.5);
  gtk_label_set_yalign(GTK_LABEL(widget), 0.5);
  gtk_label_set_justify(GTK_LABEL(widget), GTK_JUSTIFY_CENTER);
  Label* label = (Label*)malloc(sizeof(Label));
  label->owner = app;
  label->events = NULL;
  label->handle = widget;
  g_object_ref(label->handle);
  return label;
}

void mbarL_push_new_label(BarApp* app, const char* text) {
  ASSERT(app);
  Label* label = mbar_create_label(app, text);
#define L app->L
  if(!label) {
    luaL_error(L, "failed to create Label");
    return;
  }
  mbarL_pushlabel(L, label);
#undef L
}

void mbar_free_label(Label* value) {
  if(!value)
    return;
  //TODO(@s0cks): should probably free callbacks in Label
  g_object_unref(value->handle);
  free(value);
}
