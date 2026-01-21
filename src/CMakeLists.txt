file(GLOB MBAR_SOURCES
  "${CMAKE_CURRENT_SOURCE_DIR}/*.c")

add_library(${PROJECT_NAME}-core SHARED ${MBAR_SOURCES})
target_include_directories(${PROJECT_NAME}-core
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
 target_link_libraries(${PROJECT_NAME}-core
  PUBLIC ${PROJECT_NAME}::api
         ${PROJECT_NAME}::hypr)
target_enable_iwyu(${PROJECT_NAME}-core ${MOONBAR_IWYU_MAPPINGS})

add_library(${PROJECT_NAME}::core ALIAS ${PROJECT_NAME}-core)
