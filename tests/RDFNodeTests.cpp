//
// Created by Ciaran on 4/17/2020.
//
#include "librdf.h"
#include "raptor2.h"
#include <semsim/RDFNode.h>
#include "gtest/gtest.h"

class RDFNodeTests : public ::testing::Test {
public:
    librdf_world* world;
    librdf_model* model;
    librdf_storage* storage;
    RDFNodeTests() {
        world = librdf_new_world();
        storage = librdf_new_storage(world, "memory", "test", nullptr);
        model = librdf_new_model(world, storage, nullptr);

    }

    ~RDFNodeTests() override{
        librdf_free_world(world);
        librdf_free_model(model);
        librdf_free_storage(storage);
    }
};


TEST_F(RDFNodeTests, TestLiteral1){
    semsim::RDFLiteralNode literal(world, "Cheesy Watsit");
    unsigned char* actual = librdf_node_get_literal_value(literal.toRdfNode());
    ASSERT_STREQ("Cheesy Watsit", (const char*)actual);
}
TEST_F(RDFNodeTests, TestLiteral2){
    semsim::RDFLiteralNode literal(world, "Cheesy Watsit");
    raptor_uri* uri = librdf_node_get_literal_value_datatype_uri(literal.toRdfNode());
    const char* actual = (const char*) raptor_uri_to_string(uri);
    const char* expected = "http://www.w3.org/2001/XMLSchema#string";
    ASSERT_STREQ(expected, actual);
}

TEST_F(RDFNodeTests, TestURI){
    semsim::RDFURINode rdfuriNode(world, "https://en.wikipedia.org/wiki/Adolf_Hitler");
    unsigned char* actual = raptor_uri_to_string(
            librdf_node_get_uri(rdfuriNode.toRdfNode()));
    ASSERT_STREQ("https://en.wikipedia.org/wiki/Adolf_Hitler", (const char*)actual);
}

TEST_F(RDFNodeTests, TestBlank){
    semsim::RDFBlankNode rdfBlankNode(world, "placeholder");
    unsigned char* actual = librdf_node_get_blank_identifier(rdfBlankNode.toRdfNode());
    ASSERT_STREQ("placeholder", (const char*)actual);
}





















