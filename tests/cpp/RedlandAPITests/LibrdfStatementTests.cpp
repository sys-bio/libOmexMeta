//
// Created by Ciaran on 5/17/2020.
//

#include "gtest/gtest.h"
#include "semsim/RedlandAPIWrappers/LibrdfWorld.h"
#include "semsim/RedlandAPIWrappers/LibrdfStatement.h"
#include "semsim/SemsimUtils.h"

class LibrdfStatementTests : public ::testing::Test {

public:

    LibrdfStatementTests() = default;

};

TEST_F(LibrdfStatementTests, TestGetSubject) {

    semsim::LibrdfWorld world;
    semsim::LibrdfStatement statement1 = world.newStatementFromNodes(
            world.newNodeUriString("subject"),
            world.newNodeUriString("predicate"),
            world.newNodeUriString("resource")
    );
    HERE();
    std::string actual = statement1.getSubjectNode().str();
    HERE();
    ASSERT_EQ("subject", actual.c_str());
    HERE();
}

TEST_F(LibrdfStatementTests, TestGetPredicate) {
    semsim::LibrdfWorld world;
    semsim::LibrdfNode subject = world.newNodeUriString("subject");
    semsim::LibrdfNode predicate = world.newNodeUriString("predicate");
    semsim::LibrdfNode resource = world.newNodeUriString("resource");
    semsim::LibrdfStatement statement1 = world.newStatementFromNodes(
            subject, predicate, resource
    );
    HERE();
    statement1.getPredicateNode().str();
//    semsim::LibrdfNode predicate_out = statement1.getPredicateNode();
//    HERE();
//    predicate_out.str();
    HERE();


    ASSERT_EQ("predicate", statement1.getPredicateNode().str());
}

TEST_F(LibrdfStatementTests, TestGetObject) {
    semsim::LibrdfWorld world;
    semsim::LibrdfStatement statement1 = world.newStatementFromNodes(
            world.newNodeUriString("subject"),
            world.newNodeUriString("predicate"),
            world.newNodeUriString("resource")
    );
    ASSERT_EQ("resource", statement1.getObjectNode().str());
}

TEST_F(LibrdfStatementTests, TestCopyConstructor) {
    semsim::LibrdfWorld world;
    semsim::LibrdfStatement statement1 = world.newStatementFromNodes(
            world.newNodeUriString("subject"),
            world.newNodeUriString("predicate"),
            world.newNodeUriString("resource")
    );
    semsim::LibrdfStatement statement2 = statement1;
    ASSERT_EQ(statement1, statement2);
}

//TEST_F(LibrdfStatementTests, TestCopyAssignment) {
//    semsim::LibrdfWorld world;
//    semsim::LibrdfStorage storage1 = world.newStorage("memory", "semsim_store1");
//    semsim::LibrdfStatement statement1 = world.newStatement(storage1);
//    auto statement1_ptr_int = reinterpret_cast<std::uintptr_t>(*statement1.getStatement());
//    semsim::LibrdfStatement statement2 = world.newStatement(storage1);
//    auto statement2_ptr_int_before = reinterpret_cast<std::uintptr_t>(*statement2.getStatement());
//    ASSERT_NE(statement1_ptr_int, statement2_ptr_int_before);
//    statement2 = statement1;
//    auto statement2_ptr_int_after = reinterpret_cast<std::uintptr_t>(*statement2.getStatement());
//    ASSERT_EQ(statement1_ptr_int, statement2_ptr_int_after);
//}
//
//
//TEST_F(LibrdfStatementTests, TestMoveConstructor) {
//    semsim::LibrdfWorld world;
//    semsim::LibrdfStorage storage1 = world.newStorage("memory", "semsim_store1");
//    semsim::LibrdfStatement statement1 = world.newStatement(storage1);
//    auto statement1_int_ptr = reinterpret_cast<std::uintptr_t>(*statement1.getStatement());
//    semsim::LibrdfStatement statement2 = std::move(statement1);
//    auto statement2_int_ptr = reinterpret_cast<std::uintptr_t>(*statement2.getStatement());
//    ASSERT_EQ(statement1_int_ptr, statement2_int_ptr);
//}
//
//TEST_F(LibrdfStatementTests, TestMoveAssignment) {
//    semsim::LibrdfWorld world;
//    // storage to statement is 1:1
//    semsim::LibrdfStorage storage1 = world.newStorage("memory", "semsim_store1");
//    semsim::LibrdfStorage storage2 = world.newStorage("memory", "semsim_store2");
//    semsim::LibrdfStatement statement1 = world.newStatement(storage1);
//    auto statement1_int_ptr = reinterpret_cast<std::uintptr_t>(*statement1.getStatement());
//    semsim::LibrdfStatement statement2 = world.newStatement(storage2);
//    statement2 = std::move(statement1);
//    auto statement2_int_ptr = reinterpret_cast<std::uintptr_t>(*statement2.getStatement());
//    ASSERT_EQ(statement1_int_ptr, statement2_int_ptr);
//}




