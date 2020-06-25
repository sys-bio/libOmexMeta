
#A note on the build system. Occasionally you will
#see "_CMakeLists.txt". This is an old version of the
#build system. This will be deleted in due course.

cmake_minimum_required(VERSION 3.15)


# Set version.
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_MICRO 8)

set(LIBOMEXMETA_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_MICRO})

# configure VERSION.txt for Python to read
configure_file("${CMAKE_SOURCE_DIR}/VERSION.in" "${CMAKE_SOURCE_DIR}/VERSION.txt")

project(libOmexMeta VERSION "${LIBOMEXMETA_VERSION}")

######################################################
# Load stuff

# load the ExternalProject functions for superbuild
include(ExternalProject)

# load a custom function for determining the current platform
include(${CMAKE_SOURCE_DIR}/cmake/DeterminePlatform.cmake)

# defines ${PLATFORM}
DeterminePlatform()

# defines a macro for locating the dependencies
include(${CMAKE_SOURCE_DIR}/cmake/FindDependencies.cmake)

# defines a macro that allows easily setting of platform dependent values for a variable
include(${CMAKE_SOURCE_DIR}/cmake/SetCrossPlatform.cmake)

# defines a macro that prints out configuration summary
include(${CMAKE_SOURCE_DIR}/cmake/ConfigurationSummary.cmake)

######################################################
#   Set some variables
#

# global settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CXX_STANDARD_REQUIRED ON)

# pic - needed on linux ignored on other platofrms
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# location of pyomexmeta development pacakge.
set(PYOMEXMETA_DIR "${CMAKE_SOURCE_DIR}/src/pyomexmeta")

# location of googletesting framework
set(GOOGLETEST_SOURCE ${CMAKE_SOURCE_DIR}/third_party/googletest)

# put all runtime targets (exe and dll) into bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

# put libraries into lib
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

# archives
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

# export all on windows. Ignored on other.
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)


####################################################################
# User options
#

# this is a CMake variable, so defining an option not needed
if (BUILD_SHARED_LIBS)
    add_definitions("-DBUILD_SHARED_LIBS=ON")
endif ()

option(DEBUG_DEPENDENCIES "Catch missing libraries by throwing error message if they do not exist" OFF)

option(BUILD_DOCS "Build libomexmeta documentation" ON)

# build tests?
SET(BUILD_TESTS OFF CACHE BOOL "build the tests")

# number processes
SET(N 8 CACHE STRING "number of cores to use for build. Passed onto -j for make")

# verbose
set(CMAKE_VERBOSE_MAKEFILE ON)

option(WITH_SANITIZER "link with address sanitizer for memory debugging" OFF)
if (WITH_SANITIZER)
    SET(ADDRESS_SANITIZER_FLAGS "-fsanitize=address")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${ADDRESS_SANITIZER_LINK_FLAGS}")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ADDRESS_SANITIZER_FLAGS}")
endif ()

option(WITH_BDB "build user suport for berkely database" ON)
if (${WITH_BDB})
    add_definitions(-DWITH_BDB)
endif ()
############################################################3
# configure some paths relative to vcpkg root
set(VCPKG_ROOT "D:/vcpkg" CACHE STRING "Absolute path to root vcpkg directory. On mine its D:\\vcpkg")
if (NOT EXISTS ${VCPKG_ROOT})
    message(FATAL_ERROR "vcpkg root not found (${VCPKG_ROOT}). Remember to \
add /mnt/<driveletter> on wsl (like \"/mnt/d/vcpkg\")")
endif ()

set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Path to vcpkg toolchain file")

# ensure the toolchain file exists and user has provided it.
if (NOT EXISTS ${CMAKE_TOOLCHAIN_FILE})
    message(FATAL_ERROR "No vcpkg toolchain installed, got \"${CMAKE_TOOLCHAIN_FILE}\".
Have you passed in the root to vcpkg? i.e. -DVCPKG_ROOT=\"D:/vcpkg\"")
endif ()

# determine which triplet we need to use for finding shared libraries and include dirs.
SetCrossPlatform(VCPKG_ARCH "x64-windows" "x64-linux" "x64-osx")

# location of installed libraries in vcpkg
set(VCPKG_X64_INSTALLED_PACKAGES "${VCPKG_ROOT}/installed/${VCPKG_ARCH}")

# location of installed static packages in vcpkg
SetCrossPlatform(VCPKG_X64_STATIC_INSTALLED_PACKAGES
        "${VCPKG_ROOT}/installed/x64-windows-static"
        "${VCPKG_ROOT}/installed/x64-linux" # note: on linux, this is same for shared and static
        "${VCPKG_ROOT}/installed/x64-osx"
        )

# Path to static libraries
set(VCPKG_X64_STATIC_LIB_DIR "${VCPKG_X64_STATIC_INSTALLED_PACKAGES}/lib")
# Path to shared libraries
set(VCPKG_X64_LIB_DIR "${VCPKG_X64_INSTALLED_PACKAGES}/lib")
# Path to binaries
SetCrossPlatform(VCPKG_X64_BIN_DIR
        "${VCPKG_X64_INSTALLED_PACKAGES}/bin" # windows
        "${VCPKG_X64_INSTALLED_PACKAGES}/lib" # linux
        "${VCPKG_X64_INSTALLED_PACKAGES}/lib" # mac
        )
# include directories (should be the same for static and dynamic)
set(VCPKG_X64_INCLUDE_DIR "${VCPKG_X64_INSTALLED_PACKAGES}/include")


set(_VCPKG_DIRECTORIES
        ${VCPKG_X64_STATIC_LIB_DIR}
        ${VCPKG_X64_LIB_DIR}
        ${VCPKG_X64_BIN_DIR}
        ${VCPKG_X64_INCLUDE_DIR}
        )

