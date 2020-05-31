//
// Created by Ciaran on 4/4/2020.
//

#include <semsim/Predicate.h>
#include <semsim/Resource.h>
#include <semsim/Subject.h>
#include <semsim/_Triple.h>
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
//        this->subject = std::move(
//                Subject(std::move(LibrdfNode::fromUriString(subject_str))
//                ));
        resource = Resource(LibrdfNode::fromUriString(resource_namespace + "/" + resource_id));
        this->predicate = BiomodelsBiologyQualifier("is");

    }
};

TEST_F(TripleTests, TestInstantiation1) {
    _Triple triple(
            std::move(subject),
            std::make_unique<Predicate>(std::move(predicate)),
            std::move(resource));
    ASSERT_TRUE(true); // if we get this far the test has passed
}

TEST_F(TripleTests, TestInstantiation2) {
    _Triple triple(std::move(subject), std::move(predicate), std::move(resource));
    ASSERT_TRUE(true); // if we get this far the test has passed
}

TEST_F(TripleTests, TestSubjectMetaId) {
    _Triple triple(std::move(subject), std::move(std::move(predicate)), std::move(resource));
    std::string &expected = subject_str;
    std::string actual = triple.getSubjectStr();
    ASSERT_STREQ(expected.c_str(), actual.c_str()
    );
}


TEST_F(TripleTests, TestSubjectMetaId2) {
    _Triple triple(std::move(subject), std::move(predicate), std::move(resource));
    std::string &expected = subject_str;
    ASSERT_STREQ(expected.c_str(), triple.getSubjectStr().c_str());
}

TEST_F(TripleTests, TestPredicate1) {
    _Triple triple(std::move(subject), std::move(predicate), std::move(resource));
    std::string expected = predicate_str;
    std::string actal = triple.getPredicateStr();
    ASSERT_STREQ(expected.c_str(), actal.c_str());
}


