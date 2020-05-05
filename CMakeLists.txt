# todo explore: https://stackoverflow.com/questions/16799164/compiling-a-library-redland-in-cygwin-using-gcc-and-using-the-output-in-visual/48428588#48428588
cmake_minimum_required(VERSION 3.15)

cmake_policy(SET CMP0003 NEW) # useless
cmake_policy(SET CMP0028 NEW) # double-colon
cmake_policy(SET CMP0042 NEW) # macos rpath
cmake_policy(SET CMP0048 NEW) # can set project version
cmake_policy(SET CMP0060 NEW) # useless
cmake_policy(SET CMP0078 NEW) # used to set target name for swig
cmake_policy(SET CMP0086 NEW) # pass -module flag to swig

include(ExternalProject)

set(HAVE_DEPENDENCIES FALSE CACHE BOOL "Automate dependency manegment")
MESSAGE(STATUS "HAVE_DEPENDENCIES ${HAVE_DEPENDENCIES}")
SET(BUILD_TESTS ON CACHE BOOL "build the tests")

# When we don't have dependencies we can't build the tests
if (BUILD_TESTS AND NOT HAVE_DEPENDENCIES)
    set(BUILD_TESTS OFF)
endif ()

# modules
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})
# global settings

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-std=c++14")

add_compile_definitions(SEMSIM_INTERNAL_BUILD)
message(STATUS "CMAKE_CXX_STANDARD ${CMAKE_CXX_STANDARD}")
message(STATUS "CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}")

if ("${CMAKE_SYSTEM_NAME}" MATCHES "Linux" OR "${CMAKE_SYSTEM_NAME}" MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif ()

# https://gitlab.kitware.com/cmake/cmake/issues/16589
set(CMAKE_MACOSX_RPATH ON)

SET(THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party)

if (CYGWIN)
    set(CYG_ROOT C:/cygwin64 CACHE PATH "absolute path to cygwin root installation")
    set(CYG_LIB_DIR ${CYG_ROOT}/lib)
    set(CYG_BIN_DIR ${CYG_ROOT}/bin)
    set(CYG_INCLUDE_DIR ${CYG_ROOT}/usr/include)
endif ()

set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/INSTALL/${CMAKE_BUILD_TYPE}/INSTALL/${CMAKE_BUILD_TYPE}")

##########################################################################
# variables for building semsim dependencies
#
set(THIRD_PARTY_DIRS ${CMAKE_SOURCE_DIR}/third_party)

# google test source dir
set(GOOGLETEST_SOURCE ${THIRD_PARTY_DIRS}/googletest)

set(LIBSBML_DEPS_SOURCE_DIR ${THIRD_PARTY_DIRS}/libsbml-dependencies)
set(LIBSBML_DEPS_BINARY_DIR ${LIBSBML_DEPS_SOURCE_DIR}/build)
set(LIBSBML_DEPS_INSTALL_PREFIX ${LIBSBML_DEPS_SOURCE_DIR}/INSTALL)
set(LIBSBML_DEPS_INCLUDE_DIR ${LIBSBML_DEPS_INSTALL_PREFIX}/include)
set(LIBSBML_DEPS_LIB_DIR ${LIBSBML_DEPS_INSTALL_PREFIX}/lib)

set(LIBSBML_SOURCE_DIR ${THIRD_PARTY_DIRS}/libsbml-5.18.0)
set(LIBSBML_BINARY_DIR ${LIBSBML_SOURCE_DIR}/build)
set(LIBSBML_INSTALL_PREFIX ${LIBSBML_SOURCE_DIR}/INSTALL)

set(ZIPPER_SOURCE_DIR ${THIRD_PARTY_DIRS}/zipper)
set(ZIPPER_BINARY_DIR ${ZIPPER_SOURCE_DIR}/build)
set(ZIPPER_INSTALL_PREFIX ${ZIPPER_SOURCE_DIR}/INSTALL)
set(ZIPPER_LIB_DIR "${ZIPPER_INSTALL_PREFIX}/lib")

set(ZLIB_SOURCE_DIR ${THIRD_PARTY_DIRS}/zlib-1.2.11)
set(ZLIB_BINARY_DIR ${ZLIB_SOURCE_DIR}/build)
set(ZLIB_INSTALL_PREFIX ${ZLIB_SOURCE_DIR}/INSTALL)
set(ZLIB_LIB_DIR "${ZLIB_INSTALL_PREFIX}/lib")

set(LIBCOMBINE_SOURCE_DIR ${THIRD_PARTY_DIRS}/libCombine-0.2.3)
set(LIBCOMBINE_BINARY_DIR ${LIBCOMBINE_SOURCE_DIR}/build)
set(LIBCOMBINE_INSTALL_PREFIX ${LIBCOMBINE_SOURCE_DIR}/INSTALL)
set(LIBCOMBINE_LIB_DIR "${LIBCOMBINE_INSTALL_PREFIX}/lib")

set(RAPTOR_SOURCE_DIR ${THIRD_PARTY_DIRS}/raptor2-2.0.15)
set(RAPTOR_BINARY_DIR ${RAPTOR_SOURCE_DIR}/build)
set(RAPTOR_INSTALL_PREFIX ${RAPTOR_SOURCE_DIR}/install_dir)
set(RAPTOR_LIB_DIR "${RAPTOR_INSTALL_PREFIX}/lib")

set(RASQAL_SOURCE_DIR ${THIRD_PARTY_DIRS}/rasqal-0.9.33)
set(RASQAL_BINARY_DIR ${RASQAL_SOURCE_DIR}/build)
set(RASQAL_INSTALL_PREFIX ${RASQAL_SOURCE_DIR}/install_dir)
set(RASQAL_LIB_DIR "${RASQAL_INSTALL_PREFIX}/lib")

set(LIBRDF_SOURCE_DIR ${THIRD_PARTY_DIRS}/redland-1.0.17)
set(LIBRDF_BINARY_DIR ${LIBRDF_SOURCE_DIR}/build)
set(LIBRDF_INSTALL_PREFIX ${LIBRDF_SOURCE_DIR}/install_dir)
set(LIBRDF_LIB_DIR "${LIBRDF_INSTALL_PREFIX}/lib")

#################################################################
# Superbuild magic
#

if (NOT HAVE_DEPENDENCIES)
message(STATUS "DOING SUPERBUILD")
    project(libsemsim-superbuild)
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/superbuild.cmake)
    return() # stop after processing superbuild.cmake
