include(ExternalProject)

#######################################################################
#   Build third party libs
#

set(DEPENDENCY_INCLUDE_DIRS)
set(DEPENDENCY_LINK_LIBRARIES)

if (${PLATFORM} STREQUAL "linux")

    # build zlib
    ExternalProject_Add(libcurl
            SOURCE_DIR ${LIBCURL_SOURCE_DIR}
            BINARY_DIR ${LIBCURL_BUILD_DIR}
            BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} -j${N}
            CMAKE_ARGS
            -DCMAKE_INSTALL_PREFIX=${LIBCURL_INSTALL_PREFIX}
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
            -DCMAKE_POSITION_INDEPENDENT_CODE=ON
            )
    ExternalProject_Add(zlib
            SOURCE_DIR ${ZLIB_SOURCE_DIR}
            BINARY_DIR ${ZLIB_BUILD_DIR}
            BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} -j${N}
            CMAKE_ARGS
            -DCMAKE_INSTALL_PREFIX=${ZLIB_INSTALL_PREFIX}
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
            -DCMAKE_POSITION_INDEPENDENT_CODE=ON
            )

    # build libsbml-dependencies, which itself has no dependencies
    ExternalProject_Add(libsbml-dependencies

            SOURCE_DIR ${LIBSBML_DEPS_SOURCE_DIR}
            BINARY_DIR ${LIBSBML_DEPS_BINARY_DIR}
            BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} -j${N}
            CMAKE_ARGS
            -DCMAKE_POSITION_INDEPENDENT_CODE=ON
            -DCMAKE_INSTALL_PREFIX=${LIBSBML_DEPS_INSTALL_PREFIX}
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
            -DFORCE_BUILD_ICONV=ON
            -DBUILD_SHARED_LIBS=ON
            )

    # build zipper
    ExternalProject_Add(zipper

            SOURCE_DIR ${ZIPPER_SOURCE_DIR}
            BINARY_DIR ${ZIPPER_BINARY_DIR}
            BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} -j${N}
            DEPENDS zlib
            CMAKE_ARGS
            -DCMAKE_POSITION_INDEPENDENT_CODE=ON
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
            -DCMAKE_INSTALL_PREFIX=${ZIPPER_INSTALL_PREFIX}
            -DLIBSBML_DEPS_INSTALL_PREFIX=${LIBSBML_DEPS_INSTALL_PREFIX}
            -DZLIB_LIBRARY=${ZLIB_STATIC_LIBRARY}
            -DZLIB_INCLUDE_DIR=${ZLIB_INCLUDE_DIR}
            )

    message(STATUS "CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}")


    ExternalProject_Add(libxml2
            SOURCE_DIR ${LIBXML2_SOURCE_DIR}
            BINARY_DIR ${LIBXML2_BINARY_DIR}
            BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} -j${N}
            CMAKE_ARGS
            -DCMAKE_POSITION_INDEPENDENT_CODE=ON
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
            -DCMAKE_INSTALL_PREFIX=${LIBXML2_INSTALL_PREFIX}
            -DBUILD_SHARED_LIBS=ON
            -DLIBXML2_WITH_PYTHON=OFF
            -DCMAKE_POSITION_INDEPENDENT_CODE=ON
            -DCMAKE_EXE_LINKER_FLAGS= -lpthread -Wl,--whole-archive -llzma -licu -liconv -lzlib -Wl,--no-whole-archive
            )
    ## get libxml2 libraries
    #find_library(LIBXML2_STATIC_LIBRARY
    #        NAMES libxml2.a
    #        )
    #
    #find_path(LIBXML2_INCLUDE_DIR
    #        NAMES libxml/parser.h
    #        PATHS /usr/local/include/libxml2
    #        )

    if (BUILD_LIBSBML)
        # build libsbml
        ExternalProject_Add(libsbml
                SOURCE_DIR ${LIBSBML_SOURCE_DIR}
                BINARY_DIR ${LIBSBML_BINARY_DIR}
                DEPENDS libsbml-dependencies
                BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} -j${N}
                CMAKE_ARGS
                -DCMAKE_POSITION_INDEPENDENT_CODE=ON
                -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                -DCMAKE_INSTALL_PREFIX=${LIBSBML_INSTALL_PREFIX}
                -WITH_LIBXML=ON
                -DENABLE_LAYOUT=ON
                -DWITH_CPP_NAMESPACE=ON
                -DLIBSBML_DEPENDENCY_DIR=${LIBSBML_DEPS_INSTALL_PREFIX}
                -DLIBSBML_SKIP_SHARED_LIBRARY=ON
                )
    endif ()

    if (BUILD_LIBCOMBINE)
        # build libcombine
        ExternalProject_Add(libCombine
                SOURCE_DIR ${LIBCOMBINE_SOURCE_DIR}
                BINARY_DIR ${LIBCOMBINE_BINARY_DIR}
                BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} -j${N}
                DEPENDS zipper libsbml libxml2
                LIST_SEPARATOR | # for EXTRA_LIBS argument
                CMAKE_ARGS
                -DCMAKE_POSITION_INDEPENDENT_CODE=ON
                -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                -DCMAKE_INSTALL_PREFIX=${LIBCOMBINE_INSTALL_PREFIX}
                -DLIBSBML_LIBRARY=${LIBSBML_STATIC_LIBRARY}
                -DLIBSBML_INCLUDE_DIR=${LIBSBML_INCLUDE_DIR}
                -DZIPPER_INCLUDE_DIR=${ZIPPER_INCLUDE_DIR}
                -DZIPPER_LIBRARY=${ZIPPER_STATIC_LIBRARY}
                -DEXTRA_LIBS=${LIBXML2_STATIC_LIBRARY}|${BZ2_STATIC_LIBRARY}|${ZLIB_STATIC_LIBRARY}|iconv|lzma #linux only, will need to change for windows
                )
    endif ()

    # we now call and build the parent project with HAVE_DEPENDENCIES=TRUE
    ExternalProject_Add(libsemsim
            DEPENDS zlib libsbml-dependencies zipper
            libxml2
            SOURCE_DIR ${CMAKE_SOURCE_DIR}
            BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} -j${N}
            BINARY_DIR ${CMAKE_BINARY_DIR}
            INSTALL_DIR ""
            CMAKE_ARGS
            -DCMAKE_POSITION_INDEPENDENT_CODE=ON
            -DHAVE_DEPENDENCIES=TRUE
            )

