//
// Created by Ciaran on 5/17/2020.
//
#include "gtest/gtest.h"
#include "World.h"
#include "LibrdfQuery.h"
#include "iostream"

using namespace semsim;

class LibrdfQueryTests : public ::testing::Test {

public:

    std::string query_string = "SELECT ?x ?y ?z \n"
                               "WHERE {?x ?y ?z}";

    LibrdfQueryTests() = default;

};

TEST_F(LibrdfQueryTests, TestInstantiateQuery) {
    semsim::LibrdfQuery query1 = LibrdfQuery(query_string);
    ASSERT_NE(query1.get(), nullptr);
}


TEST_F(LibrdfQueryTests, TestMoveConstructor) {
    semsim::LibrdfQuery query1 = LibrdfQuery(query_string);
    auto query1_int_ptr = reinterpret_cast<std::uintptr_t>(query1.get());
    semsim::LibrdfQuery query2 = std::move(query1);
    auto query2_int_ptr = reinterpret_cast<std::uintptr_t>(query2.get());
    ASSERT_EQ(query1.get(), nullptr);
    ASSERT_EQ(query1_int_ptr, query2_int_ptr);
}

TEST_F(LibrdfQueryTests, TestMoveAssignment) {
    semsim::LibrdfQuery query1 = LibrdfQuery(query_string);
    auto query1_int_ptr = reinterpret_cast<std::uintptr_t>(query1.get());
    semsim::LibrdfQuery query2 = LibrdfQuery(query_string);
    auto query2_int_ptr = reinterpret_cast<std::uintptr_t>(query2.get());
    query1 = std::move(query2);
    ASSERT_NE(query1_int_ptr, query2_int_ptr);
    ASSERT_EQ(query2.get(), nullptr);
}















