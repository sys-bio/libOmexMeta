set(OMEXMETA_TEST_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# "CMAKE_CURRENT_SOURCE_DIR" changes in the different files were
# add_test_executable gets called. We can use this as a constant
set(ThisDirectory ${CMAKE_CURRENT_SOURCE_DIR})

# Adds a new executable cmake target to cmake.
# Links roadrunner-static and gtest.
# Parameters:
#   - TEST_TARGET: name of the test target binary
#   - OUT_VARIABLE: list variable to append BINARY. Creates the list if not exist.
#   - All further arguments are added to the binary as sources.
function(add_test_executable TEST_TARGET OUT_VARIABLE)
    add_executable(${TEST_TARGET} ${ARGN})

    target_include_directories(
            ${TEST_TARGET} PRIVATE
            "${ThisDirectory}"
    )

    target_link_libraries(${TEST_TARGET} PUBLIC
            OmexMeta-static gtest gtest_main gmock gmock_main
            )

    add_dependencies(${TEST_TARGET} OmexMeta-static redland-combined-static gtest gtest_main gmock gmock_main)
    set_target_properties(${TEST_TARGET} PROPERTIES LINKER_LANGUAGE CXX)

    # Add to ctest.
    # add_test(NAME ${BINARY} COMMAND "$<TARGET_FILE:${BINARY}>")
    gtest_discover_tests(
            ${TEST_TARGET}
            TEST_LIST omexmeta-tests
            DISCOVERY_TIMEOUT 500
            )

    set_tests_properties(${omexmeta-tests} PROPERTIES TIMEOUT 500)


    set(test_targets "${test_targets}" "${testid}")
    if ("${${OUT_VARIABLE}}" STREQUAL "")
        set(${OUT_VARIABLE} "${TEST_LIST}" PARENT_SCOPE)
    else ()
        set(${OUT_VARIABLE} "${${OUT_VARIABLE}}" "${TEST_LIST}" PARENT_SCOPE)
    endif ()

endfunction()


add_subdirectory(cpp)
add_subdirectory(C)

if (${BUILD_PYTHON})
    add_subdirectory(python)
endif ()

# set dependencies only to make sure they get run first
add_custom_target(run-ctest
        COMMAND ${CMAKE_CTEST_COMMAND} --verbose --extra-verbose --progress -C ${CMAKE_BUILD_TYPE} ${CMAKE_BINARY_DIR}
        DEPENDS redland-wrapper-tests ${OmexMetaTests} OmexMetaCAPITests
        VERBATIM
        )


install(
        TARGETS ${OmexMetaTests} redland-wrapper-tests OmexMetaCAPITests
        RUNTIME DESTINATION bin
        COMPONENT Tests
)

