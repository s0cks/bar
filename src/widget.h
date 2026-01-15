#ifndef MOONBAR_WIDGET_H
#define MOONBAR_WIDGET_H

#define MOONBAR_WIDGET_FIELDS \
  GtkWidget* handle;          \
  EventRoute* events;         \
  BarApp* owner;

#define FOR_EACH_WIDGET_SIGNAL(V) \
  V(map) \
  V(unmap)

static inline GtkWidget**
mbar_widget_get_handle_ptr(const void* widget) {
  ASSERT(widget);
  return (GtkWidget**)widget;
}

static inline GtkWidget*
mbar_widget_get_handle(const void* widget) {
  return *(mbar_widget_get_handle_ptr(widget));
}

static inline EventRoute**
mbar_widget_get_events_ptr(const void* widget) {
  return (EventRoute**)(widget + sizeof(GtkWidget*));
}

static inline EventRoute*
mbar_widget_get_events(const void* widget) {
  return *(mbar_widget_get_events_ptr(widget));
}

static inline BarApp**
mbar_widget_get_owner_ptr(const void* widget) {
  return (BarApp**)(widget + sizeof(GtkWidget*) + sizeof(EventRoute*));
}

static inline BarApp*
mbar_widget_get_owner(const void* widget) {
  return *(mbar_widget_get_owner_ptr(widget));
}

static inline void
mbar_widget_onl(const void* widget, const char* event, lua_State* L, const int index) {
  ASSERT(widget);
  ASSERT(L);
  if(!lua_isfunction(L, index)) {
    // TODO(@s0cks): fix error reporting
    luaL_error(L, "expected argument to be a function");
    return;
  }
  event_route_insertl(mbar_widget_get_events(widget), event, L, index);
}

static inline void
mbar_widget_publish(void* widget, const char* event) {
  ASSERT(widget);
  ASSERT(event);
  EventRoute* root = event_route_search(mbar_widget_get_events(widget), event);
  if(!root)
    return;
#define L mbar_widget_get_owner(widget)->L
  event_route_call(L, root);
#undef L
}

#endif // MOONBAR_WIDGET_H
