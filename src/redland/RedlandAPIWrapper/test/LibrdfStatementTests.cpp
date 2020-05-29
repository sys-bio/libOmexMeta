//
// Created by Ciaran on 5/17/2020.
//

#include "gtest/gtest.h"
#include "World.h"
#include "LibrdfStatement.h"
//#include "semsim/SemsimUtils.h"

using namespace semsim;

class LibrdfStatementTests : public ::testing::Test {

public:
    LibrdfNode subject = LibrdfNode::fromUriString("subject");
    LibrdfNode predicate = LibrdfNode::fromUriString("predicate");
    LibrdfNode resource = LibrdfNode::fromUriString("resource");

    LibrdfStatementTests() = default;
};

TEST_F(LibrdfStatementTests, TestCreate) {
    semsim::LibrdfStatement statement = LibrdfStatement(std::move(subject), std::move(predicate), std::move(resource));
    ASSERT_NE(statement.get(), nullptr);

}

TEST_F(LibrdfStatementTests, TestCreate2) {
    LibrdfStatement s = LibrdfStatement(
            std::move(LibrdfNode::fromUriString("http://www.dajobe.org/")),
            std::move(LibrdfNode::fromUriString("http://purl.org/dc/elements/1.1/title")),
            std::move(LibrdfNode::fromLiteral("My Home Page"))
    );
}

//TEST_F(LibrdfStatementTests, TestCopyConstructor) {
//    semsim::LibrdfStatement statement1 = LibrdfStatement(std::move(subject), std::move(predicate), std::move(resource));
//    semsim::LibrdfStatement statement2 = statement1;
//    ASSERT_EQ(statement1, statement2);
//}

TEST_F(LibrdfStatementTests, TestMoveConstructor) {
    semsim::LibrdfStatement statement1 = LibrdfStatement(std::move(subject), std::move(predicate), std::move(resource));
    semsim::LibrdfStatement statement2 = std::move(statement1);
    std::string expected = "subject";
    std::string actual = statement2.getSubject().str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

//TEST_F(LibrdfStatementTests, TestCopyAssignment) {
//    semsim::LibrdfStatement statement1 = LibrdfStatement(std::move(subject), std::move(predicate), std::move(resource));
//    semsim::LibrdfStatement statement2 = statement1;
//    std::string actual = statement2.getSubject().str();
//    std::string expected = "subject";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}

TEST_F(LibrdfStatementTests, TestMoveAssignment) {
    semsim::LibrdfStatement statement1 = LibrdfStatement(std::move(subject), std::move(predicate), std::move(resource));
    semsim::LibrdfStatement statement2 = std::move(statement1);
    std::string actual = statement2.getSubject().str();
    std::string expected = "subject";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(LibrdfStatementTests, TestGetPredicateStr) {
    semsim::LibrdfStatement statement1 = LibrdfStatement(std::move(subject), std::move(predicate), std::move(resource));
    std::string expected = "predicate";
    std::string actual = statement1.getPredicate().str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

