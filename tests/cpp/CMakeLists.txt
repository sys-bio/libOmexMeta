###########################################################################
#   Sources for tests
#

set(TEST_SOURCES
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
        MarkupIdentifierTests.cpp sbml_semantic_extraction/ElementExtractorTests.cpp sbml_semantic_extraction/SBMLSemanticExtractionTests.cpp)

# docs-build test executable
add_executable(OmexMetaTests ${TEST_SOURCES})

# add test so it can be run with $ctest or $make test
add_test(
        NAME OmexMetaTests
        COMMAND $<TARGET_FILE:OmexMetaTests>
)
set_tests_properties(OmexMetaTests PROPERTIES DEPENDS OmexMeta)
add_dependencies(OmexMetaTests OmexMeta-static gtest gtest_main)

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















