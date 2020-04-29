//
// Created by Ciaran on 4/4/2020.
//

#include <semsim/Subject.h>
#include "gtest/gtest.h"


class SubjectTests : public ::testing::Test {
public:
    librdf_world *world;
    librdf_model *model;
    librdf_storage *storage;

    SubjectTests() {
        world = librdf_new_world();
        storage = librdf_new_storage(world, "memory", "test", nullptr);
        model = librdf_new_model(world, storage, nullptr);

    }

    ~SubjectTests() override {
    }

};

TEST_F(SubjectTests, TestDefaultConstructor) {
    semsim::Subject subject;
    ASSERT_TRUE(true); // if you get this far the test passes
}

TEST_F(SubjectTests, TestGetMetaId) {
    semsim::Subject subject(world, semsim::RDFURINode(world, "meta754"));
    std::string expected = subject.str();
    ASSERT_STREQ(expected.c_str(), "meta754");
}

TEST_F(SubjectTests, TestStringUri) {
    std::string url_str = "https://www.notarealaddress.com";
    semsim::Subject subject(world, semsim::RDFURINode(world, url_str));
    const std::string &expected = subject.str();
    ASSERT_STREQ(url_str.c_str(), expected.c_str());
}

TEST_F(SubjectTests, TestToNode) {
    std::string url_str = "https://www.notarealaddress.com";
    semsim::RDFURINode node(semsim::RDFURINode(world, url_str));
    semsim::Subject subject(world, node);
    librdf_node *n = subject.toRdfNode();
    const char *actual = (const char *) librdf_uri_as_string(librdf_node_get_uri(n));
    ASSERT_STREQ(url_str.c_str(), actual);
}


TEST_F(SubjectTests, TestFromUriNode) {
    std::string url_str = "https://www.notarealaddress.com";
    librdf_node* node = librdf_new_node_from_uri_string(world, (const unsigned char*)url_str.c_str());
    semsim::Subject subject(world, node);
    librdf_node *n = subject.toRdfNode();
    const char *actual = (const char *) librdf_uri_as_string(librdf_node_get_uri(n));
    ASSERT_STREQ(url_str.c_str(), actual);
}


















