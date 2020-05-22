message(STATUS "inside semsim cmakelists")

set(SEMSIM_HEADERS
        "RedlandAPIWrappers/RedlandAPIWrapper.h"
        "RedlandAPIWrappers/LibrdfWorld.h"
        "RedlandAPIWrappers/RaptorWorld.h"
        "RedlandAPIWrappers/LibrdfStorage.h"
        "RedlandAPIWrappers/LibrdfModel.h"
        "RedlandAPIWrappers/LibrdfNode.h"
        "RedlandAPIWrappers/LibrdfUri.h"
        "RedlandAPIWrappers/LibrdfStatement.h"
        "RedlandAPIWrappers/LibrdfQuery.h"
        "RedlandAPIWrappers/LibrdfQueryResults.h"
        "RedlandAPIWrappers/LibrdfSerializer.h"
        "RedlandAPIWrappers/LibrdfParser.h"
        "RedlandAPIWrappers/LibrdfStream.h"

        #        "SemsimUtils.h"
        #        "RDFNode.h"
        #        "Subject.h"
        #        "Predicate.h"
        #        "CurlGet.h"
        #        "Resource.h"
        #        "Triple.h"
        #        "MetaID.h"
        #        "XmlAssistant.h"
        #        "Reader.h"
        #        "Editor.h"
        #        "Writer.h"
        #        "TripleWriter.h"
        #        "RDF.h"
        #        "SemSim.h"
        #        "Participant.h"
        #        "PhysicalEntity.h"
        #        "PhysicalPhenomenon.h"
        #        "PhysicalProcess.h"
        #        "PhysicalPropertyResource.h"
        #        "AnnotationType.h"
        #        "PhysicalForce.h"
        #        "Query.h"
        #        "Triples.h"
        #        "SemsimCApi.h"
        #        "HERE.h"
        )

set(SEMSIM_SOURCES
        "RedlandAPIWrappers/LibrdfWorld.cpp"
        "RedlandAPIWrappers/RaptorWorld.cpp"
        "RedlandAPIWrappers/LibrdfModel.cpp"
        "RedlandAPIWrappers/LibrdfNode.cpp"
        "RedlandAPIWrappers/LibrdfStorage.cpp"
        "RedlandAPIWrappers/RaptorWorld.cpp"
        "RedlandAPIWrappers/LibrdfUri.cpp"
        "RedlandAPIWrappers/LibrdfStatement.cpp"
        "RedlandAPIWrappers/LibrdfQuery.cpp"
        "RedlandAPIWrappers/LibrdfQueryResults.cpp"
        "RedlandAPIWrappers/LibrdfSerializer.cpp"
        "RedlandAPIWrappers/LibrdfParser.cpp"
        "RedlandAPIWrappers/LibrdfStream.cpp"

        #                "CurlGet.cpp"
        #                "SemsimUtils.cpp"
        #        "RDFNode.cpp"
        #        "Subject.cpp"
        #        "Predicate.cpp"
        #        "Resource.cpp"
        #        "Triple.cpp"
        #        "MetaID.cpp"
        #        "XmlAssistant.cpp"
        #        "Reader.cpp"
        #        "Editor.cpp"
        #        "Writer.cpp"
        #        "TripleWriter.cpp"
        #        "RDF.cpp"
        #        "Participant.cpp"
        #        "PhysicalEntity.cpp"
        #        "PhysicalPhenomenon.cpp"
        #        "PhysicalProcess.cpp"
        #        "PhysicalPropertyResource.cpp"
        #        "PhysicalForce.cpp"
        #        "Query.cpp"
        #        "Triples.cpp"
        #        "SemsimCApi.cpp"
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
        ${INCLUDE_DIRS}
        )


target_link_libraries(${SEMSIM_STATIC_LIBRARY} PUBLIC # make public so libraries propagate into test binaries
        ${LINK_LIBRARIES}
        )


message(STATUS "Installing to ${CMAKE_INSTALL_PREFIX}")
install(TARGETS semsim-static
        EXPORT semsim-static.a
        LIBRARY
        DESTINATION lib
        PUBLIC_HEADER DESTINATION include
        )


if (BUILD_SHARED)
    set(BUILD_SHARED_LIBS ON)
    set(CMAKE_VERBOSE_MAKEFILE ON)
    # shared library
    add_library(semsim SHARED "${SEMSIM_HEADERS}" "${SEMSIM_SOURCES}")

    #    target_link_options(semsim PUBLIC -Wl,--whole-archive)
    #
    message(STATUS "LIBBZ_INCLUDE_DIR ${LIBBZ_INCLUDE_DIR}")
    target_include_directories(semsim PUBLIC # make public so include dirs propagate into test binaries
            ${INCLUDE_DIRS}
            )

    target_link_libraries(semsim PUBLIC # make public so libraries propagate into test binaries
            z
            ${LINK_LIBRARIES}

            )
    set(x)
    get_target_property(x semsim LINK_LIBRARIES)

    message(STATUS "xASDFASD ${x}")
    install(TARGETS semsim
            LIBRARY
            DESTINATION lib
            PUBLIC_HEADER DESTINATION include
            )
    install(TARGETS semsim
            LIBRARY
            DESTINATION ${CMAKE_SOURCE_DIR}/src/pysemsim
            )


endif ()




























