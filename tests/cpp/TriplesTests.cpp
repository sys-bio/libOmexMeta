//
// Created by Ciaran on 4/29/2020.
//
#include "RedlandAPIWrapper.h"
#include "AnnotationSamples.h"
#include <semsim/Triples.h>

#include <librdf.h>
#include <gtest/gtest.h>

using namespace semsim;

class TriplesTests : public ::testing::Test {

public:

    AnnotationSamples samples;
    LibrdfStorage storage;
    LibrdfModel model;

    Subject subject;
    Resource resource;
    BiomodelsBiologyQualifier predicate;


    //todo subject could pass the world to the node
    TriplesTests() {
        model = LibrdfModel(storage.get());
        this->subject = Subject::fromRawPtr(LibrdfNode::fromUriString("subby").get());
        this->resource = Resource::fromRawPtr(LibrdfNode::fromUriString(("space/id")).get());
        this->predicate = BiomodelsBiologyQualifier("is");
    }

    ~TriplesTests(){
        storage.freeStorage();
        model.freeModel();
    }
};

TEST_F(TriplesTests, TestCreate) {
    Triple triple1 = Triple(subject.getNode(), predicate.getNode(), resource.getNode());
    Triples triples(std::move(triple1));
    ASSERT_EQ(1, triples.size());
}

TEST_F(TriplesTests, TestCreate2) {
    Triple triple1 = Triple(subject.getNode(), predicate.getNode(), resource.getNode());
    TripleVector vec;
    vec.push_back(std::move(triple1));
    Triples triples(std::move(vec));
    ASSERT_EQ(1, triples.size());
}

TEST_F(TriplesTests, TestPushBack) {
    Triple triple1 = Triple(subject.getNode(), predicate.getNode(), resource.getNode());
    Triples triples;
    triples.push_back(std::move(triple1));
    ASSERT_EQ(1, triples.size());
}

TEST_F(TriplesTests, TestEmplaceBack2) {
    Triples triples;
    triples.emplace_back(std::move(subject),
                         std::make_unique<Predicate>(std::move(predicate)),
                         std::move(resource));
    ASSERT_EQ(1, triples.size());
}

TEST_F(TriplesTests, TestEmplaceBack3) {
    Triples triples;
    triples.emplace_back(std::move(subject),
                         BiomodelsModelQualifier("isDerivedFrom"),
                         std::move(resource));
    ASSERT_EQ(1, triples.size());
    // When you give a subject/predicate/resource to Triple/Triples they
    // are given ownership of the node pointer inside the subject/predicate/resource/
    // In this test we do not use predicate (from setting up test fixture) so we must free it.
    predicate.freeNode();
}

TEST_F(TriplesTests, TestEmplaceBack4) {
    Triples triples;
    triples.emplace_back(std::move(subject),
                         BiomodelsBiologyQualifier("is"),
                         std::move(resource));
    ASSERT_EQ(1, triples.size());
    predicate.freeNode();
}

TEST_F(TriplesTests, TestEmplaceBack5) {
    Triples triples;
    triples.emplace_back(std::move(subject),
                         DCTerm("Description"),
                         std::move(resource));
    ASSERT_EQ(1, triples.size());
    predicate.freeNode();
}

TEST_F(TriplesTests, TestEmplaceBack6) {
    Triples triples;
    triples.emplace_back(std::move(subject),
                         SemSim("hasSourceParticipant"),
                         std::move(resource));
    ASSERT_EQ(1, triples.size());
    predicate.freeNode();
}


TEST(TriplesTestsNoFixture, TestStr) {
    Triples triples;
    triples.emplace_back(
            LibrdfNode::fromUriString("http://subject1.com/subject1").get(),
            LibrdfNode::fromUriString("http://predicate1.com/predicate1").get(),
            LibrdfNode::fromUriString("http://resource1.com/resource1").get()
    );
    triples.emplace_back(
            LibrdfNode::fromUriString("http://subject2.com/subject2").get(),
            LibrdfNode::fromUriString("http://predicate2.com/predicate2").get(),
            LibrdfNode::fromUriString("http://resource2.com/resource2").get()
    );
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"http://subject1.com/subject1\">\n"
                           "    <ns1:predicate1 xmlns:ns1=\"http://predicate1.com/\"\n"
                           "       rdf:resource=\"http://resource1.com/resource1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://subject2.com/subject2\">\n"
                           "    <ns2:predicate2 xmlns:ns2=\"http://predicate2.com/\"\n"
                           "       rdf:resource=\"http://resource2.com/resource2\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    std::string actual = triples.str();
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}



TEST(TriplesTestsNoFixture, TestIteration) {
    Triples triples;
    triples.emplace_back(
            LibrdfNode::fromUriString("http://subject1.com/subject1").get(),
            LibrdfNode::fromUriString("http://predicate1.com/predicate1").get(),
            LibrdfNode::fromUriString("http://resource1.com/resource1").get()
    );
    triples.emplace_back(
            LibrdfNode::fromUriString("http://subject2.com/subject2").get(),
            LibrdfNode::fromUriString("http://predicate2.com/predicate2").get(),
            LibrdfNode::fromUriString("http://resource2.com/resource2").get()
    );
    std::ostringstream os;
    for (auto it: triples){
        os << it->getSubjectStr() << std::endl;
    }
    std::string expected = "http://subject1.com/subject1\n"
                           "http://subject2.com/subject2\n";
    ASSERT_STREQ(expected.c_str(), os.str().c_str());

}



