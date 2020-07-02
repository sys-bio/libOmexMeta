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


add_executable(redland-wrapper-tests ${REDLAND_WRAPPER_TEST_SOURCES})
set_target_properties(redland-wrapper-tests PROPERTIES INSTALL_RPATH ${RPATH})#:$ORIGIN:/home/ciaran/vcpkg/installed/x64-linux/lib")
set_target_properties(redland-wrapper-tests PROPERTIES BUILD_RPATH ${RPATH})

#ignored on other platforms
set_target_properties(redland-wrapper-tests PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded")

add_dependencies(redland-wrapper-tests redland-combined-static)

target_include_directories(redland-wrapper-tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${GOOGLETEST_SOURCE}/googletest/include
        ${INCLUDE_DIRECTORIES}
        )

target_link_libraries(redland-wrapper-tests PRIVATE
        gtest gtest_main
        $<TARGET_FILE:redland-combined-static>
        ${LINK_LIBRARIES}
        )

#foreach (lib ${LIBRARIES})
#    message(STATUS "copying ${lib} to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
#    add_custom_command(TARGET redland-wrapper-tests POST_BUILD        # Adds a post-build event to MyTest
#            COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
#            "${lib}"      # <--this is in-file
#            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
#endforeach ()


add_dependencies(redland-wrapper-tests redland-combined-static)

install(
        TARGETS redland-wrapper-tests
        EXPORT redland-wrapper-tests
        RUNTIME DESTINATION bin
)










