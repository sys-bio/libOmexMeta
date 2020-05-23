option(REDLAND_WRAPPER_TESTS "Whether to include the Redland API wrapper tests" ON)

set(REDLAND_WRAPPER_TEST_SOURCES
        RedlandAPITests/CWrapperTests.cpp
        RedlandAPITests/LibrdfWorldTests.cpp
        RedlandAPITests/LibrdfUriTests.cpp
        RedlandAPITests/LibrdfNodeTests.cpp
        RedlandAPITests/LibrdfStatementTests.cpp
        RedlandAPITests/LibrdfStorageTests.cpp
        RedlandAPITests/LibrdfModelTests.cpp
        RedlandAPITests/LibrdfParserTests.cpp
        RedlandAPITests/LibrdfSerializerTests.cpp
        RedlandAPITests/LibrdfQueryTests.cpp
        RedlandAPITests/LibrdfQueryResultsTests.cpp
        RedlandAPITests/LibrdfStreamTests.cpp
        )

set(TEST_SOURCES
        #        SemsimUtilsTests.cpp
        SBMLFactory.h
        #        RDFNodeTests.cpp
        #        SubjectTests.cpp
        #        PredicateTests.cpp
        #        ResourceTests.cpp
        #        TripleTests.cpp
        #        AnnotationSamples.h
        #        CurlGetTests.cpp
        #        MetaIDTests.cpp
        #        XmlAssistantTests.cpp
        #        ReaderTests.cpp
        #        WriterTests.cpp
        #        EditorTests.cpp
        #        RDFTests.cpp
        #        ParticipantTests.cpp
        #        PhysicalPropertyTests.cpp
        #        PhysicalEntityTests.cpp
        #        PhysicalPhenomenonTests.cpp
        #        PhysicalProcessTests.cpp
        #        PhysicalForceTests.cpp
        #        SemsimCombineArchiveTests.cpp
        #        QueryTests.cpp
        #        TripplesTests.cpp
        #        RDFReadAndWriteTests.cpp
        #        CAPITests.cpp
        )

if (REDLAND_WRAPPER_TESTS)
    set(TEST_SOURCES ${TEST_SOURCES} ${REDLAND_WRAPPER_TEST_SOURCES})
endif ()

add_executable(semsim-tests ${TEST_SOURCES})

target_compile_options(semsim-tests PRIVATE -g)

add_dependencies(semsim-tests semsim-static)

message(STATUS "LINK_LIBRARIES ${LINK_LIBRARIES}")
message(STATUS "REDLAND_LIBRARY ${REDLAND_LIBRARY}")

target_link_libraries(semsim-tests PUBLIC
        $<TARGET_FILE:semsim-static>
        gtest gtest_main
        ${LINK_LIBRARIES}
        curl
        xml2
        dl
        pthread
        m
        c
        lzma
        )

set(CMAKE_VERBOSE_MAKEFILE 1)
message(STATUS "HERE")
message(STATUS "CMAKE_CXX_COMPILER ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER_ID ${CMAKE_CXX_COMPILER_ID}")
if (CLANG)
    message(STATUS "CLANG cmopiler")
    SET(ADDRESS_SANITIZER_FLAGS "-fsatize=address")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${ADDRESS_SANITIZER_LINK_FLAGS}")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ADDRESS_SANITIZER_FLAGS}")
ENDIF ()


MESSAGE(STATUS "INCLUDE_DIRS ${INCLUDE_DIRS}")
target_include_directories(semsim-tests PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/src/semsim
        ${CMAKE_CURRENT_SOURCE_DIR}/RedlandAPITests
        ${GOOGLETEST_SOURCE}/googletest/include
        ${INCLUDE_DIRS}
        )

add_dependencies(semsim-tests
        semsim-static
        )
install(
        TARGETS semsim-tests
        EXPORT semsim-tests.a
        RUNTIME
        DESTINATION bin
)

















