# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\apptimelineEditor_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\apptimelineEditor_autogen.dir\\ParseCache.txt"
  "apptimelineEditor_autogen"
  )
endif()
