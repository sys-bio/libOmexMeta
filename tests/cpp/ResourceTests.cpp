//
// Created by Ciaran on 4/4/2020.
//

#include <semsim/Resource.h>
#include "gtest/gtest.h"
#include "librdf.h"

#include "RedlandAPIWrapper.h"

using namespace semsim;

class ResourceTests : public ::testing::Test {
public:

    ResourceTests() {}

    ~ResourceTests() override = default;

};

// todo make the Resource/Predicate/subject pass the world onto node so we dont have to give it twice!

TEST_F(ResourceTests, TestResourceUri1) {
    Resource resource = Resource::fromRawPtr(LibrdfNode::fromUriString(
            "https://en.wikipedia.org/wiki").get()
    );
    std::string expected = "https://en.wikipedia.org/wiki";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    resource.free();
}


TEST_F(ResourceTests, TestResourceUriFromIdentifiersOrg) {
    Resource resource = Resource::fromRawPtr(LibrdfNode::fromUriString("fma/FMA:1234").get());
    std::string expected = "https://identifiers.org/fma/FMA:1234";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    resource.free();
}


TEST_F(ResourceTests, TestResourceUriIdentifiersOrgColonNotationFromStr) {
    Resource resource = Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:1234").get());
    std::string expected = "https://identifiers.org/fma/FMA:1234";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    resource.free();
}

TEST_F(ResourceTests, TestResourceUriIdentifiersOrgColonNotationFromNode) {
    Resource resource = Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:1234").get());
    std::string expected = "https://identifiers.org/fma/FMA:1234";
    std::string actual = (const char *) librdf_uri_as_string(librdf_node_get_uri(resource.getNode()));
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    resource.free();
}

TEST_F(ResourceTests, TestResourceUriIdentifiersOrgColonNotationFromNod2e) {
    Resource resource = Resource::fromRawPtr(LibrdfNode::fromUriString("fma:FMA:1234").get());
    std::string expected = "https://identifiers.org/fma/FMA:1234";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    resource.free();
}

TEST_F(ResourceTests, TestResourceUriFromFileOnDiskStr) {
    Resource resource = Resource::fromRawPtr(LibrdfNode::fromUriString("/file/on/disk").get());
    std::string expected = "/file/on/disk";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    resource.free();
}

TEST_F(ResourceTests, TestResourceUriFromFileOnDiskNode) {
    Resource resource = Resource::fromRawPtr(LibrdfNode::fromUriString("/file/on/disk").get());
    std::string expected = "/file/on/disk";
    std::string actual = (const char *) librdf_uri_as_string(librdf_node_get_uri(resource.getNode()));
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    resource.free();
}

TEST_F(ResourceTests, TestResourceUriFromRelativeFileOnDiskStr) {
    Resource resource = Resource::fromRawPtr(LibrdfNode::fromUriString("./relative/file/on/disk").get());
    std::string expected = "./relative/file/on/disk";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    resource.free();
}

TEST_F(ResourceTests, TestResourceUriFromRelativeFileOnDiskNode) {
    Resource resource = Resource::fromRawPtr(LibrdfNode::fromUriString("./relative/file/on/disk").get());
    std::string expected = "./relative/file/on/disk";
    std::string actual = (const char *) librdf_uri_as_string(librdf_node_get_uri(resource.getNode()));
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    resource.free();
}


TEST_F(ResourceTests, TestResourceLiteral) {
    Resource resource = Resource::fromRawPtr(LibrdfNode::fromLiteral("biscuits").get());
    std::string expected = "biscuits";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    resource.free();
}

TEST_F(ResourceTests, TestResourceBlank) {
    Resource resource = Resource::fromRawPtr(LibrdfNode::fromBlank("biscuits").get());
    std::string expected = "biscuits";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    resource.free();
}


TEST_F(ResourceTests, TestFromUriNode) {
    std::string url_str = "https://www.notarealaddress.com";
    Resource resource = Resource::fromRawPtr(LibrdfNode::fromUriString(url_str).get());
    ASSERT_STREQ(url_str.c_str(), resource.str().c_str());
    resource.free();
}


TEST_F(ResourceTests, TestIsSetWhenTrue) {
    std::string url_str = "https://www.notarealaddress.com";
    Resource resource = Resource::fromRawPtr(LibrdfNode::fromUriString(url_str).get());
    std::string actual = resource.str();
    ASSERT_TRUE(resource.isSet());
    resource.free();
}

TEST_F(ResourceTests, TestIsSetWhenFalse) {
    Resource resource;
    ASSERT_FALSE(resource.isSet());
    resource.free();
}


TEST_F(ResourceTests, TestIsLiterralWithDatatype) {
    Resource resource = Resource::fromRawPtr(
            LibrdfNode::fromLiteral(
                    "1.0",
                    "http://www.w3.org/2001/XMLSchema#double"
            ).get()
    );
    ASSERT_TRUE(resource.isSet());
    resource.free();
}


TEST_F(ResourceTests, TestThatIcanPutAResourceInAVector) {
    Resource resource = Resource::fromRawPtr(
            LibrdfNode::fromLiteral(
                    "1.0",
                    "http://www.w3.org/2001/XMLSchema#double"
            ).get()
    );
    std::vector<Resource> res = {resource};
    std::string expected = "1.0";
    std::string actual = res[0].str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    resource.free();
}

TEST(ResourceTestsNoFixture, TestEquality) {
    Resource resource1 = Resource(
            LibrdfNode::fromLiteral(
                    "1.0",
                    "http://www.w3.org/2001/XMLSchema#double"
            )
    );
    Resource resource2 = Resource(
            LibrdfNode::fromLiteral(
                    "1.0",
                    "http://www.w3.org/2001/XMLSchema#double"
            )
    );
    ASSERT_EQ(resource1, resource2);
    resource1.free();
    resource2.free();
}

TEST(ResourceTestsNoFixture, TestInequality) {
    Resource resource1 = Resource(
            LibrdfNode::fromLiteral(
                    "2.0",
                    "http://www.w3.org/2001/XMLSchema#double"
            )
    );
    Resource resource2 = Resource(
            LibrdfNode::fromLiteral(
                    "1.0",
                    "http://www.w3.org/2001/XMLSchema#double"
            )
    );
    ASSERT_NE(resource1, resource2);
    resource2.free();
    resource1.free();
}










