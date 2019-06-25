cmake_minimum_required(VERSION 3.12.0)
project(libsemgen)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

find_package(LibXml2 REQUIRED)
find_package(ZLIB    REQUIRED)
find_package(PugiXML REQUIRED)
find_package(LibZip  REQUIRED)
find_package(libSBML REQUIRED)
find_package(Raptor2 REQUIRED)
find_package(Rasqal REQUIRED)
find_package(LibRDF REQUIRED)
# https://stackoverflow.com/questions/20746936/cmake-of-what-use-is-find-package-if-you-need-to-specify-cmake-module-path-an?rq=1
find_package(libcellml CONFIG REQUIRED)
find_package(SWIG)
cmake_policy(SET CMP0078 NEW)
cmake_policy(SET CMP0086 NEW)
# consider using https://cpp-netlib.org/ if networking is required (also handles URIs)
# otherwise consider adding https://github.com/uriparser/uriparser for uri handling

set(SEMSIM_CXX_STANDARD 98 CACHE STRING "The C++ standard to use (11 or 98)")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++${SEMSIM_CXX_STANDARD} -Wall -Wextra -Wno-unused-parameter -fPIC")

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_C_VISIBILITY_PRESET hidden)

set(ENABLE_STATIC_LIB TRUE CACHE BOOL "Build static libraries?")
set(ENABLE_SHARED_LIB TRUE CACHE BOOL "Build shared libraries?")

set(CMAKE_CXX_STANDARD ${SEMSIM_CXX_STANDARD})

# bindings
option(BUILD_PYTHON "Build Python SWIG module" ON)

# diagnostics
get_target_property(LIBCELLML_LIBS cellml LOCATION)
get_target_property(LIBCELLML_INCLUDE_DIRS cellml INTERFACE_INCLUDE_DIRECTORIES)

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
      libxml2 library           ${LIBXML2_LIBRARIES}
      libxml2 include dirs      ${LIBXML2_INCLUDE_DIRS}
      zlib library              ${ZLIB_LIBRARIES}
      zlib include dir          ${ZLIB_INCLUDE_DIRS}
      PugiXML library           ${PUGIXML_LIBRARY}
      PugiXML include dir       ${PUGIXML_INCLUDE_DIR}
      libzip library            ${LIBZIP_LIBRARY}
      libzip include dir (zip)  ${LIBZIP_INCLUDE_DIR_ZIP}
      libzip include dir (zipconf) ${LIBZIP_INCLUDE_DIR_ZIPCONF}
      libSBML library           ${libSBML_LIBRARIES}
      libSBML include dir       ${libSBML_INCLUDE_DIRS}
      Raptor library            ${Raptor2_LIBRARIES}
      Raptor include dir        ${Raptor2_INCLUDE_DIRS}
      Rasqal library            ${Rasqal_LIBRARIES}
      Rasqal include dir        ${Rasqal_INCLUDE_DIRS}
      LibRDF library            ${LibRDF_LIBRARIES}
      LibRDF include dir        ${LibRDF_INCLUDE_DIRS}
      LibCellML (optional)      ${LIBCELLML_LIBS}
      LibRDF include dir        ${LIBCELLML_INCLUDE_DIRS}

    Language bindings:
      Python                    ${BUILD_PYTHON}
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
include_directories(.)

# Add cellml, sbml
add_library(semanticio STATIC cellml.cpp sbml.cpp sbml.h omex.cpp omex.h)

install(TARGETS semanticio
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include)

# Set up public headers for cellml
# set_target_properties(semanticio PROPERTIES PUBLIC_HEADER "cellml.h")

add_subdirectory(semsim)

# Add subdirectories for each language if desired
if(BUILD_PYTHON)
  find_package (Python COMPONENTS Interpreter Development)
  if (Python_FOUND)
    include_directories(${PYTHON_INCLUDE_PATH})
    add_subdirectory(swig/python)
  else()
    message(SEND_ERROR "BUILD_PYTHON is enabled but could not find a suitable Python runtime environment")
  endif()
endif()
# add_subdirectory(swig)
# target_link_libraries(semgen /usr/local/Cellar/raptor/2.0.15/lib/libraptor2.dylib)
# target_link_libraries(semgen-static /usr/local/Cellar/raptor/2.0.15/lib/libraptor2.dylib)
