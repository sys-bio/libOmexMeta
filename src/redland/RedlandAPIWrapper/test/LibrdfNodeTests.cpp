//
// Created by Ciaran on 5/17/2020.
//
#include "gtest/gtest.h"
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
    node.freeNode();
}

TEST_F(LibrdfNodeTests, TestUnderlyingNodeHasUri) {
    std::string expected = "https://notarealaddress.com";
    LibrdfNode node = LibrdfNode::fromUriString(expected);
    LibrdfUri uri = node.getUri(); // owned by node
    std::string s = uri.str();
    ASSERT_STREQ("https://notarealaddress.com", s.c_str());
    node.freeNode();
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
    node2.freeNode();
}

//TEST_F(LibrdfNodeTests, TestAssignmentOperator) {
//    std::string expected1 = "https://notarealaddress1.com";
//    std::string expected2 = "https://notarealaddress2.com";
//    LibrdfNode node1 = LibrdfNode::fromUriString(expected1);
//    LibrdfNode node2 = LibrdfNode::fromUriString(expected2);
//    node2 = node1;
//    std::string actual = node2.str();
//    ASSERT_STREQ(expected1.c_str(), actual.c_str());
//}


TEST_F(LibrdfNodeTests, TestMoveAssignmentOperator) {
    std::string expected1 = "https://notarealaddress1.com";
    std::string expected2 = "https://notarealaddress2.com";
    LibrdfNode node1 = LibrdfNode::fromUriString(expected1);
    LibrdfNode node2 = LibrdfNode::fromUriString(expected2);
    node1 = std::move(node2);
    std::string actual = node1.str();
    ASSERT_STREQ(expected2.c_str(), actual.c_str());
    node1.freeNode();
}

TEST_F(LibrdfNodeTests, TestLiteral1) {
    /*
     * uri is an empty string
     */
    // http://www.w3.org/2001/XMLSchema#string
    LibrdfNode node = LibrdfNode::fromLiteral("Literal Node");
    std::string actual = node.str();
    ASSERT_STREQ("Literal Node", actual.c_str());
    node.freeNode();
}

TEST_F(LibrdfNodeTests, TestTypedLiteral1) {
    LibrdfNode node = LibrdfNode::fromLiteral("TypedLiteral");
    unsigned char *actual = librdf_node_get_literal_value(node.get());
    ASSERT_STREQ("TypedLiteral", (const char *) actual);
    node.freeNode();
}

TEST_F(LibrdfNodeTests, TestTypedLiteral2) {
    LibrdfNode node = LibrdfNode::fromLiteral("TypedLiteral");
    LibrdfUri n = node.getLiteralDatatype();
    std::string actual = n.str();
    ASSERT_STREQ("http://www.w3.org/1999/02/22-rdf-syntax-ns#string", actual.c_str());
    node.freeNode();
}

TEST_F(LibrdfNodeTests, TestTypedLiteral3) {
    LibrdfNode node = LibrdfNode::fromLiteral("TypedLiteral");
    std::string actual = node.getLiteralLanguage();
    ASSERT_STREQ("", actual.c_str());
    node.freeNode();
}

TEST_F(LibrdfNodeTests, TestBlank) {
    // http://www.w3.org/2001/XMLSchema#string
    LibrdfNode node = LibrdfNode::fromBlank("Blanky");
    unsigned char *actual = librdf_node_get_blank_identifier(node.get());
    ASSERT_STREQ("Blanky", (const char *) actual);
    node.freeNode();
}

TEST_F(LibrdfNodeTests, TestNodeUri) {
    std::string expected = "https://notarealaddress.com";
    LibrdfNode node = LibrdfNode::fromUriString(expected);
    librdf_uri *uri_actual = librdf_node_get_uri(node.get());
    unsigned char *actual = librdf_uri_to_string(uri_actual);
    ASSERT_STREQ(expected.c_str(), (const char *) actual);
    free(actual);
    node.freeNode();
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
    uri1.freeNode();
    uri2.freeNode();
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
    librdf_free_statement(stmt);

}


TEST_F(LibrdfNodeTests, TestgetUri) {
    LibrdfNode subject = LibrdfNode::fromUriString("subject");
    LibrdfUri u = subject.getUri();
    std::string actual = u.str();
    std::string expected = "subject";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    subject.freeNode();
}

TEST_F(LibrdfNodeTests, TestSetUri) {
    LibrdfNode subject = LibrdfNode::fromUriString("subject");
    subject.setUri("predicate");
    std::string actual = subject.getUri().str();
    std::string expected = "predicate";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    subject.freeNode();
}

