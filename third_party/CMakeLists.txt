




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
        -DCMAKE_INSTALL_PREFIX=${ZIPPER_INSTALL_PREFIX}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DLIBSBML_DEPS_INSTALL_PREFIX=${LIBSBML_DEPS_INSTALL_PREFIX}
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
            -DWITH_CPP_NAMESPACE=OFF
            -DLIBSBML_DEPENDENCY_DIR=${LIBSBML_DEPS_INSTALL_PREFIX}
        )


ExternalProject_Add(libCombine
        SOURCE_DIR ${LIBCOMBINE_SOURCE_DIR}
        BINARY_DIR ${LIBCOMBINE_BINARY_DIR}
        DEPENDS
        zipper libsbml
        CMAKE_ARGS
            -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
            -DCMAKE_INSTALL_PREFIX=${LIBCOMBINE_INSTALL_PREFIX}
            -DCMAKE_PREFIX_PATH=D:/libsemsim/third_party/libsbml/INSTALL
            -DZIPPER_INSTALL_PREFIX=D:/libsemsim/third_party/zipper/INSTALL
            -DLIBSBML_DEPS_INSTALL_PREFIX=D:/libsemsim/third_party/libSBML-dependencies/INSTALL
            -DEXTRA_LIBS=D:/libsemsim/third_party/libSBML-dependencies/INSTALL/lib/libbz2.a;C:/cygwin64/lib/libxml2.dll.a;D:/libsemsim/third_party/libSBML-dependencies/INSTALL/lib/libzlib.a        -DZIPPER_INSTALL_PREFIX=D:/libsemsim/third_party/zipper/INSTALL
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


