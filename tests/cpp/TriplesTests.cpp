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

    ~TriplesTests() {
        storage.freeStorage();
        model.freeModel();
    }
};

/*
 * We can create an empty vector and *move* a triple into it.
 */
TEST_F(TriplesTests, TestCreateMoveAfterInstantiation) {
    Triple triple1 = Triple(subject.getNode(), predicate.getNode(), resource.getNode());
    Triples triples;
    triples.move_back(triple1);
    ASSERT_EQ(1, triples.size());
    triples.freeTriples();
}

/*
 * We can also move the triple into it on instantiation.
 */
TEST_F(TriplesTests, TestCreateMoveOnInstantiation) {
    Triple triple1 = Triple(subject.getNode(), predicate.getNode(), resource.getNode());
    Triples triples(triple1);
    ASSERT_EQ(1, triples.size());
    triples.freeTriples();
}


TEST_F(TriplesTests, TestEmplaceBack) {
    Triples triples;
    triples.emplace_back(subject,
                         std::make_unique<Predicate>(std::move(predicate)),
                         resource);
    ASSERT_EQ(1, triples.size());
    triples.freeTriples();
}

/*
 * Note: we no longer need to explicitely call the move method
 * on the subject/predicate/resource arguments since this is
 * done automatically behind the scenes anyway - it is equivalent to
 * TestEmplaceBack
 */
TEST_F(TriplesTests, TestEmplaceBack2) {
    Triples triples;
    triples.emplace_back(subject,
                         std::make_unique<Predicate>(std::move(predicate)),
                         resource);
    ASSERT_EQ(1, triples.size());
    triples.freeTriples();
}

TEST_F(TriplesTests, TestEmplaceBack3) {
    Triples triples;
    triples.emplace_back(subject,
                         BiomodelsModelQualifier("isDerivedFrom"),
                         resource);
    ASSERT_EQ(1, triples.size());
    // When you give a subject/predicate/resource to Triple/Triples they
    // are given ownership of the node pointer inside the subject/predicate/resource/
    // In this test we do not use predicate (from setting up test fixture) so we must free it.
    predicate.freeNode();
    triples.freeTriples();
}

TEST_F(TriplesTests, TestEmplaceBack4) {
    Triples triples;
    triples.emplace_back(subject,
                         BiomodelsBiologyQualifier("is"),
                         resource);
    ASSERT_EQ(1, triples.size());
    predicate.freeNode();
    triples.freeTriples();
}

TEST_F(TriplesTests, TestEmplaceBack5) {
    Triples triples;
    triples.emplace_back(subject,
                         DCTerm("Description"),

                         resource);
    ASSERT_EQ(1, triples.size());
    predicate.freeNode();
    triples.freeTriples();
}

TEST_F(TriplesTests, TestEmplaceBack6) {
    Triples triples;
    triples.emplace_back(subject,
                         SemSim("hasSourceParticipant"),
                         resource);
    ASSERT_EQ(1, triples.size());
    predicate.freeNode();
    triples.freeTriples();
}

TEST(TriplesTestsNoFixture, TestGetterOperator) {
    Triples triples;
    triples.emplace_back(LibrdfNode::fromUriString("subject1").get(),
                         SemSim("hasSinkParticipant").getNode(),
                         LibrdfNode::fromLiteral("literal node1").get());
    triples.emplace_back(LibrdfNode::fromUriString("subject2").get(),
                         SemSim("hasSourceParticipant").getNode(),
                         LibrdfNode::fromLiteral("literal node2").get());
    // make sure we have 2 triples
    ASSERT_EQ(2, triples.size());

    // get by copy
    Triple triple = triples[1];

    // make sure we still have two Triple objects in Triples
    ASSERT_EQ(2, triples.size());

    // do checks for raptors internal reference counter
    ASSERT_EQ(1, triples[0].getStatement()->usage);
    ASSERT_EQ(2, triples[1].getStatement()->usage);
    ASSERT_EQ(2, triple.getStatement()->usage);

    // free the triple and reduce count to 1
    triple.freeStatement();
    ASSERT_EQ(1, triples[1].getStatement()->usage);

    // finally free the triples. All is accounted for.
    triples.freeTriples();

}

TEST(TriplesTestsNoFixture, TestPop) {
    Triples triples;
    triples.emplace_back(LibrdfNode::fromUriString("subject1").get(),
                         SemSim("hasSinkParticipant").getNode(),
                         LibrdfNode::fromLiteral("literal node1").get());
    triples.emplace_back(LibrdfNode::fromUriString("subject2").get(),
                         SemSim("hasSourceParticipant").getNode(),
                         LibrdfNode::fromLiteral("literal node2").get());
    // make sure we have 2 triples
    ASSERT_EQ(2, triples.size());

    // get by move
    Triple triple = triples.pop();

    // make sure we still have 1 Triple objects in Triples
    ASSERT_EQ(1, triples.size());

    // do checks for raptors internal reference counter
    ASSERT_EQ(1, triples[0].getStatement()->usage);
    ASSERT_EQ(1, triple.getStatement()->usage);

    // free the triple and reduce count to 1
    triple.freeStatement();

    // free the triples. All is accounted for.
    triples.freeTriples();

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
    triples.freeTriples();
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
    for (int i=0; i<triples.size();i++) {
        os << triples[i].getSubjectStr() << std::endl;
    }
    std::string expected = "http://subject1.com/subject1\n"
                           "http://subject2.com/subject2\n";
    ASSERT_STREQ(expected.c_str(), os.str().c_str());
    triples.freeTriples();
}

TEST(TriplesTestsNoFixture, TestMakeSameTriplesTwice) {
//    Triples triples;
//    triples.emplace_back(
//            LibrdfNode::fromUriString("http://subject1.com/subject1").get(),
//            LibrdfNode::fromUriString("http://predicate1.com/predicate1").get(),
//            LibrdfNode::fromUriString("http://resource1.com/resource1").get()
//    );
//    triples.emplace_back(
//            LibrdfNode::fromUriString("http://subject2.com/subject2").get(),
//            LibrdfNode::fromUriString("http://predicate2.com/predicate2").get(),
//            LibrdfNode::fromUriString("http://resource2.com/resource2").get()
//    );
//    std::ostringstream os;
//    for (int i=0; i<triples.size();i++) {
//        os << triples[i].getSubjectStr() << std::endl;
//    }
//    std::string expected = "http://subject1.com/subject1\n"
//                           "http://subject2.com/subject2\n";
//    ASSERT_STREQ(expected.c_str(), os.str().c_str());
//    triples.freeTriples();
}



