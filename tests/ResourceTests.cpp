//
// Created by Ciaran on 4/4/2020.
//

#include <semsim/Resource.h>
#include <semsim/uri.h>
#include "gtest/gtest.h"


class ResourceTests : public ::testing::Test {
public:

    std::string uri_str1;
    semsim::Uri uri;

    void SetUp() override {
        uri_str1 = "http://www.example.com/";
        uri = semsim::Uri(uri_str1);
    }
};

TEST_F(ResourceTests, TestGetMetaId) {
    semsim::Resource resource("x", uri);
    std::string expected = resource.getMetaId();
    ASSERT_STREQ(expected.c_str(), "x");
}

TEST_F(ResourceTests, TestStringUri) {
    std::string url_str = "www.notarealaddress.com";
    semsim::Resource resource("x", url_str);
    std::string expected = resource.getUri().str();
    ASSERT_STREQ(url_str.c_str(), expected.c_str());
}

TEST_F(ResourceTests, TestGetUri) {
    semsim::Resource resource("x", uri);
    semsim::Uri expected = resource.getUri();
    ASSERT_STREQ(expected.str().c_str(), uri_str1.c_str());
}

TEST_F(ResourceTests, TestEqualityOperator) {
    semsim::Resource resource1("x", uri);
    semsim::Resource resource2("x", uri);
    ASSERT_EQ(resource1, resource2);
}

TEST_F(ResourceTests, TestInequalityOperator) {
    semsim::Resource resource1("x", uri);
    semsim::Resource resource2("y", uri);
    ASSERT_NE(resource1, resource2);
}

TEST_F(ResourceTests, TestStreamOperator) {
    semsim::Resource resource1("x", uri);
    std::ostringstream os;
    os << resource1;
    std::string expected = "Resource(metaId=x, uri=http://www.example.com/)";
    ASSERT_STREQ(expected.c_str(), os.str().c_str());
}














