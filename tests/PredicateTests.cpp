//
// Created by Ciaran on 4/5/2020.
//

#include "gtest/gtest.h"
#include "semsim/Predicate.h"


class PredicateTests : public ::testing::Test {
public:
    std::string bqb_ns;

    PredicateTests() : bqb_ns("http://biomodels.net/biology-qualifiers/") {}
};

TEST_F(PredicateTests, TestUri) {
    semsim::BiomodelsQualifier bqb_is("is");
    std::string expected = bqb_ns + "is";
    ASSERT_STREQ(expected.c_str(), bqb_is.getUri().str().c_str());
}


TEST_F(PredicateTests, TestFailure) {
    ASSERT_THROW(semsim::BiomodelsQualifier bqb_is("isa"), std::invalid_argument);
}











