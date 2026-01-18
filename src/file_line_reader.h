#ifndef MOONBAR_FILE_LINE_READER_H
#define MOONBAR_FILE_LINE_READER_H

#include "moonbar.h"

typedef struct _FileLineReader {
  BarApp* owner;
  uv_fs_t open_handle;
  uv_fs_t read_handle;
  uv_buf_t buf;
  char* remainder;
  size_t remainder_len;
  int on_next;
  int on_error;
  int on_finished;
} FileLineReader;

void line_reader_init(BarApp* owner, FileLineReader* ctx, const int on_next, const int on_err, const int on_finished);
void line_reader_read(FileLineReader* ctx, const char* filename);
void line_reader_free(FileLineReader* ctx);

#endif // MOONBAR_FILE_LINE_READER_H
