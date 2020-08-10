#A note on the docs-build system. Occasionally you will
#see "_CMakeLists.txt". This is an old version of the
#docs-build system. This will be deleted in due course.

cmake_minimum_required(VERSION 3.15)


# Set version.
set(VERSION_MAJOR 1)
set(VERSION_MINOR 1)
set(VERSION_MICRO 5)

set(LIBOMEXMETA_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_MICRO})
project(libOmexMeta VERSION "${LIBOMEXMETA_VERSION}")

# configure VERSION.txt for Python to read
configure_file("${CMAKE_SOURCE_DIR}/VERSION.in" "${CMAKE_SOURCE_DIR}/VERSION.txt" @ONLY)

######################################################
# Load stuff
# set the module path
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# load the ExternalProject functions for superbuild
include(ExternalProject)

# load a custom function for determining the current platform
include(DeterminePlatform)

# defines ${PLATFORM}
DeterminePlatform()

# defines a macro for locating the dependencies
include(FindDependencies)

# defines a macro that allows easily setting of platform dependent values for a variable
include(SetCrossPlatform)

# defines a macro that prints out configuration summary
include(ConfigurationSummary)

# include some code for coverage configuration
#include(CodeCoverage)

######################################################
#   Set some variables
#

# global settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# pic - needed on linux ignored on other platofrms
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# location of pyomexmeta development package.
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

option(BUILD_DOCS "Build libomexmeta documentation" OFF)
option(BUILD_DOCS_EXAMPLES "Build the examples in the documentation. BUILD_DOCS must be ON to have an effect" OFF)

# docs-build tests?
SET(BUILD_TESTS OFF CACHE BOOL "build the tests")

# verbose
set(CMAKE_VERBOSE_MAKEFILE ON)

option(WITH_SANITIZER "link with address sanitizer for memory debugging" OFF)
if (WITH_SANITIZER)
    if (${PLATFORM} STREQUAL "linux")
        SET(ADDRESS_SANITIZER_FLAGS "-g -fsanitize=address")
        SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${ADDRESS_SANITIZER_LINK_FLAGS}")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ADDRESS_SANITIZER_FLAGS}")
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${ADDRESS_SANITIZER_FLAGS}")
    elseif (${PLATFORM} STREQUAL "windows-msvc")

    elseif (${PLATFORM} STREQUAL "macos")
        message(FATAL_ERROR "Sad face mac user =[")
    endif ()
endif ()

#set(CMAKE_CXX_FLAGS "-O0")
#set(CMAKE_C_FLAGS "-O0")
#set(CMAKE_CXX_FLAGS_RELEASE "-O0")
#set(CMAKE_C_FLAGS_RELEASE "-O0")
#set(CMAKE_CXX_FLAGS_DEBUG "-O0")
#set(CMAKE_C_FLAGS_DEBUG "-O0")
#set(CMAKE_CXX_FLAGS "-O0")
#set(CMAKE_C_FLAGS "-O0")

option(WITH_BDB "build user suport for berkely database" ON)
if (${WITH_BDB})
    add_definitions(-DWITH_BDB)
endif ()

#if (NOT PLATFORM STREQUAL "windows-msvc")
#    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
#        #  remove optimizations for Debug builds.
#        #  and add -g -> instructs compiler to generate and retain
#        #  source level debug information.
#        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")
#        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g")
#
#    elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
#        # set optimizations to highest level for Release builds
#        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os")
#        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os")
#    endif ()
#endif (NOT PLATFORM STREQUAL "windows-msvc")
# run the tests and generate coverage output
option(WITH_COVERAGE OFF)

# set RPATH for libraries and executables.
set(RPATH "$ORIGIN:$ORIGIN/../lib")

# set runtime library on windows, which is different between debug and release.
if (PLATFORM STREQUAL "windows-msvc")
    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(RUNTIME "libucrtd")
    elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
        set(RUNTIME "libucrt")
    endif ()
endif ()

