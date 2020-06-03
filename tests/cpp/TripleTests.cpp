//
// Created by Ciaran on 4/4/2020.
//

#include <semsim/Predicate.h>
#include <semsim/Resource.h>
#include <semsim/Subject.h>
#include <semsim/Triple.h>
#include "gtest/gtest.h"
#include "AnnotationSamples.h"

using namespace semsim;

class TripleTests : public ::testing::Test {
public:

    AnnotationSamples samples;
    std::string subject_str = "./MyModel#metaid_0";
    std::string predicate_str = "http://biomodels.net/biology-qualifiers/is";
    std::string resource_namespace = "uniprot";
    std::string resource_id = "P0DP23";

    Subject subject;
    Resource resource;
    BiomodelsBiologyQualifier predicate;


    //todo subject could pass the world_ to the node
    TripleTests() {
        subject = Subject::fromRawPtr(LibrdfNode::fromUriString(subject_str));
        resource = Resource::fromRawPtr(LibrdfNode::fromUriString(resource_namespace + "/" + resource_id));
        predicate = BiomodelsBiologyQualifier("is");

    }
};

TEST_F(TripleTests, TestInstantiation1) {
    Triple triple(subject.getNode(), predicate.getNode(), resource.getNode());
    ASSERT_TRUE(true); // if we get this far the test has passed
}

TEST(TripleTestsNoFixture, TestInstantiationEmptyForBuilder) {
    // when we use builder interface, Triple is created empty and we fill in the bits of information  from user input
    Triple triple;
    ASSERT_TRUE(triple.isEmpty());
    // remember to free the unused resources from test fixture
}

TEST_F(TripleTests, TestInstantiation2) {
    Triple triple(subject,
                  std::make_shared<Predicate>(predicate),
                  resource);
    ASSERT_TRUE(true); // if we get this far the test has passed
}

TEST_F(TripleTests, TestSubjectString) {
    Triple triple(subject.getNode(), predicate.getNode(), resource.getNode());
    std::string &expected = subject_str;
    librdf_node *node = triple.getSubject();
    librdf_uri *uri = librdf_node_get_uri(node);
    const char *actual = (const char *) librdf_uri_as_string(uri);
    ASSERT_STREQ(expected.c_str(), actual);
}


TEST_F(TripleTests, TestSubjectStr2) {
    Triple triple(subject.getNode(), predicate.getNode(), resource.getNode());
    std::string &expected = subject_str;
    ASSERT_STREQ(expected.c_str(), triple.getSubjectStr().c_str());
}

TEST_F(TripleTests, TestPredicate1) {
    Triple triple(subject.getNode(), predicate.getNode(), resource.getNode());
    std::string expected = predicate_str;
    ASSERT_STREQ(expected.c_str(), triple.getPredicateStr().c_str());
}


TEST_F(TripleTests, TestResource) {
    Triple triple(subject.getNode(), predicate.getNode(), resource.getNode());
    std::string actual = triple.getResourceStr();
    std::string expected = resource_id;
    ASSERT_STREQ(expected.c_str(), resource_id.c_str());
}

TEST_F(TripleTests, TestTriple2VecGetResource) {
    Triple triple(subject.getNode(), predicate.getNode(), resource.getNode());
    std::vector<Triple> vec;
    vec.push_back(triple);
    std::string actual = vec[0].getResourceStr();
    std::string expected = "https://identifiers.org/uniprot/P0DP23";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(TripleTests, TestStatementSubject) {
    Triple triple(subject.getNode(), predicate.getNode(), resource.getNode());
    librdf_statement *statement = triple.get();
    librdf_node *n = librdf_statement_get_subject(statement);
    librdf_uri *uri = librdf_node_get_uri(n);
    unsigned char *s = librdf_uri_as_string(uri);
    std::string expected = "./MyModel#metaid_0";
    ASSERT_STREQ(expected.c_str(), (const char *) s);
}

TEST_F(TripleTests, TestStatementPred) {
    Triple triple(subject.getNode(), predicate.getNode(), resource.getNode());
    librdf_statement *statement = triple.get();
    librdf_node *n = librdf_statement_get_predicate(statement);
    librdf_uri *uri = librdf_node_get_uri(n);
    unsigned char *s = librdf_uri_as_string(uri);
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    ASSERT_STREQ(expected.c_str(), (const char *) s);
}

TEST_F(TripleTests, TestStatementResource) {
    Triple triple(subject.getNode(), predicate.getNode(), resource.getNode());
    librdf_statement *statement = triple.get();
    librdf_node *n = librdf_statement_get_object(statement);
    librdf_uri *uri = librdf_node_get_uri(n);
    unsigned char *s = librdf_uri_as_string(uri);
    std::string expected = "https://identifiers.org/uniprot/P0DP23";
    ASSERT_STREQ(expected.c_str(), (const char *) s);
}


TEST(TripleTestsNoFixture, TestAbout) {
    Triple triple;
    triple.setAbout("metaid2");
    std::string expected = "metaid2";
    std::string actual = triple.getAbout();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST(TripleTestsNoFixture, TestSetPredicate) {
    Triple triple;
    triple.setPredicate("bqb", "is");
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    ASSERT_STREQ(expected.c_str(), triple.getPredicateStr().c_str());
}


TEST(TripleTestsNoFixture, TestResourceLiteral) {
    Triple triple;
    triple.setResourceLiteral("Annotating");
    std::string expected = "Annotating";
    std::string actual = triple.getResourceStr();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST(TripleTestsNoFixture, TestResourceUri) {
    Triple triple;
    triple.setResourceUri("AnnotatingUri");
    std::string expected = "AnnotatingUri";
    ASSERT_STREQ(expected.c_str(), triple.getResourceStr().c_str());

}

TEST(TripleTestsNoFixture, TestResourceBlank) {
    Triple triple;
    triple.setResourceBlank("AnnotatingBlank");
    std::string expected = "AnnotatingBlank";
    ASSERT_STREQ(expected.c_str(), triple.getResourceStr().c_str());

}

TEST_F(TripleTests, TestBuilderPattern) {
    Triple triple;

    triple.setAbout("metaid1")
            .setPredicate("bqb", "is")
            .setResourceUri("uniprot/PD4034");

    std::string actual = triple.str();
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"metaid1\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/uniprot/PD4034\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());

    // Aaand free the excess nodes
    predicate.freeNode();
    subject.free();
    resource.free();
}

TEST_F(TripleTests, TestBuilderPatternWithSemSimPredicate) {
    Triple triple;

    triple.setAbout("metaid1")
            .setPredicate("SemSim", "hasSourceParticipant")
            .setResourceUri("uniprot/PD4034");

    std::string actual = triple.str();
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"metaid1\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/uniprot/PD4034\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());

    // Aaand free the excess nodes
    predicate.freeNode();
    subject.free();
    resource.free();
}





























