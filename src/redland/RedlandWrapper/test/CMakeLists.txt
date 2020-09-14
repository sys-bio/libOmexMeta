# set varibale to hold wrapper sources.
set(REDLAND_WRAPPER_TEST_SOURCES
                LibrdfWorldTests.cpp
                LibrdfUriTests.cpp
                LibrdfNodeTests.cpp
                LibrdfStatementTests.cpp
                LibrdfStorageTests.cpp
                LibrdfModelTests.cpp
                LibrdfParserTests.cpp
                LibrdfSerializerTests.cpp
                LibrdfQueryTests.cpp
                LibrdfQueryResultsTests.cpp
                LibrdfStreamTests.cpp
        )

# add test executable
add_executable(redland-wrapper-tests ${REDLAND_WRAPPER_TEST_SOURCES})

# indicate were using static version of redland
target_compile_definitions(redland-wrapper-tests PRIVATE REDLAND_STATIC_DEFINE)

# tell cmake about the test so we can run with $ctest or $ make test
add_test(
        NAME redland-wrapper-tests
        COMMAND $<TARGET_FILE:redland-wrapper-tests>
)
# tests_properties is apparently different to target properties
set_tests_properties(redland-wrapper-tests PROPERTIES DEPENDS redland-wrapper-tests)

# set the RPATH for both install and docs-build builds
set_target_properties(redland-wrapper-tests PROPERTIES INSTALL_RPATH ${RPATH})
set_target_properties(redland-wrapper-tests PROPERTIES BUILD_RPATH ${RPATH})

# setup dependencies
add_dependencies(redland-wrapper-tests redland-combined-static gtest gtest_main)

# includes
target_include_directories(redland-wrapper-tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${GOOGLETEST_SOURCE}/googletest/include
        ${INCLUDE_DIRECTORIES}
        )



# links
target_link_libraries(redland-wrapper-tests PRIVATE
        gtest gtest_main
        $<TARGET_FILE:redland-combined-static>
        ${LINK_LIBRARIES}
        ${RUNTIME}# best here so no clash with dynamic
        )

# install tests.
install(
        TARGETS redland-wrapper-tests
        EXPORT redland-wrapper-tests
        RUNTIME DESTINATION bin
)

gtest_discover_tests(redland-wrapper-tests)


# copies dependencies into docs-build directory. Commented out for now, delete in future if definately not needed.
#foreach (lib ${LIBRARIES})
#    message(STATUS "copying ${lib} to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
#    add_custom_command(TARGET redland-wrapper-tests POST_BUILD        # Adds a post-docs-build event to MyTest
#            COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
#            "${lib}"      # <--this is in-file
#            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
#endforeach ()












