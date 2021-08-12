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
        QueryTests.cpp
        )



# Adds a new executable cmake target to cmake.
# Links roadrunner-static and gtest.
# Parameters:
#   - TEST_TARGET: name of the test target binary
#   - OUT_VARIABLE: list variable to append BINARY. Creates the list if not exist.
#   - All further arguments are added to the binary as sources.
macro(add_redland_test_executable TEST_TARGET OUT_VARIABLE)
    add_executable(${TEST_TARGET} ${ARGN})

    target_include_directories(
            ${TEST_TARGET} PRIVATE
            "${ThisDirectory}"
    )

    target_link_libraries(${TEST_TARGET} PUBLIC
            redland-combined-static gtest gtest_main gmock gmock_main
            )

    add_dependencies(${TEST_TARGET} redland-combined-static gtest gtest_main gmock gmock_main)
    set_target_properties(${TEST_TARGET} PROPERTIES LINKER_LANGUAGE CXX)

    # Add to ctest.
    # add_test(NAME ${BINARY} COMMAND "$<TARGET_FILE:${BINARY}>")
    gtest_discover_tests(
            ${TEST_TARGET}
            TEST_LIST redland-combined-tests
            DISCOVERY_TIMEOUT 500
    )

    set_tests_properties(${redland-combined-tests} PROPERTIES TIMEOUT 500)

#    set(test_targets "${test_targets}" "${testid}")
#    if ("${${OUT_VARIABLE}}" STREQUAL "")
#        set(${OUT_VARIABLE} "${TEST_LIST}" PARENT_SCOPE)
#    else ()
#        set(${OUT_VARIABLE} "${${OUT_VARIABLE}}" "${TEST_LIST}" PARENT_SCOPE)
#    endif ()

endmacro()



# add test executable
#add_executable(${target} ${REDLAND_WRAPPER_TEST_SOURCES})
#
## indicate were using static version of redland
#target_compile_definitions(${target} PRIVATE REDLAND_STATIC_DEFINE)
#
## tell cmake about the test so we can run with $ctest or $ make test
#gtest_discover_tests(${target})
#
## set the RPATH for both install and docs-build builds
#set_target_properties(${target} PROPERTIES INSTALL_RPATH ${RPATH})
#set_target_properties(${target} PROPERTIES BUILD_RPATH ${RPATH})
#
## setup dependencies
#add_dependencies(${target} redland-combined-static gtest gtest_main)
#
## includes
#target_include_directories(${target} PRIVATE
#        "${CMAKE_CURRENT_SOURCE_DIR}"
#        "${GOOGLETEST_SOURCE}/googletest/include"
#        ${INCLUDE_DIRECTORIES}
#        )
#
#
## links
#target_link_libraries(${target} PUBLIC
#        gtest gtest_main
#        redland-combined-static
#        )
#
#
#if (WIN32)
#    target_link_options(${target} PRIVATE "/NODEFAULTLIB:library")
#endif ()


add_redland_test_executable(redland_wrapper_RefCountedTests RedlandTests RefCountedTests.cpp)
add_redland_test_executable(redland_wrapper_LibrdfUriTests RedlandTests LibrdfUriTests.cpp)
add_redland_test_executable(redland_wrapper_LibrdfNodeTests RedlandTests LibrdfNodeTests.cpp)
add_redland_test_executable(redland_wrapper_LibrdfStatementTests RedlandTests LibrdfStatementTests.cpp)
add_redland_test_executable(redland_wrapper_LibrdfParserTests RedlandTests LibrdfParserTests.cpp)
add_redland_test_executable(redland_wrapper_LibrdfModelTests RedlandTests LibrdfModelTests.cpp)
add_redland_test_executable(redland_wrapper_LibrdfStorageTests RedlandTests LibrdfStorageTests.cpp)
add_redland_test_executable(redland_wrapper_LibrdfStreamTests RedlandTests LibrdfStreamTests.cpp)
add_redland_test_executable(redland_wrapper_LibrdfSerializerTests RedlandTests LibrdfSerializerTests.cpp)
add_redland_test_executable(redland_wrapper_LibrdfQueryTests RedlandTests LibrdfQueryTests.cpp)
add_redland_test_executable(redland_wrapper_Logger RedlandTests LoggingTests.cpp)











