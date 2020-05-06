message(STATUS "inside semsim cmakelists")

set(SEMSIM_SOURCES
        "CurlGet.cpp"
        "RDFNode.cpp"
        "Subject.cpp"
        "Predicate.cpp"
        "Resource.cpp"
        "Triple.cpp"
        "SemsimUtils.cpp"
        "MetaID.cpp"
        "XmlAssistant.cpp"
        "Reader.cpp"
        "Editor.cpp"
        "Writer.cpp"
        "RDF.cpp"
        "Participant.cpp"
        "PhysicalEntity.cpp"
        "PhysicalPhenomenon.cpp"
        "PhysicalProcess.cpp"
        "PhysicalPropertyResource.cpp"
        "PhysicalForce.cpp"
        "Query.cpp"
        "SemsimCombineArchive.cpp"
        "Triples.cpp"
        )

set(SEMSIM_HEADERS
        "CurlGet.h"
        "RDFNode.h"
        "Subject.h"
        "Predicate.h"
        "Resource.h"
        "Triple.h"
        "SemsimUtils.h"
        "MetaID.h"
        "XmlAssistant.h"
        "Reader.h"
        "Editor.h"
        "Writer.h"
        "RDF.h"
        "SemSim.h"
        "Participant.h"
        "PhysicalEntity.h"
        "PhysicalPhenomenon.h"
        "PhysicalProcess.h"
        "PhysicalPropertyResource.h"
        "AnnotationType.h"
        "PhysicalForce.h"
        "Query.h"
        "SemsimCombineArchive.h"
        "Triples.h"
        )

message(STATUS "SEMSIM_HEADERS ${SEMSIM_HEADERS}")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SEMSIM_STATIC_LIBRARY semsim-static)
set(SEMSIM_LIBRARY semsim)


# static library
add_library(${SEMSIM_STATIC_LIBRARY} STATIC ${SEMSIM_HEADERS} ${SEMSIM_SOURCES})

# add target headers so they install correctly
    set_target_properties(semsim-static PROPERTIES PUBLIC_HEADER "${SEMSIM_HEADERS}")


target_include_directories(${SEMSIM_STATIC_LIBRARY} PUBLIC # make public so include dirs propagate into test binaries
        ${CMAKE_SOURCE_DIR}
        ${CYG_INCLUDE_DIR}

        ${LIBXML2_INCLUDE_DIR}
        ${LIBSBML_DEPS_INCLUDE_DIR}
        ${LIBSBML_INCLUDE_DIR}
        ${ZLIB_INCLUDE_DIR}
        ${ZIPPER_INCLUDE_DIR}
        ${LIBCOMBINE_INCLUDE_DIR}
        ${LIBBZ_INCLUDE_DIR}

        ${REDLAND_INCLUDE_DIR}
        ${RASQAL_INCLUDE_DIR}
        ${RAPTOR2_INCLUDE_DIR}

        )

target_link_libraries(${SEMSIM_STATIC_LIBRARY} PUBLIC # make public so libraries propagate into test binaries
        ${LIBCOMBINE_STATIC_LIB}
        ${ZIPPER_STATIC_LIBRARY}
        ${ZLIB_STATIC_LIBRARY}
        ${LIBSBML_STATIC_LIB}
        ${LIBBZ_STATIC_LIBRARY}
        ${REDLAND_LIBRARY}
        ${RASQAL_LIBRARY}
        ${RAPTOR2_LIBRARY}
        ${LIBXML2_STATIC_LIBRARY}
        dl bz2 z curl xslt
        )


message(STATUS "Installing to ${CMAKE_INSTALL_PREFIX}")
install(TARGETS semsim-static
        EXPORT semsim-static.a
        LIBRARY
        DESTINATION lib
        PUBLIC_HEADER DESTINATION include

        )

#    add_dependencies(semsim-static
#            libsbml
#            libCombine
#            zipper
#            libsbml-dependencies
#            )

# shared library
#add_library(${SEMSIM_LIBRARY} SHARED ${SEMSIM_SOURCES})
#if (UNIX)
#    MESSAGE(STATUS "LINUX strS")
#fPIC for linux shared library strs
#    set_property(TARGET ${SEMSIM_LIBRARY} PROPERTY POSITION_INDEPENDENT_CODE ON)
#endif ()


#target_include_directories(${SEMSIM_LIBRARY} PUBLIC # make public so include dirs propagate into test binaries
#        ${CMAKE_SOURCE_DIR}
#        ${CYG_INCLUDE_DIR}
#
#        ${LIBXML2_INCLUDE_DIR}
#        ${LIBSBML_DEPS_INCLUDE_DIR}
#        ${LIBSBML_INCLUDE_DIR}
#        ${ZLIB_INCLUDE_DIR}
#        ${ZIPPER_INCLUDE_DIR}
#        ${LIBCOMBINE_INCLUDE_DIR}
#        ${LIBBZ_INCLUDE_DIR}
#        ${RAPTOR2_INCLUDE_DIR}
#        ${RASQAL_INCLUDE_DIR}
#        ${REDLAND_INCLUDE_DIR}
#        )

#target_link_libraries(${SEMSIM_LIBRARY} PUBLIC # make public so libraries propagate into test binaries
#        ${LIBCOMBINE_STATIC_LIB}
#        ${LIBXML2_STATIC_LIBRARY}
#        ${LIBSBML_STATIC_LIBRARY}
#        #        ${ZLIB_STATIC_LIBRARY}
#        ${ZIPPER_STATIC_LIBRARY}
#        #        ${LIBBZ_STATIC_LIBRARY}
#        ${RAPTOR2_LIBRARY}
#        ${RASQAL_LIBRARY}
#        ${REDLAND_LIBRARY}
#        dl bz2 z curl xslt
#        )
