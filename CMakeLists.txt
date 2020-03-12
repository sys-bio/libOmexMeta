cmake_minimum_required(VERSION 3.14.0)

cmake_policy(SET CMP0003 NEW) # useless
cmake_policy(SET CMP0028 NEW) # double-colon
cmake_policy(SET CMP0042 NEW) # macos rpath
cmake_policy(SET CMP0048 NEW) # can set project version
cmake_policy(SET CMP0060 NEW) # useless
cmake_policy(SET CMP0078 NEW) # used to set target name for swig
cmake_policy(SET CMP0086 NEW) # pass -module flag to swig

project(libsemgen LANGUAGES CXX VERSION 0.1.0)

# modules

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

# global settings

set(SEMSIM_CXX_STANDARD 11 CACHE STRING "The C++ standard to use (11 or 98)")
if ("${CMAKE_SYSTEM_NAME}" MATCHES "Linux" OR "${CMAKE_SYSTEM_NAME}" MATCHES "Darwin")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++${SEMSIM_CXX_STANDARD} -Wall -Wextra -fPIC")
endif ()

set(CMAKE_CXX_STANDARD ${SEMSIM_CXX_STANDARD})
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_compile_definitions(SEMSIM_INTERNAL_BUILD)
# https://gitlab.kitware.com/cmake/cmake/issues/16589
set(CMAKE_MACOSX_RPATH ON)

SET(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/third_party)

# ensure correct shared lib suffIx for this platform
if (CYGWIN)
#    set(CMAKE_SHARED_LIBRARY_SUFFIX "dll.a")
#    set(CMAKE_STATIC_LIBRARY_SUFFIX  "a")
#    set(CMAKE_SHARED_LIBRARY_PREFIX  "lib") # change default from "cyg"

    set(CYG_ROOT C:/cygwin64 CACHE PATH "absolute path to cygwin root installation")
    set(CYG_LIB_DIR ${CYG_ROOT}/lib)
    set(CYG_BIN_DIR ${CYG_ROOT}/bin)
    set(CYG_INCLUDE_DIR ${CYG_ROOT}/usr/include)
endif ()

# variables for building semsim dependencies
set(THIRD_PARTY_DIRS ${CMAKE_SOURCE_DIR}/third_party)

set(LIBSBML_DEPS_SOURCE_DIR ${THIRD_PARTY_DIRS}/libsbml-dependencies)
set(LIBSBML_DEPS_BINARY_DIR ${THIRD_PARTY_DIRS}/libsbml-dependencies/build)
set(LIBSBML_DEPS_INSTALL_PREFIX ${LIBSBML_DEPS_SOURCE_DIR}/INSTALL)
set(LIBSBML_DEPS_INCLUDE_DIR ${LIBSBML_DEPS_INSTALL_PREFIX}/include)
set(LIBSBML_DEPS_LIB_DIR ${LIBSBML_DEPS_INSTALL_PREFIX}/lib)

set(LIBSBML_SOURCE_DIR ${THIRD_PARTY_DIRS}/libsbml)
set(LIBSBML_BINARY_DIR ${LIBSBML_SOURCE_DIR}/build)
set(LIBSBML_INSTALL_PREFIX ${LIBSBML_SOURCE_DIR}/INSTALL)
set(LIBSBML_INCLUDE_DIR "${LIBSBML_INSTALL_PREFIX}/include")
set(LIBSBML_LIB_DIR "${LIBSBML_INSTALL_PREFIX}/lib")
set(LIBSBML_LIB "${LIBSBML_LIB_DIR}/libsbml.dll.a")
set(LIBSBML_STATIC_LIB "${LIBSBML_LIB_DIR}/libsbml-static.a")

