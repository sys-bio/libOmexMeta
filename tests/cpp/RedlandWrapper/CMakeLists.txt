set(target redland-wrapper-tests)

# set varibale to hold wrapper sources.
set(REDLAND_WRAPPER_TEST_SOURCES
        LibrdfUriTests.cpp
        LibrdfWorldTests.cpp
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
add_executable(${target} ${REDLAND_WRAPPER_TEST_SOURCES})

# indicate were using static version of redland
target_compile_definitions(${target} PRIVATE REDLAND_STATIC_DEFINE)

# tell cmake about the test so we can run with $ctest or $ make test
#gtest_add_tests(
#        TARGET ${target}
#        SOURCES ${REDLAND_WRAPPER_TEST_SOURCES}
#)
gtest_discover_tests(${target})

# set the RPATH for both install and docs-build builds
set_target_properties(${target} PROPERTIES INSTALL_RPATH ${RPATH})
set_target_properties(${target} PROPERTIES BUILD_RPATH ${RPATH})

# setup dependencies
add_dependencies(${target} redland-combined-static gtest gtest_main)

# includes
target_include_directories(${target} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${GOOGLETEST_SOURCE}/googletest/include"
        ${INCLUDE_DIRECTORIES}
        )


# links
target_link_libraries(${target} PUBLIC
        gtest gtest_main
        redland-combined-static
        )


if (WIN32)
    target_link_options(${target} PRIVATE "/NODEFAULTLIB:library")
endif ()
# install tests.
install(
        TARGETS ${target}
        EXPORT ${target}
        RUNTIME DESTINATION bin
)

#gtest_discover_tests(${target})


# copies dependencies into docs-build directory. Commented out for now, delete in future if definately not needed.
#foreach (lib ${LIBRARIES})
#    message(STATUS "copying ${lib} to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
#    add_custom_command(TARGET ${target} POST_BUILD        # Adds a post-docs-build event to MyTest
#            COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
#            "${lib}"      # <--this is in-file
#            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
#endforeach ()












