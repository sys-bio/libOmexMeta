include(ExternalProject)

#######################################################################
#   Build third party libs
#

# build zlib
ExternalProject_Add(zlib
        SOURCE_DIR ${ZLIB_SOURCE_DIR}
        BINARY_DIR ${ZLIB_BUILD_DIR}
        BUILD_COMMAND make -j${N}
        CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${ZLIB_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_POSITION_INDEPENDENT_CODE=ON
        )

# build libsbml-dependencies, which itself has no dependencies
ExternalProject_Add(libsbml-dependencies
        SOURCE_DIR ${LIBSBML_DEPS_SOURCE_DIR}
        BINARY_DIR ${LIBSBML_DEPS_BINARY_DIR}
        BUILD_COMMAND make -j${N}
        CMAKE_ARGS
        -DCMAKE_POSITION_INDEPENDENT_CODE=ON
        -DCMAKE_INSTALL_PREFIX=${LIBSBML_DEPS_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        )

# build zipper
ExternalProject_Add(zipper
        SOURCE_DIR ${ZIPPER_SOURCE_DIR}
        BINARY_DIR ${ZIPPER_BINARY_DIR}
        BUILD_COMMAND make -j${N}
        DEPENDS zlib
        CMAKE_ARGS
        -DCMAKE_POSITION_INDEPENDENT_CODE=ON
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX=${ZIPPER_INSTALL_PREFIX}
        -DLIBSBML_DEPS_INSTALL_PREFIX=${LIBSBML_DEPS_INSTALL_PREFIX}
        -DZLIB_LIBRARY=${ZLIB_STATIC_LIBRARY}
        -DZLIB_INCLUDE_DIR=${ZLIB_INCLUDE_DIR}
        )

# build zipper
ExternalProject_Add(libxml2
        SOURCE_DIR ${LIBXML2_SOURCE_DIR}
        BINARY_DIR ${LIBXML2_BINARY_DIR}
        BUILD_COMMAND make -j${N}
        CMAKE_ARGS
        -DCMAKE_POSITION_INDEPENDENT_CODE=ON
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX=${LIBXML2_INSTALL_PREFIX}
        -DBUILD_SHARED_LIBS=OFF
        -DLIBXML2_WITH_PYTHON=OFF
        -DCMAKE_POSITION_INDEPENDENT_CODE=ON

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

# build libsbml
ExternalProject_Add(libsbml
        SOURCE_DIR ${LIBSBML_SOURCE_DIR}
        BINARY_DIR ${LIBSBML_BINARY_DIR}
        DEPENDS libsbml-dependencies
        BUILD_COMMAND make -j${N}
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


# build libcombine
ExternalProject_Add(libCombine
        SOURCE_DIR ${LIBCOMBINE_SOURCE_DIR}
        BINARY_DIR ${LIBCOMBINE_BINARY_DIR}
        BUILD_COMMAND make -j${N}
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


# we now call and build the parent project with HAVE_DEPENDENCIES=TRUE
ExternalProject_Add(libsemsim
        DEPENDS zlib libsbml-dependencies zipper
        libsbml libCombine raptor rasqal librdf
        libxml2
        SOURCE_DIR ${CMAKE_SOURCE_DIR}
        BUILD_COMMAND make -j${N}
        BINARY_DIR ${CMAKE_BINARY_DIR}
        INSTALL_DIR ""
        CMAKE_ARGS
        -DCMAKE_POSITION_INDEPENDENT_CODE=ON
        -DHAVE_DEPENDENCIES=TRUE
        )


find_library(RAPTOR2_STATIC_LIBRARY
        NAMES libraptor2.a raptor2.a
        PATHS ${RAPTOR2_INSTALL_PREFIX}/lib
        /usr/local/lib
        )

find_path(RAPTOR2_INCLUDE_DIR
        NAMES raptor2.h
        PATHS ${RAPTOR2_INSTALL_PREFIX}/include/raptor2
        /usr/local/include/raptor2
        )

# rasqal
find_library(RASQAL_STATIC_LIBRARY
        NAMES librasqal.a rasqal.a
        PATHS ${RASQAL_INSTALL_PREFIX}/lib
        /usr/local/lib
        )

find_path(RASQAL_INCLUDE_DIR
        NAMES rasqal.h
        PATHS ${RASQAL_INSTALL_PREFIX}/include/rasqal
        /usr/local/include/rasqal
        )

find_library(REDLAND_STATIC_LIBRARY
        NAMES librdf.a rdf.a
        PATHS ${REDLAND_INSTALL_PREFIX}/lib
        /usr/local/lib

        )

find_path(REDLAND_INCLUDE_DIR
        NAMES librdf.h
        PATHS ${REDLAND_INSTALL_PREFIX}/include
        /usr/local/include
        )
