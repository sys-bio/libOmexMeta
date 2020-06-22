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

#ignored on other platforms
set_target_properties(redland-wrapper-tests PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded")
#get_target_property(runtime redland-wrapper-tests  MSVC_RUNTIME_LIBRARY)
#message(STATUS "runtime ${runtime}")
add_dependencies(redland-wrapper-tests redland-combined)

target_include_directories(redland-wrapper-tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${GOOGLETEST_SOURCE}/googletest/include
        ${INCLUDE_DIRECTORIES}
#        "C:/Program Files (x86)/Windows Kits/10/Include/10.0.17134.0/ucrt"
        )

target_link_libraries(redland-wrapper-tests PRIVATE
        gtest gtest_main
        $<TARGET_FILE:redland-combined>
        ${LINK_LIBRARIES}
        )

foreach (lib ${LIBRARIES_DLL})
    message(STATUS "copying ${lib} to ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    add_custom_command(TARGET redland-wrapper-tests POST_BUILD        # Adds a post-build event to MyTest
            COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
            "${lib}"      # <--this is in-file
            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endforeach ()


add_dependencies(redland-wrapper-tests
        redland-combined
        )

install(
        TARGETS redland-wrapper-tests
        EXPORT redland-wrapper-tests
        RUNTIME
        DESTINATION bin
)










