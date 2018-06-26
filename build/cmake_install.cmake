# Install script for directory: /home/xjmao/catkin_despot/src/despot

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libdespot.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libdespot.so")
    FILE(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libdespot.so"
         RPATH "")
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/xjmao/catkin_despot/src/despot/build/libdespot.so")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libdespot.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libdespot.so")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libdespot.so")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/despot" TYPE DIRECTORY FILES "/home/xjmao/catkin_despot/src/despot/include/despot/")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/despot/cmake/DespotTargets.cmake")
    FILE(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/despot/cmake/DespotTargets.cmake"
         "/home/xjmao/catkin_despot/src/despot/build/CMakeFiles/Export/lib/despot/cmake/DespotTargets.cmake")
    IF(EXPORT_FILE_CHANGED)
      FILE(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/despot/cmake/DespotTargets-*.cmake")
      IF(OLD_CONFIG_FILES)
        MESSAGE(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/despot/cmake/DespotTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        FILE(REMOVE ${OLD_CONFIG_FILES})
      ENDIF(OLD_CONFIG_FILES)
    ENDIF(EXPORT_FILE_CHANGED)
  ENDIF()
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/despot/cmake" TYPE FILE FILES "/home/xjmao/catkin_despot/src/despot/build/CMakeFiles/Export/lib/despot/cmake/DespotTargets.cmake")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/despot/cmake" TYPE FILE FILES "/home/xjmao/catkin_despot/src/despot/build/CMakeFiles/Export/lib/despot/cmake/DespotTargets-noconfig.cmake")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^()$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/despot/cmake" TYPE FILE FILES "/home/xjmao/catkin_despot/src/despot/build/DespotConfig.cmake")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/xjmao/catkin_despot/src/despot/build/examples/cpp_models/adventurer/cmake_install.cmake")
  INCLUDE("/home/xjmao/catkin_despot/src/despot/build/examples/cpp_models/bridge/cmake_install.cmake")
  INCLUDE("/home/xjmao/catkin_despot/src/despot/build/examples/cpp_models/chain/cmake_install.cmake")
  INCLUDE("/home/xjmao/catkin_despot/src/despot/build/examples/cpp_models/navigation/cmake_install.cmake")
  INCLUDE("/home/xjmao/catkin_despot/src/despot/build/examples/cpp_models/pocman/cmake_install.cmake")
  INCLUDE("/home/xjmao/catkin_despot/src/despot/build/examples/cpp_models/reg_demo/cmake_install.cmake")
  INCLUDE("/home/xjmao/catkin_despot/src/despot/build/examples/cpp_models/rock_sample/cmake_install.cmake")
  INCLUDE("/home/xjmao/catkin_despot/src/despot/build/examples/cpp_models/simple_rock_sample/cmake_install.cmake")
  INCLUDE("/home/xjmao/catkin_despot/src/despot/build/examples/cpp_models/tag/cmake_install.cmake")
  INCLUDE("/home/xjmao/catkin_despot/src/despot/build/examples/cpp_models/tiger/cmake_install.cmake")
  INCLUDE("/home/xjmao/catkin_despot/src/despot/build/examples/pomdpx_models/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/home/xjmao/catkin_despot/src/despot/build/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/home/xjmao/catkin_despot/src/despot/build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
