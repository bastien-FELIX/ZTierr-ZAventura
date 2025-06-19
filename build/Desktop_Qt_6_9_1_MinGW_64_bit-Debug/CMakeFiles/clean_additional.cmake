# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Zerra_Zaventura_Zeditor_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Zerra_Zaventura_Zeditor_autogen.dir\\ParseCache.txt"
  "Zerra_Zaventura_Zeditor_autogen"
  )
endif()