if (${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    message(FATAL_ERROR "In source builds are disabled")
endif ()

# set gtest libraries which are different between debug and release.
#if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
set(GTEST_LIBS $<TARGET_FILE:gtest> $<TARGET_FILE:gtest_main>)
#elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
#    set(GTEST_LIBS gtest gtest_main)
#endif ()

if (PLATFORM STREQUAL "linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
endif ()

set(PYTHON_EXECUTABLE "/home/ciaran/miniconda3/bin/python" CACHE FILEPATH "Full path to python executable")



############################################################3
# configure some paths relative to vcpkg root
set(VCPKG_ROOT "D:/vcpkg" CACHE STRING "Absolute path to root vcpkg directory. On mine its \"D:\\vcpkg\" on windows and \"/home/ciaran/vcpkg\" on WSL (Ubuntu)")
if (NOT EXISTS ${VCPKG_ROOT})
    message(FATAL_ERROR "vcpkg root not found (${VCPKG_ROOT})")
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
            "${SQLITE3_STATIC_LIBRARY}"
            "${BERKELY_STATIC_LIBRARY}"
            "${POSTGRESQL_STATIC_LIBRARY}"
            ws2_32 # needed on windows to statically link libxml2
            )
    # on windows it was much easier to just
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
    # On linux, order is essential.
    # if A depends on B, A must come before B in this list.
    # On linux, I pulled as many libraries as possible
    # into a static library. This was not possible with a few
    # for strange and unusual reasons which only the programming gods
    # can explain.
    set(LINK_LIBRARIES
            ${LIBXML2_LIBRARY} # dynamic
            ${LIBXSLT_LIBRARY} # dynamic
            ${SQLITE3_LIBRARY}
            ${BERKELY_LIBRARY}
            ${POSTGRESQL_LIBRARY}
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
            -Wl,--no-whole-archive
            m
            dl
            ldap
            lber
            )

elseif (PLATFORM STREQUAL "macos")
    message(FATAL_ERROR "Stupid mac.")
endif ()


set(INCLUDE_DIRECTORIES
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
        ${CMAKE_SOURCE_DIR}/src/redland/RedlandWrapper/src

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
# Build libOmexMeta targets and tests

# source directories
add_subdirectory(src)

# test directories
if (BUILD_TESTS)
    # allows collecting tests using add_test
    enable_testing()

    # collected tests can be run conveniently together using the command `ctest` from terminal
    # but we create a custom target which does the same.
    add_custom_target(ctest COMMAND ${CMAKE_CTEST_COMMAND})

    # include googletest as source
    add_subdirectory(${GOOGLETEST_SOURCE})

    # add the tests
    add_subdirectory(tests/cpp)

    if (WITH_COVERAGE)
#        if (NOT ${CMAKE_BUILD_TYPE} STREQUAL "Debug")
#            message(FATAL_ERROR "\"WITH_COVERAGE=ON\" must only be used in debug mode because compiler optimizations in release mode will bias coverage results")
#        endif ()

        set(GCOVR_PATH "/home/ciaran/miniconda3/bin/gcovr" CACHE FILEPATH "Full path to gcovr")
        if (NOT GCOVR_PATH)
            message(FATAL_ERROR "gcovr variable GCOVR_PATH (${GCOVR_PATH}) is empty")
        endif ()

        if (CMAKE_COMPILER_IS_GNUCXX)
            include(CodeCoverage)
            append_coverage_compiler_flags()

            # we need to turn off optimization for non-skewed coverage reports
            # we've done this in debug mode so we do not need to do it ehere
            #            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
            #            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")

            # optional excludes - None needed here
            set(COVERAGE_EXCLUDES
                    ${CMAKE_BINARY_DIR}/src/redland/raptor2-2.0.15
                    ${CMAKE_BINARY_DIR}/src/redland/rasqal-0.9.33
                    ${CMAKE_BINARY_DIR}/src/redland/redland-1.0.17
                    ${CMAKE_BINARY_DIR}/src/redland/RedlandWrapper/test
                    ${CMAKE_SOURCE_DIR}/tests
                    ${CMAKE_SOURCE_DIR}/test
                    ${CMAKE_SOURCE_DIR}/third_party
                    )

            # importantly, set the path to the gcovr executable that you downladed
            #  https://github.com/bilke/cmake-modules/issues/8
            setup_target_for_coverage_gcovr_html(
                    NAME TestCoverageHtml
                    EXECUTABLE ctest -j 8
                    DEPENDENCIES ctest
            )
            setup_target_for_coverage_gcovr_xml(
                    NAME TestCoverageXml
                    EXECUTABLE ctest -j 8
                    DEPENDENCIES ctest
            )
        else ()
            message(FATAL_ERROR "Coverage only available using gcov with gcc compilers")
        endif (CMAKE_COMPILER_IS_GNUCXX)
        # need different code for windows.
    endif (WITH_COVERAGE)
endif (BUILD_TESTS)

# docs-build documentation.
if (BUILD_DOCS)
    add_subdirectory(docs)
endif ()


# print out config summary
ConfigurationSummary()
