#set(ZLIB_SOURCE_DIR ${THIRD_PARTY_DIRS}/zlib)
#set(ZLIB_BINARY_DIR ${ZLIB_SOURCE_DIR}/build)
#set(ZLIB_INSTALL_PREFIX ${ZLIB_SOURCE_DIR}/INSTALL)
#set(ZLIB_INCLUDE_DIR "${ZLIB_INSTALL_PREFIX}/include")
#set(ZLIB_LIB_DIR "${ZLIB_INSTALL_PREFIX}/lib")
#set(ZLIB_LIB "${ZLIB_LIB_DIR}/libZipper-static${CMAKE_STATIC_LIBRARY_PREFIX}")

set(ZIPPER_SOURCE_DIR ${THIRD_PARTY_DIRS}/zipper)
set(ZIPPER_BINARY_DIR ${ZIPPER_SOURCE_DIR}/build)
set(ZIPPER_INSTALL_PREFIX ${ZIPPER_SOURCE_DIR}/INSTALL)
set(ZIPPER_INCLUDE_DIR "${ZIPPER_INSTALL_PREFIX}/include")
set(ZIPPER_LIB_DIR "${ZIPPER_INSTALL_PREFIX}/lib")
set(ZIPPER_LIB "${ZIPPER_LIB_DIR}/libZipper-static.a")

set(LIBCOMBINE_SOURCE_DIR ${THIRD_PARTY_DIRS}/libCombine)
set(LIBCOMBINE_BINARY_DIR ${LIBCOMBINE_SOURCE_DIR}/build)
set(LIBCOMBINE_INSTALL_PREFIX ${LIBCOMBINE_SOURCE_DIR}/INSTALL)
set(LIBCOMBINE_INCLUDE_DIR "${LIBCOMBINE_INSTALL_PREFIX}/include")
set(LIBCOMBINE_LIB_DIR "${LIBCOMBINE_INSTALL_PREFIX}/lib")
set(LIBCOMBINE_LIB "${LIBCOMBINE_LIB_DIR}/libCombine${CMAKE_SHARED_LIBRARY_SUFFIX}")
set(LIBCOMBINE_STATIC_LIB "${LIBCOMBINE_LIB_DIR}/libCombine-static${CMAKE_STATIC_LIBRARY_SUFFIX}")

set(CATCH2_SOURCE_DIR ${THIRD_PARTY_DIRS}/Catch2)
set(CATCH2_BINARY_DIR ${CATCH2_SOURCE_DIR}/build)
set(CATCH2_INSTALL_PREFIX ${CATCH2_SOURCE_DIR}/INSTALL)
set(CATCH2_INCLUDE_DIR "${CATCH2_INSTALL_PREFIX}/include")
set(CATCH2_LIB_DIR "${CATCH2_INSTALL_PREFIX}/lib")
set(CATCH2_LIB "${CATCH2_LIB_DIR}/Catch2${CMAKE_SHARED_LIBRARY_SUFFIX}")
#set(CATCH2_LIB "${CATCH2_LIB_DIR}/Catch2-static${CMAKE_STATIC_LIBRARY_SUFFIX}")

set(RAPTOR2_SOURCE_DIR ${THIRD_PARTY_DIRS}/raptor)
set(RAPTOR2_BINARY_DIR ${RAPTOR2_SOURCE_DIR}/build)
set(RAPTOR2_INSTALL_PREFIX ${RAPTOR2_SOURCE_DIR}/INSTALL)
set(RAPTOR2_INCLUDE_DIR "${RAPTOR2_INSTALL_PREFIX}/include")
set(RAPTOR2_LIB_DIR "${RAPTOR2_INSTALL_PREFIX}/lib")
#set(RAPTOR2_LIB "${RAPTOR2_LIB_DIR}/raptor${CMAKE_SHARED_LIBRARY_SUFFIX}")
#set(RAPTOR2_LIB "${RAPTOR2_LIB_DIR}/raptor-static${CMAKE_STATIC_LIBRARY_SUFFIX}")

