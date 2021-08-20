//
// Created by Ciaran on 5/17/2020.
//
#include "redland/LibrdfNode.h"
#include "redland/LibrdfStatement.h"
#include "redland/LibrdfWorld.h"
#include "gtest/gtest.h"

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

TEST_F(LibrdfNodeTests, CheckFromRawPtr) {
    librdf_node* nPtr = librdf_new_node_from_uri_string(LibrdfWorld::getWorld(), (const unsigned char*)"http://uri.com");
    LibrdfNode node(nPtr);
    ASSERT_EQ(node.getUsage(), 1);
}

TEST_F(LibrdfNodeTests, CheckFromRawPtrCpyAssignment) {
    LibrdfNode node;
    librdf_node* nPtr = librdf_new_node_from_uri_string(LibrdfWorld::getWorld(), (const unsigned char*)"http://uri.com");
    node = LibrdfNode(nPtr);
    ASSERT_EQ(node.getUsage(), 1);
}


TEST_F(LibrdfNodeTests, CheckCanCreateEmptyNode) {
    LibrdfNode node;
    ASSERT_TRUE(node.isNull());
}

TEST_F(LibrdfNodeTests, UriNodeUrnMiriam) {
    std::string expected = "urn:miriam:reactome:R12345";
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
}

TEST_F(LibrdfNodeTests, TestLiteral1) {
    /*
     * uri is an empty string
     */
    // http://www.w3.org/2001/XMLSchema#string
    LibrdfNode node = LibrdfNode::fromLiteral("Literal Node");
    std::string actual = node.str();
    ASSERT_STREQ("Literal Node", actual.c_str());
}

TEST_F(LibrdfNodeTests, TestTypedLiteral1) {
    LibrdfNode node = LibrdfNode::fromLiteral("TypedLiteral");
    librdf_node* n = node.get();
    unsigned char *actual = librdf_node_get_literal_value(n);
    librdf_free_node(n);
    ASSERT_STREQ("TypedLiteral", (const char *) actual);
}

TEST_F(LibrdfNodeTests, TestTypedLiteral2) {
    LibrdfNode node = LibrdfNode::fromLiteral("TypedLiteral", "string");
    LibrdfUri n = node.getLiteralDatatype();
    std::string actual = n.str();
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
    unsigned char *actual = librdf_node_get_blank_identifier(node.getWithoutIncrement());
    ASSERT_STREQ("Blanky", (const char *) actual);
}

