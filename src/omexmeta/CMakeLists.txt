##########################################################################
#   Set libOmexMeta sources
#

set(target OmexMeta)

# Note: this doesn't work as intended when using the install tree.
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
    "logger.h"
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
    "ElementExtractor.h"
    "SBMLSemanticExtraction.h"
    "OmexMetaXmlType.h"
    "Error.h"
    #    dbg.h
    )

set(OMEXMETA_SOURCES
    "ElementExtractor.cpp"
    "SBMLSemanticExtraction.cpp"
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
    )


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
        OMEXMETA_STATIC_DEFINE #indicate use of omex static library
        REDLAND_STATIC_DEFINE # indivate use of redland static library
)

# links
target_link_libraries(
        ${target}-static PRIVATE
        redland-combined-static
        ${LINK_LIBRARIES}
)
set_target_properties(${target}-static PROPERTIES PUBLIC_HEADER "${OMEXMETA_HEADERS}")


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
    # C API binary

    set(CAPI_SOURCES OmexMetaCApi.h OmexMetaCApi.cpp
        "${CMAKE_CURRENT_BINARY_DIR}/omexmetacapi_export.h"
        )


    add_library(OmexMetaCAPI SHARED ${CAPI_SOURCES})
    generate_export_header(OmexMetaCAPI BASE_NAME OmexMetaCAPI)
    set_target_properties(OmexMetaCAPI PROPERTIES
                          PUBLIC_HEADER "OmexMetaCApi.h;${CMAKE_CURRENT_BINARY_DIR}/omexmetacapi_export.h"
                          SOVERSION ${LIBOMEXMETA_VERSION}
                          )

    #includes
    get_filename_component(PARENT_DIR ${CMAKE_CURRENT_BINARY_DIR} DIRECTORY)
    target_include_directories(OmexMetaCAPI PRIVATE
                               ${INCLUDE_DIRECTORIES}
                               ${CMAKE_CURRENT_SOURCE_DIR}
                               ${CMAKE_CURRENT_BINARY_DIR} # CAPI export header
                               ${PARENT_DIR} # C++ api export header
                               )


    # These need defining to indicate that we're linking the static
    # version of omexmeta and redland as well as exporting
    # symbols from the omexmeta c api
    target_compile_definitions(OmexMetaCAPI PRIVATE
                               OmexMetaCAPI_EXPORTS
                               OMEXMETA_STATIC_DEFINE
                               REDLAND_STATIC_DEFINE
                               )

    # links
    target_link_libraries(OmexMetaCAPI PRIVATE
                          -Wl,--whole-archive
                          OmexMeta-static
                          redland-combined-static
                          -Wl,--no-whole-archive
                          ${LINK_LIBRARIES}
                          )
    add_dependencies(OmexMetaCAPI OmexMeta-static redland-combined-static)

    # add to ctest target
    add_test(
            NAME OmexMetaCAPI
            COMMAND $<TARGET_FILE:OmexMetaCAPI>
    )


    # install
    install(TARGETS OmexMetaCAPI
            EXPORT OmexMetaCAPI
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/omexmeta
            )


    # install the export info
    install(
            EXPORT OmexMetaCAPI
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/omexmeta
            NAMESPACE OmexMeta::
            FILE OmexMetaCAPI.cmake
    )
    install(FILES $<TARGET_FILE:OmexMetaCAPI> DESTINATION ${PYOMEXMETA_DIR})
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

set_target_properties(${target} PROPERTIES PUBLIC_HEADER "${OMEXMETA_HEADERS}")

# Write mytools_export.h to the current binary directory
generate_export_header(${target} BASE_NAME OMEXMETA)

# Static target needs special preprocessor define
# to prevent symbol import/export keywords being added
target_compile_definitions(
        ${target} PRIVATE
        OmexMeta_EXPORTS # indicate that we are building this library to get correct export symbols

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
    if (EXISTS "${CMAKE_INSTALL_PREFIX}")
        install(FILES ${REDISTRIB} DESTINATION ${PYOMEXMETA_DIR})
        #        message(FATAL_ERROR "libOmexMeta needs to be installed before you \
        #can copy windows redistributables into python directory. Please -DBUILD_PACKAGING=OFF until \
        #you have built the windows install tree.")
    endif ()


elseif (PLATFORM STREQUAL "macos")
    message(STATUS "macos == sad face =[")
endif ()


# note to self.
# If I'm using the install tree then it is up to the user to provide
# curl and libxml2 include dirs.
#
## Curl headers
##   collect and install the curl headers since you've used curl as a dependency.
##   Its probably worth removing this dependency as the OmexMetaUtils::download
##   utility isn't essential.
#if (NOT EXISTS ${CURL_INCLUDE_DIR})
#    message(FATAL_ERROR "No curl include directory found")
#endif ()
#
#file(GLOB CURL_HEADERS "${CURL_INCLUDE_DIR}/curl/*.h")
#message(STATUS "CURL ${CURL_INCLUDE_DIR}/curl/*.h ${CURL_HEADERS}")
#install(FILES ${CURL_HEADERS} DESTINATION "include/curl")
#
## libxml headers
##   Again, for the install tree to be functional we need
##   libxml headers available. Simple solution is to copy them
##   accross. May be another better solution
#if (NOT EXISTS ${LIBXML2_INCLUDE_DIR})
#    message(FATAL_ERROR "No libxml2 include directory found")
#endif ()
#
#file(GLOB LIBXML_HEADERS "${LIBXML2_INCLUDE_DIR}/curl/*.h")
#message(STATUS "CURL ${LIBXML2_INCLUDE_DIR}/libxml/*.h ${LIBXML_HEADERS}")
#install(FILES ${LIBXML_HEADERS} DESTINATION "include/libxml")
#
#
#

















