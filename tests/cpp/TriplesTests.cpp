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

//    librdf_world *world;
//    raptor_world *raptorWorld;
    LibrdfStorage storage;
    LibrdfModel model;

    Subject subject;
    Resource resource;
    BiomodelsBiologyQualifier predicate;


    //todo subject could pass the world to the node
    TriplesTests() {
        model = LibrdfModel(std::move(storage));
        this->subject = Subject::fromRawPtr(LibrdfNode::fromUriString("subby"));
        this->resource = Resource::fromRawPtr(LibrdfNode::fromUriString(("space/id")));
        this->predicate = BiomodelsBiologyQualifier("is");
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



