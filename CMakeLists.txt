# todo explore: https://stackoverflow.com/questions/16799164/compiling-a-library-redland-in-cygwin-using-gcc-and-using-the-output-in-visual/48428588#48428588
cmake_minimum_required(VERSION 3.15)

cmake_policy(SET CMP0003 NEW) # useless
cmake_policy(SET CMP0028 NEW) # double-colon
cmake_policy(SET CMP0042 NEW) # macos rpath
cmake_policy(SET CMP0048 NEW) # can set project version
cmake_policy(SET CMP0060 NEW) # useless
cmake_policy(SET CMP0078 NEW) # used to set target name for swig
cmake_policy(SET CMP0086 NEW) # pass -module flag to swig

project(libsemgen LANGUAGES CXX VERSION 0.1.0)
include(ExternalProject)

# modules

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

# global settings

set(SEMSIM_CXX_STANDARD 11 CACHE STRING "The C++ standard to use (11 or 98)")
if ("${CMAKE_SYSTEM_NAME}" MATCHES "Linux" OR "${CMAKE_SYSTEM_NAME}" MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif ()

set(CMAKE_CXX_STANDARD ${SEMSIM_CXX_STANDARD})
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_compile_definitions(SEMSIM_INTERNAL_BUILD)
# https://gitlab.kitware.com/cmake/cmake/issues/16589
set(CMAKE_MACOSX_RPATH ON)

SET(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/third_party)

if (CYGWIN)
    set(CYG_ROOT C:/cygwin64 CACHE PATH "absolute path to cygwin root installation")
    set(CYG_LIB_DIR ${CYG_ROOT}/lib)
    set(CYG_BIN_DIR ${CYG_ROOT}/bin)
    set(CYG_INCLUDE_DIR ${CYG_ROOT}/usr/include)
endif ()

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/INSTALL/${CMAKE_BUILD_TYPE}")

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

set(LIBSBML_SOURCE_DIR ${THIRD_PARTY_DIRS}/libsbml)
set(LIBSBML_BINARY_DIR ${LIBSBML_SOURCE_DIR}/build)
set(LIBSBML_INSTALL_PREFIX ${LIBSBML_SOURCE_DIR}/INSTALL)

set(ZIPPER_SOURCE_DIR ${THIRD_PARTY_DIRS}/zipper)
set(ZIPPER_BINARY_DIR ${ZIPPER_SOURCE_DIR}/build)
set(ZIPPER_INSTALL_PREFIX ${ZIPPER_SOURCE_DIR}/INSTALL)
set(ZIPPER_LIB_DIR "${ZIPPER_INSTALL_PREFIX}/lib")

set(LIBCOMBINE_SOURCE_DIR ${THIRD_PARTY_DIRS}/libCombine)
set(LIBCOMBINE_BINARY_DIR ${LIBCOMBINE_SOURCE_DIR}/build)
set(LIBCOMBINE_INSTALL_PREFIX ${LIBCOMBINE_SOURCE_DIR}/INSTALL)
set(LIBCOMBINE_LIB_DIR "${LIBCOMBINE_INSTALL_PREFIX}/lib")

#######################################################################
#   Build third party libs
#

# build libsbml-dependencies, which itself has no dependencies
ExternalProject_Add(libsbml-dependencies
        SOURCE_DIR ${LIBSBML_DEPS_SOURCE_DIR}
        BINARY_DIR ${LIBSBML_DEPS_BINARY_DIR}
        CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${LIBSBML_DEPS_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        )

# find zlib to give to zipper which depends on it
find_library(ZLIB_STATIC_LIBRARY
        NAMES zlib.a libzlib.a zlib.dll libzlib.dll
        PATHS ${LIBSBML_DEPS_LIB_DIR}
        REQUIRED
        )

find_path(ZLIB_INCLUDE_DIR
        NAMES zlib/zlib.h
        PATHS ${LIBSBML_DEPS_INCLUDE_DIR}
        REQUIRED
        )

# build zipper
ExternalProject_Add(zipper
        SOURCE_DIR ${ZIPPER_SOURCE_DIR}
        BINARY_DIR ${ZIPPER_BINARY_DIR}
        #        DEPENDS zlib
        CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX=${ZIPPER_INSTALL_PREFIX}
        -DLIBSBML_DEPS_INSTALL_PREFIX=${LIBSBML_DEPS_INSTALL_PREFIX}
        -DZLIB_LIBRARY=${ZLIB_STATIC_LIBRARY}
        -DZLIB_INCLUDE_DIR=${ZLIB_INCLUDE_DIR}
        )

# find zipper lib and include dirs
find_library(ZIPPER_STATIC_LIBRARY
        NAMES libZipper-static.a libZipper-static
        PATHS ${ZIPPER_INSTALL_PREFIX}/lib
        )
find_path(ZIPPER_INCLUDE_DIR
        NAMES zipper/zipper.h
        PATHS ${ZIPPER_INSTALL_PREFIX}/include
        )

# find bz library and include dirs
find_library(LIBBZ_STATIC_LIBRARY
        NAMES libbz2.a
        PATHS ${LIBSBML_DEPS_LIB_DIR}
        )
find_path(LIBBZ_INCLUDE_DIR
        NAMES bzip2/bzlib.h
        PATHS ${LIBSBML_DEPS_INCLUDE_DIR}
        )

# get libxml2 libraries
find_library(LIBXML2_STATIC_LIBRARY
        NAMES libxml2.a
        )

find_path(LIBXML2_INCLUDE_DIR
        NAMES libxml/parser.h
        PATHS /usr/local/include/libxml2
        )

# build libsbml
ExternalProject_Add(libsbml
        SOURCE_DIR ${LIBSBML_SOURCE_DIR}
        BINARY_DIR ${LIBSBML_BINARY_DIR}
        DEPENDS libsbml-dependencies
        CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX=${LIBSBML_INSTALL_PREFIX}
        -WITH_LIBXML=ON
        -DENABLE_LAYOUT=ON
        #todo despite there being logic for handling the libsbml namespace
        #   it looks as though there is a namespace clash between libsbml::model
        #   and libsemsim::model when namespaces for libsbml are set to OFF.
        #todo Double check the truth of this and rectify.
        -DWITH_CPP_NAMESPACE=ON
        -DLIBSBML_DEPENDENCY_DIR=${LIBSBML_DEPS_INSTALL_PREFIX}
        )

# find the libsbml library and include dire
find_library(LIBSBML_STATIC_LIBRARY
        NAMES libsbml-static.a libsbml-static.lib
        PATHS ${LIBSBML_INSTALL_PREFIX}/lib
        REQUIRED
        )

find_path(LIBSBML_INCLUDE_DIR
        NAMES SBMLTypes.h
        PATHS ${LIBSBML_INSTALL_PREFIX}/include/sbml
        REQUIRED
        )

# build libcombine
ExternalProject_Add(libCombine
        SOURCE_DIR ${LIBCOMBINE_SOURCE_DIR}
        BINARY_DIR ${LIBCOMBINE_BINARY_DIR}
        DEPENDS
        zipper libsbml
        LIST_SEPARATOR | # for EXTRA_LIBS argument
        CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX=${LIBCOMBINE_INSTALL_PREFIX}
        -DZIPPER_INSTALL_PREFIX=${ZIPPER_INSTALL_PREFIX}
        -DLIBSBML_DEPS_INSTALL_PREFIX=${LIBSBML_DEPS_INSTALL_PREFIX}
        -DLIBSBML_INSTALL_PREFIX=${LIBSBML_INSTALL_PREFIX}
        -DEXTRA_LIBS=${LIBBZ_STATIC_LIBRARY}|${ZLIB_STATIC_LIBRARY}|xml2 # works on linux, will need changing on windows
        )
find_library(LIBCOMBINE_STATIC_LIB
        NAMES libcombine-static.a
        PATHS ${LIBCOMBINE_INSTALL_PREFIX}/lib
        )
find_path(LIBCOMBINE_INCLUDE_DIR
        NAMES combine/combinearchive.h
        PATHS ${LIBCOMBINE_INSTALL_PREFIX}/include
        )

##################################################
# get redland libraries for linking
#

set(REDLAND_ROOT "/home/ciaran/Software/redland" CACHE PATH "A directory containing the redland libraries, raptor2, rasqal and redland")
set(RAPTOR2_INSTALL_PREFIX ${REDLAND_ROOT}/raptor2-2.0.15/install)
set(RASQAL_INSTALL_PREFIX ${REDLAND_ROOT}/rasqal-0.9.33/install)
set(REDLAND_INSTALL_PREFIX ${REDLAND_ROOT}/redland-1.0.17/install)

# check we have the redland libraries
if (NOT EXISTS ${RAPTOR2_INSTALL_PREFIX})
    MESSAGE(FATAL_ERROR "RAPTOR2_INSTALL_PREFIX ${RAPTOR2_INSTALL_PREFIX} does not exist")
endif ()
if (NOT EXISTS ${RASQAL_INSTALL_PREFIX})
    MESSAGE(FATAL_ERROR "RASQAL_INSTALL_PREFIX ${RASQAL_INSTALL_PREFIX} does not exist")
endif ()
if (NOT EXISTS ${REDLAND_INSTALL_PREFIX})
    MESSAGE(FATAL_ERROR "REDLAND_INSTALL_PREFIX ${REDLAND_INSTALL_PREFIX} does not exist")
endif ()

# raptor2
find_library(RAPTOR2_STATIC_LIBRARY
        NAMES libraptor2.a raptor2.a
        PATHS ${RAPTOR2_INSTALL_PREFIX}/lib
        )

find_path(RAPTOR2_INCLUDE_DIR
        NAMES raptor2.h
        PATHS ${RAPTOR2_INSTALL_PREFIX}/include/raptor2
        )

# rasqal
find_library(RASQAL_STATIC_LIBRARY
        NAMES librasqal.a rasqal.a
        PATHS ${RASQAL_INSTALL_PREFIX}/lib
        )

find_path(RASQAL_INCLUDE_DIR
        NAMES rasqal.h
        PATHS ${RASQAL_INSTALL_PREFIX}/include/rasqal
        NO_DEFAULT_PATH
        )

# redland api
find_library(REDLAND_STATIC_LIBRARY
        NAMES librdf.a rdf.a
        PATHS ${REDLAND_INSTALL_PREFIX}/lib
        )

find_path(REDLAND_INCLUDE_DIR
        NAMES librdf.h
        PATHS ${REDLAND_INSTALL_PREFIX}/include
        )


##find_package(SWIG)
##find_package(Python COMPONENTS Interpreter Development)
### check the Python version
##if (Python_VERSION_MAJOR EQUAL 3 AND Python_VERSION_MINOR LESS 4)
##    message(SEND_ERROR "Supported Python versions are 2.7 and >= 3.4. You have ${Python_VERSION}.")
##elseif (Python_VERSION_MAJOR EQUAL 2 AND Python_VERSION_MINOR LESS 7)
##    message(SEND_ERROR "Supported Python versions are 2.7 and >= 3.4. You have ${Python_VERSION}.")
##elseif (Python_VERSION_MAJOR EQUAL 1)
##    message(SEND_ERROR "Supported Python versions are 2.7 and >= 3.4. You have ${Python_VERSION}.")
##endif ()
##
##find_package(Doxygen)
##
### consider using https://cpp-netlib.org/ if networking is required (also handles URIs)
### otherwise consider adding https://github.com/uriparser/uriparser for uri handling
##
### build options (some defaults are automatically configured)
##set(ENABLE_STATIC_LIB TRUE CACHE BOOL "Build static libraries?")
##set(ENABLE_SHARED_LIB TRUE CACHE BOOL "Build shared libraries?")
##option(ENABLE_SBML_SUPPORT "Enable support for SBML models" ${libSBML_FOUND})
##option(ENABLE_CELLML_SUPPORT "Enable support for CellML models" ${LIBCELLML_FOUND})
##option(ENABLE_TESTS "Enable tests" ${Catch2_FOUND})
##option(BUILD_DOCS "Build the documentation (requires Doxygen)" ${Doxygen_FOUND})
##option(ENABLE_EXAMPLES "Build example programs" ON)
### bindings
##if (${SWIG_FOUND} AND ${PYTHON_FOUND})
##    option(BUILD_PYTHON "Build Python SWIG module" ON)
##else ()
##    option(BUILD_PYTHON "Build Python SWIG module" OFF)
##endif ()
#
## diagnostics
##get_target_property(LIBCOMBINE_LIBS libCombine-static LOCATION)
##get_target_property(LIBCOMBINE_INCLUDE_DIRS libCombine-static INTERFACE_INCLUDE_DIRECTORIES)
##
##if (cellml_FOUND)
##    get_target_property(LIBCELLML_LIBS cellml LOCATION)
##    get_target_property(LIBCELLML_INCLUDE_DIRS cellml INTERFACE_INCLUDE_DIRECTORIES)
##else ()
##    set(LIBCELLML_LIBS "")
##    set(LIBCELLML_INCLUDE_DIRS "")
##endif ()
##
##if (Catch2_FOUND)
##    get_target_property(CATCH2_INCLUDE_DIRS Catch2::Catch2 INTERFACE_INCLUDE_DIRECTORIES)
##else ()
##    set(CATCH2_INCLUDE_DIRS "")
##endif ()
#
#find_package(LibXml2 )
#
#
add_subdirectory(semsim)
#add_subdirectory(tests)
#add_subdirectory(${GOOGLETEST_SOURCE})
#
#
## Recurse into subdirectories for each wrapper language if specified
##if (BUILD_PYTHON)
##    if (NOT (${SEMSIM_CXX_STANDARD} EQUAL 11))
##        message(SEND_ERROR "Python bindings require C++11 to be used")
##    endif ()
##    if (Python_FOUND)
##        include_directories(${PYTHON_INCLUDE_PATH})
##        add_subdirectory(swig/python)
##    else ()
##        message(SEND_ERROR "BUILD_PYTHON is enabled but a suitable Python runtime environment was not found")
##    endif ()
##endif ()
##
##if (BUILD_DOCS)
##    if (Doxygen_FOUND)
##        add_subdirectory(docs)
##    else ()
##        message(SEND_ERROR "BUILD_DOCS was specified but Doxygen was not found")
##    endif ()
##endif ()
##
##if (ENABLE_TESTS)
##    include(CTest)
##    enable_testing()
##    add_subdirectory(tests)
##endif ()
##
##if (ENABLE_EXAMPLES)
##    add_subdirectory(examples)
##endif ()
##


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
            LIBBZ_STATIC_LIBRARY                      ${LIBBZ_STATIC_LIBRARY}
            LIBBZ_INCLUDE_DIR                  ${LIBBZ_INCLUDE_DIR}

        zlib
            ZLIB_STATIC_LIBRARY                        ${ZLIB_STATIC_LIBRARY}
            ZLIB_INCLUDE_DIR                    ${ZLIB_INCLUDE_DIR}

        zipper
            ZIPPER_INCLUDE_DIR                 ${ZIPPER_INCLUDE_DIR}
            ZIPPER_STATIC_LIBRARY              ${ZIPPER_STATIC_LIBRARY}

        libxml2
            LIBXML2_STATIC_LIBRARY             ${LIBXML2_STATIC_LIBRARY}
            LIBXML2_INCLUDE_DIR                ${LIBXML2_INCLUDE_DIR}

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
                REDLAND_STATIC_LIBRARY          ${REDLAND_STATIC_LIBRARY}
                REDLAND_INCLUDE_DIR             ${REDLAND_INCLUDE_DIR}

        googletest
            GOOGLETEST_SOURCE                  ${GOOGLETEST_SOURCE}
    ")
