
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
        "PhysicalProperty.h"
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
        "PhysicalProperty.cpp"
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

# set runtime static for windows (ignored on other systems)
set_property(TARGET semsim-static PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded")

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

    set(CMAKE_BUILD_RPATH_USE_ORIGIN TRUE)
    set(CMAKE_INSTALL_RPATH
            "${CMAKE_INSTALL_PREFIX}/lib"   # probs not needed, but for good measure
            "${PYSEMSIM_DIR}"               # python test package
            "$ORIGIN"                       # current directory (for when in site-packages)
            )


    set(BUILD_SHARED_LIBS ON)
    set(CMAKE_VERBOSE_MAKEFILE ON)

    # shared library
    add_library(semsim SHARED "${SEMSIM_HEADERS}" "${SEMSIM_SOURCES}" Preproc.h)

    # set runtime static for windows (ignored on other systems)
    set_property(TARGET semsim PROPERTY
            MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")

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
    set_target_properties(${semsim} PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)

    install(TARGETS semsim
            LIBRARY
            DESTINATION lib
            PUBLIC_HEADER DESTINATION include/semsim
            )

    # for automatically installing to folder containing python api
    install(TARGETS semsim
            LIBRARY
            DESTINATION ${PYSEMSIM_DIR}
            )

    message(STATUS "LIBXML_LIBRARY ${LIBXML_LIBRARY}")
    #    if (NOT EXISTS ${LIBXML2_LIBRARY})
    #        message(FATAL_ERROR "libxml not found.  Build dependencies first ")
    #    endif ()
    #
    #    if (NOT EXISTS ${LIBCURL_LIBRARY})
    #        message(FATAL_ERROR "libcurl not found. Build dependencies first")
    #    endif ()
    install(FILES ${LIBXML2_LIBRARY} ${LIBCURL_LIBRARY}
            DESTINATION ${PYSEMSIM_DIR})


    # An alternative command that copies on configuration, not install
    #    file(COPY ${LIBXML2_LIBRARY} DESTINATION ${PYSEMSIM_DIR})


endif ()


























