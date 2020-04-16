//
// Created by Ciaran on 4/5/2020.
//

#include "gtest/gtest.h"
#include "semsim/Predicate.h"


class ControlledVocabularyTests : public ::testing::Test {
public:
    std::string bqb_root;

    ControlledVocabularyTests() : bqb_root("http://biomodels.net/biology-qualifiers/") {}
};

TEST_F(ControlledVocabularyTests, TestUri) {
    semsim::BiomodelsQualifier bqb_is("is");
    std::string expected = bqb_root + "is";
    ASSERT_STREQ(expected.c_str(), bqb_is.getUri().str().c_str());
}


TEST_F(ControlledVocabularyTests, TestFailure) {
    ASSERT_THROW(semsim::BiomodelsQualifier bqb_is("isa"), std::invalid_argument);
}











