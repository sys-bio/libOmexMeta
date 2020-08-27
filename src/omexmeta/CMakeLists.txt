##########################################################################
#   Set libOmexMeta sources
#

set(target OmexMeta)

SET(OMEXMETA_PUBLIC_HEADERS
    "RDF.h"
    "Editor.h"
    "Triple.h"
    "Triples.h"
    "PhysicalForce.h"
    "PhysicalEntity.h"
    "PhysicalProcess.h"
    "PersonalInformation.h"
    "OmexMeta.h"
    "${CMAKE_CURRENT_BINARY_DIR}/omexmeta_export.h"
    )
set(OMEXMETA_HEADERS
    ${OMEXMETA_PUBLIC_HEADERS}
    "OmexMetaUtils.h"
    "CurlGet.h"
    "OmexMetaXmlAssistant.h"

    "Subject.h"
    "Resource.h"
    "Query.h"
    "Predicate.h"
    "MetaID.h"
    "PhysicalProperty.h"
    "Participant.h"

    "PhysicalPhenomenon.h"
    "AnnotationType.h"
    "OmexMeta.h"
    "MarkupIdentifier.h"
    sbml_semantic_extraction/ElementExtractor.cpp
    sbml_semantic_extraction/ElementExtractor.h
    sbml_semantic_extraction/SBMLSemanticExtraction.cpp
    sbml_semantic_extraction/SBMLSemanticExtraction.h
    OmexMetaXmlType.h
    dbg.h
    )

set(OMEXMETA_SOURCES
    "OmexMetaUtils.cpp"
    "RDF.cpp"
    "Query.cpp"
    "CurlGet.cpp"
    "OmexMetaXmlAssistant.cpp"
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
    "PersonalInformation.cpp"
    "MarkupIdentifier.cpp"
    sbml_semantic_extraction/ElementExtractor.cpp sbml_semantic_extraction/ElementExtractor.h sbml_semantic_extraction/SBMLSemanticExtraction.cpp sbml_semantic_extraction/SBMLSemanticExtraction.h)


#####################################################################3
#
#

# static library
add_library(${target}-static STATIC ${OMEXMETA_HEADERS} ${OMEXMETA_SOURCES})

# add redland-combined as dependency
add_dependencies(${target}-static redland-combined-static)

#includes
target_include_directories(
        ${target}-static PRIVATE
        ${INCLUDE_DIRECTORIES}
        ${CMAKE_CURRENT_BINARY_DIR} # for export header
)

target_compile_definitions(
        ${target}-static PRIVATE
        RAPTOR_STATIC
        RASQAL_STATIC
        LIBRDF_STATIC
        OMEXMETA_STATIC_DEFINE
)

# links
target_link_libraries(
        ${target}-static PRIVATE
        redland-combined-static
        ${LINK_LIBRARIES}
)
set_target_properties(${target}-static PROPERTIES PUBLIC_HEADER "${OMEXMETA_PUBLIC_HEADERS}")


# install
install(
        TARGETS ${target}-static
        EXPORT ${target}-static
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/omexmeta
)

# install the export info
install(
        EXPORT ${target}-static
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/omexmeta
        NAMESPACE OmexMeta::
        FILE OmexMetaStatic.cmake
)

# and build the CAPI if needed
if (${BUILD_C_API})
    add_subdirectory(C)
endif ()


# shared library
add_library(${target} SHARED "${OMEXMETA_HEADERS}" "${OMEXMETA_SOURCES}")

set_target_properties(${target} PROPERTIES SOVERSION ${LIBOMEXMETA_VERSION})

# includes
target_include_directories(
        ${target} PRIVATE
        ${INCLUDE_DIRECTORIES}
        ${CMAKE_CURRENT_BINARY_DIR}
)


# msvc, linux, macos values
# On msvc this is the lib file counterpart to the redland-combined dll
# on linux simply the .a file
# only for shared lib
SetCrossPlatform(REDLAND_LINK_LIBRARY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/redland-combined.lib $<TARGET_FILE:redland-combined-static> $<TARGET_FILE:redland-combined-static>)

# links
target_link_libraries(${target} PUBLIC
                      ${REDLAND_LINK_LIBRARY}
                      ${LINK_LIBRARIES}
                      )

# Technically linux version depends on static version and windows depends on the dynamic library
add_dependencies(${target} redland-combined redland-combined-static)

set_target_properties(${target} PROPERTIES PUBLIC_HEADER "${OMEXMETA_PUBLIC_HEADERS}")

