##########################################################################
#   Set libOmexMeta sources
#

set(target OmexMeta)

set(OMEXMETA_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Note: this doesn't work as intended when using the install tree.
SET(OMEXMETA_PUBLIC_HEADERS
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/RDF.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/Editor.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/Triple.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/Triples.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/EnergyDiff.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/PhysicalEntity.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/PhysicalProcess.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/PersonalInformation.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/OmexMeta.h"
        "${CMAKE_CURRENT_BINARY_DIR}/omexmeta_export.h"
        )

set(OMEXMETA_HEADERS
        ${OMEXMETA_PUBLIC_HEADERS}
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/logger.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/OmexMetaUtils.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/CurlGet.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/OmexMetaXmlAssistant.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/Subject.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/Resource.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/Query.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/Predicate.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/MetaID.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/PhysicalProperty.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/Participant.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/PropertyBearer.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/AnnotationType.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/OmexMeta.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/MarkupIdentifier.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/ElementExtractor.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/SBMLSemanticExtraction.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/OmexMetaXmlType.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/Error.h"
        "${OMEXMETA_INCLUDE_DIR}/omexmeta/UriHandler.h"
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
        "PropertyBearer.cpp"
        "Editor.cpp"
        "PhysicalProcess.cpp"
        "EnergyDiff.cpp"
        "PersonalInformation.cpp"
        "MarkupIdentifier.cpp"
        "UriHandler.cpp"
        )


#####################################################################3
#
#

# static library
add_library(${target}-static STATIC ${OMEXMETA_HEADERS} ${OMEXMETA_SOURCES})

# add redland-combined as dependency
add_dependencies(${target}-static redland-combined-static)

set_target_properties(${target}-static PROPERTIES OUTPUT_NAME ${target}-static-${LIBOMEXMETA_VERSION})

# links
target_link_libraries(
        ${target}-static PUBLIC
        redland-combined-static
        #        ${LINK_LIBRARIES}
)

#includes
target_include_directories(
        ${target}-static
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_compile_definitions(
        ${target}-static PUBLIC
        OMEXMETA_STATIC_DEFINE #indicate use of omex static library
)

# install
install(
        TARGETS ${target}-static
        EXPORT ${target}-static
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/omexmeta
)
message(STATUS "VCPKG_INCLUDE_DIR ${VCPKG_INCLUDE_DIR}")
# install the export info
install(
        EXPORT ${target}-static
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/omexmeta
        NAMESPACE OmexMeta::
        FILE OmexMetaStatic.cmake
)

##########################################
# shared library
#

add_library(${target} SHARED "${OMEXMETA_HEADERS}" "${OMEXMETA_SOURCES}")

set_target_properties(${target} PROPERTIES SOVERSION ${LIBOMEXMETA_VERSION})

target_link_libraries(${target} PUBLIC $<TARGET_PROPERTY:${target}-static,LINK_LIBRARIES>)
target_include_directories(${target} PUBLIC $<TARGET_PROPERTY:${target}-static,INCLUDE_DIRECTORIES>)
add_dependencies(${target} redland-combined-static)

if (WIN32)
    # mac already does this and linux has so name
    set_target_properties(${target} PROPERTIES OUTPUT_NAME ${target}-${LIBOMEXMETA_VERSION})
endif ()

generate_export_header(${target} BASE_NAME OMEXMETA)

# Static target needs special preprocessor define
# to prevent symbol import/export keywords being added
target_compile_definitions(
        ${target} PUBLIC
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


##########################################
# C API library
#

add_library(${target}CAPI SHARED "${CMAKE_CURRENT_SOURCE_DIR}/OmexMetaCApi.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/include/omexmeta/OmexMetaCApi.h")

set_target_properties(${target}CAPI PROPERTIES SOVERSION ${LIBOMEXMETA_VERSION})

target_link_libraries(${target}CAPI PUBLIC ${target}-static)
target_include_directories(
        ${target}CAPI PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<BUILD_INTERFACE:$<TARGET_PROPERTY:${target}-static,INCLUDE_DIRECTORIES>>
)
add_dependencies(${target}CAPI ${target}-static)

set_target_properties(${target}CAPI PROPERTIES OUTPUT_NAME "${target}CAPI-${LIBOMEXMETA_VERSION}")

generate_export_header(${target}CAPI BASE_NAME OMEXMETA_CAPI)
target_compile_definitions(${target}CAPI PUBLIC OmexMeta_CAPI_EXPORTS)

install(TARGETS ${target}CAPI
        EXPORT ${target}CAPI
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/omexmeta
        )

# install the export info
install(
        EXPORT ${target}CAPI
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/omexmeta
        NAMESPACE OmexMeta::
        FILE ${target}CAPI.cmake
)




#
## for automatically installing to folder containing python api
#install(FILES $<TARGET_FILE:${target}> DESTINATION ${PYOMEXMETA_DIR})
#install(FILES $<TARGET_FILE:OmexMetaCAPI> DESTINATION ${PYOMEXMETA_DIR})
#
#
## install the shared library dependencies
#if (PLATFORM STREQUAL "linux")
#
#    # On linux we only need a few dynamic libraries due to static linking the rest.
#    install(FILES ${LIBXML2_LIBRARY}
#            ${LIBXSLT_LIBRARY}
#            ${SQLITE3_LIBRARY}
#            ${BERKELY_LIBRARY}
#            ${POSTGRESQL_LIBRARY}
#            DESTINATION ${PYOMEXMETA_DIR})
#
#    # I had issues installing a few of the dynamic libraries, namely:
#    #       - ${LIBXML2_LIBRARY}
#    #       - ${LIBXSLT_LIBRARY}
#    #       - ${SQLITE3_LIBRARY}
#    #       - ${BERKELY_LIBRARY}
#    #       - ${POSTGRESQL_LIBRARY}
#    # Checkout the LINK_LIBRARIES variable for details on which were statically
#    # and which were dynamically linked. I later realized that in order to use these at run time you need both a smbolic
#    # link link libx.so.1 which points to the actual library libx.so.1.0.15. Both
#    # need to be copied into the pyomexmeta src directory which will then be incorporated
#    # into the python docs-build.
#    # This is a viable strategy, and should probably be implemented soon so users do not
#    # need to manually install packages from apt. However, for now, we rely on users
#    # installing these dependencies manually.
#
#    # The exception is the libstdc++ library. Since ive docs-build
#    # using a later version than is easily obtainably
#    # using apt-get, I just distribute along with python
#    #        install(FILES ${LIBSTDCXX6_LIBRARY} DESTINATION ${PYOMEXMETA_DIR})
#
#
#    # curl was statically linked in the end
#    #        install(FILES "${CURL_LIBRARY}" DESTINATION ${PYOMEXMETA_DIR} RENAME libsqlite.so.0)
#
#elseif (PLATFORM STREQUAL "windows-msvc")
#    # Just take all of them on windows, since we've linked dynamically to everything
#    install(FILES ${LIBRARIES} DESTINATION bin)
#
#    # Remember to copy dependency dlls to pyomexmeta directory
#    install(FILES ${LIBRARIES} DESTINATION ${PYOMEXMETA_DIR})
#    install(FILES $<TARGET_FILE:redland-combined> DESTINATION ${PYOMEXMETA_DIR})
#
#    # Note: I deleted the code that copies windows redistributables because
#    #  the package "InstallRequiredSystemLibraries" does this for me
#    #  just by including it. (Very nice).
#    find_file(API_MS_WIN_CORE_WOW64_L1_1_0_LIBRARY NAMES api-ms-win-core-wow64-l1-1-0.dll PATHS C:/Windows/System32/downlevel)
#
#    set(REDISTRIB
#            ${CMAKE_INSTALL_PREFIX}/bin/concrt140.dll
#            ${CMAKE_INSTALL_PREFIX}/bin/msvcp140.dll
#            ${CMAKE_INSTALL_PREFIX}/bin/msvcp140_1.dll
#            ${CMAKE_INSTALL_PREFIX}/bin/msvcp140_2.dll
#            ${CMAKE_INSTALL_PREFIX}/bin/msvcp140_codecvt_ids.dll
#            ${CMAKE_INSTALL_PREFIX}/bin/vcruntime140.dll
#            ${CMAKE_INSTALL_PREFIX}/bin/vcruntime140_1.dll
#            ${API_MS_WIN_CORE_WOW64_L1_1_0_LIBRARY}
#            )
#    if (EXISTS "${CMAKE_INSTALL_PREFIX}")
#        install(FILES ${REDISTRIB} DESTINATION ${PYOMEXMETA_DIR})
#        #        message(FATAL_ERROR "libOmexMeta needs to be installed before you \
#        #can copy windows redistributables into python directory. Please -DBUILD_PACKAGING=OFF until \
#        #you have built the windows install tree.")
#    endif ()
#
#
#elseif (PLATFORM STREQUAL "macos")
#    message(STATUS "macos == sad face =[")
#endif ()
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
#
