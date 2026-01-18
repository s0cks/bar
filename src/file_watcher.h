#ifndef MOONBAR_FILE_WATCHER_H
#define MOONBAR_FILE_WATCHER_H

typedef struct _FileWatcher {
  BarApp* owner;
  uv_fs_event_t handle;
  char* filename;
  int callback;
} FileWatcher;

void mbar_file_watcher_init(BarApp* app, FileWatcher* ctx, const char* filename, const int index);
void mbar_file_watcher_start(FileWatcher* ctx);
void mbar_file_watcher_stop(FileWatcher* ctx);
void mbar_file_watcher_free(FileWatcher* app);

static inline bool
mbar_file_watcher_is_running(FileWatcher* ctx) {
  return ctx
      && uv_is_active((uv_handle_t*)&ctx->handle);
}

#endif // MOONBAR_FILE_WATCHER_H
