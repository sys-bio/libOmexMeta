//
// Created by Ciaran on 5/17/2020.
//
#include"gtest/gtest.h"
#include "World.h"
#include "LibrdfNode.h"

using namespace redland;

class LibrdfNodeTests : public ::testing::Test {

public:

    LibrdfNodeTests() = default;

};


TEST_F(LibrdfNodeTests, TestCreate) {
    std::string expected = "https://notarealaddress.com";
    LibrdfNode node = LibrdfNode::fromUriString(expected);
    std::string actual = node.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfNodeTests, TestUnderlyingNodeHasUri) {
    std::string expected = "https://notarealaddress.com";
    LibrdfNode node = LibrdfNode::fromUriString(expected);
    LibrdfUri uri = node.getUri();
    std::string s = uri.str();
    ASSERT_STREQ("https://notarealaddress.com", s.c_str());
}


TEST_F(LibrdfNodeTests, TestCopyConstructor) {
    std::string expected1 = "https://notarealaddress1.com";
    LibrdfNode node1 = LibrdfNode::fromUriString(expected1);
    LibrdfNode node2 = node1;
    std::string actual = node2.str();
    ASSERT_STREQ(expected1.c_str(), actual.c_str());
}


TEST_F(LibrdfNodeTests, TestMoveConstructor) {
    std::string expected1 = "https://notarealaddress1.com";
    LibrdfNode node = LibrdfNode::fromUriString(expected1);
    LibrdfNode node2 = std::move(node);
    std::string actual = node2.str();
    ASSERT_STREQ(expected1.c_str(), actual.c_str());
}

TEST_F(LibrdfNodeTests, TestAssignmentOperator) {
    std::string expected1 = "https://notarealaddress1.com";
    std::string expected2 = "https://notarealaddress2.com";
    LibrdfNode node1 = LibrdfNode::fromUriString(expected1);
    LibrdfNode node2 = LibrdfNode::fromUriString(expected2);
    node2 = node1;
    std::string actual = node2.str();
    ASSERT_STREQ(expected1.c_str(), actual.c_str());
}

//
TEST_F(LibrdfNodeTests, TestMoveAssignmentOperator) {
    std::string expected1 = "https://notarealaddress1.com";
    std::string expected2 = "https://notarealaddress2.com";
    LibrdfNode node1 = LibrdfNode::fromUriString(expected1);
    LibrdfNode node2 = LibrdfNode::fromUriString(expected2);
    node1 = std::move(node2);
    std::string actual = node1.str();
    ASSERT_STREQ(expected2.c_str(), actual.c_str());
}

TEST_F(LibrdfNodeTests, TestLiteral1) {
    // http://www.w3.org/2001/XMLSchema#string
    LibrdfNode node = LibrdfNode::fromLiteral("Literal Node");
    unsigned char *actual = librdf_node_get_literal_value(node.get());
    ASSERT_STREQ("Literal Node", (const char *) actual);
}

TEST_F(LibrdfNodeTests, TestLiteral2) {
    // http://www.w3.org/2001/XMLSchema#string
    LibrdfNode node = LibrdfNode::fromLiteral("Literal Node");
    std::string actual = node.str();
    ASSERT_STREQ("Literal Node", actual.c_str());
}

TEST_F(LibrdfNodeTests, TestTypedLiteral1) {
    LibrdfNode node = LibrdfNode::fromLiteral("TypedLiteral");
    unsigned char *actual = librdf_node_get_literal_value(node.get());
    ASSERT_STREQ("TypedLiteral", (const char *) actual);
}

TEST_F(LibrdfNodeTests, TestTypedLiteral2) {
    LibrdfNode node = LibrdfNode::fromLiteral("TypedLiteral");
    std::string actual = node.getLiteralDatatype().str();
    ASSERT_STREQ("http://www.w3.org/1999/02/22-rdf-syntax-ns#string", actual.c_str());
}

TEST_F(LibrdfNodeTests, TestTypedLiteral3) {
    LibrdfNode node = LibrdfNode::fromLiteral("TypedLiteral");
    std::string actual = node.getLiteralLanguage();
    ASSERT_STREQ("", actual.c_str());
}

TEST_F(LibrdfNodeTests, TestBlank) {
    // http://www.w3.org/2001/XMLSchema#string
    LibrdfNode node = LibrdfNode::fromBlank("Blanky");
    unsigned char *actual = librdf_node_get_blank_identifier(node.get());
    ASSERT_STREQ("Blanky", (const char *) actual);
}

