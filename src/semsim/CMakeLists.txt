
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


# add target headers so they install correctly
set_target_properties(semsim-static PROPERTIES PUBLIC_HEADER "${SEMSIM_HEADERS}")

# set runtime static for windows (ignored on other systems)
set_target_properties(semsim-static PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded")

add_dependencies(semsim-static redland-combined-static)
target_include_directories(semsim-static PUBLIC # make public so include dirs propagate into test binaries
        ${INCLUDE_DIRECTORIES}
        ${WRAPPER_SOURCE_DIR}
        )


target_link_libraries(semsim-static PUBLIC # make public so libraries propagate into test binaries
        $<TARGET_FILE:redland-combined-static>
        ${LINK_LIBRARIES}
        )


install(TARGETS semsim-static
        EXPORT semsim-static
        LIBRARY
        DESTINATION lib
        PUBLIC_HEADER DESTINATION include/semsim
        )


if (${BUILD_SHARED_LIBS})

    set(CMAKE_BUILD_RPATH_USE_ORIGIN TRUE)
    set(CMAKE_INSTALL_RPATH
            "${CMAKE_INSTALL_PREFIX}/lib"   # probs not needed, but for good measure
            "${PYSEMSIM_DIR}"               # python test package
            "$ORIGIN"                       # current directory (for when in site-packages)
            )
    set_target_properties(${semsim} PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)

    set(CMAKE_VERBOSE_MAKEFILE ON)

    # shared library
    add_library(semsim SHARED "${SEMSIM_HEADERS}" "${SEMSIM_SOURCES}" Preproc.h)

    # set runtime shared for windows (ignored on other systems)
    if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
        set_property(TARGET semsim PROPERTY
                MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    elseif (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set_property(TARGET semsim PROPERTY
                MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")
    endif ()

    add_dependencies(semsim redland-combined-static)
    target_include_directories(semsim PUBLIC
            ${INCLUDE_DIRECTORIES}
            )

    target_link_libraries(semsim PUBLIC
            ${CMAKE_BINARY_DIR}/lib/redland-combined.lib
            ${LINK_LIBRARIES}
            )

    install(TARGETS semsim
            LIBRARY
            ARCHIVE
            RUNTIME
            PUBLIC_HEADER DESTINATION include/semsim
            )

    install(FILES ${LIBRARIES_DLL}
            DESTINATION bin
            )


    # for automatically installing to folder containing python api
    install(TARGETS semsim
            RUNTIME DESTINATION ${PYSEMSIM_DIR}
            )
    # and remember we need the dll's in the python src dir as well
    install(FILES ${LIBRARIES_DLL}
            DESTINATION ${PYSEMSIM_DIR}
            )


    if (PLATFORM STREQUAL "linux")
        install(FILES ${LIBXML2_LIBRARY} ${LIBCURL_LIBRARY}
                DESTINATION ${PYSEMSIM_DIR})
    elseif (PLATFORM STREQUAL "windows-msvc")
    endif ()

    # An alternative command that copies on configuration, not install
    #    file(COPY ${LIBXML2_LIBRARY} DESTINATION ${PYSEMSIM_DIR})

endif ()


























