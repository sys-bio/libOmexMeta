//
// Created by Ciaran on 4/29/2020.
//
#include "RedlandAPIWrapper.h"
#include "AnnotationSamples.h"
#include "omexmeta/Triples.h"

#include <librdf.h>
#include <gtest/gtest.h>

using namespace omexmeta;

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
                         DCTerm("description"),
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



/*
 * deleted test. It copies and we removed ability to copy tripels.
 */
//TEST(TriplesTestsNoFixture, TestGetterOperator) {
//    Triples triples;
//    triples.emplace_back(LibrdfNode::fromUriString("subject1").get(),
//                         SemSim("hasSinkParticipant").getNode(),
//                         LibrdfNode::fromLiteral("literal node1").get());
//    triples.emplace_back(LibrdfNode::fromUriString("subject2").get(),
//                         SemSim("hasSourceParticipant").getNode(),
//                         LibrdfNode::fromLiteral("literal node2").get());
//    // make sure we have 2 triples
//    ASSERT_EQ(2, triples.size());
//
//    // get by copy
//    Triple triple = triples[1];
//
//    // make sure we still have two Triple objects in Triples
//    ASSERT_EQ(2, triples.size());
//
//    // do checks for raptors internal reference counter
//    ASSERT_EQ(1, triples[0].getStatement()->usage);
//    ASSERT_EQ(2, triples[1].getStatement()->usage);
//    ASSERT_EQ(2, triple.getStatement()->usage);
//
//    // free the triple and reduce count to 1
//    triple.freeStatement();
//    ASSERT_EQ(1, triples[1].getStatement()->usage);
//
//    // finally free the triples. All is accounted for.
//    triples.freeTriples();
//
//}

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

    // make sure we have the right triple left
    ASSERT_STREQ("subject1", triples[0].getSubjectStr().c_str());
    ASSERT_STREQ("subject2", triple.getSubjectStr().c_str());

    // free the triple and reduce count to 1
    triple.freeStatement();

    // free the triples. All is accounted for.
    triples.freeTriples();

}

TEST(TriplesTestsNoFixture, TestPreallocate) {
    Triples triples(2);
    ASSERT_EQ(2, triples.capacity());

    triples.emplace_back(LibrdfNode::fromUriString("subject1").get(),
                         SemSim("hasSinkParticipant").getNode(),
                         LibrdfNode::fromLiteral("literal node1").get());
    triples.emplace_back(LibrdfNode::fromUriString("subject2").get(),
                         SemSim("hasSourceParticipant").getNode(),
                         LibrdfNode::fromLiteral("literal node2").get());
    // make sure we have 2 triples
    ASSERT_EQ(2, triples.size());

    // free the triples. All is accounted for.
    triples.freeTriples();

}

TEST(TriplesTestsNoFixture, TestPopFrontUrisDifferent) {
    // create a triples object containing 2 triple objects
    Triples triples(2);
    triples.emplace_back(LibrdfNode::fromUriString("subject1").get(),
                         SemSim("hasSinkParticipant").getNode(),
                         LibrdfNode::fromUriString("UriNode1").get());
    triples.emplace_back(LibrdfNode::fromUriString("subject2").get(),
                         SemSim("hasSourceParticipant").getNode(),
                         LibrdfNode::fromUriString("UriNode2").get());
    std::cout << triples.str("ntriples", "base") << std::endl;
    // make sure we have 2 triples
    ASSERT_EQ(2, triples.size());

    // get by move
    Triple triple = triples.pop_front();
    std::cout << triple.str("ntriples", "base") << std::endl;

    // make sure we still have 1 Triple objects in Triples
    ASSERT_EQ(1, triples.size());

    // do checks for raptors internal reference counter
    ASSERT_EQ(1, triples[0].getStatement()->usage);
    ASSERT_EQ(1, triple.getStatement()->usage);


    // make sure we have the right triple left
    ASSERT_STREQ("subject2", triples[0].getSubjectStr().c_str());
    ASSERT_STREQ("subject1", triple.getSubjectStr().c_str());

    // now check the URI ref counts
    ASSERT_EQ(1, librdf_uri_get_usage(triple.getSubject()->value.uri));
    ASSERT_EQ(1, librdf_uri_get_usage(triple.getPredicate()->value.uri));
    ASSERT_EQ(1, librdf_uri_get_usage(triple.getResource()->value.uri));

    // free the triple
    triple.freeStatement();

    // free the triples. All is accounted for.
    triples.freeTriples();

}

