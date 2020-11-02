//
// Created by Ciaran on 5/17/2020.
//

#include "gtest/gtest.h"
#include "redland/LibrdfModel.h"

using namespace redland;

class LibrdfModelTests : public ::testing::Test {

public:
    LibrdfStorage storage1 = LibrdfStorage();
    LibrdfStorage storage2 = LibrdfStorage();

    LibrdfModelTests() = default;

    ~LibrdfModelTests() {
        storage1.freeStorage();
        storage2.freeStorage();
    }

};

TEST_F(LibrdfModelTests, TestNew) {
    LibrdfModel model1 = LibrdfModel(storage1.get());
    ASSERT_NE(model1.get(), nullptr);
    model1.freeModel();
}


TEST_F(LibrdfModelTests, TestMoveConstructor) {
    LibrdfModel model1 = LibrdfModel(storage1.get());
    auto model1_int_ptr = reinterpret_cast<std::uintptr_t>(model1.get());
    LibrdfModel model2 = std::move(model1);
    auto model2_int_ptr = reinterpret_cast<std::uintptr_t>(model2.get());
    ASSERT_EQ(model1_int_ptr, model2_int_ptr);
    model2.freeModel();
}

TEST_F(LibrdfModelTests, TestMoveAssignment) {
    LibrdfModel model1 = LibrdfModel(storage1.get());
    // get ptr as int to store for comparison later:
    auto model1_int_ptr = reinterpret_cast<std::uintptr_t>(model1.get());
    LibrdfModel model2 = LibrdfModel(storage2.get());
    model2 = std::move(model1);
    auto model2_int_ptr = reinterpret_cast<std::uintptr_t>(model2.get());
    ASSERT_EQ(model1_int_ptr, model2_int_ptr);
    model2.freeModel();
}


TEST_F(LibrdfModelTests, TestAddStatement) {
    auto model1 = LibrdfModel(storage1.get());
    LibrdfStatement statement = LibrdfStatement::fromRawNodePtrs(
            LibrdfNode::fromUriString("subject").get(),
            LibrdfNode::fromUriString("predicate").get(),
            LibrdfNode::fromUriString("resource").get()
    );
    model1.addStatement(statement.get());
    int expected = 1;
    int actual = model1.size();
    ASSERT_EQ(expected, actual);
    model1.freeModel();
    statement.freeStatement();
}

TEST_F(LibrdfModelTests, TestRemoveStatement) {
    LibrdfModel model1 = LibrdfModel(storage1.get());
    LibrdfStatement statement1 = LibrdfStatement::fromRawNodePtrs(
            LibrdfNode::fromUriString("subject1").get(),
            LibrdfNode::fromUriString("predicate1").get(),
            LibrdfNode::fromUriString("resource1").get()
    );
    model1.addStatement(statement1.get());

    LibrdfStatement statement2 = LibrdfStatement::fromRawNodePtrs(
            LibrdfNode::fromUriString("subject2").get(),
            LibrdfNode::fromUriString("predicate2").get(),
            LibrdfNode::fromUriString("resource2").get()
    );
    model1.addStatement(statement2.get());
//    librdf_model_remove_statement(model1.get(), statement2.get());
    model1.removeStatement(statement2);
    int expected = 1;
    int actual = model1.size();
    ASSERT_EQ(expected, actual);
    model1.freeModel();
    statement1.freeStatement();
    statement2.freeStatement();
}

TEST_F(LibrdfModelTests, TestContext) {
    LibrdfStorage storage;
    LibrdfModel model(storage.get());
    ASSERT_FALSE(model.supportsContexts());
    model.freeModel();
    storage.freeStorage();
}


TEST_F(LibrdfModelTests, containsPass) {
    LibrdfStatement statement1 = LibrdfStatement::fromRawNodePtrs(
            LibrdfNode::fromUriString("subject1").get(),
            LibrdfNode::fromUriString("predicate1").get(),
            LibrdfNode::fromUriString("resource1").get()
    );

    auto model1 = LibrdfModel(storage1.get());
    model1.addStatement(statement1.get());

    ASSERT_TRUE(model1.containsStatement(statement1.get()));
    ASSERT_TRUE(model1.containsStatement(statement1.get()));
    model1.freeModel();
    statement1.freeStatement();
}

