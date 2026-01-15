#ifndef MBAR_BUTTON_H
#define MBAR_BUTTON_H

#include "moonbar.h"
#include "widget.h"

#define FOR_EACH_BUTTON_SIGNAL(V) \
  FOR_EACH_WIDGET_SIGNAL(V)       \
  V(clicked)

struct _Button {
  MOONBAR_WIDGET_FIELDS;
};

#endif // MBAR_BUTTON_H
