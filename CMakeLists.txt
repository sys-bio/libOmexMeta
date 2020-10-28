#A note on the docs-build system. Occasionally you will
#see "_CMakeLists.txt". This is an old version of the
#docs-build system. This will be deleted in due course.

cmake_minimum_required(VERSION 3.15)


# Set version.
set(VERSION_MAJOR 1)
set(VERSION_MINOR 1)
set(VERSION_MICRO 18)

set(LIBOMEXMETA_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_MICRO})
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

# defines ${PLATFORM}
DeterminePlatform()

# defines a macro for locating the dependencies
include(FindDependencies)

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
set(CMAKE_INSTALL_DOCDIR ${CMAKE_INSTALL_PREFIX}/docs)

# The InstallRequiredSystemLibraries module is intended to provide projects with the details of
#relevant run time libraries for the major compilers
set(CMAKE_INSTALL_SYSTEM_RUNTIME_COMPONENT MyProj_Runtime)
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

# location of googletesting framework
set(GOOGLETEST_SOURCE ${CMAKE_SOURCE_DIR}/third_party/googletest)

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

option(BUILD_SHARED_LIBS "build share libraries" ON)
if (${BUILD_SHARED_LIBS})
    add_definitions("-DBUILD_SHARED_LIBS=ON")
endif ()

option(DEBUG_DEPENDENCIES "Catch missing libraries by throwing error message if they do not exist" OFF)

option(BUILD_DOCS "Build libomexmeta documentation" OFF)
option(BUILD_DOCS_EXAMPLES "Build the examples in the documentation. BUILD_DOCS must be ON to have an effect" OFF)
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
    if (${PLATFORM} STREQUAL "linux")
        SET(ADDRESS_SANITIZER_FLAGS "-g -fsanitize=address")
        SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${ADDRESS_SANITIZER_LINK_FLAGS}")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ADDRESS_SANITIZER_FLAGS}")
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${ADDRESS_SANITIZER_FLAGS}")
    elseif (${PLATFORM} STREQUAL "windows-msvc")

    elseif (${PLATFORM} STREQUAL "macos")
        message(FATAL_ERROR "Sad face mac user =[")
    endif ()
endif ()


option(WITH_BDB "build user suport for berkely database" ON)
if (${WITH_BDB})
    add_definitions(-DWITH_BDB)
endif ()

# run the tests and generate coverage output
option(WITH_COVERAGE OFF)

# set RPATH for libraries and executables.
set(RPATH "$ORIGIN:$ORIGIN/../lib")

# set runtime library on windows, which is different between debug and release.
if (PLATFORM STREQUAL "windows-msvc")
    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(RUNTIME "libucrtd")
    elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
        set(RUNTIME "libucrt")
    endif ()
endif ()

if (${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR})
    message(FATAL_ERROR "In source builds are disabled")
endif ()

# set gtest libraries which are different between debug and release.
set(GTEST_LIBS $<TARGET_FILE:gtest> $<TARGET_FILE:gtest_main>)

# needed for configuration of pythons setup.py configuration
set(README_FILE ${CMAKE_CURRENT_SOURCE_DIR}/README.md)