elseif (${PLATFORM} STREQUAL "windows-msvc")

    set(VCPKG_ROOT "D:/vcpkg" CACHE STRING "Absolute path to root vcpkg directory. On mine its D:\\vcpkg")
    set(VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "The vcpkg triplet to use")
    set(CMAKE_GENERATOR_PLATFORM "x64-windows")
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Path to vcpkg toolchain file")
    set(VCPKG_X64_INSTALLED_PACKAGES "${VCPKG_ROOT}/installed/x64-windows")
    set(VCPKG_X64_LIB_DIR "${VCPKG_X64_INSTALLED_PACKAGES}/lib")
    set(VCPKG_X64_INCLUDE_DIR "${VCPKG_X64_INSTALLED_PACKAGES}/include")

    if (NOT EXISTS ${CMAKE_TOOLCHAIN_FILE})
        message(FATAL_ERROR "No vcpkg toolchain installed. Have you configured vcpkg yet? If so,
pass in -DCMAKE_TOOLCHAIN_FILE=\"C:/full/path/to/vcpkg.cmake\"")
    endif ()

    find_library(LIBXML_LIBRARY
            NAMES libxml2
            PATHS ${VCPKG_X64_LIB_DIR}
            REQUIRED
            )

    find_path(LIBXML_INCLUDE_DIR
            NAMES libxml/parser.h
            PATHS ${VCPKG_X64_LIB_DIR}
            REQUIRED
            )

    if (NOT EXISTS ${LIBXML_LIBRARY})
        message(FATAL_ERROR "Libxml not found")
    endif ()

    find_library(CURL_LIBRARY
            NAMES libcurl
            PATHS ${VCPKG_X64_LIB_DIR}
            REQUIRED
            )

    find_path(CURL_INCLUDE_DIR
            NAMES curl/curl.h
            PATHS ${VCPKG_X64_LIB_DIR}
            REQUIRED
            )

    if (NOT EXISTS ${CURL_LIBRARY})
        message(FATAL_ERROR "curl not found")
    endif ()

    #    target_include_directories(main PRIVATE ${LIBXML2_INCLUDE_DIR})
    #    target_link_libraries(main PRIVATE ${LIBXML2_LIBRARIES})

    #    find_package(CURL CONFIG REQUIRED)# PATHS D:/vcpkg/installed/x64-windows/share/curl)
    #    #    target_link_libraries(main PRIVATE CURL::libcurl)
    #
    #    find_package(ZLIB REQUIRED)
    #    #    target_link_libraries(main PRIVATE ZLIB::ZLIB)

    # we now call and build the parent project with HAVE_DEPENDENCIES=TRUE
    ExternalProject_Add(libsemsim
            SOURCE_DIR ${CMAKE_SOURCE_DIR}
            BUILD_COMMAND ${CMAKE_MAKE_PROGRAM} -j${N}
            BINARY_DIR ${CMAKE_BINARY_DIR}
            INSTALL_DIR ""
            CMAKE_ARGS
            -DCMAKE_POSITION_INDEPENDENT_CODE=ON
            -DHAVE_DEPENDENCIES=TRUE
            )


elseif (${PLATFORM} STREQUAL "macos")
    message(FATAL_ERROR "macos not yet supported")
endif ()



