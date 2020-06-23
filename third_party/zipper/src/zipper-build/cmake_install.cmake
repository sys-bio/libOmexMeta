# Install script for directory: /cygdrive/d/libomexmeta/third_party/zipper

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/cygdrive/d/libomexmeta/third_party/zipper/src/zipper-build/libZipper-static.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/zipper" TYPE FILE FILES
    "/cygdrive/d/libomexmeta/third_party/zipper/minizip/crypt.h"
    "/cygdrive/d/libomexmeta/third_party/zipper/minizip/ioapi.h"
    "/cygdrive/d/libomexmeta/third_party/zipper/minizip/ioapi_buf.h"
    "/cygdrive/d/libomexmeta/third_party/zipper/minizip/ioapi_mem.h"
    "/cygdrive/d/libomexmeta/third_party/zipper/minizip/iowin32.h"
    "/cygdrive/d/libomexmeta/third_party/zipper/minizip/unzip.h"
    "/cygdrive/d/libomexmeta/third_party/zipper/minizip/zip.h"
    "/cygdrive/d/libomexmeta/third_party/zipper/zipper/CDirEntry.h"
    "/cygdrive/d/libomexmeta/third_party/zipper/zipper/defs.h"
    "/cygdrive/d/libomexmeta/third_party/zipper/zipper/tools.h"
    "/cygdrive/d/libomexmeta/third_party/zipper/zipper/unzipper.h"
    "/cygdrive/d/libomexmeta/third_party/zipper/zipper/zipper.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/cygdrive/d/libomexmeta/third_party/zipper/src/zipper-build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
