//
// Created by Ciaran on 4/29/2020.
//
#include <librdf.h>
#include <gtest/gtest.h>
#include <semsim/RDF.h>
#include <semsim/Triples.h>
#include "SBMLFactory.h"
#include "AnnotationSamples.h"
#include "semsim/Query.h"
#include "semsim/Triples.h"

class TriplesTests : public ::testing::Test {

public:

    AnnotationSamples samples;

    librdf_world *world;
    raptor_world *raptorWorld;
    librdf_storage *storage;
    librdf_model *model;
    semsim::Subject subject;
    semsim::Resource resource;
    semsim::BiomodelsBiologyQualifier predicate;
    semsim::PredicatePtr predicatePtr;


    //todo subject could pass the world to the node
    TriplesTests() {
        this->world = librdf_new_world();
        this->subject = semsim::Subject(world, semsim::RDFURINode(world, "subby"));
        this->resource = semsim::Resource(world, semsim::RDFURINode(world, "space/id"));
        this->predicate = semsim::BiomodelsBiologyQualifier(world, "is");
        predicatePtr = std::make_shared<semsim::Predicate>(predicate);

    }
};


TEST_F(TriplesTests, TestSize) {
    semsim::Triple triple1(world,
                           subject,
                           predicatePtr,
                           resource);
    semsim::Triple triple2(world,
                           subject,
                           predicatePtr,
                           resource);
    semsim::Triples triples;
    triples.push_back(triple1);
    triples.push_back(triple2);
    ASSERT_EQ(2, triples.size());
}

TEST_F(TriplesTests, TestEmplaceBack1) {
    semsim::Triples triples;
    triples.emplace_back(world,
                         subject,
                         predicatePtr,
                         resource);
    ASSERT_EQ(1, triples.size());
}

TEST_F(TriplesTests, TestEmplaceBack2) {
    semsim::Triple triple(world,
                          subject,
                          predicatePtr,
                          resource);
    librdf_statement *statement = triple.toStatement();
    semsim::Triples triples;
    triples.emplace_back(world, statement);
    ASSERT_EQ(1, triples.size());
}

