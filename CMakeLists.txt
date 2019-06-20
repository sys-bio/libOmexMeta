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

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra -Wno-unused-parameter -fPIC")

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_C_VISIBILITY_PRESET hidden)

set(ENABLE_STATIC_LIB TRUE CACHE BOOL "Build static libraries?")
set(ENABLE_SHARED_LIB TRUE CACHE BOOL "Build shared libraries?")

set(CMAKE_CXX_STANDARD 14)

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

# Add cellml, sbml
add_library(semanticio STATIC cellml.cpp sbml.cpp sbml.h omex.cpp omex.h)

install(TARGETS semanticio
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include)

# Set up public headers for cellml
# set_target_properties(semanticio PROPERTIES PUBLIC_HEADER "cellml.h")

# Create main and link to cellml
if (ENABLE_SHARED_LIB)
  add_library(semgen SHARED libsemgen.cpp)
  # set_target_properties(semgen PROPERTIES PUBLIC_HEADER "libsemgen.h")
endif ()
if (ENABLE_STATIC_LIB)
  add_library(semgen-static STATIC libsemgen.cpp)
  # set_target_properties(semgen-static PROPERTIES PUBLIC_HEADER "libsemgen.h")
endif ()

# Add swig subdirectory
# add_subdirectory(swig)

if (${ENABLE_SHARED_LIB})
  list(APPEND LIBRARIES semgen)
endif ()
if (${ENABLE_STATIC_LIB})
  list(APPEND LIBRARIES semgen-static)
endif ()
foreach(l ${LIBRARIES})
  message("Library ${l}")
  target_link_libraries(${l} semanticio)
  target_link_libraries(${l} ${libSBML_LIBRARIES})
  target_link_libraries(${l} LibXml2::LibXml2)
  target_link_libraries(${l} ZLIB::ZLIB)
  target_link_libraries(${l} ${Raptor2_LIBRARIES})
  target_link_libraries(${l} ${Rasqal_LIBRARIES})
  target_link_libraries(${l} ${LibRDF_LIBRARIES})
  install(TARGETS ${l}
          RUNTIME DESTINATION bin
          LIBRARY DESTINATION lib
          ARCHIVE DESTINATION lib
          PUBLIC_HEADER DESTINATION include)
endforeach ()
# target_link_libraries(semgen /usr/local/Cellar/raptor/2.0.15/lib/libraptor2.dylib)
# target_link_libraries(semgen-static /usr/local/Cellar/raptor/2.0.15/lib/libraptor2.dylib)
