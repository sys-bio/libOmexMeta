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


TEST_F(LibrdfNodeTests, TestCreate) {
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
    unsigned char *actual = librdf_node_get_literal_value(literal.get());
    ASSERT_STREQ("Literal Node", (const char *) actual);
}

TEST_F(LibrdfNodeTests, TestTypedLiteral1) {
    // http://www.w3.org/2001/XMLSchema#string
    semsim::LibrdfNode literal = world_.newNodeTypedLiteral("TypedLiteral");
    unsigned char *actual = librdf_node_get_literal_value(literal.get());
    ASSERT_STREQ("TypedLiteral", (const char *) actual);
}

TEST_F(LibrdfNodeTests, TestBlank) {
    // http://www.w3.org/2001/XMLSchema#string
    semsim::LibrdfNode literal = world_.newNodeBlank("Blanky");
    unsigned char *actual = librdf_node_get_blank_identifier(literal.get());
    ASSERT_STREQ("Blanky", (const char *) actual);
}

TEST_F(LibrdfNodeTests, TestNodeUri) {
    std::string expected = "https://notarealaddress.com";
    semsim::LibrdfUri uri = world_.newUri(expected);
    semsim::LibrdfNode literal = world_.newNodeUri(uri);
    librdf_uri *uri_actual = librdf_node_get_uri(literal.get());
    unsigned char *actual = librdf_uri_to_string(uri_actual);
    ASSERT_STREQ(expected.c_str(), (const char *) actual);
    free(actual);
}

TEST_F(LibrdfNodeTests, TestNodeLiteral) {
    std::string expected = "https://notarealaddress.com";
    semsim::LibrdfUri uri = world_.newUri(expected);
    semsim::LibrdfNode literal = world_.newNodeUri(uri);
    std::string actual = literal.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfNodeTests, TestNodeUriString) {
    std::string expected = "https://notarealaddress.com";
    semsim::LibrdfNode literal = world_.newNodeUriString(expected);
    std::string actual = literal.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfNodeTests, TestNodeUriStringTwice) {
    std::string expected1 = "https://notarealaddress.com1";
    std::string expected2 = "https://notarealaddress.com2";
    semsim::LibrdfNode uri1 = world_.newNodeUriString(expected1);
    semsim::LibrdfNode uri2 = world_.newNodeUriString(expected2);
    std::string actual1 = uri1.str();
    std::string actual2 = uri2.str();
    ASSERT_STREQ(expected1.c_str(), actual1.c_str());
    ASSERT_STREQ(expected2.c_str(), actual2.c_str());
}


TEST_F(LibrdfNodeTests, TestUseNodsToMakeAStatement) {
    semsim::LibrdfWorld world;
    semsim::LibrdfNode subject = world.newNodeUriString("subject");
    semsim::LibrdfNode predicate = world.newNodeUriString("predicate");
    semsim::LibrdfNode resource = world.newNodeUriString("resource");

    librdf_statement *stmt = librdf_new_statement_from_nodes(
            world.get(), subject.get(), predicate.get(), resource.get());

    librdf_node *n = librdf_statement_get_subject(stmt);
    librdf_uri *uri = librdf_node_get_uri(n);
    char *actual = (char *) librdf_uri_to_string(uri);
    const char *expected = "subject";
    ASSERT_STREQ(expected, actual);

    free(actual);
//    librdf_free_uri(uri);
    free(stmt);
//    librdf_free_node(n);

/*
 * First block is telling me that the memory was allocated
 *      here: semsim::LibrdfNode resource = world.newNodeUriString("resource");
 * And its an invalid write, so something is trying to write to a memory zone that it shouldn't
 * Size of 4, so probably a int.
 *
 * Then were trying to use the librdf_free_statement function, which
 * internally free's the memory associated with the librdf_node.
 *
 * Then the defaulted destructor of LibrdfNode is trying to free the node again.
 * So what is the solution???
 *
 * Could try making a copy of the nodes for statement.
 *
 * Could also try modifying LibrdfNode destructor to only kill if exists.
 *
 * What about transferring ownership from the node to the statement?
 */
}

















