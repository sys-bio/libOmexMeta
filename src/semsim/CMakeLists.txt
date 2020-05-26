message(STATUS "inside semsim cmakelists")

set(SEMSIM_HEADERS
        "RedlandAPIWrapper/RedlandAPIWrapper.h"
        "RedlandAPIWrapper/World.h"
        "RedlandAPIWrapper/RaptorWorld.h"
        "RedlandAPIWrapper/LibrdfStorage.h"
        "RedlandAPIWrapper/LibrdfModel.h"
        "RedlandAPIWrapper/LibrdfNode.h"
        "RedlandAPIWrapper/LibrdfUri.h"
        "RedlandAPIWrapper/LibrdfStatement.h"
        "RedlandAPIWrapper/LibrdfQuery.h"
        "RedlandAPIWrapper/LibrdfQueryResults.h"
        "RedlandAPIWrapper/LibrdfSerializer.h"
        "RedlandAPIWrapper/LibrdfParser.h"
        "RedlandAPIWrapper/LibrdfStream.h"

        "SemsimUtils.h"
        "Subject.h"
        "Predicate.h"
        "Resource.h"
        "CurlGet.h"
        "Triple.h"
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
        RedlandAPIWrapper/RaptorTermValue.cpp RedlandAPIWrapper/RaptorTermValue.h Log.h)

set(SEMSIM_SOURCES
        "RedlandAPIWrapper/World.cpp"
        "RedlandAPIWrapper/RaptorWorld.cpp"
        "RedlandAPIWrapper/LibrdfModel.cpp"
        "RedlandAPIWrapper/LibrdfNode.cpp"
        "RedlandAPIWrapper/LibrdfStorage.cpp"
        "RedlandAPIWrapper/RaptorWorld.cpp"
        "RedlandAPIWrapper/LibrdfUri.cpp"
        "RedlandAPIWrapper/LibrdfStatement.cpp"
        "RedlandAPIWrapper/LibrdfQuery.cpp"
        "RedlandAPIWrapper/LibrdfQueryResults.cpp"
        "RedlandAPIWrapper/LibrdfSerializer.cpp"
        "RedlandAPIWrapper/LibrdfParser.cpp"
        "RedlandAPIWrapper/LibrdfStream.cpp"

        "SemsimUtils.cpp"
        "Subject.cpp"
        "Predicate.cpp"
        "Resource.cpp"
        #        "RDFNode.cpp"
        "CurlGet.cpp"
        "Triple.cpp"
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
        RedlandAPIWrapper/RaptorTermValue.cpp RedlandAPIWrapper/RaptorTermValue.h Log.h)

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
    add_library(semsim SHARED "${SEMSIM_HEADERS}" "${SEMSIM_SOURCES}" Preproc.h)

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


if (BUILD_DOCS)
    # https://devblogs.microsoft.com/cppblog/clear-functional-c-documentation-with-sphinx-breathe-doxygen-cmake/
    find_package(Doxygen REQUIRED)

    set(DOXYGEN_INPUT_DIR "${CMAKE_SOURCE_DIR}/src/semsim")
    set(DOXYGEN_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/docs/cpp")
    set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.html)
    set(DOXYFILE_IN ${CMAKE_SOURCE_DIR}/Doxyfile.in)
    set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)


    configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)
    file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})

    add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
            DEPENDS ${SEMSIM_HEADERS}
            COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            MAIN_DEPENDENCY Doxyfile
            COMMENT "Generating docs")

    add_custom_target(Doxygen ALL DEPENDS ${DOXYGEN_INDEX_FILE})
endif ()


























