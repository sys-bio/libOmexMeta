# C API binary

set(target "OmexMetaCAPI")
set(CAPI_SOURCES OmexMetaCApi.h OmexMetaCApi.cpp)


add_library(${target} SHARED ${CAPI_SOURCES})
set_target_properties(${target} PROPERTIES
                      PUBLIC_HEADER OmexMetaCApi.h
                      SOVERSION ${LIBOMEXMETA_VERSION}
                      )

#includes
target_include_directories(${target} PRIVATE
                           ${INCLUDE_DIRECTORIES}
                           ${CMAKE_CURRENT_SOURCE_DIR}
                           )

# links
target_link_libraries(${target} PRIVATE
                      OmexMeta-static
                      redland-combined-static
                      ${LINK_LIBRARIES}
                      )
add_dependencies(${target} OmexMeta-static)

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
