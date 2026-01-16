#ifndef MOONBAR_HYPR_CLIENT_H
#define MOONBAR_HYPR_CLIENT_H

#include <linux/limits.h>
#include "moonbar.h"
#include "log.h"

struct _HyprClient {
  BarApp* owner;
  char instance_path[PATH_MAX];
  uv_pipe_t cmd_pipe;
  uv_pipe_t event_pipe;
};

void mbar_hypr_init(HyprClient* client, BarApp* app);
void mbar_hypr_close(HyprClient* client);

static inline HyprClient*
mbar_hypr_new(BarApp* owner) {
  if(!owner) {
    DLOG("cannot create HyprClient w/ NULL owner");
    return NULL;
  }
  HyprClient* hypr = (HyprClient*)malloc(sizeof(HyprClient));
  if(!hypr) {
    fprintf(stderr, "failed to allocate memory for HyprClient\n");
    return NULL;
  }
  mbar_hypr_init(hypr, owner);
  return hypr;
}

static inline void
mbar_hypr_free(HyprClient* hypr) {
  if(!hypr)
    return;
  free(hypr);
}

#endif // MOONBAR_HYPR_CLIENT_H
