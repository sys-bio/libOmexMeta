//
// Created by Ciaran on 5/17/2020.
//

#include "gtest/gtest.h"
#include "redland/LibrdfModel.h"

using namespace redland;

class LibrdfModelTests : public ::testing::Test {

public:
    LibrdfStorage storage1;
    LibrdfStorage storage2;

    LibrdfModelTests() = default;

    ~LibrdfModelTests() override = default;

};

TEST_F(LibrdfModelTests, TestNew) {
    LibrdfModel model1 = LibrdfModel(storage1);
    // get as an R value would be a memory leak, so we avoid incrementing the usage count.
    ASSERT_NE(model1.getWithoutIncrement(), nullptr);
}


TEST_F(LibrdfModelTests, TestMoveConstructor) {
    // test with valgrind
    LibrdfModel model1 = LibrdfModel(storage1);
    LibrdfModel model2 = std::move(model1);
    ASSERT_EQ(1, model2.getUsage());
}

TEST_F(LibrdfModelTests, TestMoveAssignment) {
    // test with valgrind
    LibrdfModel model1(storage1);
    LibrdfModel model2(storage2);
    model2 = std::move(model1);
    ASSERT_EQ(1, model2.getUsage());
}


TEST_F(LibrdfModelTests, TestAddStatement) {
    auto model1 = LibrdfModel(storage1);
    LibrdfStatement statement = LibrdfStatement(
            LibrdfNode::fromUriString("subject"),
            LibrdfNode::fromUriString("predicate"),
            LibrdfNode::fromUriString("resource")
    );
    model1.addStatement(statement);
    int expected = 1;
    int actual = model1.size();
    ASSERT_EQ(expected, actual);
}

TEST_F(LibrdfModelTests, TestRemoveStatement) {
    LibrdfModel model1 = LibrdfModel(storage1);
    LibrdfStatement statement1 = LibrdfStatement(
            LibrdfNode::fromUriString("subject1"),
            LibrdfNode::fromUriString("predicate1"),
            LibrdfNode::fromUriString("resource1")
    );
    model1.addStatement(statement1);

    LibrdfStatement statement2 = LibrdfStatement(
            LibrdfNode::fromUriString("subject2"),
            LibrdfNode::fromUriString("predicate2"),
            LibrdfNode::fromUriString("resource2")
    );
    model1.addStatement(statement2);
//    librdf_model_remove_statement(model1, statement2);
    model1.removeStatement(statement2);
    int expected = 1;
    int actual = model1.size();
    ASSERT_EQ(expected, actual);
}

TEST_F(LibrdfModelTests, TestContext) {
    LibrdfStorage storage;
    LibrdfModel model(storage);
    ASSERT_FALSE(model.supportsContexts());
}


TEST_F(LibrdfModelTests, containsPass) {
    LibrdfStatement statement1 = LibrdfStatement(
            LibrdfNode::fromUriString("subject1"),
            LibrdfNode::fromUriString("predicate1"),
            LibrdfNode::fromUriString("resource1")
    );

    auto model1 = LibrdfModel(storage1);
    model1.addStatement(statement1);

    ASSERT_TRUE(model1.containsStatement(statement1));
}

TEST_F(LibrdfModelTests, containsFail) {
    LibrdfStatement statement1 = LibrdfStatement(
            LibrdfNode::fromUriString("subject1"),
            LibrdfNode::fromUriString("predicate1"),
            LibrdfNode::fromUriString("resource1")
    );
    LibrdfStatement statement2 = LibrdfStatement(
            LibrdfNode::fromUriString("subject2"),
            LibrdfNode::fromUriString("predicate2"),
            LibrdfNode::fromUriString("resource2")
    );

    LibrdfModel model1 = LibrdfModel(storage1);
    model1.addStatement(statement1);
    ASSERT_EQ(1, model1.size());

    ASSERT_TRUE(model1.containsStatement(statement1));
    ASSERT_FALSE(model1.containsStatement(statement2));
}


TEST_F(LibrdfModelTests, Equality1Pass) {
    LibrdfStatement statement1 = LibrdfStatement(
            LibrdfNode::fromUriString("subject1"),
            LibrdfNode::fromUriString("predicate1"),
            LibrdfNode::fromUriString("resource1")
    );

    LibrdfStatement statement2 = LibrdfStatement(
            LibrdfNode::fromUriString("subject2"),
            LibrdfNode::fromUriString("predicate2"),
            LibrdfNode::fromUriString("resource2")
    );

    auto model1 = LibrdfModel(storage1);
    auto model2 = LibrdfModel(storage2);
    model1.addStatement(statement1);
    model1.addStatement(statement2);
    model2.addStatement(statement1);
    model2.addStatement(statement2);

    ASSERT_TRUE(model1 == model2);
}

TEST_F(LibrdfModelTests, Equality1Blanks) {
    // subject1 and subject2 are blank identifiers and not used in the comparison.
    LibrdfStatement statement1 = LibrdfStatement(
            LibrdfNode::fromBlank("subject1"),
            LibrdfNode::fromUriString("predicate1"),
            LibrdfNode::fromUriString("resource1")
    );

    LibrdfStatement statement2 = LibrdfStatement(
            LibrdfNode::fromBlank("subject2"),
            LibrdfNode::fromUriString("predicate2"),
            LibrdfNode::fromUriString("resource2")
    );

    auto model1 = LibrdfModel(storage1);
    auto model2 = LibrdfModel(storage2);
    model1.addStatement(statement1);
    model1.addStatement(statement2);
    model2.addStatement(statement1);
    model2.addStatement(statement2);

    ASSERT_TRUE(model1 == model2);
}

TEST_F(LibrdfModelTests, Equality1Fail) {
    LibrdfStatement statement1 = LibrdfStatement(
            LibrdfNode::fromUriString("subject1"),
            LibrdfNode::fromUriString("predicate1"),
            LibrdfNode::fromUriString("resource1")
    );

    LibrdfStatement statement2 = LibrdfStatement(
            LibrdfNode::fromUriString("subject2"),
            LibrdfNode::fromUriString("predicate2"),
            LibrdfNode::fromUriString("resource2")
    );

    LibrdfStatement statement3 = LibrdfStatement(
            LibrdfNode::fromUriString("subject3"),
            LibrdfNode::fromUriString("predicate3"),
            LibrdfNode::fromUriString("resource3")
    );

    LibrdfModel model1 = LibrdfModel(storage1);
    LibrdfModel model2 = LibrdfModel(storage2);
    model1.addStatement(statement1);
    model1.addStatement(statement3);
    model2.addStatement(statement1);
    model2.addStatement(statement2);

    ASSERT_FALSE(model1 == model2);
}



