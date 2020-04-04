//
// Created by Ciaran on 4/4/2020.
//

#include <semsim/Predicate.h>
#include "gtest/gtest.h"


class TripleTests : public ::testing::Test {
public:

    std::string subject_str;
    std::string predicate_str;
    std::string object_str;

    semsim::Uri subject_uri;
    semsim::Uri predicate_uri;
    semsim::Uri object_uri;

    void SetUp() override {
        subject_str = "./MyModel#metaid_0";
        predicate_str = "http://biomodels.net/biology-qualifiers/is";
        object_str = "https://identifiers.org/uniprot:P0DP23";
    }
};

TEST_F(TripleTests, te){

}































