#A note on the docs-build system. Occasionally you will
#see "_CMakeLists.txt". This is an old version of the
#docs-build system. This will be deleted in due course.

cmake_minimum_required(VERSION 3.15)


# Set version.
set(VERSION_MAJOR 1)
set(VERSION_MINOR 2)
set(VERSION_MICRO 0)

set(LIBOMEXMETA_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_MICRO})
configure_file(VERSION.txt.in VERSION.txt)
configure_file(VERSION.txt.in "${CMAKE_CURRENT_SOURCE_DIR}/src/pyomexmeta/VERSION.txt")


install(FILES
        requirements.txt
        LICENCE.txt
        banner.txt
        environment.yml
        DESTINATION .)

############################################################3
# configure some paths relative to vcpkg root
# should happen before call to project(libOmexMeta) as per the docs
# https://vcpkg.readthedocs.io/en/latest/users/integration/

find_path(VCPKG_ROOT NAMES ports/libxml2/CMakeLists.txt REQUIRED
        HINTS "$ENV{HOMEDRIVE}" "$ENV{HOMEPATH}" "D:/")

if (NOT EXISTS ${VCPKG_ROOT})
    message(FATAL_ERROR "vcpkg root not found (${VCPKG_ROOT})")
else ()
    message(STATUS "Found VCPKG_ROOT at ${VCPKG_ROOT}")
endif ()

find_file(
        VCPKG_TOOLCHAIN_FILE
        NAMES vcpkg.cmake
        HINTS "${VCPKG_ROOT}/scripts/buildsystems"
        REQUIRED
)

# ensure the toolchain file exists and user has provided it.
if (NOT EXISTS ${VCPKG_TOOLCHAIN_FILE})
    message(FATAL_ERROR "No vcpkg toolchain installed, got \"${CMAKE_TOOLCHAIN_FILE}\".
Have you passed in the root to vcpkg? i.e. -DVCPKG_ROOT=\"D:/vcpkg\"")
else ()
    message(STATUS "Using vcpkg toolchain file \"${VCPKG_TOOLCHAIN_FILE}\"")
endif ()

if (WIN32)
    set(VCPKG_TARGET_TRIPLET x64-windows-static CACHE STRING "vcpkg triplet to use")
elseif (UNIX AND NOT APPLE)
    set(VCPKG_TARGET_TRIPLET x64-linux CACHE STRING "vcpkg triplet to use")
elseif (APPLE)
    set(VCPKG_TARGET_TRIPLET x64-osx CACHE STRING "vcpkg triplet to use")
endif ()

# this needs to be before project() call
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_TOOLCHAIN_FILE}")

###########################################################################
#   Start configuring libOmexMeta
#

project(libOmexMeta
        VERSION "${LIBOMEXMETA_VERSION}"
        DESCRIPTION "Annotation library for models in mathematical biology"
        )

# for linux shared libraries
set(SOVERSION ${VERSION_MAJOR})

######################################################
# Load stuff
# set the module path
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# load the ExternalProject functions for superbuild
include(ExternalProject)

# load a custom function for determining the current platform
include(DeterminePlatform)


# defines a macro for locating the dependencies
#include(FindDependencies)

# defines a macro that allows easily setting of platform dependent values for a variable
include(SetCrossPlatform)

# defines a macro that prints out configuration summary
include(ConfigurationSummary)

# include some code for coverage configuration
#include(CodeCoverage)

# for verification of include files
include(CheckIncludeFiles)
include(CheckIncludeFile)

# standard install locations
include(GNUInstallDirs)

# GNUInstallDirs creates cache variable CMAKE_INSTALL_DOCDIR for documentation
# but the default is defined by a call to project, which can vary throughout the
# cmake hierachy. Therefore its best to set now.
set(CMAKE_INSTALL_DOCDIR "${CMAKE_INSTALL_PREFIX}/docs")

# The InstallRequiredSystemLibraries module is intended to provide projects with the details of
#relevant run time libraries for the major compilers
include(InstallRequiredSystemLibraries)

