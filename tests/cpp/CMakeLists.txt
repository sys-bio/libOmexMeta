

set(TEST_SOURCES
        SBMLFactory.h
        SemsimUtilsTests.cpp
        RDFTests.cpp
        SubjectTests.cpp
        ResourceTests.cpp
        PredicateTests.cpp
        TripleTests.cpp
        TriplesTests.cpp

        AnnotationSamples.h

        CurlGetTests.cpp
        MetaIDTests.cpp
        XmlAssistantTests.cpp
        ParticipantTests.cpp

        PhysicalEntityTests.cpp
        PhysicalPropertyTests.cpp
        PhysicalPhenomenonTests.cpp
        PhysicalForceTests.cpp
        PhysicalProcessTests.cpp
        QueryTests.cpp
        EditorTests.cpp

        #        ReaderTests.cpp
        #        WriterTests.cpp
        #        RDFTests.cpp
        #        RDFReadAndWriteTests.cpp
        #        SemsimCombineArchiveTests.cpp
        #        CAPITests.cpp
        )

if (REDLAND_WRAPPER_TESTS)
    set(TEST_SOURCES ${TEST_SOURCES} ${REDLAND_WRAPPER_TEST_SOURCES} RDFTests.cpp)
endif ()

add_executable(semsim-tests ${TEST_SOURCES})

target_compile_options(semsim-tests PRIVATE -g)

add_dependencies(semsim-tests semsim-static)

message(STATUS "LINK_LIBRARIES ${LINK_LIBRARIES}")
message(STATUS "REDLAND_LIBRARY ${REDLAND_LIBRARY}")

target_link_libraries(semsim-tests PUBLIC
        # Order matters!
        $<TARGET_FILE:semsim-static>
        $<TARGET_FILE:redland-combined>
        ${LINK_LIBRARIES}
        gtest gtest_main
        )

set(CMAKE_VERBOSE_MAKEFILE 1)
if (CLANG)
    message(STATUS "CLANG cmopiler")
    SET(ADDRESS_SANITIZER_FLAGS "-fsatize=address")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${ADDRESS_SANITIZER_LINK_FLAGS}")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ADDRESS_SANITIZER_FLAGS}")
ENDIF ()


MESSAGE(STATUS "INCLUDE_DIRS ${INCLUDE_DIRS}")
target_include_directories(semsim-tests PRIVATE
        ${GOOGLETEST_SOURCE}/googletest/include
        ${INCLUDE_DIRS}
        ${WRAPPER_SOURCE_DIR}
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

