TEST_F(LibrdfModelTests, containsFail) {
    LibrdfStatement statement1 = LibrdfStatement::fromRawNodePtrs(
            LibrdfNode::fromUriString("subject1").get(),
            LibrdfNode::fromUriString("predicate1").get(),
            LibrdfNode::fromUriString("resource1").get()
    );
    LibrdfStatement statement2 = LibrdfStatement::fromRawNodePtrs(
            LibrdfNode::fromUriString("subject2").get(),
            LibrdfNode::fromUriString("predicate2").get(),
            LibrdfNode::fromUriString("resource2").get()
    );

    LibrdfModel model1 = LibrdfModel(storage1.get());
    model1.addStatement(statement1.get());
    ASSERT_EQ(1, model1.size());

    ASSERT_TRUE(model1.containsStatement(statement1.get()));
//    ASSERT_FALSE(model1.containsStatement(statement2));
    ASSERT_FALSE(model1.containsStatement(statement2.get()));

    model1.freeModel();
    statement1.freeStatement();
    statement2.freeStatement();
}


TEST_F(LibrdfModelTests, Equality1Pass) {
    LibrdfStatement statement1 = LibrdfStatement::fromRawNodePtrs(
            LibrdfNode::fromUriString("subject1").get(),
            LibrdfNode::fromUriString("predicate1").get(),
            LibrdfNode::fromUriString("resource1").get()
    );

    LibrdfStatement statement2 = LibrdfStatement::fromRawNodePtrs(
            LibrdfNode::fromUriString("subject2").get(),
            LibrdfNode::fromUriString("predicate2").get(),
            LibrdfNode::fromUriString("resource2").get()
    );

    auto model1 = LibrdfModel(storage1.get());
    auto model2 = LibrdfModel(storage2.get());
    model1.addStatement(statement1.get());
    model1.addStatement(statement2.get());
    model2.addStatement(statement1.get());
    model2.addStatement(statement2.get());

    ASSERT_TRUE(model1 == model2);
    statement1.freeStatement();
    statement2.freeStatement();
    model1.freeModel();
    model2.freeModel();
}

TEST_F(LibrdfModelTests, Equality1Blanks) {
    // subject1 and subject2 are blank identifiers and not used in the comparison.
    LibrdfStatement statement1 = LibrdfStatement::fromRawNodePtrs(
            LibrdfNode::fromBlank("subject1").get(),
            LibrdfNode::fromUriString("predicate1").get(),
            LibrdfNode::fromUriString("resource1").get()
    );

    LibrdfStatement statement2 = LibrdfStatement::fromRawNodePtrs(
            LibrdfNode::fromBlank("subject2").get(),
            LibrdfNode::fromUriString("predicate2").get(),
            LibrdfNode::fromUriString("resource2").get()
    );

    auto model1 = LibrdfModel(storage1.get());
    auto model2 = LibrdfModel(storage2.get());
    model1.addStatement(statement1.get());
    model1.addStatement(statement2.get());
    model2.addStatement(statement1.get());
    model2.addStatement(statement2.get());

    ASSERT_TRUE(model1 == model2);
    model1.freeModel();
    model2.freeModel();
    statement1.freeStatement();
    statement2.freeStatement();
}

TEST_F(LibrdfModelTests, Equality1Fail) {
    LibrdfStatement statement1 = LibrdfStatement::fromRawNodePtrs(
            LibrdfNode::fromUriString("subject1").get(),
            LibrdfNode::fromUriString("predicate1").get(),
            LibrdfNode::fromUriString("resource1").get()
    );

    LibrdfStatement statement2 = LibrdfStatement::fromRawNodePtrs(
            LibrdfNode::fromUriString("subject2").get(),
            LibrdfNode::fromUriString("predicate2").get(),
            LibrdfNode::fromUriString("resource2").get()
    );

    LibrdfStatement statement3 = LibrdfStatement::fromRawNodePtrs(
            LibrdfNode::fromUriString("subject3").get(),
            LibrdfNode::fromUriString("predicate3").get(),
            LibrdfNode::fromUriString("resource3").get()
    );

    LibrdfModel model1 = LibrdfModel(storage1.get());
    LibrdfModel model2 = LibrdfModel(storage2.get());
    model1.addStatement(statement1.get());
    model1.addStatement(statement3.get());
    model2.addStatement(statement1.get());
    model2.addStatement(statement2.get());

    ASSERT_FALSE(model1 == model2);
    model1.freeModel();
    statement1.freeStatement();
    statement2.freeStatement();
    statement3.freeStatement();
}



