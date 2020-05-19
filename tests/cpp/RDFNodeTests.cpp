//
// Created by Ciaran on 4/17/2020.
//
#include "librdf.h"
#include "raptor2.h"
#include "gtest/gtest.h"

#include "semsim/RDFNode.h"
#include "semsim/RelandAPIWrappers/LibrdfWorld.h"

//class RDFNodeTests : public ::testing::Test {
//public:
//    semsim::LibrdfWorld world_;
////    librdf_world *world;
////    librdf_model *model;
////    librdf_storage *storage;
//
//    RDFNodeTests() {
////        world = librdf_new_world();
////        storage = librdf_new_storage(world, "memory", "test", nullptr);
////        model = librdf_new_model(world, storage, nullptr);
//
//    }
//
//    ~RDFNodeTests() override {
////        librdf_free_model(model);
////        librdf_free_storage(storage);
////        librdf_free_world(world);
//    }
//};
//
//TEST_F(RDFNodeTests, TestLiteral1) {
//    // http://www.w3.org/2001/XMLSchema#string
//    semsim::LibrdfNode literal = world_.newNodeLiteral("Literal Node");
//    unsigned char *actual = librdf_node_get_literal_value(*literal.getNode());
//    ASSERT_STREQ("Literal Node", (const char *) actual);
//    free(actual);
//}
//
//
////TEST_F(RDFNodeTests, TestTypedLiteral1) {
////    // http://www.w3.org/2001/XMLSchema#string
////    semsim::LibrdfNode literal = world_.newNodeTypedLiteral(
////            "TypedLiteral", <#initializer#>, nullptr);
////    semsim::RDFLiteralNode literal(world_, "Cheesy Watsit");
////    unsigned char *actual = librdf_node_get_literal_value(literal.toRdfNode());
////    ASSERT_STREQ("Cheesy Watsit", (const char *) actual);
////    free(actual);
////}
//
//TEST_F(RDFNodeTests, TestLiteral2) {
//    semsim::RDFLiteralNode literal(world_, "Cheesy Watsit");
//    librdf_node* node = literal.toRdfNode();
//    raptor_uri *uri = librdf_node_get_literal_value_datatype_uri(node);
//    librdf_free_node(node);
//    unsigned char* s = raptor_uri_to_string(uri);
//    const char *actual = (const char *) s;
//    const char *expected = "http://www.w3.org/2001/XMLSchema#string";
//    ASSERT_STREQ(expected, actual);
//    raptor_free_uri(uri);
//}
//
//TEST_F(RDFNodeTests, TestURI) {
//    semsim::RDFURINode rdfuriNode(world, "https://en.wikipedia.org/wiki/Adolf_Hitler");
//    unsigned char *actual = raptor_uri_to_string(
//            librdf_node_get_uri(rdfuriNode.toRdfNode()));
//    ASSERT_STREQ("https://en.wikipedia.org/wiki/Adolf_Hitler", (const char *) actual);
//    free(actual);
//}
//
//TEST_F(RDFNodeTests, TestURI2) {
//    semsim::RDFURINode rdfuriNode(world, "https://www.notarealaddress.com");
//    unsigned char *actual = raptor_uri_to_string(
//            librdf_node_get_uri(rdfuriNode.toRdfNode()));
//    ASSERT_STREQ("https://www.notarealaddress.com", (const char *) actual);
//    free(actual);
//}
//
//TEST_F(RDFNodeTests, TestURIIdentifiersString1) {
//    semsim::RDFURINode rdfuriNode(world, "ident/Number");
//    unsigned char *actual = raptor_uri_to_string(
//            librdf_node_get_uri(rdfuriNode.toRdfNode()));
//    ASSERT_STREQ("https://identifiers.org/ident/Number", (const char *) actual);
//    free(actual);
//}
//
//TEST_F(RDFNodeTests, TestURIIdentifiersString2) {
//    semsim::RDFURINode rdfuriNode(world, "ident:Number");
//    unsigned char *actual = raptor_uri_to_string(
//            librdf_node_get_uri(rdfuriNode.toRdfNode()));
//    ASSERT_STREQ("https://identifiers.org/ident/Number", (const char *) actual);
//    free(actual);
//}
//
//TEST_F(RDFNodeTests, TestURIFromFile) {
//    semsim::RDFURINode rdfuriNode(world, "file:///mnt/d/libsemsim/tests/rdfxml.rdf");
//    unsigned char *actual = raptor_uri_to_string(
//            librdf_node_get_uri(rdfuriNode.toRdfNode()));
//    ASSERT_STREQ("file:///mnt/d/libsemsim/tests/rdfxml.rdf", (const char *) actual);
//    free(actual);
//}
//
//TEST_F(RDFNodeTests, TestURIFromFile2) {
//    semsim::RDFURINode rdfuriNode(world, "/mnt/d/libsemsim/tests/rdfxml.rdf");
//    unsigned char *actual = raptor_uri_to_string(
//            librdf_node_get_uri(rdfuriNode.toRdfNode()));
//    ASSERT_STREQ("/mnt/d/libsemsim/tests/rdfxml.rdf", (const char *) actual);
//    free(actual);
//}
//
//TEST_F(RDFNodeTests, TestURIFromFile3) {
//    semsim::RDFURINode rdfuriNode(world, "file://D:/libsemsim/tests/rdfxml.rdf");
//    unsigned char *actual = raptor_uri_to_string(
//            librdf_node_get_uri(rdfuriNode.toRdfNode()));
//    ASSERT_STREQ("file://D:/libsemsim/tests/rdfxml.rdf", (const char *) actual);
//    free(actual);
//}
//
//TEST_F(RDFNodeTests, TestURIFromFile4) {
//    semsim::RDFURINode rdfuriNode(world, R"(file://D:\libsemsim\tests\rdfxml.rdf)");
//    unsigned char *actual = raptor_uri_to_string(
//            librdf_node_get_uri(rdfuriNode.toRdfNode()));
//    ASSERT_STREQ(R"(file://D:\libsemsim\tests\rdfxml.rdf)", (const char *) actual);
//    free(actual);
//}
//
//TEST_F(RDFNodeTests, TestURIFromFile5) {
//    semsim::RDFURINode rdfuriNode(world, "file://./tests/rdfxml.rdf");
//    unsigned char *actual = raptor_uri_to_string(
//            librdf_node_get_uri(rdfuriNode.toRdfNode()));
//    ASSERT_STREQ("file://./tests/rdfxml.rdf", (const char *) actual);
//    free(actual);
//}
//
//TEST_F(RDFNodeTests, TestURIFromFile6) {
//    semsim::RDFURINode rdfuriNode(world, "file://.\\tests\\rdfxml.rdf");
//    unsigned char *actual = raptor_uri_to_string(
//            librdf_node_get_uri(rdfuriNode.toRdfNode()));
//    ASSERT_STREQ("file://.\\tests\\rdfxml.rdf", (const char *) actual);
//    free(actual);
//}
//
//TEST_F(RDFNodeTests, TestURIFromFile7) {
//    semsim::RDFURINode rdfuriNode(world, ".\\tests\\rdfxml.rdf");
//    unsigned char *actual = raptor_uri_to_string(
//            librdf_node_get_uri(rdfuriNode.toRdfNode()));
//    ASSERT_STREQ(".\\tests\\rdfxml.rdf", (const char *) actual);
//    free(actual);
//}
//
//
//TEST_F(RDFNodeTests, TestURIFromFile8) {
//    semsim::RDFURINode rdfuriNode(world, "./tests/rdfxml.rdf");
//    unsigned char *actual = raptor_uri_to_string(
//            librdf_node_get_uri(rdfuriNode.toRdfNode()));
//    ASSERT_STREQ("./tests/rdfxml.rdf", (const char *) actual);
//    free(actual);
//}
//
//TEST_F(RDFNodeTests, TestToNode) {
//    std::string url_str = "https://www.notarealaddress.com";
//    semsim::RDFURINode node(world, url_str);
//    librdf_node *n = node.toRdfNode();
//    librdf_uri* uri = librdf_node_get_uri(n);
//    unsigned char* s = raptor_uri_to_string(uri);
//    const char *actual = (const char *)s;
//    ASSERT_STREQ(url_str.c_str(), actual);
//    free(s);
//}
//
//TEST_F(RDFNodeTests, TestBlank) {
//    semsim::RDFBlankNode rdfBlankNode(world, "placeholder");
//    unsigned char *actual = librdf_node_get_blank_identifier(rdfBlankNode.toRdfNode());
//    ASSERT_STREQ("placeholder", (const char *) actual);
//    free(actual);
//
//}
//
//
//TEST_F(RDFNodeTests, TestUriNodeFromLibrdfNode) {
//    librdf_node *node = librdf_new_node_from_uri_string(world, (const unsigned char *) "file://./MyModel.xml");
//    semsim::RDFURINode rdfuriNode(world, node);
//    std::string expected = "file://./MyModel.xml";
//    std::string actual = (const char *) librdf_uri_to_string(librdf_node_get_uri(rdfuriNode.toRdfNode()));
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
//TEST_F(RDFNodeTests, TestBlankNodeFromLibrdfNode) {
//    librdf_node *node = librdf_new_node_from_blank_identifier(world, (const unsigned char *) "file://./MyModel.xml");
//    semsim::RDFBlankNode blankNode(world, node);
//    std::string expected = "file://./MyModel.xml";
//    std::string actual = (const char *) librdf_node_get_blank_identifier(blankNode.toRdfNode());
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
//TEST_F(RDFNodeTests, TestLiteralNodeFromLibrdfNode) {
//    librdf_node *node = librdf_new_node_from_literal(world, (const unsigned char *) "file://./MyModel.xml", nullptr,
//                                                     false);
//    semsim::RDFLiteralNode literalNode(world, node);
//    std::string expected = "file://./MyModel.xml";
//    std::string actual = (const char *) librdf_node_get_blank_identifier(literalNode.toRdfNode());
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}





















