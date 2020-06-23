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

set(LIBOMEXMETA_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_MICRO})
#configure_file("${CMAKE_SOURCE_DIR}/VERSION.in" "${CMAKE_SOURCE_DIR}/VERSION.txt")

if ("${CMAKE_SYSTEM_NAME}" MATCHES "Linux" OR "${CMAKE_SYSTEM_NAME}" MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fPIC")
endif ()

# https://gitlab.kitware.com/cmake/cmake/issues/16589
set(CMAKE_MACOSX_RPATH ON)

####################################################################3
# User options
#
if (BUILD_SHARED_LIBS)
    add_definitions("-DBUILD_SHARED_LIBS=ON")
endif ()
# superbuild variable
set(HAVE_DEPENDENCIES FALSE CACHE BOOL
        "When true, the dependencies will be
         automatically built before building libomexmeta. When False
         the dependencies are assumed to already exist")

option(BUILD_DOCS "Build libomexmeta documentation" ON)
option(BUILD_LIBSBML "Build libsbml" OFF)
option(BUILD_LIBCOMBINE "Build libcombine" OFF)


# tests
SET(BUILD_TESTS OFF CACHE BOOL "build the tests")

SET(N 8 CACHE STRING "number of cores to use for build. Passed onto -j for make")

set(CMAKE_VERBOSE_MAKEFILE ON)

# When we don't have dependencies we can't build the tests
if (BUILD_TESTS AND NOT HAVE_DEPENDENCIES)
    set(BUILD_TESTS OFF)
endif ()


#################################################################
# Superbuild
#
if (NOT HAVE_DEPENDENCIES)
    project(libomexmeta-superbuild)
    DeterminePlatform() #defined ${PLATFORM}

    # Set the paths we need for building libomexmeta + dependencies
    SetPaths("${PLATFORM}")

    #update apt
    #    execute_process(COMMAND sudo apt update)

    set(DEPENDENCY_LIBRARIES make build-essential checkinstall zlib1g-dev libltdl-dev lzma libpcre3 libpcre3-dev uuid-dev libxml2 libxml2-dev libxslt1-dev yajl-tools libgss-dev libmpfr-dev idn2 libpthread-stubs0-dev curl mysql-server)

    PrintOutPaths()
    add_custom_target(raptor)
    add_custom_target(rasqal)
    add_custom_target(librdf)
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/superbuild.cmake)
    return() # stop after processing superbuild.cmake

else ()
    message(STATUS "BUILDING LIBOMEXMETA")
    project(libomexmeta LANGUAGES CXX VERSION 0.1.5)
    DeterminePlatform()
    # Set the paths we need for building libomexmeta + dependencies
    SetPaths(${PLATFORM})

    if (WITH_ADDRESS_SANITIZER)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")# -OX")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")# -OX")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")# -OX")
    ENDIF ()


    # put all runtime targets (exe and dll) into bin
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

    # put libraries into lib
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

    # archives
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

    # export all on windows. Ignored on other.
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

    if (PLATFORM STREQUAL "windows-msvc")

        # determine runtime (dynamic library is modified later)
        if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
            set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
        elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
            set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
        endif ()

        set(VCPKG_ROOT "D:/vcpkg" CACHE STRING "Absolute path to root vcpkg directory. On mine its D:\\vcpkg")
        set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "The vcpkg triplet to use. Default is x64-windows.")
        set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Path to vcpkg toolchain file")
        # Here are where packages installed with vcpkg should live. These will be .lib files
        #  but we still need to provide the dll at runtime.
        set(VCPKG_X64_INSTALLED_PACKAGES "${VCPKG_ROOT}/installed/${VCPKG_TARGET_TRIPLET}")
        # for the static triplet. Unfortunately I couldn't get this to work.
        set(VCPKG_X64_STATIC_LIB_DIR "${VCPKG_ROOT}/installed/x64-windows-static/lib")
        #contains .lib files
        set(VCPKG_X64_LIB_DIR "${VCPKG_X64_INSTALLED_PACKAGES}/lib")
        #contains .dll files
        set(VCPKG_X64_BIN_DIR "${VCPKG_X64_INSTALLED_PACKAGES}/bin")
        #include directories
        set(VCPKG_X64_INCLUDE_DIR "${VCPKG_X64_INSTALLED_PACKAGES}/include")

        # ensure the toolchain file exists and user has provided it.
        if (NOT EXISTS ${CMAKE_TOOLCHAIN_FILE})
            message(FATAL_ERROR "No vcpkg toolchain installed. Have you configured vcpkg yet? If so,
pass in -DCMAKE_TOOLCHAIN_FILE=\"C:/full/path/to/vcpkg.cmake\"")
        endif ()

        ##################################################################3
        #   Find windows dependencies.
        #

        message(WARNING "You have used a different variable on windows
to store libxml2 include and libraries. You'll want to change
this when you have MSVC working. Same true for zlib. ")

        # Note: No_DEFAULT prevents other versions
        # of the same library being located and used
        # which tends to break things

        # libxml2
        find_library(LIBXML2_STATIC_LIBRARY2
                NAMES libxml2.lib
                PATHS ${VCPKG_X64_LIB_DIR}
                NO_DEFAULT_PATH
                )

        find_file(LIBXML2_LIBRARY2
                NAMES libxml2.dll xml xml.dll libxml
                PATHS ${VCPKG_X64_BIN_DIR}
                NO_DEFAULT_PATH
                )

        find_path(LIBXML2_INCLUDE_DIR2
                NAMES libxml/parser.h
                PATHS ${VCPKG_X64_INCLUDE_DIR}
                NO_DEFAULT_PATH
                )

        # libxslt
        find_library(LIBXSLT_STATIC_LIBRARY
                NAMES libxslt.lib
                PATHS ${VCPKG_X64_LIB_DIR}
                NO_DEFAULT_PATH
                )

        find_file(LIBXSLT_LIBRARY
                NAMES libxslt.dll
                PATHS ${VCPKG_X64_BIN_DIR}
                NO_DEFAULT_PATH
                )

        find_path(LIBXSLT_INCLUDE_DIR
                NAMES libxslt/libxslt.h
                PATHS ${VCPKG_X64_INCLUDE_DIR}
                NO_DEFAULT_PATH
                )

        # curl
        find_library(CURL_STATIC_LIBRARY
                NAMES libcurl.lib
                PATHS ${VCPKG_X64_LIB_DIR}
                NO_DEFAULT_PATH
                )

        find_file(CURL_LIBRARY
                NAMES libcurl.dll curl curl.dll
                PATHS ${VCPKG_X64_BIN_DIR}
                NO_DEFAULT_PATH
                REQUIRED
                )

        find_path(CURL_INCLUDE_DIR
                NAMES curl/curl.h
                PATHS ${VCPKG_X64_INCLUDE_DIR}
                NO_DEFAULT_PATH
                )

        # libcharset
        find_library(LIBCHARSET_STATIC_LIBRARY
                NAMES libcharset.lib
                PATHS ${VCPKG_X64_LIB_DIR}
                NO_DEFAULT_PATH
                )

        find_file(LIBCHARSET_LIBRARY
                NAMES libcharset.dll
                PATHS ${VCPKG_X64_BIN_DIR}
                NO_DEFAULT_PATH
                REQUIRED
                )
        #       POSSIBLY NOT NEEDED
        #        find_path(LIBCHARSETL_INCLUDE_DIR
        #                NAMES curl/curl.h
        #                PATHS ${VCPKG_X64_INCLUDE_DIR}
        #                )


        # openssl
        find_library(SSL_STATIC_LIBRARY
                NAMES libssl.lib
                PATHS ${VCPKG_X64_LIB_DIR}
                NO_DEFAULT_PATH
                )

        find_file(SSL_LIBRARY
                NAMES libssl.dll libssl-1_1-x64.dll
                PATHS ${VCPKG_X64_BIN_DIR}
                NO_DEFAULT_PATH
                REQUIRED
                )
        find_path(SSL_INCLUDE_DIR
                NAMES openssl/ssl2.h openssl/ssl3.h
                PATHS ${VCPKG_X64_INCLUDE_DIR}
                NO_DEFAULT_PATH
                )

        # libcrypto
        find_library(CRYPTO_STATIC_LIBRARY
                NAMES libcrypto.lib
                PATHS ${VCPKG_X64_LIB_DIR}
                NO_DEFAULT_PATH
                )

        find_file(CRYPTO_LIBRARY
                NAMES libcrypto.dll libcrypto-1_1-x64.dll
                PATHS ${VCPKG_X64_BIN_DIR}
                NO_DEFAULT_PATH
                REQUIRED
                )
        find_path(SSL_INCLUDE_DIR
                NAMES openssl/crypto.h
                PATHS ${VCPKG_X64_INCLUDE_DIR}
                NO_DEFAULT_PATH
                )

        # yajl
        find_library(YAJL_STATIC_LIBRARY
                NAMES yajl.lib
                PATHS ${VCPKG_X64_LIB_DIR}
                NO_DEFAULT_PATH
                )

        find_file(YAJL_LIBRARY
                NAMES yajl.dll
                PATHS ${VCPKG_X64_BIN_DIR}
                NO_DEFAULT_PATH
                REQUIRED
                )

        find_path(YAJL_INCLUDE_DIR
                NAMES yajl/yajl_parse.h
                PATHS ${VCPKG_X64_INCLUDE_DIR}
                NO_DEFAULT_PATH
                )

        # lzma
        find_library(LZMA_STATIC_LIBRARY
                NAMES lzma.lib
                PATHS ${VCPKG_X64_LIB_DIR}
                NO_DEFAULT_PATH
                )

        find_file(LZMA_LIBRARY
                NAMES lzma.dll
                PATHS ${VCPKG_X64_BIN_DIR}
                NO_DEFAULT_PATH
                REQUIRED
                )

        find_path(LZMA_INCLUDE_DIR
                NAMES lzma/lzma12.h
                PATHS ${VCPKG_X64_INCLUDE_DIR}
                NO_DEFAULT_PATH
                )

        # zlib
        find_library(ZLIB2_STATIC_LIBRARY
                NAMES zlib.lib
                PATHS ${VCPKG_X64_LIB_DIR}
                NO_DEFAULT_PATH
                REQUIRED
                )

        find_file(ZLIB2_LIBRARY
                NAMES zlib1.dll
                PATHS ${VCPKG_X64_BIN_DIR}
                NO_DEFAULT_PATH
                REQUIRED
                NO_DEFAULT_PATH
                )

        find_path(ZLIB2_INCLUDE_DIR
                NAMES zlib.h
                PATHS ${VCPKG_X64_INCLUDE_DIR}
                NO_DEFAULT_PATH
                NO_DEFAULT_PATH
                )


        # ICONV
        find_library(ICONV2_STATIC_LIBRARY
                NAMES libiconv.lib
                PATHS ${VCPKG_X64_LIB_DIR}
                NO_DEFAULT_PATH
                )

        find_file(ICONV2_LIBRARY
                NAMES libiconv.dll
                PATHS ${VCPKG_X64_BIN_DIR}
                NO_DEFAULT_PATH
                REQUIRED
                )

        find_path(ICONV2_INCLUDE_DIR
                NAMES iconv.h
                PATHS ${VCPKG_X64_INCLUDE_DIR}
                NO_DEFAULT_PATH
                )

        SET(LIBRARIES_LIB
                "${LIBXML2_STATIC_LIBRARY2}"
                "${LIBXSLT_STATIC_LIBRARY}"
                "${CURL_STATIC_LIBRARY}"
                "${LIBCHARSET_STATIC_LIBRARY}"
#                "${SSL_STATIC_LIBRARY}"
#                "${CRYPTO_STATIC_LIBRARY}"
                "${YAJL_STATIC_LIBRARY}"
                "${LZMA_STATIC_LIBRARY}"
                "${ZLIB2_STATIC_LIBRARY}"
                "${ICONV2_STATIC_LIBRARY}"
                )

        SET(LIBRARIES_DLL
                "${ZLIB2_LIBRARY}"
                "${LIBXML2_LIBRARY2}"
                "${LIBXSLT_LIBRARY}"
                "${CURL_LIBRARY}"
                "${LIBCHARSET_LIBRARY}"
#                "${SSL_LIBRARY}"
#                "${CRYPTO_LIBRARY}"
                "${YAJL_LIBRARY}"
                "${LZMA_LIBRARY}"
                "${ICONV2_LIBRARY}"
                )

        set(LIBRARIES ${LIBRARIES_LIB} ${LIBRARIES_DLL})

        foreach (lib ${LIBRARIES})
            message(STATUS "lib ${lib}")
            if (NOT EXISTS "${lib}")
                message(FATAL_ERROR "${lib} not found")
            endif ()
        endforeach ()


        #https://cmake.cmake.narkive.com/lzDZk3kO/autoheader-like-functionality
        #        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

        if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
            set(MSVC_EXTRA_LIBS "libucrtd")
        elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
            set(MSVC_EXTRA_LIBS "libucrt")
        endif ()

        # Link libraries for windows
        set(LINK_LIBRARIES ${LIBRARIES_LIB})

    elseif (PLATFORM STREQUAL "linux")
        message(STATUS "doing a linux")

        set(LINK_LIBRARIES
                # order matters: top of the dependency chain first
                # i.e. if A depends on B, A should come before B in this list
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
    endif ()
    #
    # This is what i was using for a while. it worked on linux. Keep until definately not needed.
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


    set(INCLUDE_DIRECTORIES
            # fixme lots of redundancy here at the moment.
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
            )
    #############################################
    # add semsim and tests

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



