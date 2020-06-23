

set(TEST_SOURCES
        SBMLFactory.h
        SemsimUtilsTests.cpp
        SubjectTests.cpp
        ResourceTests.cpp
        PredicateTests.cpp
        TripleTests.cpp
        TriplesTests.cpp
        RDFTests.cpp

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
        RDFReadAndWriteTests.cpp
        CAPITests.cpp
        )

#if (REDLAND_WRAPPER_TESTS)
#    set(TEST_SOURCES ${TEST_SOURCES} )
#endif ()

add_executable(semsim-tests ${TEST_SOURCES})

if (NOT ${PLATFORM} STREQUAL "window-msvc")
    target_compile_options(semsim-tests PRIVATE -g)
endif ()
add_dependencies(semsim-tests semsim-static)

message(STATUS "LINK_LIBRARIES ${LINK_LIBRARIES}")

target_link_libraries(semsim-tests PUBLIC
        # Order matters!
        $<TARGET_FILE:semsim-static>
        $<TARGET_FILE:redland-combined-static>
        ${LINK_LIBRARIES}
        gtest gtest_main
        )

set(CMAKE_VERBOSE_MAKEFILE 1)
if (CLANG)
    SET(ADDRESS_SANITIZER_FLAGS "-fsatize=address")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${ADDRESS_SANITIZER_LINK_FLAGS}")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ADDRESS_SANITIZER_FLAGS}")
ENDIF ()

foreach (lib ${LIBRARIES_DLL})
    add_custom_command(TARGET semsim-tests POST_BUILD        # Adds a post-build event to MyTest
            COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
            "${lib}"      # <--this is in-file
            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endforeach ()


target_include_directories(semsim-tests PRIVATE
        ${GOOGLETEST_SOURCE}/googletest/include
        ${INCLUDE_DIRECTORIES}
        ${WRAPPER_SOURCE_DIR}
        )

add_dependencies(semsim-tests semsim-static)

install(
        TARGETS semsim-tests
        EXPORT semsim-tests
        RUNTIME
        DESTINATION bin
)

















