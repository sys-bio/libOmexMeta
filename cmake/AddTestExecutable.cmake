# Create a test executable and add it to ctest
# BINARY: target name
# LINK_WITH_GOOGLETEST : boolean
# OUT_VARIABLE: Test target names get added to this list
# ... Arbitrary number of test sources
function(add_test_executable BINARY LINK_WITH_GOOGLETEST OUT_VARIABLE)

    add_executable(${BINARY} ${ARGN})

    set(LINK_LIBRARIES
            OmexMeta-static
            OmexMetaCAPI
            redland-combined-static
            ${LINK_LIBRARIES}
            ${RUNTIME}# best here so no clash with dynamic

            )

    if (${LINK_WITH_GOOGLETEST})
        set(LINK_LIBRARIES ${LINK_LIBRARIES}
                gtest gtest_main
                gmock gmock_main)
    endif ()

    gtest_add_tests(
            TARGET ${BINARY}
    )
    # indicate that on windows we are using the static library,
    # not the static
    target_compile_definitions(
            ${BINARY} PRIVATE OMEXMETA_STATIC_DEFINE REDLAND_STATIC_DEFINE
    )

    add_dependencies(${BINARY} OmexMeta-static redland-combined-static gtest gtest_main)

    target_link_libraries(${BINARY} PRIVATE ${LINK_LIBRARIES})

    #includes
    target_include_directories(${BINARY} PRIVATE
            ${GOOGLETEST_SOURCE}/googletest/include
            ${INCLUDE_DIRECTORIES}
            ${WRAPPER_SOURCE_DIR}
            )
    # add test so it can be run with $ctest or $make test

    set(TEST_EXECUTABLES ${TEST_EXECUTABLES} ${BINARY})


    # Add to an output scoped variable keeping track of binaries we need.
    if ("${${OUT_VARIABLE}}" STREQUAL "")
        set(${OUT_VARIABLE} "${BINARY}" PARENT_SCOPE)
    else ()
        set(${OUT_VARIABLE} "${${OUT_VARIABLE}}" "${BINARY}" PARENT_SCOPE)
    endif ()

endfunction()