#ifndef MBAR_LABEL_H
#define MBAR_LABEL_H

#include "moonbar.h"
#include "widget.h"

#define FOR_EACH_LABEL_SIGNAL(V) \
  FOR_EACH_WIDGET_SIGNAL(V)

struct _Label {
  MOONBAR_WIDGET_FIELDS;
};

#endif // MBAR_LABEL_H
