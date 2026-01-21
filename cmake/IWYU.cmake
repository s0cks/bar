find_program(IWYU "include-what-you-use" REQUIRED)

message(STATUS "found include-what-you-use: ${IWYU}")
set(IWYU_DEFAULT_OPTS "-Xiwyu")
message(STATUS "default include-what-you-use opts: ${IWYU_DEFAULT_OPTS}")

macro(target_enable_iwyu target_name mappings_file)
  set(${target_name}_IWYU_OPTS "${IWYU_DEFAULT_OPTS} --mapping_file=${mappings_file}")
  message(STATUS "${target_name} include-what-you-use opts: ${${target_name}_IWYU_OPTS}")
  set_property(
    TARGET ${target_name} 
    PROPERTY 
      CXX_INCLUDE_WHAT_YOU_USE "${IWYU};;${${target_name}_IWYU_OPTS}")
endmacro()
