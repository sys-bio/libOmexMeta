###########################################################################
#   Sources for tests
#

set(target OmexMetaTests)

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

add_executable(OmexMetaTests ${TEST_SOURCES})

target_link_libraries(OmexMetaTests PRIVATE OmexMeta-static gtest gtest_main)
add_dependencies(OmexMetaTests OmexMeta-static gtest gtest_main)
target_include_directories(OmexMetaTests PRIVATE
        "${OMEXMETA_TEST_INCLUDE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${GOOGLETEST_SOURCE_DIR}/googletest/include"
        )







