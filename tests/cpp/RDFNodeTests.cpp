//
// Created by Ciaran on 4/17/2020.
//
#include "librdf.h"
#include "raptor2.h"
#include "gtest/gtest.h"

#include "semsim/RDFNode.h"
#include "semsim/SemsimUtils.h"
#include "World.h"

using namespace semsim;

class RDFNodeTests : public ::testing::Test {
public:

    RDFNodeTests() {
    }

    ~RDFNodeTests() override {
    }
};


TEST_F(RDFNodeTests, TestLiteral1) {
    std::string expected = "LiterallyAValue";
    LibrdfNode node = LibrdfNode::fromLiteral(expected);
    RDFLiteralNode literal(node);
    unsigned char *uri = librdf_node_get_literal_value(*node.get());
    const char *actual = (const char *) uri;
    ASSERT_STREQ(expected.c_str(), actual);
}

TEST_F(RDFNodeTests, TestLiteralStr) {
    std::string expected = "LiterallyAValue";
    LibrdfNode node = LibrdfNode::fromLiteral(expected);
    RDFLiteralNode literal(node);
    std::string actual = literal.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(RDFNodeTests, TestTypedLiteral) {
    LibrdfNode typedLiteral = LibrdfNode::fromLiteral("Literal");
    std::string actual = typedLiteral.getRaptorTermType();
    const char *expected = "http://www.w3.org/2001/XMLSchema#string";
    ASSERT_STREQ(expected, actual.c_str());
}

TEST_F(RDFNodeTests, TestTypedLiteral2) {
    RDFTypedLiteralNode typedLiteralNode(LibrdfNode::fromLiteral("Literal"));
    std::string actual = typedLiteralNode.getType();
    const char *expected = "http://www.w3.org/2001/XMLSchema#string";
    ASSERT_STREQ(expected, actual.c_str());
}

TEST_F(RDFNodeTests, TestURI) {
    std::string expected = "https://webpaging.com";
    LibrdfNode node = world_.newNodeUriString(expected);
    RDFURINode rdfuriNode(node);
    raptor_uri *uri = librdf_node_get_uri(*rdfuriNode.get().get());
    unsigned char *s = raptor_uri_to_string(uri);
    std::string actual = (const char *) s;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    free(s);
}

TEST_F(RDFNodeTests, TestURI2) {
    std::string expected = "https://webpaging.com";
    LibrdfNode node = world_.newNodeUriString(expected);
    RDFURINode rdfuriNode(node);
    std::string actual = rdfuriNode.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(RDFNodeTests, TestURIIdentifiersString1) {
    LibrdfNode node = world_.newNodeUriString("ident/Number");
    RDFURINode rdfuriNode(node);
    std::string actual = rdfuriNode.str();
    ASSERT_STREQ("https://identifiers.org/ident/Number", actual.c_str());
}

TEST_F(RDFNodeTests, TestURIIdentifiersString2) {
    LibrdfNode node = world_.newNodeUriString("ident:Number");
    RDFURINode rdfuriNode(node);
    std::string actual = rdfuriNode.str();
    ASSERT_STREQ("https://identifiers.org/ident/Number", actual.c_str());
}

TEST_F(RDFNodeTests, TestURIFromFile) {
    std::string file = "file:///mnt/d/libsemsim/tests/rdfxml.rdf";
    LibrdfNode node = world_.newNodeUriString(file);
    RDFURINode rdfuriNode(node);
    std::string actual = rdfuriNode.str();
    ASSERT_STREQ("file:///mnt/d/libsemsim/tests/rdfxml.rdf", actual.c_str());
}

TEST_F(RDFNodeTests, TestURIFromFile2) {
    std::string f = "/mnt/d/libsemsim/tests/rdfxml.rdf";
    LibrdfNode node = world_.newNodeUriString(f);
    RDFURINode rdfuriNode(node);
    std::string actual = rdfuriNode.str();
    ASSERT_STREQ(f.c_str(), actual.c_str());
}

TEST_F(RDFNodeTests, TestURIFromFile3) {
    std::string f = "file://D:/libsemsim/tests/rdfxml.rdf";
    LibrdfNode node = world_.newNodeUriString(f);
    RDFURINode rdfuriNode(node);
    std::string actual = rdfuriNode.str();
    ASSERT_STREQ(f.c_str(), actual.c_str());
}

TEST_F(RDFNodeTests, TestURIFromFile4) {
    std::string f = R"(file://D:\libsemsim\tests\rdfxml.rdf)";
    LibrdfNode node = world_.newNodeUriString(f);
    RDFURINode rdfuriNode(node);
    std::string actual = rdfuriNode.str();
    ASSERT_STREQ(f.c_str(), actual.c_str());
}

TEST_F(RDFNodeTests, TestURIFromFile5) {
    std::string f = "file://./tests/rdfxml.rdf";
    LibrdfNode node = world_.newNodeUriString(f);
    RDFURINode rdfuriNode(node);
    std::string actual = rdfuriNode.str();
    ASSERT_STREQ(f.c_str(), actual.c_str());
}

TEST_F(RDFNodeTests, TestURIFromFile6) {
    std::string f = "file://.\\tests\\rdfxml.rdf";
    LibrdfNode node = world_.newNodeUriString(f);
    RDFURINode rdfuriNode(node);
    std::string actual = rdfuriNode.str();
    ASSERT_STREQ(f.c_str(), actual.c_str());
}

TEST_F(RDFNodeTests, TestURIFromFile7) {
    std::string f = ".\\tests\\rdfxml.rdf";
    LibrdfNode node = world_.newNodeUriString(f);
    RDFURINode rdfuriNode(node);
    std::string actual = rdfuriNode.str();
    ASSERT_STREQ(f.c_str(), actual.c_str());
}


TEST_F(RDFNodeTests, TestURIFromFile8) {
    std::string f = "./tests/rdfxml.rdf";
    LibrdfNode node = world_.newNodeUriString(f);
    RDFURINode rdfuriNode(node);
    std::string actual = rdfuriNode.str();
    ASSERT_STREQ(f.c_str(), actual.c_str());
}

//TEST_F(RDFNodeTests, TestToNode) {
//    std::string url_str = "https://www.notarealaddress.com";
//    RDFURINode node(world, url_str);
//    LibrdfNode  n = node.get();
//    librdf_uri* uri = librdf_node_get_uri(n);
//    unsigned char* s = raptor_uri_to_string(uri);
//    const char *actual = (const char *)s;
//    ASSERT_STREQ(url_str.c_str(), actual);
//    free(s);
//}

TEST_F(RDFNodeTests, TestBlank) {
    std::string f = "Blank";
    LibrdfNode node = world_.newNodeBlank(f);
    RDFBlankNode blankNode(node);
    std::string actual = blankNode.str();
    ASSERT_STREQ(f.c_str(), actual.c_str());

}


//TEST_F(RDFNodeTests, TestUriNodeFromLibrdfNode) {
//    librdf_node*  node = librdf_new_node_from_uri_string(world, (const unsigned char *) "file://./MyModel.xml");
//    RDFURINode rdfuriNode(world_, node);
//    std::string expected = "file://./MyModel.xml";
//    std::string actual = (const char *) librdf_uri_to_string(librdf_node_get_uri(rdfuriNode.get()));
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}

//TEST_F(RDFNodeTests, TestBlankNodeFromLibrdfNode) {
//    LibrdfNode  node = librdf_new_node_from_blank_identifier(world, (const unsigned char *) "file://./MyModel.xml");
//    RDFBlankNode blankNode(world, node);
//    std::string expected = "file://./MyModel.xml";
//    std::string actual = (const char *) librdf_node_get_blank_identifier(blankNode.get());
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}
//
//TEST_F(RDFNodeTests, TestLiteralNodeFromLibrdfNode) {
//    LibrdfNode  node = librdf_new_node_from_literal(world, (const unsigned char *) "file://./MyModel.xml", nullptr,
//                                                     false);
//    RDFLiteralNode literalNode(world, node);
//    std::string expected = "file://./MyModel.xml";
//    std::string actual = (const char *) librdf_node_get_blank_identifier(literalNode.get());
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}





















