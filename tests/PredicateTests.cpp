//
// Created by Ciaran on 4/4/2020.
//
#include <memory>
#include <semsim/Predicate.h>
#include "semsim/Predicate.h"
#include "gtest/gtest.h"


class PredicateTests : public ::testing::Test {
public:

    std::string uri_str1;
    semsim::Uri uri;

    void SetUp() override {
        uri_str1 = "http://biomodels.net/biology-qualifiers/is";
        uri = semsim::Uri(uri_str1);
    }
};

TEST_F(PredicateTests, TestDefaultConstructor) {
    semsim::Predicate predicate;
    ASSERT_TRUE(true); // if you get this far, the test passes
}

TEST_F(PredicateTests, TestGetUriFromBiomodelsQualifier) {
    semsim::BiomodelsQualifier is("is");
    semsim::Predicate predicate(is.make_shared());
    const semsim::Uri &expected = predicate.getUri();
    ASSERT_STREQ(expected.str().c_str(), uri_str1.c_str());
}

TEST_F(PredicateTests, TestEqualityOperator) {
    semsim::BiomodelsQualifier is("is");
    semsim::Predicate predicate1(is.make_shared());
    semsim::Predicate predicate2(is.make_shared());
    ASSERT_EQ(predicate1, predicate2);
}

TEST_F(PredicateTests, TestInequalityOperator) {
    semsim::BiomodelsQualifier is("is");
    semsim::BiomodelsQualifier hasPart("hasPart");
    semsim::Predicate predicate1(is.make_shared());
    semsim::Predicate predicate2(hasPart.make_shared());
    ASSERT_NE(predicate1, predicate2);
}
TEST_F(PredicateTests, TestStream) {
    semsim::BiomodelsQualifier is("is");
    semsim::Predicate predicate(is.make_shared());
    std::string expected = "Predicate(http://biomodels.net/biology-qualifiers/is)";
    std::ostringstream os;
    os << predicate;
    ASSERT_STREQ(expected.c_str(), os.str().c_str());
}














