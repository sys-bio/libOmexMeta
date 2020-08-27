###########################################################################
#   Sources for tests
#

set(target OmexMetaTests)

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
add_executable(${target} ${TEST_SOURCES})

# indicate that on windows we are using the static library,
# not the static
target_compile_definitions(
        ${target} PRIVATE OMEXMETA_STATIC_DEFINE REDLAND_STATIC_DEFINE
)

# add test so it can be run with $ctest or $make test
add_test(
        NAME ${target}
        COMMAND $<TARGET_FILE:${target}>
)

set_tests_properties(${target} PROPERTIES DEPENDS OmexMeta)
add_dependencies(${target} OmexMeta-static gtest gtest_main)

# links
target_link_libraries(${target} PUBLIC
        # Order matters!
        $<TARGET_FILE:OmexMeta-static>
        $<TARGET_FILE:redland-combined-static>
        ${LINK_LIBRARIES}
        ${RUNTIME}# best here so no clash with dynamic
        gtest gtest_main
        )

#includes
target_include_directories(${target} PRIVATE
        ${GOOGLETEST_SOURCE}/googletest/include
        ${INCLUDE_DIRECTORIES}
        ${WRAPPER_SOURCE_DIR}
        )

add_dependencies(${target} OmexMeta-static gtest gtest_main)

install(
        TARGETS ${target}
        EXPORT ${target}
        RUNTIME DESTINATION bin
)















