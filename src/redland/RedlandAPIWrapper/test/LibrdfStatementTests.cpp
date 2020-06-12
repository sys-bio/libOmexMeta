//
// Created by Ciaran on 5/17/2020.
//

#include "gtest/gtest.h"
#include "World.h"
#include "LibrdfStatement.h"
//#include "redland/SemsimUtils.h"

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
            resource
    );

    ASSERT_NE(statement.get(), nullptr);

}

TEST_F(LibrdfStatementTests, TestCopyConstructor) {
    redland::LibrdfStatement statement1 = LibrdfStatement(subject, predicate, resource);
    redland::LibrdfStatement statement2 = statement1;
    std::string actual1 = statement1.getSubjectStr();
    std::string actual2 = statement2.getSubjectStr();
    ASSERT_STREQ(actual1.c_str(), actual2.c_str());
}

TEST_F(LibrdfStatementTests, TestMoveConstructor) {
    redland::LibrdfStatement statement1 = LibrdfStatement(subject, predicate, resource);
    redland::LibrdfStatement statement2 = std::move(statement1);
    std::string expected = "subject";
    std::string actual = statement2.getSubjectStr();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfStatementTests, TestCopyAssignment) {
    redland::LibrdfStatement statement1 = LibrdfStatement(std::move(subject), std::move(predicate),
                                                          std::move(resource));
    redland::LibrdfStatement statement2 = statement1;
    std::string actual1 = statement1.getSubjectStr();
    std::string actual2 = statement2.getSubjectStr();
    ASSERT_STREQ(actual1.c_str(), actual2.c_str());
}

TEST_F(LibrdfStatementTests, TestMoveAssignment) {
    redland::LibrdfStatement statement1 = LibrdfStatement(subject, predicate,
                                                          resource);
    redland::LibrdfStatement statement2 = std::move(statement1);
    std::string actual = statement2.getSubjectStr();
    std::string expected = "subject";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(LibrdfStatementTests, TestGetPredicateStr) {
    redland::LibrdfStatement statement1 = LibrdfStatement(subject, predicate,
                                                          resource);
    std::string expected = "predicate";
    std::string actual = statement1.getPredicateStr();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(LibrdfStatementTests, TestToStatementSubject) {
    LibrdfStatement statement = LibrdfStatement(
            subject, predicate, resource);
    std::string actual = statement.getSubjectStr();
    std::string expected = "subject";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(LibrdfStatementTests, TestPartial1) {
    LibrdfStatement statement;
    statement.setSubject(subject.get());
    std::string actual = statement.getSubjectStr();
    std::string expected = "subject";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    predicate.freeNode();
    resource.freeNode();

}





















