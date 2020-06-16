###############################################################################
#
# Description       : CMake build script for libSBML dependencies
# Original author(s): Frank Bergmann <fbergman@caltech.edu>
# Organization      : California Institute of Technology
#
# This file is part of libSBML.  Please visit http://sbml.org for more
# information about SBML, and the latest version of libSBML.
#
# Copyright 2005-2011 California Institute of Technology.
# Copyright 2002-2005 California Institute of Technology and
#                     Japan Science and Technology Corporation.
# 
# This library is free software; you can redistribute it and/or modify it
# under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation.  A copy of the license agreement is provided
# in the file named "LICENSE.txt" included with this software distribution
# and also available online as http://sbml.org/software/libsbml/license.html
#
###############################################################################
cmake_minimum_required(VERSION 3.15)
project(libsbml_dependencies)

include(CMakeTestCCompiler)
include(CheckCSourceCompiles)
include(CheckCXXSourceCompiles)
include(CheckStructHasMember)
include(CheckLibraryExists)
include(CheckFunctionExists)
include(CheckCCompilerFlag)
include(CheckCSourceRuns)
include(CheckSymbolExists)
include(CheckTypeSize)


###############################################################################
#
# Parse VERSION.txt to determine the package version
#
SET(DEPENDENCIES_VERSION_MAJOR)
SET(DEPENDENCIES_VERSION_MINOR)
SET(DEPENDENCIES_VERSION_PATCH)
SET(DEPENDENCIES_VERSION_RELEASE)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION.txt")

    file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/VERSION.txt" VersionString NEWLINE_CONSUME)
    string(STRIP "${VersionString}" VersionString)
    string(REPLACE "." ";" VersionString "${VersionString}")
    string(REPLACE "-" ";" VersionString "${VersionString}")
    list(LENGTH VersionString versionLength)
    list(GET VersionString 0 DEPENDENCIES_VERSION_MAJOR)
    list(GET VersionString 1 DEPENDENCIES_VERSION_MINOR)
    list(GET VersionString 2 DEPENDENCIES_VERSION_PATCH)

    if (${versionLength} GREATER 3)
        list(GET VersionString 3 DEPENDENCIES_VERSION_RELEASE)
    endif ()

endif ()

SET(PACKAGE_VERSION "${DEPENDENCIES_VERSION_MAJOR}.${DEPENDENCIES_VERSION_MINOR}.${DEPENDENCIES_VERSION_PATCH}-${DEPENDENCIES_VERSION_RELEASE}")

###############################################################################
#
# the next lines configure the parameters for packaging the binaries
# they can be invoked with: make package / nmake package or by using 
# cpack -G zip|deb|rpm|dmg|nsis
#