TEST_F(LibrdfNodeTests, TestgetLiteralDatatype) {
    LibrdfNode subject = LibrdfNode::fromLiteral("subject");
    LibrdfUri u = subject.getLiteralDatatype();
    std::string actual = u.str();
    std::string expected = "http://www.w3.org/1999/02/22-rdf-syntax-ns#string";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    subject.freeNode();
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

//TEST_F(LibrdfNodeTests, TestsetLiteralDatatype) {
//    LibrdfNode subject = LibrdfNode::fromLiteral("subject");
//    subject.setLiteralDatatype("int");
////    LibrdfUri u = subject.getLiteralDatatype();
////    std::string actual = u.str();
////    std::string expected = "http://www.w3.org/1999/02/22-rdf-syntax-ns#int";
////    ASSERT_STREQ(expected.c_str(), actual.c_str());
//    subject.freeNode();
//}

TEST_F(LibrdfNodeTests, TestsetLiteralDatatypeDoesntChangeValue) {
    LibrdfNode subject = LibrdfNode::fromLiteral("subject");
    subject.setLiteralDatatype("int");
    std::string actual = subject.str();
    std::string expected = "subject";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    subject.freeNode();
}

TEST_F(LibrdfNodeTests, TestSetBlank) {
    LibrdfNode subject = LibrdfNode::fromBlank("subject");
    subject.setBlankIdentifier("blank subject");
    std::string actual = subject.getBlankIdentifier();
    std::string expected = "blank subject";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    subject.freeNode();
}

TEST_F(LibrdfNodeTests, TestSetBlankValueNotChanged) {
    LibrdfNode subject = LibrdfNode::fromBlank("subject");
    subject.setBlankIdentifier("blank subject");
    std::string actual = subject.str();
    std::string expected = "blank subject";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    subject.freeNode();

}

TEST_F(LibrdfNodeTests, TestSetUri2) {
    LibrdfNode subject = LibrdfNode::fromUriString("subject");
    subject.setUri("predicate");
    std::string actual = subject.getUri().str();
    std::string expected = "predicate";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    subject.freeNode();
}


TEST_F(LibrdfNodeTests, TestEquality) {
    LibrdfNode subject1 = LibrdfNode::fromUriString("subject");
    LibrdfNode subject2 = LibrdfNode::fromUriString("subject");
    ASSERT_EQ(subject1, subject2);

    subject1.freeNode();
    subject2.freeNode();
}

TEST_F(LibrdfNodeTests, TestInequality) {
    LibrdfNode subject1 = LibrdfNode::fromUriString("subject1");
    LibrdfNode subject2 = LibrdfNode::fromUriString("subject2");
    ASSERT_NE(subject1, subject2);

    /*
     * Both nodes refer to the same block of memory. But
     * librdf_node has a reference counter. Each time we free the node,
     * the ref count reduces until it gets to 1. Then it is freed.
     */
    subject1.freeNode(); // ref count to 1
    subject2.freeNode(); // ref count to 0
}

TEST_F(LibrdfNodeTests, TestCopyNodeUri) {
    LibrdfNode subject1 = LibrdfNode::fromUriString("subject1");
    LibrdfNode subject2 = LibrdfNode::copyNode(subject1);
    ASSERT_EQ(subject1, subject2);
    ASSERT_EQ(subject1.getUri(), subject2.getUri());
    ASSERT_EQ(2, subject1.getUri().getUsage());
    ASSERT_EQ(2, subject2.getUri().getUsage());

    subject1.freeNode(); // ref count to 1
    subject2.freeNode(); // ref count to 0
}

/*
 * Uri works as expected.
 */
TEST_F(LibrdfNodeTests, TestCopyNodeUriNoWrapper) {
    librdf_uri* uri1 = librdf_new_uri(World::getWorld(), (const unsigned char*)"https://uri.com");
    librdf_uri* uri2 = librdf_new_uri_from_uri(uri1);
    int expected = 2;
    int uri1_count = librdf_uri_get_usage(uri1);
    int uri2_count = librdf_uri_get_usage(uri2);
    ASSERT_EQ(uri1_count, uri2_count);
    ASSERT_EQ(expected, uri1_count);
    librdf_free_uri(uri1);
    ASSERT_EQ(1, librdf_uri_get_usage(uri2));
    librdf_free_uri(uri2);
}

TEST_F(LibrdfNodeTests, TestCopyNodeNoWrapper) {
    /*
     * This test does not work because of bug in raptor.
     * If you copy a node with a uri, you should increment
     * the uri usage count. But it does not.
     */
    librdf_node* n1 = librdf_new_node_from_uri_string(World::getWorld(), (const unsigned char*)"https://uri1.com");
    librdf_node* n2 = librdf_new_node_from_node(n1);
//    ASSERT_TRUE(librdf_node_equals(n1, n2));
}

TEST_F(LibrdfNodeTests, TestCopyNodeLiteral) {
    LibrdfNode subject1 = LibrdfNode::fromLiteral("subject1");
    LibrdfNode subject2 = LibrdfNode::copyNode(subject1);
    ASSERT_EQ(subject1, subject2);
    ASSERT_EQ(subject1.getLiteralDatatype(), subject2.getLiteralDatatype());
    ASSERT_EQ(2, subject1.getLiteralDatatype().getUsage());
    ASSERT_EQ(2, subject2.getLiteralDatatype().getUsage());

    subject1.freeNode(); // ref count to 1
    subject2.freeNode(); // ref count to 0
}



//TEST_F(LibrdfNodeTests, TestRelativeUri) {
//    LibrdfNode node = LibrdfNode::fromRelativeUri("subject1", "file://mnt/d/libOmexMeta");
//    std::string actual = node.str();
//    std::string expected = "file://mnt/d/libOmexMeta/myModel.xml#subject1";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//    node.freeNode();
//}
















