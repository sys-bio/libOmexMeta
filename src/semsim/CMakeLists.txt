
set(SEMSIM_HEADERS
        "SemsimUtils.h"
        "CurlGet.h"
        "RDF.h"
        "SemsimXmlAssistant.h"

        "Subject.h"
        "Resource.h"
        "Query.h"
        "Predicate.h"
        "Triple.h"
        "Triples.h"
        "MetaID.h"
        "PhysicalPropertyResource.h"
        "Participant.h"

        "PhysicalPhenomenon.h"
        "PhysicalEntity.h"
        "PhysicalProcess.h"
        "PhysicalForce.h"
        "AnnotationType.h"
        "Editor.h"
        #        "TripleWriter.h"
        "SemsimCApi.h"
        #        "HERE.h"
        #        Log.h
        #        RedlandAPIWrapper/RaptorIOStream.cpp
        #        RedlandAPIWrapper/RaptorIOStream.h
        #        "_Reader.h"
        #        "Writer.h"
        #                "SemSim.h"
        )

set(SEMSIM_SOURCES
        "SemsimUtils.cpp"
        "RDF.cpp"
        "Query.cpp"
        "CurlGet.cpp"
        "SemsimXmlAssistant.cpp"
        "Subject.cpp"
        "Resource.cpp"
        "Predicate.cpp"
        "Triple.cpp"
        "Triples.cpp"
        "PhysicalPropertyResource.cpp"
        "MetaID.cpp"
        "Participant.cpp"

        "PhysicalEntity.cpp"
        "PhysicalPhenomenon.cpp"
        "Editor.cpp"
        "PhysicalProcess.cpp"
        "PhysicalForce.cpp"
        "SemsimCApi.cpp"
        )


set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(SEMSIM_STATIC_LIBRARY semsim-static)
set(SEMSIM_LIBRARY semsim)


# static library
add_library(semsim-static STATIC ${SEMSIM_HEADERS} ${SEMSIM_SOURCES})

# add target headers so they install correctly
set_target_properties(semsim-static PROPERTIES PUBLIC_HEADER "${SEMSIM_HEADERS}")

add_dependencies(semsim-static redland-combined)
target_include_directories(${SEMSIM_STATIC_LIBRARY} PUBLIC # make public so include dirs propagate into test binaries
        ${INCLUDE_DIRS}
        ${WRAPPER_SOURCE_DIR}
        )


target_link_libraries(${SEMSIM_STATIC_LIBRARY} PUBLIC # make public so libraries propagate into test binaries
        $<TARGET_FILE:redland-combined>
        ${LINK_LIBRARIES}
        )


install(TARGETS semsim-static
        EXPORT semsim-static.a
        LIBRARY
        DESTINATION lib
        PUBLIC_HEADER DESTINATION include/semsim
        )


if (BUILD_SHARED)
    set(BUILD_SHARED_LIBS ON)
    set(CMAKE_VERBOSE_MAKEFILE ON)
    # shared library
    add_library(semsim SHARED "${SEMSIM_HEADERS}" "${SEMSIM_SOURCES}" Preproc.h)

    #    target_link_options(semsim PUBLIC -Wl,--whole-archive)
    #

    add_dependencies(semsim redland-combined)
    target_include_directories(semsim PUBLIC
            ${INCLUDE_DIRS}
            )

    target_link_libraries(semsim PUBLIC
            -Wl,--whole-archive
            $<TARGET_FILE:redland-combined>
            ${LINK_LIBRARIES}
            -Wl,--no-whole-archive
            )


    install(TARGETS semsim
            LIBRARY
            DESTINATION lib
            PUBLIC_HEADER DESTINATION include/semsim
            )

    # for automatically installing to folder containing python api
    install(TARGETS semsim
            LIBRARY
            DESTINATION ${CMAKE_SOURCE_DIR}/src/pysemsim
            )


endif ()


