ConfigurationSummary()

# ensure the directories we've located exist
foreach (d ${_VCPKG_DIRECTORIES})
    if (NOT EXISTS ${d})
        message(FATAL_ERROR "VCPKG directory \"${d}\" does not exist")
    endif ()
endforeach ()


###########################################################
#   Find the dependencies
#

# note, I've not used the "find_package" command because
# sometimes it doesn't work and its really difficult to debug why.
# find_library, find_path and find_file are easier

# defines:
#   - libraries as x_LIBRARY
#   - static libraries as x_STATIC_LIBRARY
#   - include paths as x_INCLUDE_DIR
#   - STATIC_LIBRARIES = list of found static libraries
#   - LIBRARIES = list of found shared libraries
FindDependencies()

if (PLATFORM STREQUAL "windows-msvc")
    # On windows, order seems less important

    # fixme
    #Note these "static" libraries are not actually static.
    set(LINK_LIBRARIES
            "${LIBXML2_STATIC_LIBRARY}"
            "${LIBXSLT_STATIC_LIBRARY}"
            "${CURL_STATIC_LIBRARY}"
            "${LIBCHARSET_STATIC_LIBRARY}"
            "${SSL_STATIC_LIBRARY}"
            "${CRYPTO_STATIC_LIBRARY}"
            "${YAJL_STATIC_LIBRARY}"
            "${LZMA_STATIC_LIBRARY}"
            "${ZLIB_STATIC_LIBRARY}"
            "${ICONV_STATIC_LIBRARY}"
            "${PCRE_STATIC_LIBRARY}"
#            "D:/vcpkg/installed/x64-windows-static/lib/sqlite3.lib"
            "${SQLITE3_STATIC_LIBRARY}"
            "${BERKELY_STATIC_LIBRARY}"
            ws2_32 # needed on windows to statically link libxml2
            )
    # moreover, on windows it was much easier to just
    # set up to link to dynamic versions of libraries.
    # I tried to pull all into a single static library
    # but this proved too faffy.

    # determine runtime (set to static, dynamic libraries are modified later)
    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
    elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
    endif ()

elseif (PLATFORM STREQUAL "linux")
    # But on linux, order is essential.
    # if A depends on B, A must come before B in this list.
    # On linux, I pulled as many libraries as possible
    # into a static library. This was not possible with a few
    # for strange and unusual reasons which are explainable only
    # by the programming gods.
    set(LINK_LIBRARIES
            ${LIBXML2_LIBRARY} # dynamic
            ${LIBXSLT_LIBRARY} # dynamic
            ${SQLITE3_LIBRARY}
            # flag for including whole archive, not just the function used.
            -Wl,--whole-archive
            ${ZLIB_STATIC_LIBRARY}
            ${LZMA_STATIC_LIBRARY}
            -Wl,--no-whole-archive
            ${ICONV_LIBRARY} # We use dynamic for now.
            ltdl
            -Wl,--whole-archive
            ${CURL_STATIC_LIBRARY}
            ${SSL_STATIC_LIBRARY}
            ${CRYPTO_STATIC_LIBRARY}
            ${YAJL_STATIC_LIBRARY}
            ${PCRE_STATIC_LIBRARY}
            ${BERKELY_STATIC_LIBRARY}
            -Wl,--no-whole-archive
            m
            dl
            )

elseif (PLATFORM STREQUAL "macos")
    message(FATAL_ERROR "Stupid mac.")
endif ()


set(INCLUDE_DIRECTORIES
        # fixme lots of redundancy here at the moment.
        # raptor includes
        ${CMAKE_SOURCE_DIR}/src/redland/raptor2-2.0.15/src
        ${CMAKE_SOURCE_DIR}/src/redland/raptor2-2.0.15/utils
        ${CMAKE_SOURCE_DIR}/src/redland/raptor2-2.0.15/librdfa

        # rasqal includes
        ${CMAKE_SOURCE_DIR}/src/redland/rasqal-0.9.33/src
        ${CMAKE_SOURCE_DIR}/src/redland/rasqal-0.9.33/libmtwist
        ${CMAKE_SOURCE_DIR}/src/redland/rasqal-0.9.33/libsv
        ${CMAKE_SOURCE_DIR}/src/redland/rasqal-0.9.33/utils

        # librdf includes
        ${CMAKE_SOURCE_DIR}/src/redland/redland-1.0.17/src
        ${CMAKE_SOURCE_DIR}/src/redland/redland-1.0.17/utils
        ${CMAKE_SOURCE_DIR}/src/redland/redland-1.0.17/libltdl

        # wrapper includes
        ${CMAKE_SOURCE_DIR}/src/redland/RedlandAPIWrapper/src

        # libomexmeta includes
        ${CMAKE_SOURCE_DIR}/src

        # dependency includes
        ${LIBXML2_INCLUDE_DIR}
        ${LIBXSLT_INCLUDE_DIR}
        ${CURL_INCLUDE_DIR}
        ${SSL_INCLUDE_DIR}
        ${SSL_INCLUDE_DIR}
        ${YAJL_INCLUDE_DIR}
        ${LZMA_INCLUDE_DIR}
        ${ZLIB_INCLUDE_DIR}
        ${PCRE_INCLUDE_DIR}
        ${ICONV_INCLUDE_DIR}
        )

#############################################
# add src directory to include targets and tests

# source directories
add_subdirectory(src)

# test directories
if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(${GOOGLETEST_SOURCE})
    add_subdirectory(tests/cpp)
endif (BUILD_TESTS)

if (BUILD_DOCS)
    add_subdirectory(docs)
endif ()


# print out config summary
ConfigurationSummary()
















