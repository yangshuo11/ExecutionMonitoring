#----------------------------------------------------------------
# Generated CMake target import file for configuration "".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "despot" for configuration ""
set_property(TARGET despot APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(despot PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libdespot.so"
  IMPORTED_SONAME_NOCONFIG "libdespot.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS despot )
list(APPEND _IMPORT_CHECK_FILES_FOR_despot "${_IMPORT_PREFIX}/lib/libdespot.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
