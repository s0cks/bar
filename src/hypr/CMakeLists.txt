file(GLOB HYPR_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

set(LIB_NAME ${PROJECT_NAME}-hypr)
add_library(${LIB_NAME} SHARED ${HYPR_SOURCES})
target_include_directories(${LIB_NAME}
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${LIB_NAME}
  PUBLIC PkgConfig::LuaJIT
         $<IF:$<TARGET_EXISTS:libuv::uv_a>,libuv::uv_a,libuv::uv>)
add_library(${PROJECT_NAME}::hypr ALIAS ${LIB_NAME})
