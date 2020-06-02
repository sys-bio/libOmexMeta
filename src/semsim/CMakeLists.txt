
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
        #        "SemsimCApi.h"
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
#                "SemsimCApi.cpp"
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
        ${LINK_LIBRARIES}
        $<TARGET_FILE:redland-combined>
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
    add_dependencies(semsim redland-combined)
    message(STATUS "LIBBZ_INCLUDE_DIR ${LIBBZ_INCLUDE_DIR}")
    target_include_directories(semsim PUBLIC # make public so include dirs propagate into test binaries
            ${INCLUDE_DIRS}
            )

    target_link_libraries(semsim PUBLIC # make public so libraries propagate into test binaries
            ${LINK_LIBRARIES}

            )
    set(x)
    get_target_property(x semsim LINK_LIBRARIES)

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


























