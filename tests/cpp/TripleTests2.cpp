//
// Created by Ciaran on 4/4/2020.
//

#include <semsim/Predicate.h>
#include <semsim/Resource.h>
#include <semsim/Subject.h>
#include <semsim/Triple2.h>
#include "gtest/gtest.h"
#include "AnnotationSamples.h"

using namespace semsim;

class Triple2Tests : public ::testing::Test {
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
    Triple2Tests() {
        subject = Subject(LibrdfNode::fromUriString(subject_str));
//        this->subject = std::move(
//                Subject(LibrdfNode::fromUriString(subject_str)
//                ));
        resource = Resource(LibrdfNode::fromUriString(resource_namespace + "/" + resource_id));
        this->predicate = BiomodelsBiologyQualifier("is");

    }
};

TEST_F(Triple2Tests, TestInstantiation1) {
    Triple2 triple(subject, predicate, resource);
    ASSERT_TRUE(true); // if we get this far the test has passed
}

TEST_F(Triple2Tests, TestInstantiation2) {
    Triple2 triple(subject,
            std::make_shared<Predicate>(predicate),
                    resource);
    ASSERT_TRUE(true); // if we get this far the test has passed
}

TEST_F(Triple2Tests, TestSubjectString) {
    Triple2 triple(subject, predicate, resource);
    std::string &expected = subject_str;
    const LibrdfNode& node = triple.getSubject();
    std::string actual = node.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(Triple2Tests, TestSubjectString2) {
    Triple2 triple(subject, predicate, resource);
    std::string &expected = subject_str;
    LibrdfNode node = triple.getSubject();
    std::string actual = node.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(Triple2Tests, TestSubjectStr3) {
    Triple2 triple2(subject, predicate, resource);
    std::string &expected = subject_str;
    ASSERT_STREQ(expected.c_str(), triple2.getSubject().str().c_str());
}

TEST_F(Triple2Tests, TestPredicate1) {
    Triple2 triple2(subject, predicate, resource);
    std::string expected = predicate_str;
    std::string actal = triple2.getPredicate().str();
    ASSERT_STREQ(expected.c_str(), actal.c_str());
}


TEST_F(Triple2Tests, TestPredicate2) {
    Triple2 triple2(subject, predicate, resource);
    std::string expected = predicate_str;
    std::string actual = triple2.getPredicate().str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(Triple2Tests, TestPredicate4) {
    Triple2 triple2(subject, predicate, resource);
    std::string expected = predicate_str;
    std::string actual = triple2.getPredicate().str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(Triple2Tests, TestResource) {
    Triple2 triple2(subject, predicate, resource);
    std::string actual = triple2.getResource().str();
    std::string expected = resource_id;
    ASSERT_STREQ(expected.c_str(), resource_id.c_str());
}

TEST_F(Triple2Tests, TestResource2) {
    Triple2 triple2(subject, predicate, resource);
    std::string actual = triple2.getResource().str();
    std::string expected = resource_id;
    ASSERT_STREQ(expected.c_str(), resource_id.c_str());
}

TEST_F(Triple2Tests, TestTriple2VecGetResource) {
    Triple2 triple21(subject, predicate, resource);
    std::vector<Triple2> vec;
    vec.push_back(triple21);
    std::string actual = vec[0].getResource().str();
    std::string expected = "https://identifiers.org/uniprot/P0DP23";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(Triple2Tests, TestTriple2VecGetResource2) {
    Triple2 triple21(subject, predicate, resource);
    std::vector<Triple2> vec;
    vec.push_back(triple21);
    std::string actual = vec[0].getResource().str();
    std::string expected = "https://identifiers.org/uniprot/P0DP23";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(Triple2Tests, TestStatementSubject) {
    Triple2 triple21(subject, predicate, resource);
    librdf_statement* statement = triple21.get();
    librdf_node* n = librdf_statement_get_subject(statement);
    librdf_uri* uri = librdf_node_get_uri(n);
    unsigned char* s = librdf_uri_as_string(uri);
    std::string expected = "./MyModel#metaid_0";
    ASSERT_STREQ(expected.c_str(), (const char*)s);
}

TEST_F(Triple2Tests, TestStatementPred) {
    Triple2 triple21(subject, predicate, resource);
    librdf_statement* statement = triple21.get();
    librdf_node* n = librdf_statement_get_predicate(statement);
    librdf_uri* uri = librdf_node_get_uri(n);
    unsigned char* s = librdf_uri_as_string(uri);
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    ASSERT_STREQ(expected.c_str(), (const char*)s);
}
TEST_F(Triple2Tests, TestStatementResource) {
    Triple2 triple21(subject, predicate, resource);
    librdf_statement* statement = triple21.get();
    librdf_node* n = librdf_statement_get_object(statement);
    librdf_uri* uri = librdf_node_get_uri(n);
    unsigned char* s = librdf_uri_as_string(uri);
    std::string expected = "https://identifiers.org/uniprot/P0DP23";
    ASSERT_STREQ(expected.c_str(), (const char*)s);
}


//TEST_F(Triple2Tests, TestAbout) {
//    Triple2 triple2;
//    triple2.setAbout("metaid2");
//    std::string expected = "metaid2";
//    std::string actual = triple2.getAbout();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
////
////
////TEST_F(Triple2Tests, TestSetPredicate) {
////    Triple2 triple2(world_);
////    Triple2.setPredicate("bqb", "is");
////    std::string expected = "http://biomodels.net/biology-qualifiers/is";
////    std::string actual = triple2.getpredicate()->str();
////    ASSERT_STREQ(expected.c_str(), actual.c_str());
////}
////
////TEST_F(Triple2Tests, TestSetPredicate2) {
////    Triple2 triple2(world_);
////    Triple2.setPredicateNew("https://stackoverflow.com/questions/", "how-do-you", "so");
////    std::string expected = "https://stackoverflow.com/questions/how-do-you";
////    predicate predicate = triple2.getpredicate();
////    std::string actual = predicate)->str(;
////    ASSERT_STREQ(expected.c_str(), actual.c_str());
////}
////
////TEST_F(Triple2Tests, TestResourceLiteral) {
////    Triple2 triple2();
////    Triple2.setResourceLiteral("Annotating");
////    std::string expected = "Annotating";
////    std::string actual = triple2.getResource().str();
////    ASSERT_STREQ(expected.c_str(), actual.c_str());
////}
////
////TEST_F(Triple2Tests, TestResourceUri) {
////    Triple2 triple2(world_);
////    Triple2.setResourceUri("AnnotatingUri");
////    std::string expected = "AnnotatingUri";
////    std::string actual = triple2.getResource().str();
////    ASSERT_STREQ(expected.c_str(), actual.c_str());
////}
////
////TEST_F(Triple2Tests, TestResourceBlank) {
////    Triple2 triple2(world_);
////    Triple2.setResourceBlank("AnnotatingBlank");
////    std::string expected = "AnnotatingBlank";
////    std::string actual = triple2.getResource().str();
////    ASSERT_STREQ(expected.c_str(), actual.c_str());
////}
////
////TEST_F(Triple2Tests, TestBuilderPattern) {
////    Triple2 triple2(world_);
////
////    Triple2.setAbout("metaid1")
////            .setPredicate("bqb", "is")
////            .setResourceUri("uniprot/PD4034");
////
////    std::string actual = Triple2.str();
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


























