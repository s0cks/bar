typedef struct _Label Label;
Label* mbar_create_label(BarApp* app, const char* text);
void mbarL_push_new_label(BarApp* app, const char* text);
void mbar_free_label(Label* value);
