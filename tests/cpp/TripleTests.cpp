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
        subject = Subject(LibrdfNode::fromUriString(subject_str));
        resource = Resource(LibrdfNode::fromUriString(resource_namespace + "/" + resource_id));
        predicate = BiomodelsBiologyQualifier("is");

    }
};

TEST_F(TripleTests, TestInstantiation1) {
    Triple triple(subject, predicate, resource);
    ASSERT_TRUE(true); // if we get this far the test has passed
}

TEST_F(TripleTests, TestInstantiation2) {
    Triple triple(subject,
                  std::make_shared<Predicate>(predicate),
                  resource);
    ASSERT_TRUE(true); // if we get this far the test has passed
}

TEST_F(TripleTests, TestSubjectString) {
    Triple triple(subject, predicate, resource);
    std::string &expected = subject_str;
    const LibrdfNode& node = triple.getSubject();
    std::string actual = node.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(TripleTests, TestSubjectString2) {
    Triple triple(subject, predicate, resource);
    std::string &expected = subject_str;
    LibrdfNode node = triple.getSubject();
    std::string actual = node.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(TripleTests, TestSubjectStr3) {
    Triple triple2(subject, predicate, resource);
    std::string &expected = subject_str;
    ASSERT_STREQ(expected.c_str(), triple2.getSubject().str().c_str());
}

TEST_F(TripleTests, TestPredicate1) {
    Triple triple2(subject, predicate, resource);
    std::string expected = predicate_str;
    std::string actal = triple2.getPredicate().str();
    ASSERT_STREQ(expected.c_str(), actal.c_str());
}


TEST_F(TripleTests, TestPredicate2) {
    Triple triple2(subject, predicate, resource);
    std::string expected = predicate_str;
    std::string actual = triple2.getPredicate().str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(TripleTests, TestPredicate4) {
    Triple triple2(subject, predicate, resource);
    std::string expected = predicate_str;
    std::string actual = triple2.getPredicate().str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(TripleTests, TestResource) {
    Triple triple2(subject, predicate, resource);
    std::string actual = triple2.getResource().str();
    std::string expected = resource_id;
    ASSERT_STREQ(expected.c_str(), resource_id.c_str());
}

TEST_F(TripleTests, TestResource2) {
    Triple triple2(subject, predicate, resource);
    std::string actual = triple2.getResource().str();
    std::string expected = resource_id;
    ASSERT_STREQ(expected.c_str(), resource_id.c_str());
}

TEST_F(TripleTests, TestTriple2VecGetResource) {
    Triple triple21(subject, predicate, resource);
    std::vector<Triple> vec;
    vec.push_back(triple21);
    std::string actual = vec[0].getResource().str();
    std::string expected = "https://identifiers.org/uniprot/P0DP23";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(TripleTests, TestTriple2VecGetResource2) {
    Triple triple21(subject, predicate, resource);
    std::vector<Triple> vec;
    vec.push_back(triple21);
    std::string actual = vec[0].getResource().str();
    std::string expected = "https://identifiers.org/uniprot/P0DP23";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(TripleTests, TestStatementSubject) {
    Triple triple21(subject, predicate, resource);
    librdf_statement* statement = triple21.get();
    librdf_node* n = librdf_statement_get_subject(statement);
    librdf_uri* uri = librdf_node_get_uri(n);
    unsigned char* s = librdf_uri_as_string(uri);
    std::string expected = "./MyModel#metaid_0";
    ASSERT_STREQ(expected.c_str(), (const char*)s);
}

TEST_F(TripleTests, TestStatementPred) {
    Triple triple21(subject, predicate, resource);
    librdf_statement* statement = triple21.get();
    librdf_node* n = librdf_statement_get_predicate(statement);
    librdf_uri* uri = librdf_node_get_uri(n);
    unsigned char* s = librdf_uri_as_string(uri);
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    ASSERT_STREQ(expected.c_str(), (const char*)s);
}

TEST_F(TripleTests, TestStatementResource) {
    Triple triple21(subject, predicate, resource);
    librdf_statement* statement = triple21.get();
    librdf_node* n = librdf_statement_get_object(statement);
    librdf_uri* uri = librdf_node_get_uri(n);
    unsigned char* s = librdf_uri_as_string(uri);
    std::string expected = "https://identifiers.org/uniprot/P0DP23";
    ASSERT_STREQ(expected.c_str(), (const char*)s);
}


//TEST_F(TripleTests, TestAbout) {
//    Triple triple2;
//    triple2.setAbout("metaid2");
//    std::string expected = "metaid2";
//    std::string actual = triple2.getAbout();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
////
////
////TEST_F(TripleTests, TestSetPredicate) {
////    Triple triple2(world_);
////    Triple.setPredicate("bqb", "is");
////    std::string expected = "http://biomodels.net/biology-qualifiers/is";
////    std::string actual = triple2.getpredicate()->str();
////    ASSERT_STREQ(expected.c_str(), actual.c_str());
////}
////
////TEST_F(TripleTests, TestSetPredicate2) {
////    Triple triple2(world_);
////    Triple.setPredicateNew("https://stackoverflow.com/questions/", "how-do-you", "so");
////    std::string expected = "https://stackoverflow.com/questions/how-do-you";
////    predicate predicate = triple2.getpredicate();
////    std::string actual = predicate)->str(;
////    ASSERT_STREQ(expected.c_str(), actual.c_str());
////}
////
////TEST_F(TripleTests, TestResourceLiteral) {
////    Triple triple2();
////    Triple.setResourceLiteral("Annotating");
////    std::string expected = "Annotating";
////    std::string actual = triple2.getResource().str();
////    ASSERT_STREQ(expected.c_str(), actual.c_str());
////}
////
////TEST_F(TripleTests, TestResourceUri) {
////    Triple triple2(world_);
////    Triple.setResourceUri("AnnotatingUri");
////    std::string expected = "AnnotatingUri";
////    std::string actual = triple2.getResource().str();
////    ASSERT_STREQ(expected.c_str(), actual.c_str());
////}
////
////TEST_F(TripleTests, TestResourceBlank) {
////    Triple triple2(world_);
////    Triple.setResourceBlank("AnnotatingBlank");
////    std::string expected = "AnnotatingBlank";
////    std::string actual = triple2.getResource().str();
////    ASSERT_STREQ(expected.c_str(), actual.c_str());
////}
////
////TEST_F(TripleTests, TestBuilderPattern) {
////    Triple triple2(world_);
////
////    Triple.setAbout("metaid1")
////            .setPredicate("bqb", "is")
////            .setResourceUri("uniprot/PD4034");
////
////    std::string actual = Triple.str();
////    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
////                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
////                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
////                           "   xml:base=\"file://./annotations.rdf\">\n"
////                           "  <rdf:Description rdf:about=\"metaid1\">\n"
////                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/uniprot/PD4034\"/>\n"
////                           "  </rdf:Description>\n"
////                           "</rdf:RDF>\n";
////    ASSERT_STREQ(expected.c_str(), actual.c_str());
////}
//
//
//


























