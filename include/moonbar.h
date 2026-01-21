#ifndef MOONBAR_H
#define MOONBAR_H

#include <gtk/gtk.h>
#include <gtk4-layer-shell.h>
#include <lauxlib.h>
#include <lua.h>
#include <luajit.h>
#include <lualib.h>
#include <uv.h>

#ifndef NOT_IMPLEMENTED

// clang-format off
#define NOT_IMPLEMENTED ({                                            \
  fprintf(stdout, "%s is not implemented\n", __PRETTY_FUNCTION__);    \
})
// clang-format on

#endif  // NOT_IMPLEMENTED

#ifdef MBAR_DEBUG

#include <assert.h>

#define ASSERT(x) assert((x))

#else

#define ASSERT(x)

#endif  // MBAR_DEBUG

// clang-format off
#define MBAR_VERSION_MAJOR @PROJECT_VERSION_MAJOR@
#define MBAR_VERSION_MINOR @PROJECT_VERSION_MINOR@
#define MBAR_VERSION_PATCH @PROJECT_VERSION_PATCH@
// clang-format on

#ifndef UV_OK
#define UV_OK 0
#endif

#define MBAR_INLINE static inline

typedef struct _HyprClient HyprClient;
typedef struct _EventRoute EventRoute;

char* mbar_get_version();
// IWYU pragma: begin_exports
#include "moonbar-app.inl.h"
#include "moonbar-box.inl.h"
#include "moonbar-buffer.inl.h"
#include "moonbar-button.inl.h"
#include "moonbar-callback.inl.h"
#include "moonbar-config.inl.h"
#include "moonbar-events.inl.h"
#include "moonbar-label.inl.h"
#include "moonbar-lua.inl.h"
#include "moonbar-process.inl.h"

#ifdef MBAR_DEBUG

#include "moonbar-debug.inl.h"

#endif  // MBAR_DEBUG
// IWYU pragma: end_exports

#endif  // MOONBAR_H
