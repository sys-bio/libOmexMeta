//
// Created by Ciaran on 4/4/2020.
//

#include <semsim/Resource.h>
#include "gtest/gtest.h"
#include "librdf.h"

#include "redland/RedlandAPIWrapper/RedlandAPIWrapper.h"

using namespace semsim;

class ResourceTests : public ::testing::Test {
public:

    ResourceTests() {

    }

    ~ResourceTests() override = default;

};

// todo make the Resource/Predicate/subject pass the world onto node so we dont have to give it twice!

TEST_F(ResourceTests, TestResourceUri1) {
    LibrdfNode node(LibrdfNode::fromUriString(
            "https://en.wikipedia.org/wiki/Adolf_Hitler")
    );
    Resource resource(std::move(node));
    std::string expected = "https://en.wikipedia.org/wiki/Adolf_Hitler";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(ResourceTests, TestResourceUriFromIdentifiersOrg) {
    LibrdfNode node = LibrdfNode(LibrdfNode::fromUriString("fma/FMA:1234"));
    Resource resource(std::move(node));
    std::string expected = "https://identifiers.org/fma/FMA:1234";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(ResourceTests, TestResourceUriIdentifiersOrgColonNotationFromStr) {
    Resource resource(LibrdfNode::fromUriString("fma:FMA:1234"));
    std::string expected = "https://identifiers.org/fma/FMA:1234";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ResourceTests, TestResourceUriIdentifiersOrgColonNotationFromNode) {
    Resource resource(LibrdfNode::fromUriString("fma:FMA:1234"));
    std::string expected = "https://identifiers.org/fma/FMA:1234";
    std::string actual = (const char *) librdf_uri_as_string(librdf_node_get_uri(resource.getNode().get()));
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ResourceTests, TestResourceUriIdentifiersOrgColonNotationFromNod2e) {
    Resource resource(LibrdfNode::fromUriString("fma:FMA:1234"));
    std::string expected = "https://identifiers.org/fma/FMA:1234";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ResourceTests, TestResourceUriFromFileOnDiskStr) {
    Resource resource(LibrdfNode::fromUriString("/file/on/disk"));
    std::string expected = "/file/on/disk";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ResourceTests, TestResourceUriFromFileOnDiskNode) {
    Resource resource(LibrdfNode::fromUriString("/file/on/disk"));
    std::string expected = "/file/on/disk";
    std::string actual = (const char *) librdf_uri_as_string(librdf_node_get_uri(resource.getNode().get()));
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ResourceTests, TestResourceUriFromRelativeFileOnDiskStr) {
    Resource resource(LibrdfNode::fromUriString("./relative/file/on/disk"));
    std::string expected = "./relative/file/on/disk";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ResourceTests, TestResourceUriFromRelativeFileOnDiskNode) {
    Resource resource(LibrdfNode::fromUriString("./relative/file/on/disk"));
    std::string expected = "./relative/file/on/disk";
    std::string actual = (const char *) librdf_uri_as_string(librdf_node_get_uri(resource.getNode().get()));
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(ResourceTests, TestResourceLiteral) {
    Resource resource(LibrdfNode::fromLiteral("biscuits"));
    std::string expected = "biscuits";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ResourceTests, TestResourceBlank) {
    Resource resource(LibrdfNode::fromBlank("biscuits"));
    std::string expected = "biscuits";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(ResourceTests, TestFromUriNode) {
    std::string url_str = "https://www.notarealaddress.com";
    LibrdfNode node = LibrdfNode::fromUriString(url_str);
    Resource resource(std::move(node));
    ASSERT_STREQ(url_str.c_str(), resource.str().c_str());
}


TEST_F(ResourceTests, TestIsSetWhenTrue) {
    std::string url_str = "https://www.notarealaddress.com";
    LibrdfNode node = LibrdfNode::fromUriString(url_str);
    Resource resource(std::move(node));
    std::string actual = resource.str();
    ASSERT_TRUE(resource.isSet());
}

TEST_F(ResourceTests, TestIsSetWhenFalse) {
    Resource resource;
    ASSERT_FALSE(resource.isSet());
}










