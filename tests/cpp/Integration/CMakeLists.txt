set(INTEGRATION_TESTS)


macro(add_integration_test BINARY_NAME)

    # binary for testing Editor's ability to extract information from sbml
    add_executable(${BINARY_NAME} ${ARGN})
    set(INTEGRATION_TESTS ${INTEGRATION_TESTS} "${BINARY_NAME}")

    target_compile_definitions(
            ${BINARY_NAME} PRIVATE OMEXMETA_STATIC_DEFINE REDLAND_STATIC_DEFINE
    )
    # add test so it can be run with $ctest or $make test
    add_test(
            NAME ${BINARY_NAME}
            COMMAND $<TARGET_FILE:${BINARY_NAME}>
    )

    set_tests_properties(${BINARY_NAME} PROPERTIES DEPENDS OmexMeta)
    add_dependencies(${BINARY_NAME} OmexMeta-static gtest gtest_main)

    # links
    target_link_libraries(${BINARY_NAME} PRIVATE
                          # Order matters!
                          $<TARGET_FILE:OmexMeta-static>
                          $<TARGET_FILE:redland-combined-static>
                          ${LINK_LIBRARIES}
                          ${RUNTIME}# best here so no clash with dynamic
                          gtest gtest_main
                          )

    target_include_directories(${BINARY_NAME} PRIVATE
                               ${GOOGLETEST_SOURCE}/googletest/include
                               ${INCLUDE_DIRECTORIES}
                               ${WRAPPER_SOURCE_DIR}
                               )

endmacro()

add_integration_test(EditorSBMLExtractionTest EditorSBMLExtractTests.cpp)


install(
        TARGETS ${INTEGRATION_TESTS}
        RUNTIME DESTINATION bin/integration
)















