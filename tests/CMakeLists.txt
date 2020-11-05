set(OMEXMETA_TEST_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_subdirectory(cpp)
add_subdirectory(C)

if (${BUILD_PYTHON})
    add_subdirectory(python)
endif ()

add_custom_target(run-ctest
        COMMAND ${CMAKE_CTEST_COMMAND} --verbose --extra-verbose --progress ${CMAKE_BINARY_DIR}
        DEPENDS ${TEST_EXECUTABLES}
        VERBATIM
        )


install(
        TARGETS OmexMetaTests redland-wrapper-tests
        EXPORT tests
        RUNTIME DESTINATION bin
)

