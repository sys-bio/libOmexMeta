//
// Created by Ciaran on 5/17/2020.
//
#include "gtest/gtest.h"
#include "semsim/RedlandAPIWrappers/LibrdfWorld.h"


class LibrdfNodeTests : public ::testing::Test {

public:
    semsim::LibrdfWorld world_;

    LibrdfNodeTests() = default;

};


TEST_F(LibrdfNodeTests, TestCopyCreate) {
    std::string expected = "https://notarealaddress.com";
    semsim::LibrdfNode node = world_.newNodeUriString(expected);
    std::string actual = node.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(LibrdfNodeTests, TestCopyConstructor) {
    std::string expected1 = "https://notarealaddress1.com";
    semsim::LibrdfNode node1 = world_.newNodeUriString(expected1);
    semsim::LibrdfNode node2 = node1;
    std::string actual = node2.str();
    ASSERT_STREQ(expected1.c_str(), actual.c_str());
}


TEST_F(LibrdfNodeTests, TestMoveConstructor) {
    std::string expected1 = "https://notarealaddress1.com";
    semsim::LibrdfNode node1 = world_.newNodeUriString(expected1);
    semsim::LibrdfNode node2 = std::move(node1);
    std::string actual = node2.str();
    ASSERT_STREQ(expected1.c_str(), actual.c_str());
}

TEST_F(LibrdfNodeTests, TestAssignmentOperator) {
    std::string expected1 = "https://notarealaddress1.com";
    std::string expected2 = "https://notarealaddress2.com";
    semsim::LibrdfNode node1 = world_.newNodeUriString(expected1);
    semsim::LibrdfNode node2 = world_.newNodeUriString(expected2);
    node2 = node1;
    std::string actual = node2.str();
    ASSERT_STREQ(expected1.c_str(), actual.c_str());
}

/*
 * todo put the use_count check in librdfWorld and Raptororld
 */

TEST_F(LibrdfNodeTests, TestMoveAssignmentOperator) {
    std::string expected1 = "https://notarealaddress1.com";
    std::string expected2 = "https://notarealaddress2.com";
    semsim::LibrdfNode node1 = world_.newNodeUriString(expected1);
    semsim::LibrdfNode node2 = world_.newNodeUriString(expected2);
    node1 = std::move(node2);
    std::string actual = node1.str();
    ASSERT_STREQ(expected2.c_str(), actual.c_str());
}

TEST_F(LibrdfNodeTests, TestLiteral1) {
    // http://www.w3.org/2001/XMLSchema#string
    semsim::LibrdfNode literal = world_.newNodeLiteral("Literal Node");
    unsigned char *actual = librdf_node_get_literal_value(*literal.getNode());
    ASSERT_STREQ("Literal Node", (const char *) actual);
}

TEST_F(LibrdfNodeTests, TestTypedLiteral1) {
    // http://www.w3.org/2001/XMLSchema#string
    semsim::LibrdfNode literal = world_.newNodeTypedLiteral("TypedLiteral");
    unsigned char *actual = librdf_node_get_literal_value(*literal.getNode());
    ASSERT_STREQ("TypedLiteral", (const char *) actual);
}

TEST_F(LibrdfNodeTests, TestBlank) {
    // http://www.w3.org/2001/XMLSchema#string
    semsim::LibrdfNode literal = world_.newNodeBlank("Blanky");
    unsigned char *actual = librdf_node_get_blank_identifier(*literal.getNode());
    ASSERT_STREQ("Blanky", (const char *) actual);
}

TEST_F(LibrdfNodeTests, TestNodeUri) {
    std::string expected = "https://notarealaddress.com";
    semsim::LibrdfUri uri = world_.newUri(expected);
    semsim::LibrdfNode literal = world_.newNodeUri(uri);
    librdf_uri *uri_actual = librdf_node_get_uri(*literal.getNode());
    unsigned char *actual = librdf_uri_to_string(uri_actual);
    ASSERT_STREQ(expected.c_str(), (const char *) actual);
    free(actual);
}

TEST_F(LibrdfNodeTests, TestNodeUri2) {
    std::string expected = "https://notarealaddress.com";
    semsim::LibrdfUri uri = world_.newUri(expected);
    semsim::LibrdfNode literal = world_.newNodeUri(uri);
    std::string actual = literal.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}




















