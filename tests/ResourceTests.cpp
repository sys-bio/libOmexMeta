//
// Created by Ciaran on 4/4/2020.
//

#include <semsim/Resource.h>
#include "gtest/gtest.h"
#include "librdf.h"

class ResourceTests : public ::testing::Test {
public:


    librdf_world *world;
    librdf_model *model;
    librdf_storage *storage;

    ResourceTests() {
        world = librdf_new_world();
        storage = librdf_new_storage(world, "memory", "test", nullptr);
        model = librdf_new_model(world, storage, nullptr);

    }

    ~ResourceTests() override {
        librdf_free_world(world);
        librdf_free_model(model);
        librdf_free_storage(storage);
    }

};

// todo make the Resource/Predicate/subject pass the world onto node so we dont have to give it twice!

TEST_F(ResourceTests, TestResourceUri1) {
    semsim::RDFURINode node(world, "https://en.wikipedia.org/wiki/Adolf_Hitler");
    semsim::Resource resource(world, node);
    std::string expected = "https://en.wikipedia.org/wiki/Adolf_Hitler";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(ResourceTests, TestResourceUriFromIdentifiersOrg) {
    semsim::RDFURINode node = semsim::RDFURINode(world, "fma/FMA:1234");
    semsim::Resource resource(world, node);
    librdf_node *n = resource.toRdfNode();
    std::string expected = "https://identifiers.org/fma/FMA:1234";
    std::string actual = (const char *) librdf_uri_as_string(librdf_node_get_uri(n));
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ResourceTests, TestResourceUriFromIdentifiersOrgStr) {
    semsim::RDFURINode node = semsim::RDFURINode(world, "fma/FMA:1234");
    semsim::Resource resource(world, node);
    std::string expected = "https://identifiers.org/fma/FMA:1234";
    std::string actual = node.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ResourceTests, TestResourceUriIdentifiersOrgColonNotationFromStr) {
    semsim::Resource resource(world, semsim::RDFURINode(world, "fma:FMA:1234"));
    std::string expected = "https://identifiers.org/fma/FMA:1234";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ResourceTests, TestResourceUriIdentifiersOrgColonNotationFromNode) {
    semsim::Resource resource(world, semsim::RDFURINode(world, "fma:FMA:1234"));
    std::string expected = "https://identifiers.org/fma/FMA:1234";
    std::string actual = (const char *) librdf_uri_as_string(librdf_node_get_uri(resource.toRdfNode()));
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ResourceTests, TestResourceUriFromFileOnDiskStr) {
    semsim::Resource resource(world, semsim::RDFURINode(world, "/file/on/disk"));
    std::string expected = "/file/on/disk";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ResourceTests, TestResourceUriFromFileOnDiskNode) {
    semsim::Resource resource(world, semsim::RDFURINode(world, "/file/on/disk"));
    std::string expected = "/file/on/disk";
    std::string actual = (const char*)librdf_uri_as_string(librdf_node_get_uri(resource.toRdfNode()));
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ResourceTests, TestResourceUriFromRelativeFileOnDiskStr) {
    semsim::Resource resource(world, semsim::RDFURINode(world, "./relative/file/on/disk"));
    std::string expected = "./relative/file/on/disk";
    std::string actual = resource.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ResourceTests, TestResourceUriFromRelativeFileOnDiskNode) {
    semsim::Resource resource(world, semsim::RDFURINode(world, "./relative/file/on/disk"));
    std::string expected = "./relative/file/on/disk";
    std::string actual = (const char*)librdf_uri_as_string(librdf_node_get_uri(resource.toRdfNode()));
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}



TEST_F(ResourceTests, TestResourceLiteral) {
    semsim::Resource resource(world, semsim::RDFLiteralNode(world, "biscuits"));
    std::string expected = "biscuits";
    std::string actual = (const char*)librdf_node_get_literal_value(resource.toRdfNode());
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(ResourceTests, TestResourceBlank) {
    semsim::Resource resource(world, semsim::RDFBlankNode(world, "biscuits"));
    std::string expected = "biscuits";
    std::string actual = (const char*)librdf_node_get_blank_identifier(resource.toRdfNode());
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}













