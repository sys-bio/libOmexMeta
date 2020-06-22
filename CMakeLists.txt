# todo explore: https://stackoverflow.com/questions/16799164/compiling-a-library-redland-in-cygwin-using-gcc-and-using-the-output-in-visual/48428588#48428588
cmake_minimum_required(VERSION 3.15)


# load the ExternalProject functions for superbuild
include(ExternalProject)


# load a custom function for finding all the dependencies if they exist.
#set(FIND_DEPENDENCIES_PATH ${CMAKE_SOURCE_DIR}/cmake/LookForDependencies.cmake)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# load a custom function for printing out found paths to console
include(${CMAKE_SOURCE_DIR}/cmake/PrintOutPaths.cmake)

# load a custom function for determining the current platform
include(${CMAKE_SOURCE_DIR}/cmake/DeterminePlatform.cmake)

# Load a custom function that configures the various paths we need
include(${CMAKE_SOURCE_DIR}/cmake/SetPaths.cmake)

######################################################
#   Set some variables
#

# global settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_MICRO 8)

set(LIBSEMSIM_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_MICRO})
#configure_file("${CMAKE_SOURCE_DIR}/VERSION.in" "${CMAKE_SOURCE_DIR}/VERSION.txt")

if ("${CMAKE_SYSTEM_NAME}" MATCHES "Linux" OR "${CMAKE_SYSTEM_NAME}" MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fPIC")
endif ()

# https://gitlab.kitware.com/cmake/cmake/issues/16589
set(CMAKE_MACOSX_RPATH ON)

# superbuild variable
set(HAVE_DEPENDENCIES FALSE CACHE BOOL
        "When true, the dependencies will be
         automatically built before building libsemsim. When False
         the dependencies are assumed to already exist")

option(BUILD_DOCS "Build libsemsim documentation" ON)
option(BUILD_LIBSBML "Build libsbml" OFF)
option(BUILD_LIBCOMBINE "Build libcombine" OFF)


MESSAGE(STATUS "HAVE_DEPENDENCIES ${HAVE_DEPENDENCIES}")

# tests
SET(BUILD_TESTS OFF CACHE BOOL "build the tests")

SET(N 8 CACHE STRING "number of cores to use for build. Passed onto -j for make")

set(CMAKE_VERBOSE_MAKEFILE ON)


# todo move the following to SetPaths.cmake


# When we don't have dependencies we can't build the tests
if (BUILD_TESTS AND NOT HAVE_DEPENDENCIES)
    set(BUILD_TESTS OFF)
endif ()


#################################################################
# Superbuild
#
if (NOT HAVE_DEPENDENCIES)
    project(libsemsim-superbuild)
    DeterminePlatform() #defined ${PLATFORM}

    # Set the paths we need for building libsemsim + dependencies
    SetPaths("${PLATFORM}")

    #update apt
    #    execute_process(COMMAND sudo apt update)

    set(DEPENDENCY_LIBRARIES make build-essential checkinstall zlib1g-dev libltdl-dev lzma libpcre3 libpcre3-dev uuid-dev libxml2 libxml2-dev libxslt1-dev yajl-tools libgss-dev libmpfr-dev idn2 libpthread-stubs0-dev curl mysql-server)

    # on linux we can use apt to download dependencies
    #    add_custom_target(
    #            apt-downloads ALL
    #            COMMAND sudo apt install -y ${DEPENDENCY_LIBRARIES}
    #            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    #            COMMENT "download required dependencies straight from apt on ubuntu"
    #    )

    PrintOutPaths()
    add_custom_target(raptor)
    add_custom_target(rasqal)
    add_custom_target(librdf)
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/superbuild.cmake)
    return() # stop after processing superbuild.cmake

else ()
    message(STATUS "BUILDING LIBSEMSIM")
    project(libsemsim LANGUAGES CXX VERSION 0.1.5)
    DeterminePlatform()
    message(STATUS "PLATFORM ${PLATFORM}")
    # Set the paths we need for building libsemsim + dependencies
    SetPaths(${PLATFORM})


    if (PLATFORM STREQUAL "windows-msvc")

        # static runtime?
        # define REDLAND_STATIC for static runtime.
        # ignored on other platforms
        # define static here and then redefine dynamic for the shared library

        if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
            set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
        elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
            set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
        endif ()

        set(VCPKG_ROOT "D:/vcpkg" CACHE STRING "Absolute path to root vcpkg directory. On mine its D:\\vcpkg")
        set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "The vcpkg triplet to use")
        #        set(CMAKE_GENERATOR_PLATFORM "x64-windows")
        set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Path to vcpkg toolchain file")
        set(VCPKG_X64_INSTALLED_PACKAGES "${VCPKG_ROOT}/installed/x64-windows")
        set(VCPKG_X64_STATIC_LIB_DIR "${VCPKG_ROOT}/installed/x64-windows-static/lib")

        set(VCPKG_X64_LIB_DIR "${VCPKG_X64_INSTALLED_PACKAGES}/lib")
        set(VCPKG_X64_BIN_DIR "${VCPKG_X64_INSTALLED_PACKAGES}/bin")
        set(VCPKG_X64_INCLUDE_DIR "${VCPKG_X64_INSTALLED_PACKAGES}/include")

        if (NOT EXISTS ${CMAKE_TOOLCHAIN_FILE})
            message(FATAL_ERROR "No vcpkg toolchain installed. Have you configured vcpkg yet? If so,
pass in -DCMAKE_TOOLCHAIN_FILE=\"C:/full/path/to/vcpkg.cmake\"")
        endif ()


        message(WARNING "You have used a different variable on windows
        to store libxml2 include and libraries. You'll want to change
        this when you have MSVC working. ")

        find_library(LIBXML2_STATIC_LIBRARY2
                NAMES libxml2.lib libxml2 xml2 xml2.lib
                PATHS
                ${VCPKG_X64_LIB_DIR}
                #                D:/vcpkg/installed/x64-windows/lib
                )


        find_path(LIBXML2_INCLUDE_DIR2
                NAMES libxml/parser.h
                PATHS ${VCPKG_X64_INCLUDE_DIR}
                REQUIRED
                )

        find_library(LIBXSLT_STATIC_LIBRARY
                NAMES libxslt
                PATHS ${VCPKG_X64_LIB_DIR}
                REQUIRED
                )

        find_path(LIBXSLT_INCLUDE_DIR
                NAMES libxslt/libxslt.h
                PATHS ${VCPKG_X64_INCLUDE_DIR}
                REQUIRED
                )


        #        message(STATUS " after LIBXML2_LIBRARY ${LIBXML2_LIBRARY}")
        #        message(STATUS "EXISTS ${LIBXML2_LIBRARY}")
        #        if (NOT EXISTS "${LIBXML2_LIBRARY}")
        #            message(FATAL_ERROR "Libxml not found")
        #        endif ()

        find_library(CURL_STATIC_LIBRARY
                NAMES libcurl curl
                PATHS ${VCPKG_X64_LIB_DIR}
                REQUIRED
                )

        find_path(CURL_INCLUDE_DIR
                NAMES curl/curl.h
                PATHS ${VCPKG_X64_INCLUDE_DIR}
                REQUIRED
                )

        find_library(MPFR_STATIC_LIBRARY
                NAMES mpfr.lib mpfr
                PATHS ${VCPKG_X64_LIB_DIR}
                REQUIRED
                )

        find_path(MPFR_INCLUDE_DIR
                NAMES mpfr.h
                PATHS ${VCPKG_X64_INCLUDE_DIR}
                REQUIRED
                )

        message(STATUS "LIBXML2_STATIC_LIBRARY2 ${LIBXML2_STATIC_LIBRARY2}")
        message(STATUS "LIBXML2_INCLUDE_DIR2 ${LIBXML2_INCLUDE_DIR2}")
        message(STATUS "LIBXSLT_STATIC_LIBRARY ${LIBXSLT_STATIC_LIBRARY}")
        message(STATUS "LIBXSLT_INCLUDE_DIR ${LIBXSLT_INCLUDE_DIR}")
        message(STATUS "CURL_STATIC_LIBRARY ${CURL_STATIC_LIBRARY}")
        message(STATUS "CURL_INCLUDE_DIR ${CURL_INCLUDE_DIR}")

        SET(LIBRARIES
                ${LIBXML2_STATIC_LIBRARY2}
                ${LIBXSLT_STATIC_LIBRARY}
                ${CURL_STATIC_LIBRARY}
                )
        foreach (lib ${LIBRARIES})
            if (NOT EXISTS "${lib}")
                message(FATAL_ERROR "${lib} not found")
            endif ()
        endforeach ()
    endif (PLATFORM STREQUAL "windows-msvc")


    # we have either just compiled the dependencies
    #  or indicated that we already have them by
    #  using HAVE_DEPENDENCIES=TRUE
    #  we now do a check to find the libraries we need to link

    #    foreach (library ${STATIC_LIBRARIES})
    #        if (NOT EXISTS {$library})
    #            message(FATAL_ERROR "Missing dependency. The library \"${library}\" should exist but doesn't")
    #        endif ()
    #    endforeach ()

    #    find_package(ICU 60 COMPONENTS uc i18n)
    #    if (NOT ICU_FOUND)
    #        message(WARNING "ICU not found. On linux, `sudo apt install icu-devtools` and try again.")
    #    endif ()

    message(STATUS "ICU_LIBRARIES ${ICU_c_LIBRARIES}")


    if (WITH_ADDRESS_SANITIZER)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")# -OX")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")# -OX")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")# -OX")
    ENDIF ()

    #    INCLUDE(CheckIncludeFile)
    #    CHECK_INCLUDE_FILE(<libxml/parser.h> HAVE_LIBXML2)


    set(INCLUDE_DIRECTORIES
            ${CMAKE_SOURCE_DIR}/src/redland/raptor2-2.0.15/src
            ${CMAKE_SOURCE_DIR}/src/redland/raptor2-2.0.15/utils
            ${CMAKE_SOURCE_DIR}/src/redland/raptor2-2.0.15/librdfa
            ${CMAKE_SOURCE_DIR}/src/redland/rasqal-0.9.33/libmtwist
            ${CMAKE_SOURCE_DIR}/src/redland/rasqal-0.9.33/libsv
            ${CMAKE_SOURCE_DIR}/src/redland/rasqal-0.9.33/utils
            ${CMAKE_SOURCE_DIR}/src/redland/redland-1.0.17/utils
            ${CMAKE_SOURCE_DIR}/src/redland/redland-1.0.17/libltdl

            ${CURL_INCLUDE_DIR}
            ${LIBXML2_INCLUDE_DIR2}
            ${LIBSBML_DEPS_INCLUDE_DIR}
            ${LIBSBML_INCLUDE_DIR}
            ${ZLIB_INCLUDE_DIR}
            ${ZIPPER_INCLUDE_DIR}
            ${LIBCOMBINE_INCLUDE_DIR}
            ${RASQAL_INCLUDE_DIR}
            ${RAPTOR2_INCLUDE_DIR}
            ${RAPTOR_SOURCE_DIR}
            ${RASQAL_SOURCE_DIR}
            ${LIBRDF_SOURCE_DIR}
            ${WRAPPER_SOURCE_DIR}
            ${LIBPQ_INCLUDE_DIR}
            ${ICONV_INCLUDE_DIR}


            BEFORE ${RAPTOR_DIR}/librdfa
            ${RAPTOR_DIR}/src
            ${RASQAL_DIR}/src
            ${RASQAL_DIR}/libmtwist
            ${RASQAL_DIR}/libsv
            ${RASQAL_DIR}/getopt
            ${LIBRDF_DIR}/src
            ${WRAPPER_SOURCE_DIR} #RedlandAPIWrapper
            ${LIBXML2_INCLUDE_DIR}
            ${LIBSBML_DEPS_INCLUDE_DIR}
            ${LIBSBML_INCLUDE_DIR}
            ${ZLIB_INCLUDE_DIR}
            ${ZIPPER_INCLUDE_DIR}
            ${LIBCOMBINE_INCLUDE_DIR}
            ${LIBPQ_INCLUDE_DIR}
            ${OPENSSL_INCLUDE_DIR}
            ${CMAKE_SOURCE_DIR}/src
            ${CMAKE_SOURCE_DIR}/src/semsim
#            D:/libsemsim/src
#            D:/libsemsim/src/semsim
            )

    #https://cmake.cmake.narkive.com/lzDZk3kO/autoheader-like-functionality


    if (${PLATFORM} STREQUAL "windows-msvc")

        #        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

        if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
            set(MSVC_EXTRA_LIBS "libucrtd")
        elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
            set(MSVC_EXTRA_LIBS "libucrt")
        endif ()

        set(LINK_LIBRARIES
                # order matters: top of the dependency chain first
                # i.e. if A depends on B, A should come before B in this list
                # needed on windows
                "${VCPKG_X64_LIB_DIR}/libcurl.lib"
                "${VCPKG_X64_LIB_DIR}/libxslt.lib"
                "${VCPKG_X64_LIB_DIR}/libxml2.lib"
                "${VCPKG_X64_LIB_DIR}/libcharset.lib"
                "${VCPKG_X64_LIB_DIR}/libssl.lib"
                "${VCPKG_X64_LIB_DIR}/libcrypto.lib"
                "${VCPKG_X64_LIB_DIR}/yajl.lib"
                "${VCPKG_X64_LIB_DIR}/lzma.lib"
                "${VCPKG_X64_LIB_DIR}/zlib.lib"
                "${VCPKG_X64_LIB_DIR}/libexslt.lib"
                "${VCPKG_X64_LIB_DIR}/libiconv.lib"
                )
    else ()

        set(LINK_LIBRARIES
                # order matters: top of the dependency chain first
                # i.e. if A depends on B, A should come before B in this list
                #            -Wl,--whole-archive
                #            ${LIBCOMBINE_STATIC_LIBRARY}
                #            ${LIBSBML_STATIC_LIBRARY}
                #            -Wl,--no-whole-archive
                #            ${ZIPPER_STATIC_LIBRARY}
                #                            -Wl,--whole-archive
                #            ${ZLIB_STATIC_LIBRARY}
                #            ${BZ2_STATIC_LIBRARY}
                xslt
                -Wl,--no-whole-archive
                ${LIBXML2_LIBRARY}
                -Wl,--whole-archive
                ${ICONV_STATIC_LIBRARY}
                -Wl,--no-whole-archive
                sqlite3
                ltdl ${CMAKE_DL_LIBS}
                pcre
                yajl
                ${LIBCURL_LIBRARY}
                stdc++fs
                )
    endif (${PLATFORM} STREQUAL "windows-msvc")
    # This is what i was using for a while. it worked on linux
    #    set(LINK_LIBRARIES
    #            # order matters: top of the dependency chain first
    #            # i.e. if A depends on B, A should come before B in this list
    ##            -Wl,--whole-archive
    ##            ${LIBCOMBINE_STATIC_LIBRARY}
    ##            ${LIBSBML_STATIC_LIBRARY}
    ##            -Wl,--no-whole-archive
    ##            ${ZIPPER_STATIC_LIBRARY}
    #            -Wl,--whole-archive
    ##            ${ZLIB_STATIC_LIBRARY}
    ##            ${BZ2_STATIC_LIBRARY}
    #            xslt
    #            -Wl,--no-whole-archive
    #            ${LIBXML2_LIBRARY}
    #            -Wl,--whole-archive
    #            ${ICONV_STATIC_LIBRARY}
    #            -Wl,--no-whole-archive
    #            sqlite3
    #            ltdl ${CMAKE_DL_LIBS}
    #            pcre
    #            yajl
    #            ${LIBCURL_LIBRARY}
    #            stdc++fs
    #            )

    # notes on libraries
    # ==================
    # back end database
    # -------------------
    #   - still need to implement support for database storage.
    #   - db - easily installed. Not yet tried.
    #   - sqlite3 - couldn't get to work
    #   - keep libpq in back pocket as alternative backend
    #       other options are sqlite3 or virtuoso ${LIBPQ_STATIC_LIBRARY}
    #     - prefer sqlite3 if you can get it working
    #
    # WWW stuff - i.e. downloading from web
    # -----------------------------------------
    #   - I have tried to cut out libcurl in favour of using libxml for www functions
    #     instead. Didn't work - though might still be possible with a bit of tuning.
    # Floating Precision libraries
    # ------------------------------
    #   - two options on linux:  mpfr or gmp. Its one or the other as they
    #     both do the same thing. If you incorporate them, ensure you modify
    #     rasqal_config.h to reflect which library you choose. Currently,
    #     I am choosing RASQAL_DECIMAL_NONE, aka none of these libraries,
    #     which just uses double and int. It'll have less accuracy but
    #     its more portable.
    #  gss
    # -----
    #   - I had this in the libraries. Not sure what it did, but it no longer
    #     breaks the build so removing it for good. Listed here as a note.
    # regexes
    # -------
    # - Two choices pcre or poxis. Both however could and should
    #   be replaced with the c++ standard library implementation of regexes.
    #   However, given that this is a lot of effort, I keep PCRE, since there is
    #   a windows build that might work: https://github.com/kiyolee/pcre-win-build
    #
    # uuid, libc and libuuid
    # ----------------------
    # - used for metaids. However, there is an internal options
    #   which is better for a portability perspective. I'll use that.
    #
    #  others
    # -------
    # a set of linux libraries that fixed earlier builds but now seem to now be needed.
    # Keep the list
    # - pthread
    # - libm
    # - libc
    # - lzma


    PrintOutPaths()
    add_subdirectory(src/redland)
    add_subdirectory(src)

    if (BUILD_TESTS)
        enable_testing()
        add_subdirectory(${GOOGLETEST_SOURCE})
        add_subdirectory(tests/cpp)
    endif (BUILD_TESTS)

    if (BUILD_DOCS)
        add_subdirectory(docs)
    endif ()

endif ()


#############################################
# add semsim and tests

