#ifndef MOONBAR_TRAY_H
#define MOONBAR_TRAY_H

#include "moonbar.h"

static const char* kTrayMetatableName = "Tray";
typedef struct _Tray {
  GtkWidget* box;
} Tray;

void tray_init(Tray* tray);
void tray_free(Tray* tray);
void trayL_initmetatable(lua_State* L);

static inline Tray* tray_new() {
  Tray* tray = (Tray*)malloc(sizeof(Tray));
  if (tray)
    tray_init(tray);
  return tray;
}

#endif  // MOONBAR_TRAY_H
