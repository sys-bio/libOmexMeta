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

# build test executable
add_executable(OmexMetaTests ${TEST_SOURCES})
# set RPATH for both install and build builds
set_target_properties(OmexMetaTests PROPERTIES INSTALL_RPATH ${RPATH})
set_target_properties(OmexMetaTests PROPERTIES BUILD_RPATH ${RPATH})

# add test so it can be run with $ctest or $make test
add_test(
        NAME OmexMetaTests
        COMMAND $<TARGET_FILE:OmexMetaTests>
)
set_tests_properties(OmexMetaTests PROPERTIES DEPENDS OmexMeta)
add_dependencies(OmexMetaTests OmexMeta-static gtest gtest_main)

#if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
#    set_target_properties(OmexMetaTests PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreaded")
#elseif (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
#    set_target_properties(OmexMetaTests PROPERTIES MSVC_RUNTIME_LIBRARY "MultiThreadedDebug")
#endif()


# links
target_link_libraries(OmexMetaTests PUBLIC
        # Order matters!
        $<TARGET_FILE:OmexMeta-static>
        $<TARGET_FILE:redland-combined-static>
        ${LINK_LIBRARIES}
        ${RUNTIME}# best here so no clash with dynamic
        gtest gtest_main
        )

#includes
target_include_directories(OmexMetaTests PRIVATE
        ${GOOGLETEST_SOURCE}/googletest/include
        ${INCLUDE_DIRECTORIES}
        ${WRAPPER_SOURCE_DIR}
        )

add_dependencies(OmexMetaTests OmexMeta-static gtest gtest_main)

install(
        TARGETS OmexMetaTests
        EXPORT OmexMetaTests
        RUNTIME DESTINATION bin
)

#if (PLATFORM STREQUAL "windows-msvc")
#    foreach (lib ${LIBRARIES_DLL})
#        add_custom_command(TARGET OmexMetaTests POST_BUILD        # Adds a post-build event to MyTest
#                COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
#                "${lib}"      # <--this is in-file
#                "${CMAKE_RUNTIME_OUTPUT_DIRECTORY} ")
#    endforeach ()
#endif ()