if (${BUILD_PYTHON})
    find_package(PythonInterp)
    # configure the python setup.py
    set(PYTHON_SETUP_CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in)
    set(PYTHON_SETUP_FILE ${CMAKE_CURRENT_BINARY_DIR}/setup.py)
    configure_file(${PYTHON_SETUP_CONFIG_FILE} ${PYTHON_SETUP_FILE} @ONLY)

    # configure the python __init.py
    set(PYTHON_INIT_CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/pyomexmeta/__init__.py.in")
    set(PYTHON_INIT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/pyomexmeta/__init__.py")
    configure_file(${PYTHON_INIT_CONFIG_FILE} ${PYTHON_INIT_FILE} @ONLY)

    # configure the python pyomexmeta_api.py.in
    set(PYTHON_API_CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/pyomexmeta/pyomexmeta_api.py.in")
    set(PYTHON_API_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/pyomexmeta/pyomexmeta_api.py")
    configure_file(${PYTHON_API_CONFIG_FILE} ${PYTHON_API_FILE} @ONLY)


endif ()


############################################################3
# configure some paths relative to vcpkg root
set(VCPKG_ROOT "D:/vcpkg" CACHE STRING "Absolute path to root vcpkg directory. On mine its \"D:\\vcpkg\" on windows and \"/home/ciaran/vcpkg\" on WSL (Ubuntu)")
if (NOT EXISTS ${VCPKG_ROOT})
    message(FATAL_ERROR "vcpkg root not found (${VCPKG_ROOT})")
endif ()

set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Path to vcpkg toolchain file")

# ensure the toolchain file exists and user has provided it.
if (NOT EXISTS ${CMAKE_TOOLCHAIN_FILE})
    message(FATAL_ERROR "No vcpkg toolchain installed, got \"${CMAKE_TOOLCHAIN_FILE}\".
Have you passed in the root to vcpkg? i.e. -DVCPKG_ROOT=\"D:/vcpkg\"")
endif ()

# determine which triplet we need to use for finding shared libraries and include dirs.
SetCrossPlatform(VCPKG_ARCH "x64-windows" "x64-linux" "x64-osx")

# location of installed libraries in vcpkg
set(VCPKG_X64_INSTALLED_PACKAGES "${VCPKG_ROOT}/installed/${VCPKG_ARCH}")

# location of installed static packages in vcpkg
SetCrossPlatform(VCPKG_X64_STATIC_INSTALLED_PACKAGES
        "${VCPKG_ROOT}/installed/x64-windows-static"
        "${VCPKG_ROOT}/installed/x64-linux" # note: on linux, this is same for shared and static
        "${VCPKG_ROOT}/installed/x64-osx"
        )

# Path to static libraries
set(VCPKG_X64_STATIC_LIB_DIR "${VCPKG_X64_STATIC_INSTALLED_PACKAGES}/lib")
# Path to shared libraries
set(VCPKG_X64_LIB_DIR "${VCPKG_X64_INSTALLED_PACKAGES}/lib")
# Path to binaries
SetCrossPlatform(VCPKG_X64_BIN_DIR
        "${VCPKG_X64_INSTALLED_PACKAGES}/bin" # windows
        "${VCPKG_X64_INSTALLED_PACKAGES}/lib" # linux
        "${VCPKG_X64_INSTALLED_PACKAGES}/lib" # mac
        )
# include directories (should be the same for static and dynamic)
set(VCPKG_X64_INCLUDE_DIR "${VCPKG_X64_INSTALLED_PACKAGES}/include")


set(_VCPKG_DIRECTORIES
        ${VCPKG_X64_STATIC_LIB_DIR}
        ${VCPKG_X64_LIB_DIR}
        ${VCPKG_X64_BIN_DIR}
        ${VCPKG_X64_INCLUDE_DIR}
        )

# ensure the directories we've located exist
foreach (d ${_VCPKG_DIRECTORIES})
    if (NOT EXISTS ${d})
        message(FATAL_ERROR "VCPKG directory \"${d}\" does not exist")
    endif ()
endforeach ()


###########################################################
#   Find the dependencies
#

# note, I've not used the "find_package" command because
# sometimes it doesn't work and its really difficult to debug why.
# find_library, find_path and find_file are easier

# defines:
#   - libraries as x_LIBRARY
#   - static libraries as x_STATIC_LIBRARY
#   - include paths as x_INCLUDE_DIR
#   - STATIC_LIBRARIES = list of found static libraries
#   - LIBRARIES = list of found shared libraries
FindDependencies()

if (PLATFORM STREQUAL "windows-msvc")
    # On windows, order seems less important

    # fixme
    #Note these "static" libraries are not actually static.
    set(LINK_LIBRARIES
            "${LIBXML2_STATIC_LIBRARY}"
            "${LIBXSLT_STATIC_LIBRARY}"
            "${CURL_STATIC_LIBRARY}"
            "${LIBCHARSET_STATIC_LIBRARY}"
            "${SSL_STATIC_LIBRARY}"
            "${CRYPTO_STATIC_LIBRARY}"
            "${YAJL_STATIC_LIBRARY}"
            "${LZMA_STATIC_LIBRARY}"
            "${ZLIB_STATIC_LIBRARY}"
            "${ICONV_STATIC_LIBRARY}"
            "${PCRE_STATIC_LIBRARY}"
            "${SQLITE3_STATIC_LIBRARY}"
            "${BERKELY_STATIC_LIBRARY}"
            "${POSTGRESQL_STATIC_LIBRARY}"
            ws2_32 # needed on windows to statically link libxml2
            )
    # on windows it was much easier to just
    # set up to link to dynamic versions of libraries.
    # I tried to pull all into a single static library
    # but this proved too faffy.

    # determine runtime (set to static, dynamic libraries are modified later)
    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
    elseif (${CMAKE_BUILD_TYPE} STREQUAL "Release")
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
    endif ()

elseif (PLATFORM STREQUAL "linux")
    # On linux, order is essential.
    # if A depends on B, A must come before B in this list.
    # On linux, I pulled as many libraries as possible
    # into a static library. This was not possible with a few
    # for strange and unusual reasons which only the programming gods
    # can explain.
    set(LINK_LIBRARIES
            ${LIBXML2_LIBRARY} # dynamic
            ${LIBXSLT_LIBRARY} # dynamic
            ${SQLITE3_LIBRARY}
            ${BERKELY_LIBRARY}
            ${POSTGRESQL_LIBRARY}
            # flag for including whole archive, not just the function used.
            -Wl,--whole-archive
            ${ZLIB_STATIC_LIBRARY}
            ${LZMA_STATIC_LIBRARY}
            -Wl,--no-whole-archive
            ${ICONV_LIBRARY} # We use dynamic for now.
            ltdl
            -Wl,--whole-archive
            ${CURL_STATIC_LIBRARY}
            ${SSL_STATIC_LIBRARY}
            ${CRYPTO_STATIC_LIBRARY}
            ${YAJL_STATIC_LIBRARY}
            ${PCRE_STATIC_LIBRARY}
            -Wl,--no-whole-archive
            m
            dl
            ldap
            lber
            pthread
            )

elseif (PLATFORM STREQUAL "macos")
    message(FATAL_ERROR "Stupid mac.")
endif ()


set(INCLUDE_DIRECTORIES
        # raptor includes
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/redland/raptor2-2.0.15/src>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/redland/raptor2-2.0.15/utils>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/redland/raptor2-2.0.15/librdfa>

        # rasqal includes
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/redland/rasqal-0.9.33/src>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/redland/rasqal-0.9.33/libmtwist>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/redland/rasqal-0.9.33/libsv>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/redland/rasqal-0.9.33/utils>

        # librdf includes
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/redland/redland-1.0.17/src>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/redland/redland-1.0.17/utils>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/redland/redland-1.0.17/libltdl>

        # wrapper includes
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/redland/RedlandWrapper/src>

        # libomexmeta includes
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/src/C>

        # dependency includes
        $<BUILD_INTERFACE:${LIBXML2_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${LIBXSLT_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${CURL_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${SSL_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${SSL_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${YAJL_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${LZMA_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${ZLIB_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${PCRE_INCLUDE_DIR}>
        $<BUILD_INTERFACE:${ICONV_INCLUDE_DIR}>

        ${CMAKE_CURRENT_BINARY_DIR}/src/omexmeta
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/src/omexmeta/C>
        ${CMAKE_CURRENT_BINARY_DIR}/src/redland
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
        )


#############################################
# Build libOmexMeta targets and tests

# source directories
add_subdirectory(src)


# test directories
if (BUILD_TESTS)
    include(GoogleTest)

    enable_testing()

    # include googletest as source
    add_subdirectory(${GOOGLETEST_SOURCE})

    # add the tests
    add_subdirectory(tests/cpp)
    add_subdirectory(tests/C)
    add_subdirectory(tests/python)


    if (WITH_COVERAGE)

        set(GCOVR_PATH "/home/ciaran/miniconda3/bin/gcovr" CACHE FILEPATH "Full path to gcovr")
        if (NOT GCOVR_PATH)
            message(FATAL_ERROR "gcovr variable GCOVR_PATH (${GCOVR_PATH}) is empty")
        endif ()

        if (CMAKE_COMPILER_IS_GNUCXX)
            include(CodeCoverage)
            append_coverage_compiler_flags()

            # we need to turn off optimization for non-skewed coverage reports
            # we've done this in debug mode so we do not need to do it ehere
            #            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
            #            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")

            # optional excludes - None needed here
            set(COVERAGE_EXCLUDES
                    ${CMAKE_BINARY_DIR}/src/redland/raptor2-2.0.15
                    ${CMAKE_BINARY_DIR}/src/redland/rasqal-0.9.33
                    ${CMAKE_BINARY_DIR}/src/redland/redland-1.0.17
                    ${CMAKE_BINARY_DIR}/src/redland/RedlandWrapper/test
                    ${CMAKE_SOURCE_DIR}/tests
                    ${CMAKE_SOURCE_DIR}/test
                    ${CMAKE_SOURCE_DIR}/third_party
                    )

            # importantly, set the path to the gcovr executable that you downladed
            #  https://github.com/bilke/cmake-modules/issues/8
            setup_target_for_coverage_gcovr_html(
                    NAME TestCoverageHtml
                    EXECUTABLE ctest -j 8
                    DEPENDENCIES ctest
            )
            setup_target_for_coverage_gcovr_xml(
                    NAME TestCoverageXml
                    EXECUTABLE ctest -j 8
                    DEPENDENCIES ctest
            )
        else ()
            message(FATAL_ERROR "Coverage only available using gcov with gcc compilers")
        endif (CMAKE_COMPILER_IS_GNUCXX)
        # need different code for windows.
    endif (WITH_COVERAGE)
endif (BUILD_TESTS)

# docs-build documentation.
message(STATUS "BUILD_DOCS ${BUILD_DOCS}")
if (${BUILD_DOCS})
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
















