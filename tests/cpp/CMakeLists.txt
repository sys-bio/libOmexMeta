###########################################################################
#   Sources for tests
#


set(TEST_EXECUTABLES)

macro(add_test_executable BINARY)
    add_executable(${BINARY} ${ARGN})

    # indicate that on windows we are using the static library,
    # not the static
    target_compile_definitions(
            ${BINARY} PRIVATE OMEXMETA_STATIC_DEFINE REDLAND_STATIC_DEFINE
    )

    # add test so it can be run with $ctest or $make test
    add_test(
            NAME ${BINARY}
            COMMAND $<TARGET_FILE:${BINARY}>
    )

    set_tests_properties(${BINARY} PROPERTIES DEPENDS OmexMeta)
    add_dependencies(${BINARY} OmexMeta-static gtest gtest_main)

    # links
    target_link_libraries(${BINARY} PUBLIC
            # Order matters!
            $<TARGET_FILE:OmexMeta-static>
            $<TARGET_FILE:redland-combined-static>
            ${LINK_LIBRARIES}
            ${RUNTIME}# best here so no clash with dynamic
            gtest gtest_main
            )

    #includes
    target_include_directories(${BINARY} PRIVATE
            ${GOOGLETEST_SOURCE}/googletest/include
            ${INCLUDE_DIRECTORIES}
            ${WRAPPER_SOURCE_DIR}
            )

    set(TEST_EXECUTABLES ${TEST_EXECUTABLES} ${BINARY})
endmacro()


set(
        TEST_SOURCES
        SBMLFactory.h
        OmexMetaUtilsTests.cpp
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
        PersonalInformationTests.cpp
        DocTests.cpp
        MarkupIdentifierTests.cpp
        ElementExtractorTests.cpp
        SBMLSemanticExtractionTests.cpp
)


##############################################################################
#   Add test executables
#

# main test executable. These should really further be divided into modules.
add_test_executable(OmexMetaTests ${TEST_SOURCES})

add_test_executable(EditorSBMLExtractionTest EditorSBMLExtractTests.cpp)

add_test_executable(JohnsTest JohnsTest.cpp)








install(
        TARGETS ${TEST_EXECUTABLES}
        EXPORT tests
        RUNTIME DESTINATION bin
)

#
#if (${BUILD_INTEGRATION_TESTS})
#endif ()
#
#
#
#
#
#








