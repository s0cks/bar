#include "tray.h"

#include <gtk/gtk.h>

static inline GtkWidget* create_tray() {
  fprintf(stdout, "creating tray widget\n");
  GtkWidget* tray = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
  if (!tray) {
    fprintf(stderr, "failed to create tray widget\n");
    return tray;
  }
  gtk_widget_add_css_class(tray, "left");
  gtk_widget_set_halign(tray, GTK_ALIGN_START);
  gtk_widget_set_valign(tray, GTK_ALIGN_CENTER);

  fprintf(stdout, "creating gtk image from google-chrome icon\n");
  GtkWidget* icon = gtk_image_new_from_icon_name("google-chrome");
  if (!icon) {
    fprintf(stderr, "failed to create icon image\n");
    return nullptr;
  }
  fprintf(stdout, "appending icon to tray box\n");
  gtk_box_append(GTK_BOX(tray), icon);

  return tray;
}

void tray_init(Tray* tray) {
  if (!tray)
    return;
  tray->box = create_tray();
  if (!tray->box) {
    fprintf(stderr, "failed to create tray box\n");
    return;
  }
}

void tray_free(Tray* tray) {
  if (!tray)
    return;
  if (tray->box)
    g_object_unref(tray->box);
}
