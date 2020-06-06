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
        DotNamespaceLeak.cpp)

add_executable(redland-wrapper-tests ${REDLAND_WRAPPER_TEST_SOURCES})

add_dependencies(redland-wrapper-tests redland-combined)

target_include_directories(redland-wrapper-tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${GOOGLETEST_SOURCE}/googletest/include
        ${INCLUDE_DIRECTORIES}
        )

target_link_libraries(redland-wrapper-tests PRIVATE
        $<TARGET_FILE:redland-combined>
        gtest gtest_main
        ${LINK_LIBRARIES}
        )


add_dependencies(redland-wrapper-tests
        redland-combined
        )
install(
        TARGETS redland-wrapper-tests
        EXPORT redland-wrapper-tests.a
        RUNTIME
        DESTINATION bin
)