TEST_F(TripleTests, TestPredicate2) {
    _Triple triple(std::move(subject), std::move(predicate), std::move(resource));
    std::string expected = predicate_str;
    std::string actual = triple.getPredicateStr();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(TripleTests, TestPredicate4) {
    _Triple triple(std::move(subject), std::move(predicate), std::move(resource));
    std::string expected = predicate_str;
    std::string actual = triple.getPredicateStr();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(TripleTests, TestResource) {
    _Triple triple(std::move(subject), std::move(predicate), std::move(resource));
    std::string actual = triple.getResourceStr();
    std::string expected = resource_id;
    ASSERT_STREQ(expected.c_str(), resource_id.c_str());
}

TEST_F(TripleTests, TestResource2) {
    _Triple triple(std::move(subject), std::move(predicate), std::move(resource));
    std::string actual = triple.getResourceStr();
    std::string expected = resource_id;
    ASSERT_STREQ(expected.c_str(), resource_id.c_str());
}

TEST_F(TripleTests, TestTripleVecGetResource) {
    _Triple triple1(std::move(subject), std::move(predicate), std::move(resource));
    std::vector<_Triple> vec;
    vec.push_back(std::move(triple1));
    std::string actual = vec[0].getResourceStr();
    std::string expected = "https://identifiers.org/uniprot/P0DP23";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(TripleTests, TestTripleVecGetResource2) {
    _Triple triple1(std::move(subject), std::move(predicate), std::move(resource));
    std::vector<_Triple> vec;
    vec.push_back(std::move(triple1));
    std::string actual = vec[0].getResourceStr();
    std::string expected = "https://identifiers.org/uniprot/P0DP23";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(TripleTests, TestNullExceptionPred) {
    PredicatePtr predicatePtr;
    ASSERT_THROW(_Triple triple1(std::move(subject), std::move(predicatePtr), std::move(resource)),
                 semsim::NullPointerException);
}

TEST_F(TripleTests, TestNullExceptionSub) {
    Subject subject1;
    ASSERT_THROW(_Triple triple1(std::move(subject1), std::move(predicate), std::move(resource)),
                 semsim::NullPointerException);
}

TEST_F(TripleTests, TestNullExceptionRes) {
    Resource resource1;
    ASSERT_THROW(_Triple triple1(std::move(subject), std::move(predicate), std::move(resource1)),
                 semsim::NullPointerException);
}

TEST_F(TripleTests, TestToStatementPrediacte) {
    _Triple triple1(std::move(subject), std::move(predicate), std::move(resource));
    librdf_statement* statement = triple1.toStatement();
    librdf_node* node = librdf_statement_get_predicate(statement);
    librdf_uri* uri = librdf_node_get_uri(node);
    unsigned char* actual = librdf_uri_as_string(uri);
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    ASSERT_STREQ(expected.c_str(), (const char*)actual);
}

TEST_F(TripleTests, TestToStatementSubject) {
    _Triple triple1(std::move(subject), std::move(predicate), std::move(resource));
    librdf_statement* statement = triple1.toStatement();
    librdf_node* node = librdf_statement_get_subject(statement);
    librdf_uri* uri = librdf_node_get_uri(node);
    unsigned char* actual = librdf_uri_as_string(uri);
    std::string expected = "./MyModel#metaid_0";
    ASSERT_STREQ(expected.c_str(), (const char*)actual);
}


TEST_F(TripleTests, TestToStatementResource) {
        _Triple triple1(std::move(subject), std::move(predicate), std::move(resource));
    librdf_statement* statement = triple1.toStatement();
    librdf_node* node = librdf_statement_get_object(statement);
    librdf_uri* uri = librdf_node_get_uri(node);
    unsigned char* actual = librdf_uri_as_string(uri);
    std::string expected = "https://identifiers.org/uniprot/P0DP23";
    ASSERT_STREQ(expected.c_str(), (const char*)actual);

}

TEST_F(TripleTests, TestFromStatementSubject) {
    _Triple triple1(std::move(subject), std::move(predicate), std::move(resource));
    librdf_statement* statement = triple1.toStatement();
    _Triple triple2 = _Triple::fromStatement(LibrdfStatement(statement));
    std::string actual = triple2.getSubjectStr();
    std::string expected = "./MyModel#metaid_0";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(TripleTests, TestFromStatementResource) {
    _Triple triple1(std::move(subject), std::move(predicate), std::move(resource));
    librdf_statement* statement = triple1.toStatement();
    _Triple triple2 = _Triple::fromStatement(LibrdfStatement(statement));
    std::string actual = triple2.getResourceStr();
    std::string expected = "https://identifiers.org/uniprot/P0DP23";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(TripleTests, TestFromStatementPredicate) {
    _Triple triple1(std::move(subject), std::move(predicate), std::move(resource));
    librdf_statement* statement = triple1.toStatement();
    _Triple triple2 = _Triple::fromStatement(LibrdfStatement(statement));
    std::string actual = triple2.getPredicateStr();
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    ASSERT_STREQ(expected.c_str(), actual.c_str()
    );
}


//TEST_F(TripleTests, TestAbout) {
//    triple.setAbout("metaid2");
//    std::string expected = "metaid2";
//    std::string actual = triple.getAbout();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
//
//TEST_F(TripleTests, TestSetPredicate) {
//    _Triple triple(world_);
//    triple.setPredicate("bqb", "is");
//    std::string expected = "http://biomodels.net/biology-qualifiers/is";
//    std::string actual = triple.getpredicate()->str();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
//TEST_F(TripleTests, TestSetPredicate2) {
//    _Triple triple(world_);
//    triple.setPredicateNew("https://stackoverflow.com/questions/", "how-do-you", "so");
//    std::string expected = "https://stackoverflow.com/questions/how-do-you";
//    predicate std::move(predicate) = triple.getpredicate();
//    std::string actual = std::move(predicate)->str();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
//TEST_F(TripleTests, TestResourceLiteral) {
//    _Triple triple();
//    triple.setResourceLiteral("Annotating");
//    std::string expected = "Annotating";
//    std::string actual = triple.getResource().str();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
//TEST_F(TripleTests, TestResourceUri) {
//    _Triple triple(world_);
//    triple.setResourceUri("AnnotatingUri");
//    std::string expected = "AnnotatingUri";
//    std::string actual = triple.getResource().str();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
//TEST_F(TripleTests, TestResourceBlank) {
//    _Triple triple(world_);
//    triple.setResourceBlank("AnnotatingBlank");
//    std::string expected = "AnnotatingBlank";
//    std::string actual = triple.getResource().str();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
//TEST_F(TripleTests, TestBuilderPattern) {
//    _Triple triple(world_);
//
//    triple.setAbout("metaid1")
//            .setPredicate("bqb", "is")
//            .setResourceUri("uniprot/PD4034");
//
//    std::string actual = triple.str();
//    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
//                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
//                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
//                           "   xml:base=\"file://./annotations.rdf\">\n"
//                           "  <rdf:Description rdf:about=\"metaid1\">\n"
//                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/uniprot/PD4034\"/>\n"
//                           "  </rdf:Description>\n"
//                           "</rdf:RDF>\n";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}





