INCLUDE(InstallRequiredSystemLibraries)

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Dependencies for libsbml (bz2, check, expat, iconv, libxml2, xerces-c, zlib")
SET(CPACK_PACKAGE_NAME "libSBML Dependencies")
SET(CPACK_PACKAGE_VENDOR "The SBML Team")
SET(CPACK_PACKAGE_CONTACT "LibSBML Team <libsbml-team@caltech.edu>")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING.txt")

# version for this dependencies release
SET(CPACK_PACKAGE_VERSION_MAJOR "${DEPENDENCIES_VERSION_MAJOR}")
SET(CPACK_PACKAGE_VERSION_MINOR "${DEPENDENCIES_VERSION_MINOR}")
SET(CPACK_PACKAGE_VERSION_PATCH "${DEPENDENCIES_VERSION_PATCH}")
SET(CPACK_PACKAGE_VERSION "${PACKAGE_VERSION}")

INCLUDE(CPack)


###############################################################################
#
# Here we have the main configuration options for libsbml
#

# build static / shared library
option(BUILD_SHARED_LIBS "Build shared library (Set to OFF to build static libraries)" OFF)

# choose the xml parsing library to be used
option(WITH_BZIP2 "Compile BZ2 compression library" ON)
option(WITH_CHECK "Compile libcheck unit test library" OFF)
option(WITH_EXPAT "Compile Expat XML parser" ON)
option(WITH_ZLIB "Compile zlib compression library" ON)

if (WITH_BZIP2)
    add_subdirectory(bzip2)
endif ()

if (WITH_CHECK)
    add_subdirectory(check)
endif ()

if (WITH_EXPAT)
    add_subdirectory(expat)
endif ()

OPTION(FORCE_BUILD_ICONV "Force the building of libiconv on all systems" OFF)
if (FORCE_BUILD_ICONV)
    set(WITH_ICONV ON)
    add_subdirectory(libiconv)
endif ()

OPTION(FORCE_BUILD_LIBXML "Force the building of libiconv on all systems" OFF)
    set(WITH_LIBXML ON)
    add_subdirectory(libxml2)
if (FORCE_BUILD_LIBXML)
endif ()


MESSAGE(STATUS "WITH_LIBXML ${WITH_LIBXML}")
if (WIN32)
    option(WITH_XERCES "Compile xerces XML parser" ON)
    option(WITH_ICONV "Compile libiconv" ON)
    option(WITH_LIBXML "Compile libxml XML parser" ON)

    if (WITH_ICONV)
        add_subdirectory(libiconv)
    endif ()

    if (WITH_LIBXML)
        add_subdirectory(libxml2)
    endif ()

    if (WITH_XERCES)
        add_subdirectory(xerces-c)
    endif ()
endif ()

if (WITH_ZLIB)
    add_subdirectory(zlib)
endif ()


###############################################################################
# misc variables
#

if (UNIX)
    set(PATH_SEP "/")
    set(FILE_SEP ":")
else ()
    set(PATH_SEP "\\")
    set(FILE_SEP ";")
endif ()

###############################################################################
#
# Set up remaining variables, add option for universal binaries
#
set(BUILD_DEFINITIONS)
if (UNIX)
    if (APPLE)
        add_definitions(-DMACOSX)
        set(BUILD_DEFINITIONS "${BUILD_DEFINITIONS} -DMACOSX")

        # On OSX it is common to build universal binaries to support multiple
        # processor architectures. The default behavior is not to build
        # multiple architectures, as most users might not need that.
        option(ENABLE_UNIVERSAL "Create Universal Binaries" OFF)

        set(CMAKE_OSX_ARCHITECTURES "${CMAKE_OSX_ARCHITECTURES}" CACHE STRING "A semicolon separated list of build architectures to be used")
        if (ENABLE_UNIVERSAL)
            # if universal binaries are requested and none defined so far
            # overwrite them with all three common architectures. If the user
            # specified their own list of architectures do not touch!
            if (CMAKE_OSX_ARCHITECTURES STREQUAL "")
                set(CMAKE_OSX_ARCHITECTURES "i386;ppc;x86_64" CACHE STRING "A semicolon separated list of build architectures to be used" FORCE)
            endif ()
        endif (ENABLE_UNIVERSAL)
    else (APPLE)
        add_definitions(-DLINUX)

        if (NOT CYGWIN)
            # on cygwin all code is position independent so -fPIC is not needed
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-strict-aliasing -fPIC")
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-strict-aliasing -fPIC")
        endif ()

        set(BUILD_DEFINITIONS "${BUILD_DEFINITIONS} -DLINUX")
    endif (APPLE)

    add_definitions(-DPACKAGE_VERSION=\"${PACKAGE_VERSION}\" -DPACKAGE_NAME=\"${PROJECT_NAME}\")
    set(BUILD_DEFINITIONS "${BUILD_DEFINITIONS} -DPACKAGE_VERSION=\"${PACKAGE_VERSION}\"  -DPACKAGE_NAME=\"${PROJECT_NAME}\"")

else (UNIX)
    add_definitions(-DWIN32 -DLIBSBML_EXPORTS -DLIBLAX_EXPORTS)
    set(BUILD_DEFINITIONS "${BUILD_DEFINITIONS} -DWIN32 -DLIBSBML_EXPORTS -DLIBLAX_EXPORTS")
    if (MSVC)
        add_definitions(-D_CRT_SECURE_NO_WARNINGS -D_CRT_NONSTDC_NO_DEPRECATE)
        set(BUILD_DEFINITIONS "${BUILD_DEFINITIONS} -D_CRT_SECURE_NO_WARNINGS")
        option(WITH_STATIC_RUNTIME "Compile using the static MSVC Runtime" OFF)
        if (WITH_STATIC_RUNTIME)
            foreach (flag_var
                    CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
                    CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
                    CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
                    CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)

                if (${flag_var} MATCHES "/MD")
                    string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
                endif (${flag_var} MATCHES "/MD")


            endforeach (flag_var)
            add_definitions(-D_MT)
        endif (WITH_STATIC_RUNTIME)


        # CMake no longer creates PDB files for static libraries after 2.8.11
        # so we store debug information in the object files instead
        if (${CMAKE_VERSION} VERSION_GREATER "2.8.11")
            foreach (flag_var
                    CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
                    CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO
                    CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE
                    CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)

                if (${flag_var} MATCHES "/Zi")
                    STRING(REPLACE "/Zi" "/Z7" "${flag_var}" "${${flag_var}}")
                endif (${flag_var} MATCHES "/Zi")

            endforeach (flag_var)
        endif ()

        file(GLOB WIN32_BINARIES ${CMAKE_SOURCE_DIR}/dependencies/bin/*.dll)
        INSTALL(FILES ${WIN32_BINARIES} DESTINATION bin)

    elseif (CYGWIN)
        add_definitions(-DCYGWIN)
        set(BUILD_DEFINITIONS "${BUILD_DEFINITIONS} -DCYGWIN")
    elseif (MINGW)
        if (WITH_LIBXML)
            # this is necessary to build with libxml2 on mingw
            add_definitions(-DLIBXML_STATIC)
        endif (WITH_LIBXML)
    endif (MSVC)

endif (UNIX)

###############################################################################
#
# Disable in-source build
#

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "In-source builds have been disabled. Please create a separate build directory.")
endif ()


if (CMAKE_BUILD_TYPE STREQUAL "")
    # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This screws up
    # differentiation between debug and release builds.
    set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()

if (NOT UNIX)
    # Create debug libraries with _d postfix
    set(CMAKE_DEBUG_POSTFIX "_d")
endif ()


if (APPLE)
    if (CMAKE_OSX_ARCHITECTURES STREQUAL "")
        message(STATUS "  Building universal binaries               = no (using native arch)")
    else ()
        list(REMOVE_DUPLICATES CMAKE_OSX_ARCHITECTURES)
        list(REMOVE_ITEM CMAKE_OSX_ARCHITECTURES "")
        list(SORT CMAKE_OSX_ARCHITECTURES)
        list(LENGTH CMAKE_OSX_ARCHITECTURES NUM_ARCHS)
        if (NUMARCHS EQUAL 1)
            message(STATUS "  Building universal binaries               = no (using ${CMAKE_OSX_ARCHITECTURES})")
        else ()
            message(STATUS "  Building universal binaries               = yes (using ${CMAKE_OSX_ARCHITECTURES})")
        endif ()
    endif ()
endif ()