TEST(TriplesTestsNoFixture, TestPopFrontSubjectUriTheSame) {
    // create a triples object containing 2 triple objects
    Triples triples(2);
    triples.emplace_back(LibrdfNode::fromUriString("subject").get(),
                         SemSim("hasSinkParticipant").getNode(),
                         LibrdfNode::fromUriString("UriNode1").get());
    triples.emplace_back(LibrdfNode::fromUriString("subject").get(),
                         SemSim("hasSourceParticipant").getNode(),
                         LibrdfNode::fromUriString("UriNode2").get());
    std::cout << triples.str("ntriples", "base") << std::endl;
    // make sure we have 2 triples
    ASSERT_EQ(2, triples.size());

    // get by move
    Triple triple = triples.pop_front();
    std::cout << triple.str("ntriples", "base") << std::endl;

    // make sure we still have 1 Triple objects in Triples
    ASSERT_EQ(1, triples.size());

    // do checks for raptors internal reference counter
    ASSERT_EQ(1, triples[0].getStatement()->usage);
    ASSERT_EQ(1, triple.getStatement()->usage);


    // make sure we have the right triple left
    ASSERT_STREQ("UriNode2", triples[0].getResourceStr().c_str());
    ASSERT_STREQ("UriNode1", triple.getResourceStr().c_str());

    // now check the URI ref counts
    ASSERT_EQ(2, librdf_uri_get_usage(triple.getSubject()->value.uri));
    ASSERT_EQ(1, librdf_uri_get_usage(triple.getPredicate()->value.uri));
    ASSERT_EQ(1, librdf_uri_get_usage(triple.getResource()->value.uri));

    // free the triples.
    triples.freeTriples();

    ASSERT_EQ(1, librdf_uri_get_usage(triple.getSubject()->value.uri));
    // free the triple
    triple.freeStatement();
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

TEST(TriplesTestsNoFixture, TestTwoIdenticalTripesObjectsCanBeFreed) {
    Triples triples1;
    triples1.emplace_back(
            LibrdfNode::fromUriString("http://subject1.com/subject1").get(),
            LibrdfNode::fromUriString("http://predicate1.com/predicate1").get(),
            LibrdfNode::fromUriString("http://resource1.com/resource1").get()
    );
    Triples triples2;
    triples2.emplace_back(
            LibrdfNode::fromUriString("http://subject1.com/subject1").get(),
            LibrdfNode::fromUriString("http://predicate1.com/predicate1").get(),
            LibrdfNode::fromUriString("http://resource1.com/resource1").get()
    );
    ASSERT_EQ(triples1, triples2);
    triples1.freeTriples();
    triples2.freeTriples();

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
    for (int i = 0; i < triples.size(); i++) {
        os << triples[i].getSubjectStr() << std::endl;
    }
    std::string expected = "http://subject1.com/subject1\n"
                           "http://subject2.com/subject2\n";
    ASSERT_STREQ(expected.c_str(), os.str().c_str());
    triples.freeTriples();
}


TEST(TriplesTestsNoFixture, TestEquality) {
    Triples triples1;
    triples1.emplace_back(
            LibrdfNode::fromUriString("http://subject1.com/subject1").get(),
            LibrdfNode::fromUriString("http://predicate1.com/predicate1").get(),
            LibrdfNode::fromUriString("http://resource1.com/resource1").get()
    );
    triples1.emplace_back(
            LibrdfNode::fromUriString("http://subject2.com/subject2").get(),
            LibrdfNode::fromUriString("http://predicate2.com/predicate2").get(),
            LibrdfNode::fromUriString("http://resource2.com/resource2").get()
    );
    Triples triples2;
    triples2.emplace_back(
            LibrdfNode::fromUriString("http://subject1.com/subject1").get(),
            LibrdfNode::fromUriString("http://predicate1.com/predicate1").get(),
            LibrdfNode::fromUriString("http://resource1.com/resource1").get()
    );
    triples2.emplace_back(
            LibrdfNode::fromUriString("http://subject2.com/subject2").get(),
            LibrdfNode::fromUriString("http://predicate2.com/predicate2").get(),
            LibrdfNode::fromUriString("http://resource2.com/resource2").get()
    );
    ASSERT_EQ(triples1, triples2);
    triples1.freeTriples();
    triples2.freeTriples();
}


TEST(TriplesTestsNoFixture, TestUsages1) {
    Triples triples1(1);
    triples1.emplace_back(
            LibrdfNode::fromUriString("http://subject1.com/subject1").get(),
            LibrdfNode::fromUriString("http://predicate1.com/predicate1").get(),
            LibrdfNode::fromUriString("http://resource1.com/resource1").get()
    );

    Triple triple = triples1.pop_front();
    auto m = triple.getUsages();
    ASSERT_EQ(1, m["statement"]);
    ASSERT_EQ(1, m["subject"]);
    ASSERT_EQ(1, m["predicate"]);
    ASSERT_EQ(1, m["resource"]);
    ASSERT_EQ(1, m["subject_uri"]);
    ASSERT_EQ(1, m["predicate_uri"]);
    ASSERT_EQ(1, m["resource_uri"]);
    triple.freeTriple();
}

TEST(TriplesTestsNoFixture, TestUsagesPhysicalForce) {
    // replicate physical force without actually using physical force
    Triples triples1(6);
    triples1.emplace_back(
            LibrdfNode::fromUriString("./MyModel.sbml#parameter_metaid_0").get(),
            LibrdfNode::fromUriString("isPropertyOf").get(),
            LibrdfNode::fromUriString("./MyModel.sbml#force_0").get()
    );

    triples1.emplace_back(
            LibrdfNode::fromUriString("./MyModel.sbml#parameter_metaid_0").get(),
            LibrdfNode::fromUriString("isVersionOf").get(),
            LibrdfNode::fromUriString("https://identifiers.org/opb/OPB_01058").get()
    );

    triples1.emplace_back(
            LibrdfNode::fromUriString("./MyModel.sbml#force_0").get(),
            LibrdfNode::fromUriString("hasSourceParticipant").get(),
            LibrdfNode::fromUriString("./MyModel.sbml#source_0").get()
    );


    triples1.emplace_back(
            LibrdfNode::fromUriString("./MyModel.sbml#force_0").get(),
            LibrdfNode::fromUriString("hasSinkParticipant").get(),
            LibrdfNode::fromUriString("./MyModel.sbml#sink_0").get()
    );

    triples1.emplace_back(
            LibrdfNode::fromUriString("./MyModel.sbml#source_0").get(),
            LibrdfNode::fromUriString("hasPhysicalEntityReference").get(),
            LibrdfNode::fromUriString("./MyModel.sbml#species_metaid_0").get()
    );

    triples1.emplace_back(
            LibrdfNode::fromUriString("./MyModel.sbml#sink_0").get(),
            LibrdfNode::fromUriString("hasPhysicalEntityReference").get(),
            LibrdfNode::fromUriString("./MyModel.sbml#species_metaid_1").get()
    );

    Triple triple1 = triples1.pop_front();
    auto m1 = triple1.getUsages();
    ASSERT_EQ(2, m1["subject_uri"]);
    ASSERT_EQ(1, m1["predicate_uri"]);
    ASSERT_EQ(3, m1["resource_uri"]);

    Triple triple2 = triples1.pop_front();
    auto m2 = triple2.getUsages();
    ASSERT_EQ(2, m2["subject_uri"]);
    ASSERT_EQ(1, m2["predicate_uri"]);
    ASSERT_EQ(1, m2["resource_uri"]);

    Triple triple3 = triples1.pop_front();
    auto m3 = triple3.getUsages();
    ASSERT_EQ(3, m3["subject_uri"]);
    ASSERT_EQ(1, m3["predicate_uri"]);
    ASSERT_EQ(2, m3["resource_uri"]);

    Triple triple4 = triples1.pop_front();
    auto m4 = triple4.getUsages();
    ASSERT_EQ(3, m4["subject_uri"]);
    ASSERT_EQ(1, m4["predicate_uri"]);
    ASSERT_EQ(2, m4["resource_uri"]);

    Triple triple5 = triples1.pop_front();
    auto m5 = triple5.getUsages();
    ASSERT_EQ(2, m5["subject_uri"]);
    ASSERT_EQ(2, m5["predicate_uri"]);
    ASSERT_EQ(1, m5["resource_uri"]);

    Triple triple6 = triples1.pop_front();
    auto m6 = triple6.getUsages();
    ASSERT_EQ(2, m6["subject_uri"]);
    ASSERT_EQ(2, m6["predicate_uri"]);
    ASSERT_EQ(1, m6["resource_uri"]);

    triple1.freeTriple();
    triple2.freeTriple();
    triple3.freeTriple();
    triple4.freeTriple();
    triple5.freeTriple();
    triple6.freeTriple();
}


/*
 * Collection of tests to try and debug the
 * reason why I can't free two triples objects
 * that are the same and generated from
 * a PhysicalEntity.
 */
class TestTriplesTwice : public :: testing::Test {
    TestTriplesTwice()= default;;
};

TEST(TestTriplesTwice, TestMakeSameTriplesTwice) {
    Triples triples1(3);
    triples1.emplace_back(
            LibrdfNode::fromUriString("http://subject1.com/subject1").get(),
            LibrdfNode::fromUriString("http://predicate1.com/predicate1").get(),
            LibrdfNode::fromUriString("http://resource1.com/resource1").get()
    );
    triples1.emplace_back(
            LibrdfNode::fromUriString("http://subject2.com/subject2").get(),
            LibrdfNode::fromUriString("http://predicate2.com/predicate2").get(),
            LibrdfNode::fromUriString("http://resource2.com/resource2").get()
    );
    triples1.emplace_back(
            LibrdfNode::fromUriString("http://subject2.com/subject2").get(),
            LibrdfNode::fromUriString("http://predicate2.com/predicate2").get(),
            LibrdfNode::fromUriString("http://resource2.com/resource2").get()
    );
    std::cout << "creating triples 2 " << std::endl;
    Triples triples2(3);
    triples2.emplace_back(
            LibrdfNode::fromUriString("http://subject1.com/subject1").get(),
            LibrdfNode::fromUriString("http://predicate1.com/predicate1").get(),
            LibrdfNode::fromUriString("http://resource1.com/resource1").get()
    );
    triples2.emplace_back(
            LibrdfNode::fromUriString("http://subject2.com/subject2").get(),
            LibrdfNode::fromUriString("http://predicate2.com/predicate2").get(),
            LibrdfNode::fromUriString("http://resource2.com/resource2").get()
    );
    triples2.emplace_back(
            LibrdfNode::fromUriString("http://subject2.com/subject2").get(),
            LibrdfNode::fromUriString("http://predicate2.com/predicate2").get(),
            LibrdfNode::fromUriString("http://resource2.com/resource2").get()
    );

    triples1.freeTriples();
    triples2.freeTriples();

}






