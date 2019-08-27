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
endif()

set(CMAKE_CXX_STANDARD ${SEMSIM_CXX_STANDARD})
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
add_compile_definitions(SEMSIM_INTERNAL_BUILD)
# https://gitlab.kitware.com/cmake/cmake/issues/16589
set(CMAKE_MACOSX_RPATH ON)

# dependencies

find_package(LibXml2 REQUIRED)
find_package(ZLIB    REQUIRED)
find_package(libSBML)
find_package(Raptor2 REQUIRED)
find_package(Rasqal)
find_package(LibRDF)
# https://stackoverflow.com/questions/20746936/cmake-of-what-use-is-find-package-if-you-need-to-specify-cmake-module-path-an?rq=1
find_package(libcellml CONFIG)
find_package(Combine CONFIG REQUIRED)
find_package(SWIG)
find_package(Catch2 CONFIG)

find_package(Python COMPONENTS Interpreter Development)
# check the Python version
if(Python_VERSION_MAJOR EQUAL 3 AND Python_VERSION_MINOR LESS 4)
    message(SEND_ERROR "Supported Python versions are 2.7 and >= 3.4. You have ${Python_VERSION}.")
elseif(Python_VERSION_MAJOR EQUAL 2 AND Python_VERSION_MINOR LESS 7)
  message(SEND_ERROR "Supported Python versions are 2.7 and >= 3.4. You have ${Python_VERSION}.")
elseif(Python_VERSION_MAJOR EQUAL 1)
  message(SEND_ERROR "Supported Python versions are 2.7 and >= 3.4. You have ${Python_VERSION}.")
endif()

find_package(Doxygen)

# consider using https://cpp-netlib.org/ if networking is required (also handles URIs)
# otherwise consider adding https://github.com/uriparser/uriparser for uri handling

# build options (some defaults are automatically configured)
set(ENABLE_STATIC_LIB TRUE CACHE BOOL "Build static libraries?")
set(ENABLE_SHARED_LIB TRUE CACHE BOOL "Build shared libraries?")
option(ENABLE_SBML_SUPPORT "Enable support for SBML models" ${libSBML_FOUND})
option(ENABLE_CELLML_SUPPORT "Enable support for CellML models" ${LIBCELLML_FOUND})
option(ENABLE_TESTS "Enable tests" ${Catch2_FOUND})
option(BUILD_DOCS "Build the documentation (requires Doxygen)" ${Doxygen_FOUND})
option(ENABLE_EXAMPLES "Build example programs" ON)
# bindings
if (${SWIG_FOUND} AND ${PYTHON_FOUND})
  option(BUILD_PYTHON "Build Python SWIG module" ON)
else()
  option(BUILD_PYTHON "Build Python SWIG module" OFF)
endif()

# diagnostics
get_target_property(LIBCOMBINE_LIBS Combine LOCATION)
get_target_property(LIBCOMBINE_INCLUDE_DIRS Combine INTERFACE_INCLUDE_DIRECTORIES)

if (cellml_FOUND)
  get_target_property(LIBCELLML_LIBS cellml LOCATION)
  get_target_property(LIBCELLML_INCLUDE_DIRS cellml INTERFACE_INCLUDE_DIRECTORIES)
else()
  set(LIBCELLML_LIBS "")
  set(LIBCELLML_INCLUDE_DIRS "")
endif()

if (Catch2_FOUND)
  get_target_property(CATCH2_INCLUDE_DIRS Catch2::Catch2 INTERFACE_INCLUDE_DIRECTORIES)
else()
  set(CATCH2_INCLUDE_DIRS "")
endif ()

message(STATUS "
-------------------------------------------------------------------------------
Configuration Summary
-------------------------------------------------------------------------------

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

    Dependencies:
      libxml2 library           ${LIBXML2_LIBRARIES}
      libxml2 include dirs      ${LIBXML2_INCLUDE_DIRS}
      zlib library              ${ZLIB_LIBRARIES}
      zlib include dir          ${ZLIB_INCLUDE_DIRS}
      libSBML library           ${libSBML_LIBRARY}
      libSBML include dir       ${libSBML_INCLUDE_DIRS}
      Raptor library            ${Raptor2_LIBRARIES}
      Raptor include dir        ${Raptor2_INCLUDE_DIRS}
      Rasqal library (optional) ${Rasqal_LIBRARIES}
      Rasqal include dir        ${Rasqal_INCLUDE_DIRS}
      LibRDF library (optional) ${LibRDF_LIBRARIES}
      LibRDF include dir        ${LibRDF_INCLUDE_DIRS}
      libCombine                ${LIBCOMBINE_LIBS}
      libCombine include dir    ${LIBCOMBINE_INCLUDE_DIRS}
      LibCellML                 ${LIBCELLML_LIBS}
      LibCellML include dir     ${LIBCELLML_INCLUDE_DIRS}
      Catch2 include (optional) ${CATCH2_INCLUDE_DIRS}
    "
)

include_directories(${LIBXML2_INCLUDE_DIRS})
include_directories(${ZLIB_INCLUDE_DIRS})
include_directories(${PUGIXML_INCLUDE_DIR})
include_directories(${LIBZIP_INCLUDE_DIR_ZIP})
include_directories(${LIBZIP_INCLUDE_DIR_ZIPCONF})
include_directories(${libSBML_INCLUDE_DIRS})
include_directories(${Raptor2_INCLUDE_DIRS})
include_directories(${Rasqal_INCLUDE_DIRS})
include_directories(${LibRDF_INCLUDE_DIRS})
include_directories(${LIBCOMBINE_INCLUDE_DIRS})
include_directories(.)

add_subdirectory(semsim)

# Recurse into subdirectories for each wrapper language if specified
if(BUILD_PYTHON)
  if (NOT (${SEMSIM_CXX_STANDARD} EQUAL 11))
    message(SEND_ERROR "Python bindings require C++11 to be used")
  endif()
  if (Python_FOUND)
    include_directories(${PYTHON_INCLUDE_PATH})
    add_subdirectory(swig/python)
  else()
    message(SEND_ERROR "BUILD_PYTHON is enabled but a suitable Python runtime environment was not found")
  endif()
endif()

if (BUILD_DOCS)
  if (Doxygen_FOUND)
    add_subdirectory(docs)
  else()
    message(SEND_ERROR "BUILD_DOCS was specified but Doxygen was not found")
  endif()
endif()

if (ENABLE_TESTS)
  include(CTest)
  enable_testing()
  add_subdirectory(tests)
endif()

if (ENABLE_EXAMPLES)
  add_subdirectory(examples)
endif()