# utility for debugging cmake
include(QueryCMakeVariables)

# generate automatic export headers
include(GenerateExportHeader)

include(GoogleTest)


######################################################
#   Set some variables
#

# global settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
endif ()
set(CXX_STANDARD_REQUIRED ON)

# pic - needed on linux ignored on other platofrms
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# location of pyomexmeta development package.
set(PYOMEXMETA_DIR "${CMAKE_SOURCE_DIR}/src/pyomexmeta")

set(THIRD_PARTY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party")

# location of googletesting framework
set(GOOGLETEST_SOURCE_DIR ${CMAKE_SOURCE_DIR}/third_party/googletest)

# put all runtime targets (exe and dll) into bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)

# put libraries into lib
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

# archives
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)

# export all on windows. Ignored on other.
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)

# In non-windows builds and only when libOmexMeta is being built
#   as a top level project, we set the default CMAKE_INSTALL_PREFIX
#   to /opt/libOmexMeta. This is cached variable and will only
#   be effective if user has not set CMAKE_INSTALL_PREFIX
if (NOT WIN32 AND CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(CMAKE_INSTALL_PREFIX "/opt/${PROJECT_NAME}" CACHE PATH "Where to install libomexmeta")
endif ()

# setup some paths that will be used for the INSTALL_RPATH paths on systems that
# support it. Adapt the "ORIGIN" to the APPLE use case
if (APPLE)
    set(base @loader_path)
else ()
    set(base $ORIGIN)
endif ()
file(RELATIVE_PATH INSTALL_RPATH_DIRECTORIES
        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}
        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}
        )
# make all shared libraries have the same directory, the bin and the lib dirs in RPATH
set(CMAKE_INSTALL_RPATH ${base} ${base}/${INSTALL_RPATH_DIRECTORIES})


# set default visibility to hidden on all platforms (GCC and Clang default is to show
# while visual studio, the default is hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN YES)

####################################################################
# User options
#


include(CMakeDependentOption)

option(BUILD_SHARED_LIBS "build share libraries" OFF)
if (${BUILD_SHARED_LIBS})
    add_definitions("-DBUILD_SHARED_LIBS=ON")
endif ()

include(CMakeDependentOption)
option(BUILD_DOCS "Build libomexmeta documentation" OFF)

# Defaults to off when BUILD_DOCS=OFF and ON when BUILD_DOCS=ON
cmake_dependent_option(
        BUILD_DOCS_EXAMPLES "Build the examples in the documentation. BUILD_DOCS must be ON to have an effect" ON
        "BUILD_DOCS" OFF
)

option(BUILD_PACKAGING "Package libOmexMeta with CPack" OFF)
option(BUILD_PYTHON "Build the Python pip package" OFF)
option(GENERATE_DEPENDENCY_GRAPH "Get CMake to generate the dependency graph" ON)
# docs-build tests?
option(BUILD_TESTS "build the tests" OFF)
# only presents BUILD_INTEGRATION_TESTS option when BUILD_TESTS is ON.
cmake_dependent_option(
        BUILD_INTEGRATION_TESTS "build integrations tests" ON
        "BUILD_TESTS" ON
)

# verbose
set(CMAKE_VERBOSE_MAKEFILE ON)

option(WITH_SANITIZER "link with address sanitizer for memory debugging" OFF)
if (WITH_SANITIZER)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${ADDRESS_SANITIZER_LINK_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ADDRESS_SANITIZER_FLAGS}")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${ADDRESS_SANITIZER_FLAGS}")
endif ()


option(WITH_BDB "build user suport for berkely database" ON)
if (${WITH_BDB})
    add_definitions(-DWITH_BDB)
endif ()

# run the tests and generate coverage output
option(WITH_COVERAGE OFF)

# set RPATH for libraries and executables.
set(RPATH "$ORIGIN:$ORIGIN/../lib")