set(RASQAL_SOURCE_DIR ${THIRD_PARTY_DIRS}/rasqal)
set(RASQAL_BINARY_DIR ${RASQAL_SOURCE_DIR}/build)
set(RASQAL_INSTALL_PREFIX ${RASQAL_SOURCE_DIR}/INSTALL)
set(RASQAL_INCLUDE_DIR "${RASQAL_INSTALL_PREFIX}/include")
set(RASQAL_LIB_DIR "${RASQAL_INSTALL_PREFIX}/lib")
#set(RASQAL_LIB "${RASQAL_LIB_DIR}/libCombine-static${CMAKE_SHARED_LIBRARY_SUFFIX}")


set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/INSTALL/${CMAKE_BUILD_TYPE}")


include(ExternalProject)



################################################################
# add the third party directory to build the dependencies
add_subdirectory(third_party)

################################################################
# get handle to dependency libraries
find_library(ZLIB_LIBRARY
        NAMES zlib-static zlib libzlib-static libzlib
        PATHS /usr/lib /usr/local/lib ${CYG_LIB_DIR}
        ${CMAKE_OSX_SYSROOT}/usr/lib
        ${LIBSBML_DEPS_INSTALL_PREFIX}/lib
        DOC "The file name of the ZIPPER library."
        REQUIRED
        DEPENDS
        libsbml-dependencies
        )
if (NOT ${ZLIB_LIBRARY_FOUND})
    message(FATAL_ERROR "ZLIB library not found")
endif ()
set(LIBZ_LIBRARY ${ZLIB_LIBRARY})

find_library(ZIPPER_LIBRARY
        NAMES Zipper-static Zipper libZipper-static libZipper
        PATHS /usr/lib /usr/local/lib ${ZIPPER_LIB_DIR}
        ${CMAKE_OSX_SYSROOT}/usr/lib
        DOC "The file name of the ZIPPER library."
        REQUIRED
        )


find_library(ICONV_LIB
        NAMES iconv libiconv
        PATHS /usr/lib /usr/local/lib ${CYG_LIB_DIR}
        ${CMAKE_OSX_SYSROOT}/usr/lib
        DOC "The file name of the ICONV library."
        REQUIRED
        )
message(STATUS "ICONV_LIB ${ICONV_LIB}")

find_library(LIBXML2_LIBRARY
        NAMES libxml2 xml2
        PATHS
#        /usr/lib /usr/local/lib
        ${LIBSBML_DEPS_INSTALL_PREFIX}/lib
        ${CMAKE_OSX_SYSROOT}/usr/lib
        NO_DEFAULT_PATH
        REQUIRED
        )
MESSAGE(STATUS "LIBSBML_DEPS_INSTALL_PREFIX ${CMAKE_STATIC_LIBRARY_PREFIX} ")
MESSAGE(STATUS "LIBSBML_DEPS_INSTALL_PREFIX ${LIBSBML_DEPS_INSTALL_PREFIX}")
MESSAGE(STATUS "LIBXML2_LIBRARY ${LIBXML2_LIBRARY}")

MESSAGE(STATUS "LIBSBML_INCLUDE_DIR ${LIBSBML_INCLUDE_DIR}")
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${LIBCOMBINE_INCLUDE_DIR})
include_directories(${LIBSBML_INCLUDE_DIR})
include_directories(${ZIPPER_INCLUDE_DIR})
include_directories(${CYG_INCLUDE_DIR}/raptor2)
include_directories(${CYG_INCLUDE_DIR}/rasqal)
#
#find_library(LIBSBML
#        NAMES Zipper-static Zipper libZipper-static libZipper
#        PATHS /usr/lib /usr/local/lib ${ZIPPER_LIB_DIR}
#        ${CMAKE_OSX_SYSROOT}/usr/lib
#        DOC "The file name of the ZIPPER library."
#        REQUIRED
#        )
#
#if (NOT ${ZIPPER_LIBRARY_FOUND})
#    message(FATAL_ERROR "zipper library not found")
#endif ()

