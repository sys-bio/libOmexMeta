//
// Created by Ciaran on 5/17/2020.
//

#include "redland/LibrdfStatement.h"
#include "redland/World.h"
#include "gtest/gtest.h"
#include "redland/LibrdfModel.h"
#include "redland/LibrdfStorage.h"

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

    ASSERT_NE(statement.get(), nullptr);
    statement.freeStatement();
}

TEST_F(LibrdfStatementTests, TestMoveConstructor) {
    redland::LibrdfStatement statement1 = LibrdfStatement(subject, predicate, resource);
    redland::LibrdfStatement statement2 = std::move(statement1);
    std::string expected = "subject";
    std::string actual = statement2.getSubjectStr();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    statement2.freeStatement();
}


TEST_F(LibrdfStatementTests, TestMoveAssignment) {
    redland::LibrdfStatement statement1 = LibrdfStatement(subject, predicate,
                                                          resource);
    redland::LibrdfStatement statement2 = std::move(statement1);
    std::string actual = statement2.getSubjectStr();
    std::string expected = "subject";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    statement2.freeStatement();
}


TEST_F(LibrdfStatementTests, TestGetPredicateStr) {
    redland::LibrdfStatement statement1 = LibrdfStatement(subject, predicate,
                                                          resource);
    std::string expected = "predicate";
    std::string actual = statement1.getPredicateStr();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    statement1.freeStatement();
}

TEST_F(LibrdfStatementTests, TestGetPredicateStr2) {
    redland::LibrdfStatement statement1 = LibrdfStatement(subject, predicate,
                                                          resource);
    std::string expected = "predicate";
    std::string actual = statement1.getPredicateStr();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    statement1.freeStatement();
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
    statement1.freeStatement();
    statement2.freeStatement();
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
    statement1.freeStatement();
    statement2.freeStatement();
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
    statement1.freeStatement();
    statement2.freeStatement();
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
    statement1.freeStatement();
    statement2.freeStatement();
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
    statement1.freeStatement();
    statement2.freeStatement();
}

TEST(LibrdfStatementTestsNoFixture, TestBlankInEquality3) {
    LibrdfStorage storage1;
    LibrdfModel model1(storage1.get());

    LibrdfStatement statement1(
            LibrdfNode::fromUriString("http://omex-library.org/NewOmex.omex/NewModel.xml").get(),
            LibrdfNode::fromUriString("https://dublincore.org/specifications/dublin-core/dcmi-terms/created").get(),
            LibrdfNode::fromBlank("").get()
            );
    model1.addStatement(statement1);
    ASSERT_TRUE(model1.containsStatement(statement1.get()));

    statement1.freeStatement();
    model1.freeModel();
    storage1.freeStorage();
}


TEST_F(LibrdfStatementTests, TestToStatementSubject) {
    LibrdfStatement statement = LibrdfStatement(
            subject, predicate, resource);
    std::string actual = statement.getSubjectStr();
    std::string expected = "subject";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    statement.freeStatement();
}


TEST_F(LibrdfStatementTests, TestPartial1) {
    LibrdfStatement statement;
    statement.setSubject(subject.get());
    std::string actual = statement.getSubjectStr();
    std::string expected = "subject";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    predicate.freeNode();
    resource.freeNode();
    statement.freeStatement();
}
