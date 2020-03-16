




ExternalProject_Add(libsbml-dependencies
        SOURCE_DIR ${LIBSBML_DEPS_SOURCE_DIR}
        BINARY_DIR ${LIBSBML_DEPS_BINARY_DIR}
        CMAKE_ARGS
            -DCMAKE_INSTALL_PREFIX=${LIBSBML_DEPS_SOURCE_DIR}/INSTALL
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        )

ExternalProject_Add(zipper
        SOURCE_DIR ${ZIPPER_SOURCE_DIR}
        BINARY_DIR ${ZIPPER_BINARY_DIR}
        CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=D:/libsemsim/third_party/zipper/install
        -DCMAKE_BUILD_TYPE=Debug
        -DLIBSBML_DEPS_INSTALL_PREFIX=D:/libsemsim/third_party/libSBML-dependencies/INSTALL
        -DLIBZ_LIBRARY=D:/libsemsim/third_party/libSBML-dependencies/INSTALL/lib/libzlib.a
        -DLIBZ_INCLUDE_DIR=D:/libsemsim/third_party/libSBML-dependencies/INSTALL/include
        )


ExternalProject_Add(libsbml
        SOURCE_DIR ${LIBSBML_SOURCE_DIR}
        BINARY_DIR ${LIBSBML_BINARY_DIR}
        DEPENDS
        libsbml-dependencies
        CMAKE_ARGS
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
            -DCMAKE_INSTALL_PREFIX=${LIBSBML_INSTALL_PREFIX}
            -WITH_LIBXML=ON
            #todo despite there being logic for handling the libsbml namespace
            #   it looks as though there is a namespace clash between libsbml::model
            #   and libsemsim::model when namespaces for libsbml are set to OFF.
            #todo Double check the truth of this and rectify.
            -DWITH_CPP_NAMESPACE=ON
            -DLIBSBML_DEPENDENCY_DIR=${LIBSBML_DEPS_INSTALL_PREFIX}
        )

# For some reason semi-colon lists go wrong when passed directly to CMAKE_ARGS
# so we can use a different delimiter for the list instead.
# https://stackoverflow.com/questions/45414507/pass-a-list-of-prefix-paths-to-externalproject-add-in-cmake-args
set(EXTRA
        "C:/cygwin64/lib/libxml2.dll.a"
        "${LIBSBML_DEPS_INSTALL_PRFIX}/lib/libbz2.a"
        "${LIBSBML_DEPS_INSTALL_PRFIX}/lib/libzlib.a"
        )
string(REPLACE ";" "|" EXTRA "${EXTRA}")

ExternalProject_Add(libCombine
        SOURCE_DIR ${LIBCOMBINE_SOURCE_DIR}
        BINARY_DIR ${LIBCOMBINE_BINARY_DIR}
        DEPENDS
        zipper libsbml
        LIST_SEPARATOR | # for EXTRA_LIBS argument
        CMAKE_ARGS
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
            -DCMAKE_INSTALL_PREFIX=${LIBCOMBINE_INSTALL_PREFIX}
            -DZIPPER_INSTALL_PREFIX=${ZIPPER_INSTALL_PREFIX}
            -DLIBSBML_DEPS_INSTALL_PREFIX=${LIBSBML_DEPS_INSTALL_PREFIX}
            -DLIBSBML_INSTALL_PREFIX=${LIBSBML_INSTALL_PREFIX}
            -DEXTRA_LIBS=${LIBBZ_LIBRARY}|${LIBXML2_LIBRARY}|${ZLIB_LIBRARY}
        )



#ExternalProject_Add(catch2
#        SOURCE_DIR ${CATCH2_SOURCE_DIR}
#        BINARY_DIR ${CATCH2_BINARY_DIR}
#        CMAKE_ARGS
#            -DCMAKE_INSTALL_PREFIX=${CATCH2_INSTALL_PREFIX}
#            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
#        )

#ExternalProject_Add(raptor2
#        SOURCE_DIR ${RAPTOR2_SOURCE_DIR}
#        BINARY_DIR ${RAPTOR2_BINARY_DIR}
#        PATHS ${RAPTOR_LIB_DIR}
#        CMAKE_ARGS
#            -DCMAKE_INSTALL_PREFIX=${RAPTOR2_INSTALL_PREFIX}
#            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
#        )


#ExternalProject_Add(rasqal
#        SOURCE_DIR ${RASQAL_SOURCE_DIR}
#        BINARY_DIR ${RASQAL_BINARY_DIR}
#        CMAKE_ARGS
#            -DCMAKE_INSTALL_PREFIX=${RASQAL_INSTALL_PREFIX}
#            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
#        )


