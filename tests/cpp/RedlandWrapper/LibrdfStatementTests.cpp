//
// Created by Ciaran on 5/17/2020.
//

#include "redland/LibrdfModel.h"
#include "redland/LibrdfStatement.h"
#include "redland/LibrdfStorage.h"
#include "redland/LibrdfWorld.h"
#include "gtest/gtest.h"

using namespace redland;

class LibrdfStatementTests : public ::testing::Test {

public:
    LibrdfNode subject = LibrdfNode::fromUriString("subject");
    LibrdfNode predicate = LibrdfNode::fromUriString("predicate");
    LibrdfNode resource = LibrdfNode::fromUriString("resource");

    LibrdfStatementTests() = default;
};

TEST_F(LibrdfStatementTests, TestCreate) {
    redland::LibrdfStatement statement = LibrdfStatement(
            subject,
            predicate,
            resource);

    ASSERT_NE(statement.getWithoutIncrement(), nullptr);
}

TEST_F(LibrdfStatementTests, TestMoveConstructor) {
    redland::LibrdfStatement statement1 = LibrdfStatement(subject, predicate, resource);
    redland::LibrdfStatement statement2 = std::move(statement1);
    std::string expected = "subject";
    std::string actual = statement2.getSubjectNode().str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(LibrdfStatementTests, TestMoveAssignment) {
    redland::LibrdfStatement statement1 = LibrdfStatement(subject, predicate,
                                                          resource);
    redland::LibrdfStatement statement2 = std::move(statement1);
    std::string actual = statement2.getSubjectNode().str();
    std::string expected = "subject";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(LibrdfStatementTests, TestGetPredicateStr) {
    redland::LibrdfStatement statement1 = LibrdfStatement(subject, predicate,resource);
    std::string expected = "predicate";
    std::string actual = statement1.getPredicateNode().str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfStatementTests, TestGetPredicateStr2) {
    redland::LibrdfStatement statement1 = LibrdfStatement(subject, predicate,
                                                          resource);
    std::string expected = "predicate";
    std::string actual = statement1.getPredicateNode().str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST(LibrdfStatementTestsNoFixture, TestInequality) {
    redland::LibrdfStatement statement1 = LibrdfStatement(
            LibrdfNode::fromUriString("subject1"),
            LibrdfNode::fromUriString("predicate1"),
            LibrdfNode::fromUriString("resource1"));
    redland::LibrdfStatement statement2 = LibrdfStatement(
            LibrdfNode::fromUriString("subject2"),
            LibrdfNode::fromUriString("predicate2"),
            LibrdfNode::fromUriString("resource2"));
    ASSERT_NE(statement1, statement2);
}

TEST(LibrdfStatementTestsNoFixture, TestEquality) {
    redland::LibrdfStatement statement1 = LibrdfStatement(
            LibrdfNode::fromUriString("subject"),
            LibrdfNode::fromUriString("predicate"),
            LibrdfNode::fromUriString("resource"));
    redland::LibrdfStatement statement2 = LibrdfStatement(
            LibrdfNode::fromUriString("subject"),
            LibrdfNode::fromUriString("predicate"),
            LibrdfNode::fromUriString("resource"));
    ASSERT_EQ(statement1, statement2);
}

TEST(LibrdfStatementTestsNoFixture, TestBlankEquality) {
    redland::LibrdfStatement statement1 = LibrdfStatement(
            LibrdfNode::fromBlank("blank_subject"),
            LibrdfNode::fromUriString("predicate"),
            LibrdfNode::fromUriString("resource"));
    redland::LibrdfStatement statement2 = LibrdfStatement(
            LibrdfNode::fromBlank("blank_subject"),
            LibrdfNode::fromUriString("predicate"),
            LibrdfNode::fromUriString("resource"));
    ASSERT_EQ(statement1, statement2);
}

TEST(LibrdfStatementTestsNoFixture, TestBlankEquality2) {
    redland::LibrdfStatement statement1 = LibrdfStatement(
            LibrdfNode::fromBlank(""),
            LibrdfNode::fromUriString("predicate"),
            LibrdfNode::fromUriString("resource"));
    redland::LibrdfStatement statement2 = LibrdfStatement(
            LibrdfNode::fromBlank("blank_subject"),
            LibrdfNode::fromUriString("predicate"),
            LibrdfNode::fromUriString("resource"));
    ASSERT_EQ(statement1, statement2);
}

TEST(LibrdfStatementTestsNoFixture, TestBlankInEquality2) {
    redland::LibrdfStatement statement1 = LibrdfStatement(
            LibrdfNode::fromBlank("subject"),
            LibrdfNode::fromBlank(""),
            LibrdfNode::fromUriString("resource"));
    redland::LibrdfStatement statement2 = LibrdfStatement(
            LibrdfNode::fromBlank("blank_subject"),
            LibrdfNode::fromUriString("predicate"),
            LibrdfNode::fromUriString("resource"));
    ASSERT_NE(statement1, statement2);
}

TEST(LibrdfStatementTestsNoFixture, TestBlankInEquality3) {
    LibrdfStorage storage1;
    LibrdfModel model1(storage1);

    LibrdfStatement statement1(
            LibrdfNode::fromUriString("http://omex-library.org/NewOmex.omex/NewModel.xml"),
            LibrdfNode::fromUriString("http://purl.org/dc/terms/created"),
            LibrdfNode::fromBlank(""));
    model1.addStatement(statement1);
    ASSERT_TRUE(model1.containsStatement(statement1));
}


TEST_F(LibrdfStatementTests, TestToStatementSubject) {
    LibrdfStatement statement = LibrdfStatement(
            subject, predicate, resource);
    std::string actual = statement.getSubjectNode().str();
    std::string expected = "subject";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(LibrdfStatementTests, TestPartial1) {
    // default construct a statement
    LibrdfStatement statement;
    statement.setSubject(subject.get());
    std::string actual = statement.getSubjectNode().str();
    std::string expected = "subject";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfStatementTests, TestGetSubjectNode) {
    LibrdfStatement statement = LibrdfStatement(subject, predicate, resource);
    ASSERT_EQ(1, statement.getUsage());
    ASSERT_EQ(2, subject.getUsage());
    ASSERT_EQ(2, predicate.getUsage());
    ASSERT_EQ(2, resource.getUsage());

    LibrdfNode s = statement.getSubjectNode();
    ASSERT_EQ(3, s.getUsage());
}

TEST_F(LibrdfStatementTests, TestGetPredicateNode) {
    LibrdfStatement statement = LibrdfStatement(subject, predicate, resource);
    ASSERT_EQ(1, statement.getUsage());

    ASSERT_EQ(2, subject.getUsage());
    ASSERT_EQ(2, predicate.getUsage());
    ASSERT_EQ(2, resource.getUsage());

    LibrdfNode s = statement.getPredicateNode();
    ASSERT_EQ(3, s.getUsage());
}

TEST_F(LibrdfStatementTests, TestGetResourceNode) {
    LibrdfStatement statement = LibrdfStatement(subject, predicate, resource);
    ASSERT_EQ(1, statement.getUsage());

    ASSERT_EQ(2, subject.getUsage());
    ASSERT_EQ(2, predicate.getUsage());
    ASSERT_EQ(2, resource.getUsage());

    LibrdfNode s = statement.getResourceNode();
    ASSERT_EQ(3, s.getUsage());
}

//
TEST_F(LibrdfStatementTests, CopyConstruct) {
    LibrdfNode n1 = LibrdfNode::fromUriString("node1");
    LibrdfNode n2 = LibrdfNode::fromUriString("node2");
    LibrdfNode n3 = LibrdfNode::fromUriString("node3");
    ASSERT_EQ(1, n1.getUsage());
    ASSERT_EQ(1, n2.getUsage());
    ASSERT_EQ(1, n3.getUsage());

    LibrdfStatement statement(n1, n2, n3);
    ASSERT_EQ(1, statement.getUsage());
    ASSERT_EQ(2, n1.getUsage());
    ASSERT_EQ(2, n2.getUsage());
    ASSERT_EQ(2, n3.getUsage());
    LibrdfStatement copy = statement;
    ASSERT_EQ(2, n1.getUsage());
    ASSERT_EQ(2, n2.getUsage());
    ASSERT_EQ(2, n3.getUsage());

    ASSERT_EQ(2, statement.getUsage());
    ASSERT_EQ(2, copy.getUsage());
}

TEST_F(LibrdfStatementTests, CopyAssignment) {
    LibrdfNode s1n1 = LibrdfNode::fromUriString("s1node1");
    LibrdfNode s1n2 = LibrdfNode::fromUriString("s1node2");
    LibrdfNode s1n3 = LibrdfNode::fromUriString("s1node3");
    LibrdfStatement s1(s1n1, s1n2, s1n3);
    ASSERT_EQ(1, s1.getUsage());

    LibrdfNode s2n1 = LibrdfNode::fromUriString("s2node1");
    LibrdfNode s2n2 = LibrdfNode::fromUriString("s2node2");
    LibrdfNode s2n3 = LibrdfNode::fromUriString("s2node3");
    LibrdfStatement s2(s2n1, s2n2, s2n3);
    ASSERT_EQ(1, s2.getUsage());
    ASSERT_EQ(s1.getSubjectNode().str(), "s1node1");
    s1 = s2;
    ASSERT_EQ(s1.getSubjectNode().str(), "s2node1");

    // they now both point to the same
    ASSERT_EQ(2, s1.getUsage());
    ASSERT_EQ(2, s2.getUsage());

}

TEST_F(LibrdfStatementTests, MoveConstruct) {
    LibrdfNode s1n1 = LibrdfNode::fromUriString("s1node1");
    LibrdfNode s1n2 = LibrdfNode::fromUriString("s1node2");
    LibrdfNode s1n3 = LibrdfNode::fromUriString("s1node3");
    LibrdfStatement s1(s1n1, s1n2, s1n3);
    ASSERT_EQ(1, s1.getUsage());
    LibrdfStatement s2 = std::move(s1);
    ASSERT_EQ(1, s2.getUsage());
}

TEST_F(LibrdfStatementTests, MoveAssignment) {
    LibrdfNode s1n1 = LibrdfNode::fromUriString("s1node1");
    LibrdfNode s1n2 = LibrdfNode::fromUriString("s1node2");
    LibrdfNode s1n3 = LibrdfNode::fromUriString("s1node3");
    LibrdfStatement s1(s1n1, s1n2, s1n3);
    ASSERT_EQ(1, s1.getUsage());
    LibrdfStatement s2;
    s2 = std::move(s1);
    ASSERT_EQ(1, s2.getUsage());
}
