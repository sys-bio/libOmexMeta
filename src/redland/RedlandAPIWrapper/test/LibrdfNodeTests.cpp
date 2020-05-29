//
// Created by Ciaran on 5/17/2020.
//
#include"gtest/gtest.h"
#include "World.h"
#include "LibrdfNode.h"

using namespace semsim;

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
    librdf_uri *u = librdf_node_get_uri(node.get());
    LibrdfUri uri(u);
    std::string s = uri.str();
    ASSERT_STREQ("https://notarealaddress.com", s.c_str());
}


//TEST_F(LibrdfNodeTests, TestCopyConstructor) {
//    std::string expected1 = "https://notarealaddress1.com";
//    LibrdfNode node1 = LibrdfNode::fromUriString(expected1);
//    LibrdfNode node2 = node1;
//    std::string actual = node2.str();
//    ASSERT_STREQ(expected1.c_str(), actual.c_str());
//}


TEST_F(LibrdfNodeTests, TestMoveConstructor) {
    std::string expected1 = "https://notarealaddress1.com";
    LibrdfNode node = LibrdfNode::fromUriString(expected1);
    LibrdfNode node2 = std::move(node);
    std::string actual = node2.str();
    ASSERT_STREQ(expected1.c_str(), actual.c_str());
}

//TEST_F(LibrdfNodeTests, TestAssignmentOperator) {
//    std::string expected1 = "https://notarealaddress1.com";
//    std::string expected2 = "https://notarealaddress2.com";
//    LibrdfNode node1 = world_.newNodeUriString(expected1);
//    LibrdfNode node2 = world_.newNodeUriString(expected2);
//    node2 = node1;
//    std::string actual = node2.str();
//    ASSERT_STREQ(expected1.c_str(), actual.c_str());
//}

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
//
//TEST_F(LibrdfNodeTests, TestClone1) {
//    LibrdfNode subject = LibrdfNode::fromUriString("subject");
//    LibrdfNode subject_clone = subject.clone();
//    ASSERT_NE(&subject.get()->type, &subject_clone.get()->type);
//}
//
//TEST_F(LibrdfNodeTests, TestClone2) {
//    LibrdfNode subject = LibrdfNode::fromUriString("subject");
//    LibrdfNode subject_clone = subject.clone();
//    ASSERT_NE(subject.get()->value.uri, subject_clone.get()->value.uri);
//}

//TEST_F(LibrdfNodeTests, TestClone3) {
//    LibrdfNode subject = LibrdfNode::fromLiteral("Literal");
//    LibrdfNode subject_clone = subject.clone();
//    ASSERT_STREQ((const char*)subject.get()->value.literal.string,
//                 (const char*)subject_clone.get()->value.literal.string);
//    ASSERT_NE(subject.get()->value.literal.string,
//            subject_clone.get()->value.literal.string);
//    ASSERT_NE(&subject.get()->value.literal.string,
//            &subject_clone.get()->value.literal.string);
//}

















