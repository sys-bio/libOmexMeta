//
// Created by Ciaran on 4/4/2020.
//

#include <semsim/Resource.h>
#include "gtest/gtest.h"
#include "librdf.h"

#include "semsim/RedlandAPIWrapper/RedlandAPIWrapper.h"

class ResourceTests : public ::testing::Test {
public:

    semsim::LibrdfWorld world;

    ResourceTests() {

    }

    ~ResourceTests() override {
    }

};

// todo make the Resource/Predicate/subject pass the world onto node so we dont have to give it twice!

TEST_F(ResourceTests, TestResourceUri1) {
    semsim::RDFURINode node(world.newNodeUriString(
            "https://en.wikipedia.org/wiki/Adolf_Hitler")
    );
    semsim::Resource resource(world, node);
    std::string expected = "https://en.wikipedia.org/wiki/Adolf_Hitler";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(ResourceTests, TestResourceUriFromIdentifiersOrg) {
    semsim::RDFURINode node = semsim::RDFURINode(world.newNodeUriString("fma/FMA:1234"));
    semsim::Resource resource(world, node);
    semsim::LibrdfNode n = resource.getNode();
    std::string expected = "https://identifiers.org/fma/FMA:1234";
    std::string actual = n.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ResourceTests, TestResourceUriFromIdentifiersOrgStr) {
    semsim::RDFURINode node(world.newNodeUriString("fma/FMA:1234"));
    semsim::Resource resource(world, node);
    std::string expected = "https://identifiers.org/fma/FMA:1234";
    std::string actual = node.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ResourceTests, TestResourceUriIdentifiersOrgColonNotationFromStr) {
    semsim::Resource resource(world, world.newNodeUriString("fma:FMA:1234"));
    std::string expected = "https://identifiers.org/fma/FMA:1234";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ResourceTests, TestResourceUriIdentifiersOrgColonNotationFromNode) {
    semsim::Resource resource(world, world.newNodeUriString("fma:FMA:1234"));
    std::string expected = "https://identifiers.org/fma/FMA:1234";
    std::string actual = (const char *) librdf_uri_as_string(librdf_node_get_uri(*resource.getNode().getNode()));
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ResourceTests, TestResourceUriIdentifiersOrgColonNotationFromNod2e) {
    semsim::Resource resource(world, world.newNodeUriString("fma:FMA:1234"));
    std::string expected = "https://identifiers.org/fma/FMA:1234";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ResourceTests, TestResourceUriFromFileOnDiskStr) {
    semsim::Resource resource(world, world.newNodeUriString("/file/on/disk"));
    std::string expected = "/file/on/disk";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ResourceTests, TestResourceUriFromFileOnDiskNode) {
    semsim::Resource resource(world, world.newNodeUriString("/file/on/disk"));
    std::string expected = "/file/on/disk";
    std::string actual = (const char *) librdf_uri_as_string(librdf_node_get_uri(*resource.getNode().getNode()));
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ResourceTests, TestResourceUriFromRelativeFileOnDiskStr) {
    semsim::Resource resource(world, world.newNodeUriString("./relative/file/on/disk"));
    std::string expected = "./relative/file/on/disk";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ResourceTests, TestResourceUriFromRelativeFileOnDiskNode) {
    semsim::Resource resource(world, world.newNodeUriString("./relative/file/on/disk"));
    std::string expected = "./relative/file/on/disk";
    std::string actual = (const char *) librdf_uri_as_string(librdf_node_get_uri(*resource.getNode().getNode()));
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(ResourceTests, TestResourceLiteral) {
    semsim::Resource resource(world, world.newNodeLiteral("biscuits"));
    std::string expected = "biscuits";
    std::string actual = (const char *) librdf_node_get_literal_value(*resource.getNode().getNode());
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ResourceTests, TestResourceBlank) {
    semsim::Resource resource(world, world.newNodeBlank("biscuits"));
    std::string expected = "biscuits";
    std::string actual = (const char *) librdf_node_get_blank_identifier(*resource.getNode().getNode());
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(ResourceTests, TestFromUriNode) {
    std::string url_str = "https://www.notarealaddress.com";
    semsim::LibrdfNode node = world.newNodeUriString(url_str.c_str());
    semsim::Resource resource(world, node);
    semsim::LibrdfNode n = resource.getNode();
    ASSERT_STREQ(url_str.c_str(), n.str().c_str());
}


TEST_F(ResourceTests, TestIsSetWhenTrue) {
    std::string url_str = "https://www.notarealaddress.com";
    semsim::LibrdfNode node = world.newNodeUriString(url_str);
    semsim::Resource resource(world, node);
    semsim::LibrdfNode n = resource.getNode();
    std::string actual = n.str();
    ASSERT_TRUE(resource.isSet());
}

TEST_F(ResourceTests, TestIsSetWhenFalse) {
    semsim::Resource resource;
    ASSERT_FALSE(resource.isSet());
}










