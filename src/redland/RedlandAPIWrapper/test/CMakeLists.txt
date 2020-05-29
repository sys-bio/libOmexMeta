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

message(WARNING "LINK_LIBRARIES ${LINK_LIBRARIES}")
target_include_directories(redland-wrapper-tests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${GOOGLETEST_SOURCE}/googletest/include
        ${INCLUDE_DIRECTORIES}
        #        ${WRAPPER_SOURCE_DIR}
        #        BEFORE ${RAPTOR_DIR}/librdfa
        #        ${RAPTOR_DIR}/src
        #        ${RASQAL_DIR}/src
        #        ${RASQAL_DIR}/libmtwist
        #        ${RASQAL_DIR}/libsv
        #        ${RASQAL_DIR}/getopt
        #        ${LIBRDF_DIR}/src
        #        ${LIBRDF_SOURCE_DIR}
        #        ${LIBRDF_DIR}/libltdl
        #        ${RASQAL_SOURCE_DIR}
        #        ${RASQAL_DIR}/libmtwist
        #        ${RASQAL_DIR}/libsv
        #        ${RASQAL_DIR}/getopt
        #        ${RAPTOR_SOURCE_DIR}
        #        /mnt/d/libsemsim/src/redland/redland-1.0.17/src
        )

message(WARNING "LINK_LIBRARIES ${LINK_LIBRARIES}")
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










