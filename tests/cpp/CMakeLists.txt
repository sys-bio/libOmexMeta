###########################################################################
#   Sources for tests
#
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

# build googletest executable
add_executable(OmexMeta-tests ${TEST_SOURCES})


if (NOT ${PLATFORM} STREQUAL "window-msvc")
    target_compile_options(OmexMeta-tests PRIVATE -g)
endif ()

add_dependencies(OmexMeta-tests OmexMeta-static)

target_link_libraries(OmexMeta-tests PUBLIC
        # Order matters!
        $<TARGET_FILE:OmexMeta-static>
        $<TARGET_FILE:redland-combined-static>
        ${LINK_LIBRARIES}
        gtest gtest_main
        )

foreach (lib ${LIBRARIES_DLL})
    add_custom_command(TARGET OmexMeta-tests POST_BUILD        # Adds a post-build event to MyTest
            COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
            "${lib}"      # <--this is in-file
            "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endforeach ()


target_include_directories(OmexMeta-tests PRIVATE
        ${GOOGLETEST_SOURCE}/googletest/include
        ${INCLUDE_DIRECTORIES}
        ${WRAPPER_SOURCE_DIR}
        )

add_dependencies(OmexMeta-tests OmexMeta-static)

install(
        TARGETS OmexMeta-tests
        EXPORT OmexMeta-tests
        RUNTIME DESTINATION bin
)

















