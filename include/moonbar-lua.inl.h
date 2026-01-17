#define DECLARE_LUA_F(Name) \
  MBAR_INLINE int Name(lua_State* L);

#define DEFINE_LUA_F(Name) \
  MBAR_INLINE int Name(lua_State* L)

BarApp* mbarL_get_mbar_app(lua_State* L);
void mbarL_dostring(BarApp* app, const char* code);
void mbarL_dofile(BarApp* app, const char* filename);

#define FOR_EACH_LUA_TYPE(V)          \
  V(box, Box)                         \
  V(label, Label)                     \
  V(button, Button)                   \
  V(event_route, EventRoute)

#define DECLARE_LUA_TYPE(Name, Type)                      \
  static const char* k##Type##MetatableName = #Type;      \
  void mbarL_initmetatable_##Name(lua_State* L);          \
  void mbarL_initlib_##Name(lua_State* L);                \

#define DECLARE_LUA_TYPE_STACK_OPS(Name, Type)            \
  void mbarL_push##Name(lua_State* L, Type* value);       \
  MBAR_INLINE void                                        \
  mbarL_push##Name##x(BarApp* app, Type* value) {         \
    return mbarL_push##Name(app->L, value);               \
  }                                                       \
  Type* mbarL_to##Name(lua_State* L, const int index);    \
  MBAR_INLINE Type*                                       \
  mbarL_to##Name##x(BarApp* app, const int index) {       \
    return mbarL_to##Name(app->L, index);                 \
  }

DECLARE_LUA_TYPE(widget, Widget)
FOR_EACH_LUA_TYPE(DECLARE_LUA_TYPE)
FOR_EACH_LUA_TYPE(DECLARE_LUA_TYPE_STACK_OPS)
#undef DECLARE_LUA_TYPE
#undef DECLARE_LUA_TYPE_STACK_OPS

#define DEFINE_LUA_TYPE_LIB(Name, Type)   \
  DECLARE_LUA_F(new_##Name);              \
  DECLARE_LUA_LIB(Type) {                 \
    { "new", new_##Name },                \
    { NULL, NULL },                       \
  };                                      \
  DEFINE_LUA_INITLIB(Name);

#define DEFINE_LUA_TYPE_INIT_F(Name) \
  DEFINE_LUA_F(new_##Name)