if (${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    message(FATAL_ERROR "In source builds are disabled")
endif ()

# set gtest libraries which are different between debug and release.
set(GTEST_LIBS $<TARGET_FILE:gtest> $<TARGET_FILE:gtest_main>)

# needed for configuration of pythons setup.py configuration
set(README_FILE ${CMAKE_CURRENT_SOURCE_DIR}/README.md)

if (${BUILD_PYTHON})
    find_package(Python)
    # configure the python setup.py
    set(PYTHON_SETUP_CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in)
    set(PYTHON_SETUP_FILE ${CMAKE_CURRENT_BINARY_DIR}/setup.py)
    configure_file(${PYTHON_SETUP_CONFIG_FILE} ${PYTHON_SETUP_FILE} @ONLY)

endif ()

# we write a file called extra_search_directories for storing locations of places python can search for
# the shared library it needs for loading libOmexMeta into Python.
file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/src/pyomexmeta/ExtraSearchDirectories.txt"
        "${CMAKE_INSTALL_PREFIX}\n"
        "${CMAKE_INSTALL_PREFIX}/lib\n"
        "${CMAKE_INSTALL_PREFIX}/bin\n"
        )


find_package(CURL CONFIG REQUIRED)
#target_link_libraries(main PRIVATE CURL::libcurl)
# curl INTERFACE_LINK_LIBRARIES has the following contents:

find_library(YAJL_STATIC_LIBRARY NAMES ${CMAKE_STATIC_LIBRARY_PREFIX}yajl_s${CMAKE_STATIC_LIBRARY_SUFFIX} REQUIRED)
find_path(YAJL_INCLUDE_DIR NAMES yajl/yajl_parse.h REQUIRED)

find_package(unofficial-sqlite3 CONFIG REQUIRED)
#target_link_libraries(main PRIVATE unofficial::sqlite3::sqlite3)

find_package(LibLZMA CONFIG REQUIRED)
#target_link_libraries(main PRIVATE LibLZMA::LibLZMA)

#find_package(unofficial-pcre CONFIG REQUIRED)
## Note: 1 target(s) were omitted.
#target_link_libraries(main PRIVATE unofficial::pcre::pcre unofficial::pcre::pcre16 unofficial::pcre::pcre32 unofficial::pcre::pcrecpp)

find_library(
        PCRE_STATIC_LIBRARY REQUIRED
        NAMES ${CMAKE_STATIC_LIBRARY_PREFIX}pcre${CMAKE_STATIC_LIBRARY_SUFFIX}
)
find_path(
        PCRE_INCLUDE_DIR REQUIRED
        NAMES pcre.h
)

add_subdirectory(third_party)
#############################################
# Build libOmexMeta targets and tests
#

# source directories
add_subdirectory(src)


# test directories
if (BUILD_TESTS)
    enable_testing()
    include(GoogleTest)

    # include googletest as source
    add_subdirectory(${GOOGLETEST_SOURCE_DIR})

    # add the tests
    add_subdirectory(tests)

endif (BUILD_TESTS)

# docs-build documentation.
if (BUILD_DOCS)
    message(STATUS "Building the docs")
    add_subdirectory(docs)
endif ()


# Best included near the end of the top leve cmakelists.
if (${BUILD_PACKAGING} AND ${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    add_subdirectory(packaging)
endif ()

# only enable this option if building as top level package
if (${GENERATE_DEPENDENCY_GRAPH} AND ${CMAKE_CURRENT_SOURCE_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    #    mkdir graphviz && cd graphviz
    #    cmake --graphviz=graph ..
    #    dot graph -Tsvg -o graph.svg
    add_custom_target(
            DependencyGraph
            COMMENT "Use CMake to generate dependency graph"
            COMMAND ${CMAKE_COMMAND} --graphviz=graph .
            COMMAND dot graph -Tsvg -o "${CMAKE_CURRENT_SOURCE_DIR}/dependency_graph.svg"
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )

endif ()


# print out config summary
ConfigurationSummary()
















