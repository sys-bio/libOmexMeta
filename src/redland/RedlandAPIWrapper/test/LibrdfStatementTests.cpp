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

//    ASSERT_NE(statement.get(), nullptr);

}

TEST_F(LibrdfStatementTests, TestCreate2) {
    LibrdfStatement s = LibrdfStatement(
            std::move(LibrdfNode::fromUriString("http://www.dajobe.org/")),
            std::move(LibrdfNode::fromUriString("http://purl.org/dc/elements/1.1/title")),
            std::move(LibrdfNode::fromLiteral("My Home Page"))
    );
}

//TEST_F(LibrdfStatementTests, TestCopyConstructor) {
//    redland::LibrdfStatement statement1 = LibrdfStatement(std::move(subject), std::move(predicate), std::move(resource));
//    redland::LibrdfStatement statement2 = statement1;
//    ASSERT_EQ(statement1, statement2);
//}

TEST_F(LibrdfStatementTests, TestMoveConstructor) {
    redland::LibrdfStatement statement1 = LibrdfStatement(std::move(subject), std::move(predicate),
                                                          std::move(resource));
    redland::LibrdfStatement statement2 = std::move(statement1);
    std::string expected = "subject";
    std::string actual = statement2.getSubject().str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

//TEST_F(LibrdfStatementTests, TestCopyAssignment) {
//    redland::LibrdfStatement statement1 = LibrdfStatement(std::move(subject), std::move(predicate), std::move(resource));
//    redland::LibrdfStatement statement2 = statement1;
//    std::string actual = statement2.getSubject().str();
//    std::string expected = "subject";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}

TEST_F(LibrdfStatementTests, TestMoveAssignment) {
    redland::LibrdfStatement statement1 = LibrdfStatement(std::move(subject), std::move(predicate),
                                                          std::move(resource));
    redland::LibrdfStatement statement2 = std::move(statement1);
    std::string actual = statement2.getSubject().str();
    std::string expected = "subject";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(LibrdfStatementTests, TestGetPredicateStr) {
    redland::LibrdfStatement statement1 = LibrdfStatement(std::move(subject), std::move(predicate),
                                                          std::move(resource));
    std::string expected = "predicate";
    std::string actual = statement1.getPredicate().str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(LibrdfStatementTests, TestToStatementSubject) {
    LibrdfStatement statement(std::move(subject), std::move(predicate), std::move(resource));
    LibrdfNode subject = statement.getSubject();
    std::string actual = subject.str();
    std::string expected = "subject";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}





















