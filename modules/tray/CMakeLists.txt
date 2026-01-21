set(LIB_NAME ${PROJECT_NAME}-tray)
file(GLOB TRAY_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

add_library(${LIB_NAME} SHARED
  tray.c)
set_target_properties(${LIB_NAME}
  PROPERTIES
    OUTPUT_NAME "tray"
    PREFIX "")
target_include_directories(${LIB_NAME}
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${LIB_NAME}
  PUBLIC ${PROJECT_NAME}::api)
