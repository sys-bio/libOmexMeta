#include <iostream>

#include "SBMLFactory.h"
#include "gtest/gtest.h"

class URLTests : public ::testing::Test {
protected:
    std::string uri_str;
    URLTests()  {
        uri_str = "https://identifiers.org/CHEBI:17234";
    };
};

TEST_F(URLTests, TestGetString){
    semsim::URI uri(uri_str);
    ASSERT_STREQ(uri_str.c_str(), uri.toString().c_str());
}

TEST_F(URLTests, TestConcatonationWithPlusSymbol){
    semsim::URI uri(uri_str);
}

TEST_F(URLTests, TestConcatonationWithPlusSymbo2l){
    semsim::URI uri(uri_str);
}
