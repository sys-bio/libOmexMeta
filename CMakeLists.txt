cmake_minimum_required(VERSION 3.12.0)
project(libsemgen)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

find_package(LibXml2 REQUIRED)
find_package(ZLIB REQUIRED)
find_package(PugiXML REQUIRED)
find_package(LibZip REQUIRED)
find_package(libSBML REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra -Wno-unused-parameter -fPIC")

# include_directories(/usr/local/include)
# include_directories(/Users/prakharagarwal/Desktop/semgen_code/)
# include_directories(/usr/local/Cellar/libzip/1.5.2)
include_directories(/home/poltergeist/home/etc/install/raptor2-2.0.15/include/raptor2)
include_directories(/home/poltergeist/home/etc/install/rasqal-0.9.33/include/rasqal)
include_directories(/home/poltergeist/home/etc/install/redland-1.0.17/include)

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
    "
)

include_directories(${LIBXML2_INCLUDE_DIRS})
include_directories(${ZLIB_INCLUDE_DIRS})
include_directories(${PUGIXML_INCLUDE_DIR})
include_directories(${LIBZIP_INCLUDE_DIR_ZIP})
include_directories(${LIBZIP_INCLUDE_DIR_ZIPCONF})
include_directories(${libSBML_INCLUDE_DIRS})

# Add cellml, sbml
add_library(semanticio cellml.cpp sbml.cpp sbml.h omex.cpp omex.h)

# Set up public headers for cellml
set_target_properties(semanticio PROPERTIES PUBLIC_HEADER "cellml.h")

# Create main and link to cellml
add_library(${PROJECT_NAME} libsemgen.cpp)
target_link_libraries(${PROJECT_NAME} semanticio)

# Set up public headers for swig-example
set_target_properties(libsemgen PROPERTIES PUBLIC_HEADER "libsemgen.h")

# Add install target
install(TARGETS ${PROJECT_NAME} semanticio
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        PUBLIC_HEADER DESTINATION include)

# Add swig subdirectory
# add_subdirectory(swig)

#ADD_SUBDIRECTORY(SBML_test)
#ADD_SUBDIRECTORY(SBML)

# target_link_libraries(${PROJECT_NAME} /extra/docker/whlbldr/install/libsbml-experimental-cos5-nons/lib64/libsbml-static.a)
target_link_libraries(${PROJECT_NAME} libSBML_LIBRARIES)
target_link_libraries(${PROJECT_NAME} LibXml2::LibXml2)
target_link_libraries(${PROJECT_NAME} ZLIB::ZLIB)
target_link_libraries(${PROJECT_NAME} /home/poltergeist/home/etc/install/redland-1.0.17/lib/librdf.a)
target_link_libraries(${PROJECT_NAME} /home/poltergeist/home/etc/install/raptor2-2.0.15/lib/libraptor2.a)
target_link_libraries(${PROJECT_NAME} /home/poltergeist/home/etc/install/rasqal-0.9.33/lib/librasqal.a)
