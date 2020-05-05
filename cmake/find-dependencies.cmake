

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






