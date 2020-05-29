# todo explore: https://stackoverflow.com/questions/16799164/compiling-a-library-redland-in-cygwin-using-gcc-and-using-the-output-in-visual/48428588#48428588
cmake_minimum_required(VERSION 3.15)

# load the ExternalProject functions for superbuild
include(ExternalProject)

# load a custom function for finding all the dependencies if they exist.
#set(FIND_DEPENDENCIES_PATH ${CMAKE_SOURCE_DIR}/cmake/LookForDependencies.cmake)

# load a custom function for printing out found paths to console
include(${CMAKE_SOURCE_DIR}/cmake/PrintOutPaths.cmake)

######################################################
#   Set some variables
#

# global settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-std=c++17")

if ("${CMAKE_SYSTEM_NAME}" MATCHES "Linux" OR "${CMAKE_SYSTEM_NAME}" MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fPIC")
endif ()

# https://gitlab.kitware.com/cmake/cmake/issues/16589
set(CMAKE_MACOSX_RPATH ON)

# superbuild variable
set(HAVE_DEPENDENCIES FALSE CACHE BOOL
        "When true, the dependencies will be
         automatically built before building libsemsim. When False
         The dependencies are assumed to already exist")

option(BUILD_DOCS "Build libsemsim documentation" ON)


MESSAGE(STATUS "HAVE_DEPENDENCIES ${HAVE_DEPENDENCIES}")

# tests
SET(BUILD_TESTS OFF CACHE BOOL "build the tests")

SET(N 8 CACHE STRING "number of cores to use for build. Passed onto -j for make")

set(CMAKE_VERBOSE_MAKEFILE ON)

# todo move the following to SetPaths.cmake

# path to redland libraries
set(REDLAND_DIR ${CMAKE_SOURCE_DIR}/src/redland)

# paths to invididual redland libraries
SET(RAPTOR_DIR ${REDLAND_DIR}/raptor2-2.0.15)
SET(RASQAL_DIR ${REDLAND_DIR}/rasqal-0.9.33)
SET(LIBRDF_DIR ${REDLAND_DIR}/redland-1.0.17)
SET(WRAPPER_DIR ${REDLAND_DIR}/RedlandAPIWrapper)

# paths to invididual redland libraries source code
SET(RAPTOR_SOURCE_DIR ${RAPTOR_DIR}/src)
SET(RASQAL_SOURCE_DIR ${RASQAL_DIR}/src)
SET(LIBRDF_SOURCE_DIR ${LIBRDF_DIR}/src)
SET(WRAPPER_SOURCE_DIR ${WRAPPER_DIR}/src)

# paths wrapper tests
SET(WRAPPER_TEST_DIR ${WRAPPER_DIR}/test)

# When we don't have dependencies we can't build the tests
if (BUILD_TESTS AND NOT HAVE_DEPENDENCIES)
    set(BUILD_TESTS OFF)
endif ()

# Set the paths we need for building libsemsim + dependencies
include(${CMAKE_SOURCE_DIR}/cmake/SetPaths.cmake)


#################################################################
# Superbuild
#

if (NOT HAVE_DEPENDENCIES)
    message(STATUS "CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")
    project(libsemsim-superbuild)
    #    set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/INSTALL/${CMAKE_BUILD_TYPE}")

    PrintOutPaths()
    add_custom_target(raptor)
    add_custom_target(rasqal)
    add_custom_target(librdf)
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/superbuild.cmake)
    return() # stop after processing superbuild.cmake

else ()
    message(STATUS "BUILDING LIBSEMSIM")
    project(libsemsim LANGUAGES CXX VERSION 0.1.5)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/INSTALL/${CMAKE_BUILD_TYPE}")
    message(STATUS "CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")
    #    include(${FIND_DEPENDENCIES_PATH})

    #    # get dependencies from /usr/local/lib
    #    find_library(RAPTOR2_STATIC_LIBRARY
    #            NAMES libraptor2.a raptor2.a
    #            PATHS ${RAPTOR2_INSTALL_PREFIX}/lib
    #            /usr/local/lib
    #            )
    #
    #    find_path(RAPTOR2_INCLUDE_DIR
    #            NAMES raptor2.h
    #            PATHS ${RAPTOR2_INSTALL_PREFIX}/include/raptor2
    #            /usr/local/include/raptor2
    #            )
    #
    #    # rasqal
    #    find_library(RASQAL_STATIC_LIBRARY
    #            NAMES librasqal.a rasqal.a
    #            PATHS ${RASQAL_INSTALL_PREFIX}/lib
    #            /usr/local/lib
    #            )
    #
    #    find_path(RASQAL_INCLUDE_DIR
    #            NAMES rasqal.h
    #            PATHS ${RASQAL_INSTALL_PREFIX}/include/rasqal
    #            /usr/local/include/rasqal
    #            )
    #
    #    find_library(REDLAND_STATIC_LIBRARY
    #            NAMES librdf.a rdf.a
    #            PATHS ${REDLAND_INSTALL_PREFIX}/lib
    #            /usr/local/lib
    #            )
    #
    #    find_path(REDLAND_INCLUDE_DIR
    #            NAMES librdf.h
    #            PATHS ${REDLAND_INSTALL_PREFIX}/include
    #            /usr/local/include
    #            )
    #

    set(INCLUDE_DIRS
            ${CMAKE_SOURCE_DIR}/src
            ${LIBXML2_INCLUDE_DIR}
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
            )

    set(LINK_LIBRARIES
            # order matters: top of the dependency chain first
            # i.e. if A depends on B, A should come before B in this list

            -Wl,--whole-archive
            "${LIBCOMBINE_STATIC_LIBRARY}"
            "${LIBSBML_STATIC_LIBRARY}"
            -Wl,--no-whole-archive
            "${ZIPPER_STATIC_LIBRARY}"
            -Wl,--whole-archive
            "${ZLIB_STATIC_LIBRARY}"
            "${BZ2_STATIC_LIBRARY}"
            "${LIBXML2_STATIC_LIBRARY}"
            -Wl,--no-whole-archive
            "iconv"
            ltdl ${CMAKE_DL_LIBS} lzma pcre curl m
            c gmp pcre uuid
            c xml2 m xslt yajl gss mpfr
            xml2 idn2 pthread curl ssl
            db curl
            )

    set(INCLUDE_DIRECTORIES
            BEFORE ${RAPTOR_DIR}/librdfa
            ${RAPTOR_DIR}/src
            ${RASQAL_DIR}/src
            ${RASQAL_DIR}/libmtwist
            ${RASQAL_DIR}/libsv
            ${RASQAL_DIR}/getopt
            ${LIBRDF_DIR}/src
            /mnt/d/libsemsim/src/redland/redland-1.0.17/src
            ${WRAPPER_SOURCE_DIR} #RedlandAPIWrapper
            ${LIBXML2_INCLUDE_DIR}
            ${LIBSBML_DEPS_INCLUDE_DIR}
            ${LIBSBML_INCLUDE_DIR}
            ${ZLIB_INCLUDE_DIR}
            ${ZIPPER_INCLUDE_DIR}
            ${LIBCOMBINE_INCLUDE_DIR}
            ${LIBPQ_INCLUDE_DIR}
            )

    message(STATUS "REDLAND_LIBRARY ${REDLAND_LIBRARY}")


    PrintOutPaths()
    #    message(WARNING "HERE")
    add_subdirectory(src/redland)
    #    add_subdirectory(src)

    if (BUILD_TESTS)
        enable_testing()
        add_subdirectory(tests/cpp)
        add_subdirectory(${GOOGLETEST_SOURCE})
    endif (BUILD_TESTS)
endif ()


#############################################
# add semsim and tests


message(STATUS "
#-------------------------------------------------------------------------------
#Configuration Summary
#-------------------------------------------------------------------------------
    Configured on host $ENV{COMPUTERNAME} ${HOSTNAME}
        host OS                   ${CMAKE_SYSTEM_NAME}
        host architecture         ${CMAKE_SYSTEM_PROCESSOR}
    General flags:
        CC                        ${CMAKE_C_COMPILER}
        CXX                       ${CMAKE_CXX_COMPILER}
        CPPFLAGS                  ${BUILD_DEFINITIONS}
        CFLAGS                    ${CMAKE_C_FLAGS}
        CXXFLAGS                  ${CMAKE_CXX_FLAGS}
        LDFLAGS                   ${CMAKE_EXE_LINKER_FLAGS}
    Installation prefix:          ${CMAKE_INSTALL_PREFIX}
    Options:
        SBML support              ${ENABLE_SBML_SUPPORT}
        CellML suppert            ${ENABLE_CELLML_SUPPORT}
        Tests (requires Catch)    ${ENABLE_TESTS}
        Python bindings           ${BUILD_PYTHON}
        Python interpreter        ${Python_EXECUTABLE}
        Python include directory  ${PYTHON_INCLUDE_PATH}
        Generate documentation    ${BUILD_DOCS}

    Paths:
        RAPTOR_DIR                ${RAPTOR_DIR}
        RASQAL_DIR                ${RASQAL_DIR}
        LIBRDF_DIR                ${LIBRDF_DIR}
        WRAPPER_DIR               ${WRAPPER_DIR}
        RAPTOR_SOURCE_DIR         ${RAPTOR_SOURCE_DIR}
        RASQAL_SOURCE_DIR         ${RASQAL_SOURCE_DIR}
        LIBRDF_SOURCE_DIR         ${LIBRDF_SOURCE_DIR}
        WRAPPER_SOURCE_DIR        ${WRAPPER_SOURCE_DIR}
        WRAPPER_TEST_DIR          ${WRAPPER_TEST_DIR}
    ")