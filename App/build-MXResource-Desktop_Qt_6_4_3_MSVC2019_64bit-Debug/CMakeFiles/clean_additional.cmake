# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\appresourceEditor_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appresourceEditor_autogen.dir\\ParseCache.txt"
  "appresourceEditor_autogen"
  )
endif()
