//
// Created by Ciaran on 4/8/2020.
//


#include "gtest/gtest.h"
#include "semsim/RDF.h"
#include "semsim/SemSim.h"
#include "AnnotationSamples.h"

class RDFTests : public ::testing::Test {

public:

    AnnoationSamples samples;

    RDFTests() = default;


};


TEST_F(RDFTests, TestDefaultConstructor) {
    semsim::RDF rdf;
    ASSERT_TRUE(true); // If we get this far we've passed
}

TEST_F(RDFTests, TestDefaultConstructor2) {
    semsim::RDF rdf;
    rdf.fromString(samples.sample_annotation1);
    rdf.toString("rdfxml");
}


TEST_F(RDFTests, TestThatMakeSerializerFunctionBreaksWithWrongFormatArgument){

}











