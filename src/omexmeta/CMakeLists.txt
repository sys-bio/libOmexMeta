##########################################################################
#   Set libOmexMeta sources
#
set(OMEXMETA_HEADERS
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
        "SemsimCApi.h"
        )

set(OMEXMETA_SOURCES
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


#####################################################################3
#
#

# static library
add_library(OmexMeta-static STATIC ${OMEXMETA_HEADERS} ${OMEXMETA_SOURCES})

# set runtime static for windows (ignored on other systems)
set_target_properties(OmexMeta-static PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded")

# add redland-combined as dependency
add_dependencies(OmexMeta-static redland-combined-static)

#includes
target_include_directories(OmexMeta-static PRIVATE
        ${INCLUDE_DIRECTORIES}
        )

# links
target_link_libraries(OmexMeta-static PRIVATE
        $<TARGET_FILE:redland-combined-static>
        ${LINK_LIBRARIES}
        )

# install
install(TARGETS OmexMeta-static
        EXPORT OmexMeta-static
        LIBRARY
        DESTINATION lib
        PUBLIC_HEADER DESTINATION include/omexmeta
        )


if (${BUILD_SHARED_LIBS})

    # FIXME some redundancy here.
    # RPATH: on linux determines where shared libraries look for other shared library dependencies.
#    set(CMAKE_BUILD_RPATH_USE_ORIGIN ON)
#    set(CMAKE_INSTALL_RPATH "")
#    set(CMAKE_INSTALL_RPATH ".")
#    set(CMAKE_BUILD_RPATH "$ORIGIN:1")
#    set(CMAKE_INSTALL_RPATH "$ORIGIN:2")

    
    # shared library
    add_library(OmexMeta SHARED "${OMEXMETA_HEADERS}" "${OMEXMETA_SOURCES}" Preproc.h)
    set_target_properties(OmexMeta PROPERTIES INSTALL_RPATH "$ORIGIN")
    set_target_properties(OmexMeta PROPERTIES BUILD_RPATH "$ORIGIN")
#    set_target_properties(OmexMeta PROPERTIES BUILD_RPATH_USE_ORIGIN TRUE)
    GET_TARGET_PROPERTY(V OmexMeta INSTALL_RPATH)
    MESSAGE(V ${V})

    # set runtime shared for windows (ignored on other systems)
    if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
        set_property(TARGET OmexMeta PROPERTY
                MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    elseif (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        set_property(TARGET OmexMeta PROPERTY
                MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL")
    endif ()

    # includes
    target_include_directories(OmexMeta PUBLIC
            ${INCLUDE_DIRECTORIES}
            )

    # msvc, linux, macos values
    # On msvc this is the lib file counterpart to the redland-combined dll
    # on linux simply the .a file
    # only for shared lib
    SetCrossPlatform(REDLAND_LINK_LIBRARY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/redland-combined.lib $<TARGET_FILE:redland-combined-static> $<TARGET_FILE:redland-combined-static>)

    # links
    target_link_libraries(OmexMeta PUBLIC
            ${REDLAND_LINK_LIBRARY}
            ${LINK_LIBRARIES}
            )

    # Technically linux version depends on static version and windows depends on the dynamic library
    add_dependencies(OmexMeta redland-combined redland-combined-static)

    # install target
    install(TARGETS OmexMeta
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
            RUNTIME DESTINATION bin
            PUBLIC_HEADER DESTINATION include/OmexMeta
            )

    # for automatically installing to folder containing python api
    install(TARGETS OmexMeta
            RUNTIME DESTINATION ${PYOMEXMETA_DIR}
            )

    # install the shared library dependencies
    if (PLATFORM STREQUAL "linux")
        # On linux we only need a few dynamic libraries due to static linking the rest.
        install(FILES $<TARGET_FILE:OmexMeta> DESTINATION ${PYOMEXMETA_DIR})
#        install(FILES "${LIBXML2_LIBRARY}" DESTINATION ${PYOMEXMETA_DIR} RENAME libxml2.so.2)
#        install(FILES "${LIBXSLT_LIBRARY}" DESTINATION ${PYOMEXMETA_DIR} RENAME libxslt.so.1)
#        install(FILES "${SQLITE3_LIBRARY}" DESTINATION ${PYOMEXMETA_DIR} RENAME libsqlite3.so.0)
#        install(FILES "${BERKELY_LIBRARY}" DESTINATION ${PYOMEXMETA_DIR} RENAME libdb-5.3.so)
#        install(FILES "${POSTGRESQL_LIBRARY}" DESTINATION ${PYOMEXMETA_DIR} RENAME libpq.so.5)

        # curl was statically linked in the end
#        install(FILES "${CURL_LIBRARY}" DESTINATION ${PYOMEXMETA_DIR} RENAME libsqlite.so.0)

    elseif (PLATFORM STREQUAL "windows-msvc")
        # Just take all of them on windows, since we've linked dynamically to everything
        install(FILES ${LIBRARIES} DESTINATION bin)

        # Remember to copy dependency dlls to pyomexmeta directory
        install(FILES ${LIBRARIES} DESTINATION ${PYOMEXMETA_DIR})
        install(FILES $<TARGET_FILE:redland-combined> DESTINATION ${PYOMEXMETA_DIR})

    elseif (PLATFORM STREQUAL "macos")
        message(STATUS "macos == sad face =[")
    endif ()


endif ()


























