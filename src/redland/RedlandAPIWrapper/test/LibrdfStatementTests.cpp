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
    librdf_node* subject = LibrdfNode::fromUriString("subject");
    librdf_node* predicate = LibrdfNode::fromUriString("predicate");
    librdf_node* resource = LibrdfNode::fromUriString("resource");

    LibrdfStatementTests() = default;
};

TEST_F(LibrdfStatementTests, TestCreate) {
    redland::LibrdfStatement statement = LibrdfStatement::fromRawNodePtrs(
            subject,
            predicate,
            resource
    );

    ASSERT_NE(statement.get(), nullptr);

}

//TEST_F(LibrdfStatementTests, TestCopyConstructor) {
//    redland::LibrdfStatement statement1 = LibrdfStatement(std::move(subject), std::move(predicate), std::move(resource));
//    redland::LibrdfStatement statement2 = statement1;
//    ASSERT_EQ(statement1, statement2);
//}

//TEST_F(LibrdfStatementTests, TestMoveConstructor) {
//    redland::LibrdfStatement statement1 = LibrdfStatement(std::move(subject), std::move(predicate),
//                                                          std::move(resource));
//    redland::LibrdfStatement statement2 = std::move(statement1);
//    std::string expected = "subject";
//    std::string actual = statement2.getSubject().str();
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}

//TEST_F(LibrdfStatementTests, TestCopyAssignment) {
//    redland::LibrdfStatement statement1 = LibrdfStatement(std::move(subject), std::move(predicate), std::move(resource));
//    redland::LibrdfStatement statement2 = statement1;
//    std::string actual = statement2.getSubject().str();
//    std::string expected = "subject";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}

//TEST_F(LibrdfStatementTests, TestMoveAssignment) {
//    redland::LibrdfStatement statement1 = LibrdfStatement(std::move(subject), std::move(predicate),
//                                                          std::move(resource));
//    redland::LibrdfStatement statement2 = std::move(statement1);
//    std::string actual = statement2.getSubject().str();
//    std::string expected = "subject";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//}


TEST_F(LibrdfStatementTests, TestGetPredicateStr) {
    redland::LibrdfStatement statement1 = LibrdfStatement::fromRawNodePtrs(std::move(subject), std::move(predicate),
                                                          std::move(resource));
    std::string expected = "predicate";
    std::string actual = statement1.getPredicateStr();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(LibrdfStatementTests, TestToStatementSubject) {
    LibrdfStatement statement = LibrdfStatement::fromRawNodePtrs(
            std::move(subject), std::move(predicate), std::move(resource));
    std::string actual = statement.getSubjectStr();
    std::string expected = "subject";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(LibrdfStatementTests, TestPartial1) {
    LibrdfStatement statement;
    statement.setSubject(subject);
    std::string actual = statement.getSubjectStr();
    std::string expected = "subject";
    ASSERT_STREQ(expected.c_str(), actual.c_str());

    librdf_free_node(predicate);
    librdf_free_node(resource);
}





















