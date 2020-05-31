//
// Created by Ciaran on 5/31/2020.
//

#include "gtest/gtest.h"
#include "semsim/RDF2.h"
#include "AnnotationSamples.h"

using namespace semsim;

class RDFTests : public ::testing::Test {

public:

    AnnotationSamples samples;

    RDFTests() = default;

    void TearDown() override {
        samples.removeAllFilesIfTheyExist();
    }
};

TEST_F(RDFTests, TestCreateEmptyRDF) {
    RDF2 rdf;
    ASSERT_EQ(0, rdf.size());
    ASSERT_TRUE(rdf.empty());
}

TEST_F(RDFTests, TestFromStringSingularAnnotation) {
    RDF2 rdf = RDF2::fromString(samples.singular_annotation1);
    int expected = 1;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
}

TEST_F(RDFTests, TestFromStringTurtleBag) {
    RDF2 rdf = RDF2::fromString(samples.rdf_turtle_bag_example, "turtle");
    int expected = 7;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
}
