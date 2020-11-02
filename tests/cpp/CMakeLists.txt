###########################################################################
#   Sources for tests
#


include(AddTestExecutable)


set(
        TEST_SOURCES
        OmexMetaTestUtils.cpp # utilities used in tests
        SBMLFactory.h
        OmexMetaUtilsTests.cpp # tests for omexmeta utils class
        SubjectTests.cpp
        ResourceTests.cpp
        PredicateTests.cpp
        TripleTests.cpp
        TriplesTests.cpp
        RDFTests.cpp

        AnnotationSamples.h

        #        CurlGetTests.cpp # periodically breaks due to file size changes and link changes
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
        PersonalInformationTests.cpp
        MarkupIdentifierTests.cpp
        ElementExtractorTests.cpp
        SBMLSemanticExtractionTests.cpp
)


##############################################################################
#   Add test executables
#

# main test executable. These should really further be divided into modules.
#BINARY LINK_WITH_GOOGLETEST OUT_VARIABLE
add_test_executable(OmexMetaTests ON TEST_EXECUTABLES ${TEST_SOURCES})


add_custom_target(run-ctest
        COMMAND ${CMAKE_CTEST_COMMAND} --verbose --extra-verbose --progress ${CMAKE_BINARY_DIR}
        DEPENDS ${TEST_EXECUTABLES}
        VERBATIM
        )



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








