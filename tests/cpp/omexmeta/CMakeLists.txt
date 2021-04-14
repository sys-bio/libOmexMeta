###########################################################################
#   Sources for tests
#

set(target OmexMetaTests)

set(
        TEST_SOURCES
        OmexMetaTestUtils.cpp # utilities used in tests
        SBMLFactory.h
        OmexMetaUtilsTests.cpp # tests for omexmeta utils class
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
        PropertyBearerTests.cpp
        EnergyDiffTests.cpp
        PhysicalProcessTests.cpp
        QueryTests.cpp
        EditorTests.cpp
        PersonalInformationTests.cpp
        MarkupIdentifierTests.cpp
        ElementExtractorTests.cpp
        SBMLSemanticExtractionTests.cpp
        CellMLTests.cpp
        UrlHandlerTests.cpp
        CellMLFactory.h
)


##############################################################################
#   Add test executables
#
#
#add_executable(OmexMetaTests ${TEST_SOURCES})
#
#target_link_libraries(OmexMetaTests PRIVATE OmexMeta-static gtest gtest_main)
#add_dependencies(OmexMetaTests OmexMeta-static gtest gtest_main)
#target_include_directories(OmexMetaTests PRIVATE
#        "${OMEXMETA_TEST_INCLUDE_DIR}"
#        "${CMAKE_CURRENT_SOURCE_DIR}"
#        "${GOOGLETEST_SOURCE_DIR}/googletest/include"
#        )
#gtest_discover_tests(OmexMetaTests)


add_test_executable(EditorTests OmexMetaTests EditorTests.cpp)
add_test_executable(ElementExtractorTests OmexMetaTests ElementExtractorTests.cpp)
add_test_executable(EnergyDiffTests OmexMetaTests EnergyDiffTests.cpp)
add_test_executable(MarkupIdentifierTests OmexMetaTests MarkupIdentifierTests.cpp)
add_test_executable(MetaIDTests OmexMetaTests MetaIDTests.cpp)
add_test_executable(OmexMetaTestUtils OmexMetaTests OmexMetaTestUtils.cpp)
add_test_executable(ParticipantTests OmexMetaTests ParticipantTests.cpp)
add_test_executable(PersonalInformationTests OmexMetaTests PersonalInformationTests.cpp)
add_test_executable(PhysicalEntityTests OmexMetaTests PhysicalEntityTests.cpp)
add_test_executable(PhysicalProcessTests OmexMetaTests PhysicalProcessTests.cpp)
add_test_executable(PhysicalPropertyTests OmexMetaTests PhysicalPropertyTests.cpp)
add_test_executable(PropertyBearerTests OmexMetaTests PropertyBearerTests.cpp)
add_test_executable(PredicateTests OmexMetaTests PredicateTests.cpp)
add_test_executable(QueryTests OmexMetaTests QueryTests.cpp)
add_test_executable(RDFTests OmexMetaTests RDFTests.cpp)
add_test_executable(SBMLSemanticExtractionTests OmexMetaTests SBMLSemanticExtractionTests.cpp)
add_test_executable(SemsimCombineArchiveTests OmexMetaTests SemsimCombineArchiveTests.cpp)
add_test_executable(TripleTests OmexMetaTests TripleTests.cpp)
add_test_executable(TriplesTests OmexMetaTests TriplesTests.cpp)
add_test_executable(UrlHandlerTests OmexMetaTests UrlHandlerTests.cpp )
add_test_executable(XmlAssistantTests OmexMetaTests XmlAssistantTests.cpp )











