typedef struct _Box Box;
Box* mbar_create_box(BarApp* app, const int orientation);
void mbarL_push_box(BarApp* app, const int orientation);
void mbarL_push_boxi(BarApp* app, const int index);
void mbar_free_box(Box* value);

MBAR_INLINE void 
mbarL_push_hbox(BarApp* app) {
  ASSERT(app);
  mbarL_push_box(app, GTK_ORIENTATION_HORIZONTAL);
}

MBAR_INLINE void
mbarL_push_vbox(BarApp* app) {
  ASSERT(app);
  mbarL_push_box(app, GTK_ORIENTATION_VERTICAL);
}