#find_library(RAPTOR2_LIBRARY
#        NAMES libraptor2 raptor2 libraptor2-static raptor2-static
#        PATHS /usr/lib /usr/local/lib ${CYG_LIB_DIR}
#        ${CMAKE_OSX_SYSROOT}/usr/lib
#        DOC "The file name of the raptor2 library."
#        REQUIRED
#        )
#
#find_library(RASQAL_LIBRARY
#        NAMES librasqal librasqal-static rasqal rasqal-static
#        PATHS /usr/lib /usr/local/lib ${CYG_LIB_DIR}
#        ${CMAKE_OSX_SYSROOT}/usr/lib
#        DOC "The file name of the rasqal library."
#        REQUIRED
#        )
#
#
##set(LIBSBML_DEPS_INCLUDE_DIR "${LIBSBML_DEPS_INSTALL_PREFIX}/include")
##set(LIBSBML_DEPS_LIB_DIR "${LIBSBML_DEPS_INSTALL_PREFIX}/lib")
##set(LIBSBML_DEPS_LIB "${LIBSBML_DEPS_LIB_DIR}/libsbml.${CMAKE_SHARED_LIBRARY_SUFFIX}")
#
#
##find_package(combine PATHS C:/cygwin64/usr/local/lib/cmake REQUIRED)
##find_package(Catch2 PATHS C:/cygwin64/usr/local/lib/cmake/Catch2)
#find_package(SWIG)
#
#
#MESSAGE(STATUS "
#
#CYGWIN variables:
#
#    CYG_ROOT            ${CYG_ROOT}
#    CYG_LIB_DIR         ${CYG_LIB_DIR}
#    CYG_BIN_DIR         ${CYG_BIN_DIR}
#    CYG_INCLUDE_DIR     ${CYG_INCLUDE_DIR}
#
#Variables for building submodule dependencies:
#
#    LIBSBML_DEPS_SOURCE_DIR         ${LIBSBML_DEPS_SOURCE_DIR}
#    LIBSBML_DEPS_BINARY_DIR         ${LIBSBML_DEPS_BINARY_DIR}
#    LIBSBML_DEPS_INSTALL_PREFIX        ${LIBSBML_DEPS_INSTALL_PREFIX}
#
#    LIBSBML_SOURCE_DIR              ${LIBSBML_SOURCE_DIR}
#    LIBSBML_BINARY_DIR              ${LIBSBML_BINARY_DIR}
#    LIBSBML_INSTALL_PREFIX             ${LIBSBML_INSTALL_PREFIX}
#
#    ZIPPER_SOURCE_DIR               ${ZIPPER_SOURCE_DIR}
#    ZIPPER_BINARY_DIR               ${ZIPPER_BINARY_DIR}
#    ZIPPER_INSTALL_PREFIX              ${ZIPPER_INSTALL_PREFIX}
#
#    LIBCOMBINE_SOURCE_DIR           ${LIBCOMBINE_SOURCE_DIR}
#    LIBCOMBINE_BINARY_DIR           ${LIBCOMBINE_BINARY_DIR}
#    LIBCOMBINE_INSTALL_PREFIX          ${LIBCOMBINE_INSTALL_PREFIX}
#
#    CATCH2_SOURCE_DIR               ${CATCH2_SOURCE_DIR}
#    CATCH2_BINARY_DIR               ${CATCH2_BINARY_DIR}
#    CATCH2_INSTALL_PREFIX              ${CATCH2_INSTALL_PREFIX}
#
#Variables for building libsemsim:
#
#    ZIPPER_LIBRARY                  ${ZIPPER_LIBRARY}
#    RAPTOR2_LIBRARY                 ${RAPTOR2_LIBRARY}
#    RASQAL_LIBRARY                  ${RASQAL_LIBRARY}
#")
#
#
#find_package(Python COMPONENTS Interpreter Development)
## check the Python version
#if (Python_VERSION_MAJOR EQUAL 3 AND Python_VERSION_MINOR LESS 4)
#    message(SEND_ERROR "Supported Python versions are 2.7 and >= 3.4. You have ${Python_VERSION}.")
#elseif (Python_VERSION_MAJOR EQUAL 2 AND Python_VERSION_MINOR LESS 7)
#    message(SEND_ERROR "Supported Python versions are 2.7 and >= 3.4. You have ${Python_VERSION}.")
#elseif (Python_VERSION_MAJOR EQUAL 1)
#    message(SEND_ERROR "Supported Python versions are 2.7 and >= 3.4. You have ${Python_VERSION}.")
#endif ()
#
#find_package(Doxygen)
#
## consider using https://cpp-netlib.org/ if networking is required (also handles URIs)
## otherwise consider adding https://github.com/uriparser/uriparser for uri handling
#
## build options (some defaults are automatically configured)
#set(ENABLE_STATIC_LIB TRUE CACHE BOOL "Build static libraries?")
#set(ENABLE_SHARED_LIB TRUE CACHE BOOL "Build shared libraries?")
#option(ENABLE_SBML_SUPPORT "Enable support for SBML models" ${libSBML_FOUND})
#option(ENABLE_CELLML_SUPPORT "Enable support for CellML models" ${LIBCELLML_FOUND})
#option(ENABLE_TESTS "Enable tests" ${Catch2_FOUND})
#option(BUILD_DOCS "Build the documentation (requires Doxygen)" ${Doxygen_FOUND})
#option(ENABLE_EXAMPLES "Build example programs" ON)
## bindings
#if (${SWIG_FOUND} AND ${PYTHON_FOUND})
#    option(BUILD_PYTHON "Build Python SWIG module" ON)
#else ()
#    option(BUILD_PYTHON "Build Python SWIG module" OFF)
#endif ()
#
## diagnostics
##get_target_property(LIBCOMBINE_LIBS libCombine-static LOCATION)
##get_target_property(LIBCOMBINE_INCLUDE_DIRS libCombine-static INTERFACE_INCLUDE_DIRECTORIES)
#
#if (cellml_FOUND)
#    get_target_property(LIBCELLML_LIBS cellml LOCATION)
#    get_target_property(LIBCELLML_INCLUDE_DIRS cellml INTERFACE_INCLUDE_DIRECTORIES)
#else ()
#    set(LIBCELLML_LIBS "")
#    set(LIBCELLML_INCLUDE_DIRS "")
#endif ()
#
#if (Catch2_FOUND)
#    get_target_property(CATCH2_INCLUDE_DIRS Catch2::Catch2 INTERFACE_INCLUDE_DIRECTORIES)
#else ()
#    set(CATCH2_INCLUDE_DIRS "")
#endif ()
#
#message(STATUS "
##-------------------------------------------------------------------------------
##Configuration Summary
##-------------------------------------------------------------------------------
#
#    Configured on host $ENV{COMPUTERNAME} ${HOSTNAME}
#      host OS                   ${CMAKE_SYSTEM_NAME}
#      host architecture         ${CMAKE_SYSTEM_PROCESSOR}
#
#    General flags:
#      CC                        ${CMAKE_C_COMPILER}
#      CXX                       ${CMAKE_CXX_COMPILER}
#      CPPFLAGS                  ${BUILD_DEFINITIONS}
#      CFLAGS                    ${CMAKE_C_FLAGS}
#      CXXFLAGS                  ${CMAKE_CXX_FLAGS}
#      LDFLAGS                   ${CMAKE_EXE_LINKER_FLAGS}
#
#    Installation prefix:        ${CMAKE_INSTALL_PREFIX}
#
#    Options:
#      SBML support              ${ENABLE_SBML_SUPPORT}
#      CellML suppert            ${ENABLE_CELLML_SUPPORT}
#      Tests (requires Catch)    ${ENABLE_TESTS}
#      Python bindings           ${BUILD_PYTHON}
#      Python interpreter        ${Python_EXECUTABLE}
#      Python include directory  ${PYTHON_INCLUDE_PATH}
#      Generate documentation    ${BUILD_DOCS}
#
#
#    "
#        )
#

#
#
#add_subdirectory(semsim)
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
