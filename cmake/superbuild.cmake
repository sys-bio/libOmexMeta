include(ExternalProject)


#######################################################################
#   Build third party libs
#

# build zlib
ExternalProject_Add(zlib
        SOURCE_DIR ${ZLIB_SOURCE_DIR}
        BINARY_DIR ${ZLIB_BUILD_DIR}
        CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${ZLIB_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        )

# build libsbml-dependencies, which itself has no dependencies
ExternalProject_Add(libsbml-dependencies
        SOURCE_DIR ${LIBSBML_DEPS_SOURCE_DIR}
        BINARY_DIR ${LIBSBML_DEPS_BINARY_DIR}
        CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${LIBSBML_DEPS_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        )

# find zlib to give to zipper which depends on it
find_library(ZLIB_STATIC_LIBRARY
        NAMES libz.a z.a zlib.a libzlib.a zlib.dll libzlib.dll
        PATHS ${ZLIB_INSTALL_PREFIX}/lib
        REQUIRED
        )

find_path(ZLIB_INCLUDE_DIR
        NAMES zlib.h
        PATHS ${ZLIB_INSTALL_PREFIX}/include
        REQUIRED
        )

# build zipper
ExternalProject_Add(zipper
        SOURCE_DIR ${ZIPPER_SOURCE_DIR}
        BINARY_DIR ${ZIPPER_BINARY_DIR}
        DEPENDS zlib
        CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX=${ZIPPER_INSTALL_PREFIX}
        -DLIBSBML_DEPS_INSTALL_PREFIX=${LIBSBML_DEPS_INSTALL_PREFIX}
        -DZLIB_LIBRARY=${ZLIB_STATIC_LIBRARY}
        -DZLIB_INCLUDE_DIR=${ZLIB_INCLUDE_DIR}
        )


# find zipper lib and include dirs
find_library(ZIPPER_STATIC_LIBRARY
        NAMES libZipper-static.a libZipper-static
        PATHS ${ZIPPER_INSTALL_PREFIX}/lib
        )
find_path(ZIPPER_INCLUDE_DIR
        NAMES zipper/zipper.h
        PATHS ${ZIPPER_INSTALL_PREFIX}/include
        )


# find bz library and include dirs
find_library(LIBBZ_STATIC_LIBRARY
        NAMES libbz2.a
        PATHS ${LIBSBML_DEPS_LIB_DIR}
        )
find_path(LIBBZ_INCLUDE_DIR
        NAMES bzip2/bzlib.h
        PATHS ${LIBSBML_DEPS_INCLUDE_DIR}
        )

# get libxml2 libraries
find_library(LIBXML2_STATIC_LIBRARY
        NAMES libxml2.a
        )

find_path(LIBXML2_INCLUDE_DIR
        NAMES libxml/parser.h
        PATHS /usr/local/include/libxml2
        )


# build libsbml
ExternalProject_Add(libsbml
        SOURCE_DIR ${LIBSBML_SOURCE_DIR}
        BINARY_DIR ${LIBSBML_BINARY_DIR}
        DEPENDS libsbml-dependencies
        CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX=${LIBSBML_INSTALL_PREFIX}
        -WITH_LIBXML=ON
        -DENABLE_LAYOUT=ON
        -DWITH_CPP_NAMESPACE=ON
        -DLIBSBML_DEPENDENCY_DIR=${LIBSBML_DEPS_INSTALL_PREFIX}
        -DLIBSBML_SKIP_SHARED_LIBRARY=ON
        )


# find the libsbml library and include dire
find_library(LIBSBML_STATIC_LIBRARY
        NAMES libsbml-static.a libsbml-static.lib
        PATHS ${LIBSBML_INSTALL_PREFIX}/lib
        REQUIRED
        )

find_path(LIBSBML_INCLUDE_DIR
        NAMES sbml/SBMLTypes.h
        PATHS ${LIBSBML_INSTALL_PREFIX}/include
        REQUIRED
        )

# build libcombine
ExternalProject_Add(libCombine
        SOURCE_DIR ${LIBCOMBINE_SOURCE_DIR}
        BINARY_DIR ${LIBCOMBINE_BINARY_DIR}
        DEPENDS
        zipper libsbml
        LIST_SEPARATOR | # for EXTRA_LIBS argument
        CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX=${LIBCOMBINE_INSTALL_PREFIX}
        -DLIBSBML_LIBRARY=${LIBSBML_STATIC_LIBRARY}
        -DLIBSBML_INCLUDE_DIR=${LIBSBML_INCLUDE_DIR}
        -DZIPPER_INCLUDE_DIR=${ZIPPER_INCLUDE_DIR}
        -DZIPPER_LIBRARY=${ZIPPER_STATIC_LIBRARY}
        -DEXTRA_LIBS=xml2|bz2|z|iconv #linux only, will need to change for windows
        )


find_library(LIBCOMBINE_STATIC_LIB
        NAMES libcombine-static.a
        PATHS ${LIBCOMBINE_INSTALL_PREFIX}/lib
        )
find_path(LIBCOMBINE_INCLUDE_DIR
        NAMES combine/combinearchive.h
        PATHS ${LIBCOMBINE_INSTALL_PREFIX}/include
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

SET(DEPENDENCIES
        ${ZLIB_STATIC_LIBRARY}
        ${ZLIB_INCLUDE_DIR}
        ${ZIPPER_STATIC_LIBRARY}
        ${ZIPPER_INCLUDE_DIR}
        ${LIBBZ_STATIC_LIBRARY}
        ${LIBBZ_INCLUDE_DIR}
        ${LIBXML2_STATIC_LIBRARY}
        ${LIBXML2_INCLUDE_DIR}
        ${LIBSBML_STATIC_LIBRARY}
        ${LIBSBML_INCLUDE_DIR}
        ${LIBCOMBINE_STATIC_LIB}
        ${LIBCOMBINE_INCLUDE_DIR}
        ${RAPTOR2_STATIC_LIBRARY}
        ${RAPTOR2_INCLUDE_DIR}
        ${RASQAL_STATIC_LIBRARY}
        ${RASQAL_INCLUDE_DIR}
        ${REDLAND_STATIC_LIBRARY}
        ${REDLAND_INCLUDE_DIR}
        )

# we now call and build the parent project with HAVE_DEPENDENCIES=TRUE
ExternalProject_Add(libsemsim
        DEPENDS zlib libsbml-dependencies zipper libsbml libCombine raptor rasqal librdf
        SOURCE_DIR ${CMAKE_SOURCE_DIR}
        BINARY_DIR ${CMAKE_BINARY_DIR}
        INSTALL_DIR ""
        CMAKE_ARGS
        -DHAVE_DEPENDENCIES=TRUE
        )

##################################################
# get redland libraries for linking
#

#set(REDLAND_ROOT "/mnt/d/redland" CACHE PATH "A directory containing the redland libraries, raptor2, rasqal and redland")
#
#set(RAPTOR2_INSTALL_PREFIX ${REDLAND_ROOT}/raptor2-2.0.15/install.linux)
#set(RASQAL_INSTALL_PREFIX ${REDLAND_ROOT}/rasqal-0.9.33/install)
#set(REDLAND_INSTALL_PREFIX ${REDLAND_ROOT}/redland-1.0.17/install)


# build raptor
#file(MAKE_DIRECTORY ${RAPTOR_INSTALL_PREFIX})
#file(MAKE_DIRECTORY ${RASQAL_INSTALL_PREFIX})
#file(MAKE_DIRECTORY ${LIBRDF_INSTALL_PREFIX})
#set(prefix "${RAPTOR_INSTALL_PREFIX}")
#ExternalProject_Add(raptor
#        SOURCE_DIR ${RAPTOR_SOURCE_DIR}
#        BINARY_DIR ${RAPTOR_BINARY_DIR}
#        MKDIR ${RAPTOR_INSTALL_PREFIX}
#
#        USES_TERMINAL_CONFIGURE 1
#        USES_TERMINAL_BUILD 1
#        USES_TERMINAL_INSTALL 1
#        CONFIGURE_COMMAND "${RAPTOR_SOURCE_DIR}/autogen.sh" "--prefix=${RAPTOR_INSTALL_PREFIX}"
#        BUILD_COMMAND "make"
#        INSTALL_COMMAND "make install"
#        )
#ExternalProject_Add_Step(raptor
#        CONFIGURE_
#        COMMAND "${RAPTOR_SOURCE_DIR}/autogen.sh" "--prefix=${RAPTOR_INSTALL_PREFIX}"
#        USES_TERMINAL 1
#        )

# raptor2


# build rasqal
#ExternalProject_Add(rasqal
#        SOURCE_DIR ${RASQAL_SOURCE_DIR}
#        BINARY_DIR ${RASQAL_BINARY_DIR}
#        DEPENDS raptor
#        CONFIGURE_COMMAND "${RASQAL_SOURCE_DIR}/autogen.sh --prefix=${RASQAL_INSTALL_PREFIX}"
#        BUILD_COMMAND "make"
#        INSTALL_COMMAND "make install"
#        )


## build librdf
#ExternalProject_Add(librdf
#        SOURCE_DIR ${LIBRDF_SOURCE_DIR}
#        BINARY_DIR ${LIBRDF_BINARY_DIR}
#        CONFIGURE_COMMAND "${LIBRDF_SOURCE_DIR}/autogen.sh --prefix=${LIBRDF_INSTALL_PREFIX}"
#        DEPENDS raptor rasqal
#        BUILD_COMMAND "make"
#        INSTALL_COMMAND "make install"
#        )
# redland api


###############################################################
# Call to build the original project
#