else ()
message(STATUS "BUILDING LIBSEMSIM")
    project(libsemsim LANGUAGES CXX VERSION 0.1.1)
endif ()


#############################################
# add semsim and tests

add_subdirectory(semsim)

enable_testing()
add_subdirectory(tests)
add_subdirectory(${GOOGLETEST_SOURCE})



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
    Installation prefix:        ${CMAKE_INSTALL_PREFIX}
    Options:
        SBML support              ${ENABLE_SBML_SUPPORT}
        CellML suppert            ${ENABLE_CELLML_SUPPORT}
        Tests (requires Catch)    ${ENABLE_TESTS}
        Python bindings           ${BUILD_PYTHON}
        Python interpreter        ${Python_EXECUTABLE}
        Python include directory  ${PYTHON_INCLUDE_PATH}
        Generate documentation    ${BUILD_DOCS}
    Paths:
        Cygwin specific paths
            CYG_ROOT              ${CYG_ROOT}
            CYG_LIB_DIR           ${CYG_LIB_DIR}
            CYG_BIN_DIR           ${CYG_BIN_DIR}
            CYG_INCLUDE_DIR       ${CYG_INCLUDE_DIR}
        libsbml dependencies
            LIBSBML_DEPS_INCLUDE_DIR           ${LIBSBML_DEPS_INCLUDE_DIR}
            LIBSBML_DEPS_LIB_DIR               ${LIBSBML_DEPS_LIB_DIR}
        bzlib
            LIBBZ_INCLUDE_DIR                  ${LIBBZ_INCLUDE_DIR}
            LIBBZ_STATIC_LIBRARY               ${LIBBZ_STATIC_LIBRARY}
        zlib
            ZLIB_INCLUDE_DIR                   ${ZLIB_INCLUDE_DIR}
            ZLIB_STATIC_LIBRARY                ${ZLIB_STATIC_LIBRARY}
        zipper
            ZIPPER_INCLUDE_DIR                 ${ZIPPER_INCLUDE_DIR}
            ZIPPER_STATIC_LIBRARY              ${ZIPPER_STATIC_LIBRARY}
        libxml2
            LIBXML2_INCLUDE_DIR                ${LIBXML2_INCLUDE_DIR}
            LIBXML2_STATIC_LIBRARY             ${LIBXML2_STATIC_LIBRARY}
        libsbml
            LIBSBML_INCLUDE_DIR                ${LIBSBML_INCLUDE_DIR}
            LIBSBML_STATIC_LIBRARY             ${LIBSBML_STATIC_LIBRARY}
        libcombine
            LIBCOMBINE_INCLUDE_DIR             ${LIBCOMBINE_INCLUDE_DIR}
            LIBCOMBINE_LIBRARY                 ${LIBCOMBINE_LIBRARY}
            LIBCOMBINE_STATIC_LIB              ${LIBCOMBINE_STATIC_LIB}
        Redland libraries
            REDLAND_ROOT                       ${REDLAND_ROOT}
            raptor
                RAPTOR2_INCLUDE_DIR            ${RAPTOR2_INCLUDE_DIR}
                RAPTOR2_STATIC_LIBRARY         ${RAPTOR2_STATIC_LIBRARY}
            rasqal
                RASQAL_INCLUDE_DIR             ${RASQAL_INCLUDE_DIR}
                RASQAL_STATIC_LIBRARY          ${RASQAL_STATIC_LIBRARY}
            librdf
                REDLAND_INCLUDE_DIR             ${REDLAND_INCLUDE_DIR}
                REDLAND_STATIC_LIBRARY          ${REDLAND_STATIC_LIBRARY}
        googletest
            GOOGLETEST_SOURCE                  ${GOOGLETEST_SOURCE}
    ")