# Write mytools_export.h to the current binary directory
generate_export_header(${target} BASE_NAME OMEXMETA)

# Static target needs special preprocessor define
# to prevent symbol import/export keywords being added
target_compile_definitions(
        ${target} PRIVATE
        OMEXMETA_STATIC_DEFINE
)


install(TARGETS ${target}
        EXPORT ${target}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/omexmeta
        )

# install the export info
install(
        EXPORT ${target}
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/omexmeta
        NAMESPACE OmexMeta::
        FILE ${target}.cmake
)


# for automatically installing to folder containing python api
install(FILES $<TARGET_FILE:${target}> DESTINATION ${PYOMEXMETA_DIR})
install(FILES $<TARGET_FILE:OmexMetaCAPI> DESTINATION ${PYOMEXMETA_DIR})


# install the shared library dependencies
if (PLATFORM STREQUAL "linux")

    # On linux we only need a few dynamic libraries due to static linking the rest.
    install(FILES ${LIBXML2_LIBRARY}
            ${LIBXSLT_LIBRARY}
            ${SQLITE3_LIBRARY}
            ${BERKELY_LIBRARY}
            ${POSTGRESQL_LIBRARY}
            DESTINATION ${PYOMEXMETA_DIR})

    # I had issues installing a few of the dynamic libraries, namely:
    #       - ${LIBXML2_LIBRARY}
    #       - ${LIBXSLT_LIBRARY}
    #       - ${SQLITE3_LIBRARY}
    #       - ${BERKELY_LIBRARY}
    #       - ${POSTGRESQL_LIBRARY}
    # Checkout the LINK_LIBRARIES variable for details on which were statically
    # and which were dynamically linked. I later realized that in order to use these at run time you need both a smbolic
    # link link libx.so.1 which points to the actual library libx.so.1.0.15. Both
    # need to be copied into the pyomexmeta src directory which will then be incorporated
    # into the python docs-build.
    # This is a viable strategy, and should probably be implemented soon so users do not
    # need to manually install packages from apt. However, for now, we rely on users
    # installing these dependencies manually.

    # The exception is the libstdc++ library. Since ive docs-build
    # using a later version than is easily obtainably
    # using apt-get, I just distribute along with python
    #        install(FILES ${LIBSTDCXX6_LIBRARY} DESTINATION ${PYOMEXMETA_DIR})


    # curl was statically linked in the end
    #        install(FILES "${CURL_LIBRARY}" DESTINATION ${PYOMEXMETA_DIR} RENAME libsqlite.so.0)

elseif (PLATFORM STREQUAL "windows-msvc")
    # Just take all of them on windows, since we've linked dynamically to everything
    install(FILES ${LIBRARIES} DESTINATION bin)

    # Remember to copy dependency dlls to pyomexmeta directory
    install(FILES ${LIBRARIES} DESTINATION ${PYOMEXMETA_DIR})
    install(FILES $<TARGET_FILE:redland-combined> DESTINATION ${PYOMEXMETA_DIR})

    # Note: I deleted the code that copies windows redistributables because
    #  the package "InstallRequiredSystemLibraries" does this for me
    #  just by including it. (Very nice).
    find_file(API_MS_WIN_CORE_WOW64_L1_1_0_LIBRARY NAMES api-ms-win-core-wow64-l1-1-0.dll PATHS C:/Windows/System32/downlevel)

    set(REDISTRIB
        ${CMAKE_INSTALL_PREFIX}/bin/concrt140.dll
        ${CMAKE_INSTALL_PREFIX}/bin/msvcp140.dll
        ${CMAKE_INSTALL_PREFIX}/bin/msvcp140_1.dll
        ${CMAKE_INSTALL_PREFIX}/bin/msvcp140_2.dll
        ${CMAKE_INSTALL_PREFIX}/bin/msvcp140_codecvt_ids.dll
        ${CMAKE_INSTALL_PREFIX}/bin/vcruntime140.dll
        ${CMAKE_INSTALL_PREFIX}/bin/vcruntime140_1.dll
        ${API_MS_WIN_CORE_WOW64_L1_1_0_LIBRARY}
        )
    if (NOT EXISTS "${CMAKE_INSTALL_PREFIX}")
        message(FATAL_ERROR "libOmexMeta needs to be installed before you
can copy windows redistributables into python directory")
    endif ()

    install(FILES ${REDISTRIB} DESTINATION ${PYOMEXMETA_DIR})

elseif (PLATFORM STREQUAL "macos")
    message(STATUS "macos == sad face =[")
endif ()
