TEST_F(LibrdfNodeTests, TestNodeUri) {
    std::string expected = "https://notarealaddress.com";
    LibrdfNode node = LibrdfNode::fromUriString(expected);
    librdf_uri *uri_actual = librdf_node_get_uri(node.get());
    unsigned char *actual = librdf_uri_to_string(uri_actual);
    ASSERT_STREQ(expected.c_str(), (const char *) actual);
    free(actual);
}


TEST_F(LibrdfNodeTests, TestNodeUriStringTwice) {
    std::string expected1 = "https://notarealaddress.com1";
    std::string expected2 = "https://notarealaddress.com2";
    LibrdfNode uri1 = LibrdfNode::fromUriString(expected1);
    LibrdfNode uri2 = LibrdfNode::fromUriString(expected2);
    std::string actual1 = uri1.str();
    std::string actual2 = uri2.str();
    ASSERT_STREQ(expected1.c_str(), actual1.c_str());
    ASSERT_STREQ(expected2.c_str(), actual2.c_str());
}


TEST_F(LibrdfNodeTests, TestUseNodsToMakeAStatement) {
    LibrdfNode subject = LibrdfNode::fromUriString("subject");
    LibrdfNode predicate = LibrdfNode::fromUriString("predicate");
    LibrdfNode resource = LibrdfNode::fromUriString("resource");

    librdf_statement *stmt = librdf_new_statement_from_nodes(
            World::getWorld(), subject.get(), predicate.get(), resource.get());

    librdf_node *n = librdf_statement_get_subject(stmt);
    librdf_uri *uri = librdf_node_get_uri(n);
    char *actual = (char *) librdf_uri_to_string(uri);
    const char *expected = "subject";
    ASSERT_STREQ(expected, actual);
    free(actual);
    free(stmt);
}


TEST_F(LibrdfNodeTests, TestgetUri) {
    LibrdfNode subject = LibrdfNode::fromUriString("subject");
    LibrdfUri u = subject.getUri();
    std::string actual = u.str();
    std::string expected = "subject";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfNodeTests, TestSetUri) {
    LibrdfNode subject = LibrdfNode::fromUriString("subject");
    subject.setUri("predicate");
    std::string actual = subject.getUri().str();
    std::string expected = "predicate";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfNodeTests, TestgetLiteralDatatype) {
    LibrdfNode subject = LibrdfNode::fromLiteral("subject");
    LibrdfUri u = subject.getLiteralDatatype();
    std::string actual = u.str();
    std::string expected = "http://www.w3.org/1999/02/22-rdf-syntax-ns#string";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfNodeTests, TestValidateLiteralDatatype) {
    std::string actual = LibrdfNode::validateLiteralDatatype("int");
    std::string expected = "http://www.w3.org/1999/02/22-rdf-syntax-ns#int";
    ASSERT_STREQ(actual.c_str(), expected.c_str());
}

TEST_F(LibrdfNodeTests, TestValidateLiteralDatatype2) {
    std::string actual = LibrdfNode::validateLiteralDatatype("http://www.w3.org/1999/02/22-rdf-syntax-ns#int");
    std::string expected = "http://www.w3.org/1999/02/22-rdf-syntax-ns#int";
    ASSERT_STREQ(actual.c_str(), expected.c_str());
}

TEST_F(LibrdfNodeTests, TestsetLiteralDatatype) {
    LibrdfNode subject = LibrdfNode::fromLiteral("subject");
    subject.setLiteralDatatype("int");
    LibrdfUri u = subject.getLiteralDatatype();
    std::string actual = u.str();
    std::string expected = "http://www.w3.org/1999/02/22-rdf-syntax-ns#int";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfNodeTests, TestsetLiteralDatatypeDoesntChangeValue) {
    LibrdfNode subject = LibrdfNode::fromLiteral("subject");
    subject.setLiteralDatatype("int");
    std::string actual = subject.str();
    std::string expected = "subject";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfNodeTests, TestSetBlank) {
    LibrdfNode subject = LibrdfNode::fromBlank("subject");
    subject.setBlankIdentifier("blank subject");
    std::string actual = subject.getBlankIdentifier();
    std::string expected = "blank subject";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfNodeTests, TestSetBlankValueNotChanged) {
    LibrdfNode subject = LibrdfNode::fromBlank("subject");
    subject.setBlankIdentifier("blank subject");
    std::string actual = subject.str();
    std::string expected = "subject";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}



//
//TEST_F(LibrdfNodeTests, TestSetUri) {
//    LibrdfNode subject = LibrdfNode::fromUriString("subject");
//    subject.setUri("predicate");
//    std::string actual = subject.getUri().str();
//    std::string expected = "predicate";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}

















