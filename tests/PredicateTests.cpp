//
// Created by Ciaran on 4/4/2020.
//

#include <semsim/Predicate.h>
#include "gtest/gtest.h"


class PredicateTests : public ::testing::Test {
public:

    std::string uri_str1;
    semsim::Uri uri;

    void SetUp() override {
        uri_str1 = "http://www.example.com/";
        uri = semsim::Uri(uri_str1);
    }
};

TEST_F(PredicateTests, TestGetUri) {
    semsim::Predicate predicate(uri);
    const semsim::Uri& expected = predicate.getUri();
    ASSERT_STREQ(expected.str().c_str(), uri_str1.c_str());
}

TEST_F(PredicateTests, TestInstantiateFromString) {
    std::string expected = "www.notarealaddress.com";
    semsim::Predicate predicate(expected);
    ASSERT_STREQ(expected.c_str(), predicate.getUri().str().c_str());
}

TEST_F(PredicateTests, TestEqualityOperator) {
    semsim::Predicate predicate1(uri);
    semsim::Predicate predicate2(uri);
    ASSERT_EQ(predicate1, predicate2);
}

TEST_F(PredicateTests, TestInequalityOperator) {
    semsim::Predicate predicate1(uri);
    semsim::Predicate predicate2("www.notarealaddress.com");
    ASSERT_NE(predicate1, predicate2);
}

TEST_F(PredicateTests, TestStreamOperator) {
    semsim::Predicate predicate1(uri);
    std::ostringstream os;
    os << predicate1;
    std::string expected = "Predicate(uri=http://www.example.com/)";
    ASSERT_STREQ(expected.c_str(), os.str().c_str());
}














