//
// Created by Ciaran on 4/17/2020.
//
#include "librdf.h"
#include "raptor2.h"
#include "gtest/gtest.h"

#include "semsim/RDFNode.h"
#include "semsim/SemsimUtils.h"
#include "semsim/RedlandAPIWrappers/LibrdfWorld.h"

class RDFNodeTests : public ::testing::Test {
public:
    semsim::LibrdfWorld world_;

    RDFNodeTests() {
    }

    ~RDFNodeTests() override {
    }
};


TEST_F(RDFNodeTests, TestLiteral1) {
    std::string expected = "LiterallyAValue";
    semsim::LibrdfNode node = world_.newNodeLiteral(expected);
    semsim::RDFLiteralNode literal(node);
    unsigned char *uri = librdf_node_get_literal_value(*node.getNode());
    const char *actual = (const char *) uri;
    ASSERT_STREQ(expected.c_str(), actual);
}

TEST_F(RDFNodeTests, TestLiteralStr) {
    std::string expected = "LiterallyAValue";
    semsim::LibrdfNode node = world_.newNodeLiteral(expected);
    semsim::RDFLiteralNode literal(node);
    std::string actual = literal.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(RDFNodeTests, TestTypedLiteral) {
    semsim::LibrdfNode typedLiteral = world_.newNodeTypedLiteral("Literal");
    semsim::RDFTypedLiteralNode typedLiteralNode(typedLiteral);
    raptor_uri *uri = librdf_node_get_literal_value_datatype_uri(*typedLiteralNode.getNode().getNode());
    unsigned char *s = raptor_uri_to_string(uri);
    std::string actual = (const char *) s;
    const char *expected = "http://www.w3.org/2001/XMLSchema#string";
    ASSERT_STREQ(expected, actual.c_str());
    free(s);
}

TEST_F(RDFNodeTests, TestTypedLiteral2) {
    semsim::RDFTypedLiteralNode typedLiteralNode(world_.newNodeTypedLiteral("Literal"));
    std::string actual = typedLiteralNode.getType();
    const char *expected = "http://www.w3.org/2001/XMLSchema#string";
    ASSERT_STREQ(expected, actual.c_str());
}

TEST_F(RDFNodeTests, TestURI) {
    std::string expected = "https://webpaging.com";
    semsim::LibrdfNode node = world_.newNodeUriString(expected);
    semsim::RDFURINode rdfuriNode(node);
    raptor_uri *uri = librdf_node_get_uri(*rdfuriNode.getNode().getNode());
    unsigned char *s = raptor_uri_to_string(uri);
    std::string actual = (const char *) s;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    free(s);
}

TEST_F(RDFNodeTests, TestURI2) {
    std::string expected = "https://webpaging.com";
    semsim::LibrdfNode node = world_.newNodeUriString(expected);
    semsim::RDFURINode rdfuriNode(node);
    std::string actual = rdfuriNode.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(RDFNodeTests, TestURIIdentifiersString1) {
    semsim::LibrdfNode node = world_.newNodeUriString("ident/Number");
    semsim::RDFURINode rdfuriNode(node);
    std::string actual = rdfuriNode.str();
    ASSERT_STREQ("https://identifiers.org/ident/Number", actual.c_str());
}

TEST_F(RDFNodeTests, TestURIIdentifiersString2) {
    semsim::LibrdfNode node = world_.newNodeUriString("ident:Number");
    semsim::RDFURINode rdfuriNode(node);
    std::string actual = rdfuriNode.str();
    ASSERT_STREQ("https://identifiers.org/ident/Number", actual.c_str());
}

TEST_F(RDFNodeTests, TestURIFromFile) {
    std::string file = "file:///mnt/d/libsemsim/tests/rdfxml.rdf";
    semsim::LibrdfNode node = world_.newNodeUriString(file);
    semsim::RDFURINode rdfuriNode(node);
    std::string actual = rdfuriNode.str();
    ASSERT_STREQ("file:///mnt/d/libsemsim/tests/rdfxml.rdf", actual.c_str());
}

TEST_F(RDFNodeTests, TestURIFromFile2) {
    std::string f = "/mnt/d/libsemsim/tests/rdfxml.rdf";
    semsim::LibrdfNode node = world_.newNodeUriString(f);
    semsim::RDFURINode rdfuriNode(node);
    std::string actual = rdfuriNode.str();
    ASSERT_STREQ(f.c_str(), actual.c_str());
}

TEST_F(RDFNodeTests, TestURIFromFile3) {
    std::string f = "file://D:/libsemsim/tests/rdfxml.rdf";
    semsim::LibrdfNode node = world_.newNodeUriString(f);
    semsim::RDFURINode rdfuriNode(node);
    std::string actual = rdfuriNode.str();
    ASSERT_STREQ(f.c_str(), actual.c_str());
}

TEST_F(RDFNodeTests, TestURIFromFile4) {
    std::string f = R"(file://D:\libsemsim\tests\rdfxml.rdf)";
    semsim::LibrdfNode node = world_.newNodeUriString(f);
    semsim::RDFURINode rdfuriNode(node);
    std::string actual = rdfuriNode.str();
    ASSERT_STREQ(f.c_str(), actual.c_str());
}

TEST_F(RDFNodeTests, TestURIFromFile5) {
    std::string f = "file://./tests/rdfxml.rdf";
    semsim::LibrdfNode node = world_.newNodeUriString(f);
    semsim::RDFURINode rdfuriNode(node);
    std::string actual = rdfuriNode.str();
    ASSERT_STREQ(f.c_str(), actual.c_str());
}

TEST_F(RDFNodeTests, TestURIFromFile6) {
    std::string f = "file://.\\tests\\rdfxml.rdf";
    semsim::LibrdfNode node = world_.newNodeUriString(f);
    semsim::RDFURINode rdfuriNode(node);
    std::string actual = rdfuriNode.str();
    ASSERT_STREQ(f.c_str(), actual.c_str());
}

TEST_F(RDFNodeTests, TestURIFromFile7) {
    std::string f = ".\\tests\\rdfxml.rdf";
    semsim::LibrdfNode node = world_.newNodeUriString(f);
    semsim::RDFURINode rdfuriNode(node);
    std::string actual = rdfuriNode.str();
    ASSERT_STREQ(f.c_str(), actual.c_str());
}


TEST_F(RDFNodeTests, TestURIFromFile8) {
    std::string f = "./tests/rdfxml.rdf";
    semsim::LibrdfNode node = world_.newNodeUriString(f);
    semsim::RDFURINode rdfuriNode(node);
    std::string actual = rdfuriNode.str();
    ASSERT_STREQ(f.c_str(), actual.c_str());
}

//TEST_F(RDFNodeTests, TestToNode) {
//    std::string url_str = "https://www.notarealaddress.com";
//    semsim::RDFURINode node(world, url_str);
//    LibrdfNode  n = node.getNode();
//    librdf_uri* uri = librdf_node_get_uri(n);
//    unsigned char* s = raptor_uri_to_string(uri);
//    const char *actual = (const char *)s;
//    ASSERT_STREQ(url_str.c_str(), actual);
//    free(s);
//}

TEST_F(RDFNodeTests, TestBlank) {
    std::string f = "Blank";
    semsim::LibrdfNode node = world_.newNodeBlank(f);
    semsim::RDFBlankNode blankNode(node);
    std::string actual = blankNode.str();
    ASSERT_STREQ(f.c_str(), actual.c_str());

}


//TEST_F(RDFNodeTests, TestUriNodeFromLibrdfNode) {
//    librdf_node*  node = librdf_new_node_from_uri_string(world, (const unsigned char *) "file://./MyModel.xml");
//    semsim::RDFURINode rdfuriNode(world_, node);
//    std::string expected = "file://./MyModel.xml";
//    std::string actual = (const char *) librdf_uri_to_string(librdf_node_get_uri(rdfuriNode.getNode()));
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}

//TEST_F(RDFNodeTests, TestBlankNodeFromLibrdfNode) {
//    LibrdfNode  node = librdf_new_node_from_blank_identifier(world, (const unsigned char *) "file://./MyModel.xml");
//    semsim::RDFBlankNode blankNode(world, node);
//    std::string expected = "file://./MyModel.xml";
//    std::string actual = (const char *) librdf_node_get_blank_identifier(blankNode.getNode());
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
//TEST_F(RDFNodeTests, TestLiteralNodeFromLibrdfNode) {
//    LibrdfNode  node = librdf_new_node_from_literal(world, (const unsigned char *) "file://./MyModel.xml", nullptr,
//                                                     false);
//    semsim::RDFLiteralNode literalNode(world, node);
//    std::string expected = "file://./MyModel.xml";
//    std::string actual = (const char *) librdf_node_get_blank_identifier(literalNode.getNode());
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}





















