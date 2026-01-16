find_package(libuv CONFIG REQUIRED)

add_subdirectory(hypr/)

file(GLOB MBAR_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

add_library(${PROJECT_NAME}-core SHARED ${MBAR_SOURCES})
target_include_directories(${PROJECT_NAME}-core
  PUBLIC ${MBAR_INCLUDE_DIR}
         ${LuaJIT_INCLUDE_DIRS}
  PRIVATE
         ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME}-core
  PUBLIC PkgConfig::GTK 
         PkgConfig::GTK_LAYER_SHELL
         PkgConfig::LuaJIT
         $<IF:$<TARGET_EXISTS:libuv::uv_a>,libuv::uv_a,libuv::uv>
         ${PROJECT_NAME}::hypr)
add_library(${PROJECT_NAME}::core ALIAS ${PROJECT_NAME}-core)
