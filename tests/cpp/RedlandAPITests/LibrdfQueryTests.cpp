//
// Created by Ciaran on 5/17/2020.
//
#include "gtest/gtest.h"
#include "semsim/RedlandAPIWrapper/LibrdfWorld.h"
#include "semsim/RedlandAPIWrapper/LibrdfQuery.h"
#include "iostream"

class LibrdfQueryTests : public ::testing::Test {

public:

    std::string query_string = "SELECT ?x ?y ?z \n"
                               "WHERE {?x ?y ?z}";

    LibrdfQueryTests() = default;

};

TEST_F(LibrdfQueryTests, TestInstantiateQuery) {
    semsim::LibrdfWorld world;
    semsim::LibrdfQuery query1 = world.newQuery(query_string);
    ASSERT_NE(query1.get(), nullptr);
}

TEST_F(LibrdfQueryTests, TestCopyConstructor) {
    semsim::LibrdfWorld world;
    semsim::LibrdfQuery query1 = world.newQuery(query_string);
    semsim::LibrdfQuery query2 = query1;
    ASSERT_EQ(query1, query2);
}

TEST_F(LibrdfQueryTests, TestCopyAssignment) {
    semsim::LibrdfWorld world;
    semsim::LibrdfQuery query1 = world.newQuery(query_string);
    semsim::LibrdfQuery query2 = world.newQuery(query_string);
    query2 = query1;
    ASSERT_EQ(query1, query2);
}


TEST_F(LibrdfQueryTests, TestMoveConstructor) {
    semsim::LibrdfWorld world;
    semsim::LibrdfQuery query1 = world.newQuery(query_string);
    auto query1_int_ptr = reinterpret_cast<std::uintptr_t>(query1.get());
    semsim::LibrdfQuery query2 = std::move(query1);
    auto query2_int_ptr = reinterpret_cast<std::uintptr_t>(query2.get());
    ASSERT_EQ(query1.getQuery(), nullptr);
    ASSERT_EQ(query1_int_ptr, query2_int_ptr);
}

TEST_F(LibrdfQueryTests, TestMoveAssignment) {
    semsim::LibrdfWorld world;
    semsim::LibrdfQuery query1 = world.newQuery(query_string);
    auto query1_int_ptr = reinterpret_cast<std::uintptr_t>(query1.get());
    semsim::LibrdfQuery query2 = world.newQuery(query_string);
    auto query2_int_ptr = reinterpret_cast<std::uintptr_t>(query2.get());
    query1 = std::move(query2);
    ASSERT_NE(query1_int_ptr, query2_int_ptr);
    ASSERT_EQ(query2.getQuery(), nullptr);
}