TEST_F(LibrdfNodeTests, TestNodeUri) {
    std::string expected = "https://notarealaddress.com";
    LibrdfNode node = LibrdfNode::fromUriString(expected);
    LibrdfUri uri = node.getUri();
    ASSERT_STREQ(expected.c_str(), uri.str().c_str());
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


TEST_F(LibrdfNodeTests, TestUseNodesToMakeARawLibrdfStatementObj) {
    LibrdfNode subject = LibrdfNode::fromUriString("subject");
    LibrdfNode predicate = LibrdfNode::fromUriString("predicate");
    LibrdfNode resource = LibrdfNode::fromUriString("resource");

    librdf_statement *stmt = librdf_new_statement_from_nodes(
            LibrdfWorld::getWorld(), subject.get(), predicate.get(), resource.get());

    librdf_node *n = librdf_statement_get_subject(stmt);
    librdf_uri *uri = librdf_node_get_uri(n);
    char *actual = (char *) librdf_uri_to_string(uri);
    const char *expected = "subject";
    ASSERT_STREQ(expected, actual);
    free(actual);
    librdf_free_statement(stmt);
}

TEST_F(LibrdfNodeTests, TestUseNodesToMakeAWrapperLibrdfStatementObj) {
    LibrdfNode subject = LibrdfNode::fromUriString("subject");
    LibrdfNode predicate = LibrdfNode::fromUriString("predicate");
    LibrdfNode resource = LibrdfNode::fromUriString("resource");

    ASSERT_EQ(subject.getUsage(), 1);
    ASSERT_EQ(predicate.getUsage(), 1);
    ASSERT_EQ(resource.getUsage(), 1);

    LibrdfStatement stmt(subject, predicate, resource);

    ASSERT_EQ(stmt.getUsage(), 1);

    ASSERT_EQ(subject.getUsage(), 2);
    ASSERT_EQ(predicate.getUsage(), 2);
    ASSERT_EQ(resource.getUsage(), 2);
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
    LibrdfNode subject = LibrdfNode::fromLiteral("subject", "int");
    LibrdfUri u = subject.getLiteralDatatype();
    std::string actual = u.str();
    std::string expected = "http://www.w3.org/1999/02/22-rdf-syntax-ns#int";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfNodeTests, TestValidateLiteralDatatype) {
    std::string actual = LibrdfNode::validateLiteralDatatype("int");
    std::string expected = "http://www.w3.org/1999/02/22-rdf-syntax-ns#int";
    ASSERT_STREQ(actual.c_str(), expected.c_str());
}

TEST_F(LibrdfNodeTests, TestValidateLiteralDatatype2) {
    std::string actual = LibrdfNode::validateLiteralDatatype("int");
    std::string expected = "http://www.w3.org/1999/02/22-rdf-syntax-ns#int";
    ASSERT_STREQ(actual.c_str(), expected.c_str());
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
    std::string expected = "blank subject";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfNodeTests, TestSetUri2) {
    LibrdfNode subject = LibrdfNode::fromUriString("subject");
    subject.setUri("predicate");
    std::string actual = subject.getUri().str();
    std::string expected = "predicate";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(LibrdfNodeTests, TestEquality) {
    LibrdfNode subject1 = LibrdfNode::fromUriString("subject");
    LibrdfNode subject2 = LibrdfNode::fromUriString("subject");
    ASSERT_EQ(subject1, subject2);
}

TEST_F(LibrdfNodeTests, TestEqualityBlank) {
    LibrdfNode subject1 = LibrdfNode::fromBlank("subject");
    LibrdfNode subject2 = LibrdfNode::fromBlank("subject");
    ASSERT_EQ(subject1, subject2);
}

TEST_F(LibrdfNodeTests, TestInequality) {
    LibrdfNode subject1 = LibrdfNode::fromUriString("subject1");
    LibrdfNode subject2 = LibrdfNode::fromUriString("subject2");
    ASSERT_NE(subject1, subject2);

}

TEST_F(LibrdfNodeTests, TestCopyNodeUri) {
    LibrdfNode subject1 = LibrdfNode::fromUriString("subject1");
    LibrdfNode subject2 = LibrdfNode::copyNode(subject1);
    ASSERT_EQ(subject1, subject2);
    ASSERT_EQ(subject1.getUri(), subject2.getUri());
}

/*
 * Uri works as expected.
 */
TEST_F(LibrdfNodeTests, TestCopyNodeUriNoWrapper) {
    librdf_uri *uri1 = librdf_new_uri(LibrdfWorld::getWorld(), (const unsigned char *) "https://uri.com");
    librdf_uri *uri2 = librdf_new_uri_from_uri(uri1);
    int expected = 2;
    int uri1_count = librdf_uri_get_usage(uri1);
    int uri2_count = librdf_uri_get_usage(uri2);
    ASSERT_EQ(uri1_count, uri2_count);
    ASSERT_EQ(expected, uri1_count);
    librdf_free_uri(uri1);
    ASSERT_EQ(1, librdf_uri_get_usage(uri2));
    librdf_free_uri(uri2);
}


TEST_F(LibrdfNodeTests, TestCopyNodeLiteral) {
    LibrdfNode subject1 = LibrdfNode::fromLiteral("subject1", "string");
    LibrdfNode subject2 = LibrdfNode::copyNode(subject1);
    ASSERT_EQ(subject1, subject2);
    ASSERT_EQ(subject1.getLiteralDatatype(), subject2.getLiteralDatatype());
}

TEST_F(LibrdfNodeTests, TestTwoNodesUriCountDifferentContentUsingRaptor) {
    // n1 and n2 are two different nodes
    librdf_node *n1 = librdf_new_node_from_uri_string(LibrdfWorld::getWorld(), (const unsigned char *) "node1");
    librdf_node *n2 = librdf_new_node_from_uri_string(LibrdfWorld::getWorld(), (const unsigned char *) "node2");

    ASSERT_EQ(1, n1->usage);
    ASSERT_EQ(1, n2->usage);
    ASSERT_EQ(1, librdf_uri_get_usage(n1->value.uri));
    ASSERT_EQ(1, librdf_uri_get_usage(n2->value.uri));
    librdf_free_node(n1);
    librdf_free_node(n2);
;}

TEST_F(LibrdfNodeTests, TestTwoNodesUriCountSameContentUsingRaptor) {
    // n1 and n2 are different nodes but they share the same uri
    librdf_node *n1 = librdf_new_node_from_uri_string(LibrdfWorld::getWorld(), (const unsigned char *) "node1");
    librdf_node *n2 = librdf_new_node_from_uri_string(LibrdfWorld::getWorld(), (const unsigned char *) "node1");

    ASSERT_EQ(1, n1->usage);
    ASSERT_EQ(1, n2->usage);
    // same uri is used twice
    ASSERT_EQ(2, librdf_uri_get_usage(n1->value.uri));
    ASSERT_EQ(2, librdf_uri_get_usage(n2->value.uri));

    librdf_free_node(n1);
    ASSERT_EQ(1, librdf_uri_get_usage(n2->value.uri));
    librdf_free_node(n2);
}


//TEST_F(LibrdfNodeTests, TestTwoNodesUriCountDifferentContentUsingMyCode) {
//    // n1 and n2 are two different nodes
//    LibrdfNode n1 = LibrdfNode::fromUriString("node1");
//    LibrdfNode n2 = LibrdfNode::fromUriString("node2");
//
//    ASSERT_EQ(1, n1.getUsage());
//    ASSERT_EQ(1, n2.getUsage());
//    LibrdfUri uri1 = n1.getUri();
//    LibrdfUri uri2 = n2.getUri();
//    ASSERT_EQ(2, uri1.getUsage());
//    ASSERT_EQ(2, uri2.getUsage());
//}

TEST_F(LibrdfNodeTests, GetNamespace1) {
    // n1 and n2 are two different nodes
    LibrdfNode n1 = LibrdfNode::fromUriString("http://biomodels.net/biology-qualifiers/is");
    std::string expected = "http://biomodels.net/biology-qualifiers/";
    std::string actual = n1.getNamespace();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(LibrdfNodeTests, GetNamespace2) {
    // n1 and n2 are two different nodes
    LibrdfNode n1 = LibrdfNode::fromUriString("http://bime.uw.edu/semsim#hasMultiplier");
    std::string expected = "http://bime.uw.edu/semsim#";
    std::string actual = n1.getNamespace();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(LibrdfNodeTests, TestRefCounterOneNode) {
    LibrdfNode n1 = LibrdfNode::fromUriString("node1");
    ASSERT_EQ(1, n1.getUsage());
}

TEST_F(LibrdfNodeTests, TestRefCounterOneNodesUri) {
    LibrdfNode n1 = LibrdfNode::fromUriString("node1");
    ASSERT_EQ(1, n1.getUsage());

    // get uri. increase ref count but pointer belongs to
    // uri1 so do not free
    LibrdfUri uri1 = n1.getUri();
    ASSERT_EQ(2, uri1.getUsage());
    ASSERT_STREQ(uri1.str().c_str(), "node1");

    // remaining pointers are cleaned up by destructors
}


TEST_F(LibrdfNodeTests, CopyConstruct) {
    LibrdfNode node = LibrdfNode::fromUriString("node");
    ASSERT_EQ(1, node.getUsage());
    LibrdfNode nodeCopy = node;
    ASSERT_EQ(2, node.getUsage());
    ASSERT_EQ(2, nodeCopy.getUsage());
}

TEST_F(LibrdfNodeTests, CopyAssignment) {
    LibrdfNode node1 = LibrdfNode::fromUriString("https://node1.com");
    ASSERT_EQ(1, node1.getUsage());
    LibrdfNode node2 = LibrdfNode::fromUriString("https://node2.com");
    ASSERT_EQ(1, node2.getUsage());

    node1 = node2;
    ASSERT_STREQ("https://node2.com", node1.str().c_str());
    ASSERT_STREQ("https://node2.com", node2.str().c_str());
    ASSERT_EQ(2, node1.getUsage());
    ASSERT_EQ(2, node2.getUsage());
    ASSERT_EQ(node1, node2);
}

TEST_F(LibrdfNodeTests, MoveConstruct) {
    LibrdfNode node = LibrdfNode::fromUriString("https://node.com");
    ASSERT_EQ(1, node.getUsage());
    LibrdfNode nodeMoved = std::move(node);
    ASSERT_EQ(1, nodeMoved.getUsage());
}

TEST_F(LibrdfNodeTests, MoveAssignment) {
    LibrdfNode node1 = LibrdfNode::fromUriString("https://node1.com");
    ASSERT_EQ(1, node1.getUsage());
    LibrdfNode node2 = std::move(node1);
    ASSERT_EQ(1, node2.getUsage());
}

TEST_F(LibrdfNodeTests, isBlank) {
    LibrdfNode node1 = LibrdfNode::fromBlank("BlankId");
    ASSERT_TRUE(node1.isBlank());
}

TEST_F(LibrdfNodeTests, isUri) {
    LibrdfNode node1 = LibrdfNode::fromUriString("https://uri.com");
    ASSERT_TRUE(node1.isUri());
}

TEST_F(LibrdfNodeTests, isLiteral) {
    LibrdfNode node1 = LibrdfNode::fromLiteral("LiteralNode");
    ASSERT_TRUE(node1.isLiteral());
}
