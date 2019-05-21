cmake_minimum_required(VERSION 3.13)
project(libsemgen)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra -Wno-unused-parameter -fPIC")

include_directories(/usr/local/include)
include_directories(/Users/prakharagarwal/Desktop/semgen_code/)
include_directories(/usr/local/Cellar/libzip/1.5.2)
include_directories(/Users/prakharagarwal/Desktop/semgen_code/raptor2-2.0.15/src)
include_directories(/Users/prakharagarwal/Desktop/semgen_code/rasqal-0.9.33/src)

set(CMAKE_CXX_STANDARD 14)

# Add cellml, sbml
add_library(a cellml.cpp sbml.cpp sbml.h omex.cpp omex.h)

# Set up public headers for cellml
set_target_properties(a PROPERTIES PUBLIC_HEADER "cellml.h")

# Create main and link to cellml
add_library(${PROJECT_NAME} libsemgen.cpp)
target_link_libraries(${PROJECT_NAME} a)

# Set up public headers for swig-example
set_target_properties(libsemgen PROPERTIES PUBLIC_HEADER "libsemgen.h")

# Add install target
install(TARGETS ${PROJECT_NAME} a
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static
        PUBLIC_HEADER DESTINATION include)

# Add swig subdirectory
add_subdirectory(swig)

#ADD_SUBDIRECTORY(SBML_test)
#ADD_SUBDIRECTORY(SBML)

find_package(LibXml2 REQUIRED)


message(STATUS LIBXML2_FOUND = ${LIBXML2_FOUND})
include_directories(${LIBXML2_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${LIBXML2_LIBRARIES})
target_link_libraries(${PROJECT_NAME} /usr/local/lib/libsbml.5.dylib)
target_link_libraries(${PROJECT_NAME} /usr/local/Cellar/libzip/1.5.2/lib/libzip.5.dylib)
target_link_libraries(${PROJECT_NAME} /usr/local/Cellar/redland/1.0.17_1/lib/librdf.0.dylib)
target_link_libraries(${PROJECT_NAME} /usr/local/Cellar/raptor/2.0.15/lib/libraptor2.0.dylib)
target_link_libraries(${PROJECT_NAME} /usr/local/Cellar/rasqal/0.9.33/lib/librasqal.3.dylib)