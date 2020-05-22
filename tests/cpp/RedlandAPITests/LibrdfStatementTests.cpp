//
// Created by Ciaran on 5/17/2020.
//

#include "gtest/gtest.h"
#include "semsim/RedlandAPIWrappers/LibrdfWorld.h"
#include "semsim/RedlandAPIWrappers/LibrdfStatement.h"
#include "semsim/SemsimUtils.h"

class LibrdfStatementTests : public ::testing::Test {

public:
    semsim::LibrdfWorld world;
    semsim::LibrdfNode subject = world.newNodeUriString("subject");
    semsim::LibrdfNode predicate = world.newNodeUriString("predicate");
    semsim::LibrdfNode resource = world.newNodeUriString("resource");

    LibrdfStatementTests() = default;

};

TEST_F(LibrdfStatementTests, TestCreate) {
    semsim::LibrdfStatement statement = world.newStatementFromNodes(subject, predicate, resource);
    ASSERT_TRUE(true);
}

TEST_F(LibrdfStatementTests, TestCopyConstructor) {
    semsim::LibrdfStatement statement1 = world.newStatementFromNodes(subject, predicate, resource);
    semsim::LibrdfStatement statement2 = statement1;
    ASSERT_EQ(statement1, statement2);
}

TEST_F(LibrdfStatementTests, TestMoveConstructor) {
    semsim::LibrdfStatement statement1 = world.newStatementFromNodes(subject, predicate, resource);
    semsim::LibrdfStatement statement2 = std::move(statement1);
    std::string expected = "subject";
    semsim::LibrdfNode node = statement2.getSubjectNode();
    std::string actual = node.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfStatementTests, TestCopyAssignment) {
    semsim::LibrdfStatement statement1 = world.newStatementFromNodes(subject, predicate, resource);
    semsim::LibrdfStatement statement2 = statement1;
    std::string actual = statement2.getSubjectNode().str();
    std::string expected = "subject";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfStatementTests, TestMoveAssignment) {
    semsim::LibrdfStatement statement1 = world.newStatementFromNodes(subject, predicate, resource);
    semsim::LibrdfStatement statement2 = std::move(statement1);
    std::string actual = statement2.getSubjectNode().str();
    std::string expected = "subject";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(LibrdfStatementTests, TestGetPredicateStr) {
    semsim::LibrdfStatement statement1 = world.newStatementFromNodes(subject, predicate, resource);
    std::string expected = "predicate";
    std::string actual = statement1.getPredicateNode().str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

