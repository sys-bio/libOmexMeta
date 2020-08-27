# C API binary

set(target "OmexMetaCAPI")
set(CAPI_SOURCES OmexMetaCApi.h OmexMetaCApi.cpp
        "${CMAKE_CURRENT_BINARY_DIR}/omexmetacapi_export.h"
)


add_library(${target} SHARED ${CAPI_SOURCES})
generate_export_header(OmexMetaCAPI BASE_NAME OmexMetaCAPI)
set_target_properties(${target} PROPERTIES
                      PUBLIC_HEADER "OmexMetaCApi.h;${CMAKE_CURRENT_BINARY_DIR}/omexmetacapi_export.h"
                      SOVERSION ${LIBOMEXMETA_VERSION}
                      )

#includes
get_filename_component(PARENT_DIR ${CMAKE_CURRENT_BINARY_DIR} DIRECTORY)
target_include_directories(${target} PRIVATE
                           ${INCLUDE_DIRECTORIES}
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           ${CMAKE_CURRENT_BINARY_DIR} # CAPI export header
                           ${PARENT_DIR} # C++ api export header
                           )


# These need defining to indicate that we're linking the static
# version of omexmeta and redland as well as exporting
# symbols from the omexmeta c api
target_compile_definitions(${target} PRIVATE
                           OmexMetaCAPI_EXPORTS
                           OMEXMETA_STATIC_DEFINE
                           REDLAND_STATIC_DEFINE
                           )

# links
target_link_libraries(${target} PRIVATE
                      -Wl,--whole-archive
                      OmexMeta-static
                      redland-combined-static
                      -Wl,--no-whole-archive
                      ${LINK_LIBRARIES}
                      )
add_dependencies(${target} OmexMeta-static redland-combined-static)

# add to ctest target
add_test(
        NAME OmexMetaCAPI
        COMMAND $<TARGET_FILE:OmexMetaCAPI>
)


# install
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
        FILE OmexMetaCAPI.cmake
)
if (WIN32)
    install(FILES $<TARGET_FILE:${target}> DESTINATION ${PYOMEXMETA_DIR})
endif()
