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

TEST_F(URLTests, test2){
    semsim::URI uri(uri_str);
}
