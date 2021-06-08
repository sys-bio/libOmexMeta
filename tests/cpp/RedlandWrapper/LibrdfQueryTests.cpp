//
// Created by Ciaran on 5/17/2020.
//
#include "iostream"
#include "redland/LibrdfQuery.h"
#include "redland/LibrdfWorld.h"
#include "gtest/gtest.h"

using namespace redland;

class LibrdfQueryTests : public ::testing::Test {

public:
    std::string query_string = "SELECT ?x ?y ?z \n"
                               "WHERE {?x ?y ?z}";

    LibrdfQueryTests() = default;
};

TEST_F(LibrdfQueryTests, TestInstantiateQuery) {
    LibrdfQuery query1 = LibrdfQuery(query_string);
    ASSERT_NE(query1.getWithoutIncrement(), nullptr);
}


TEST_F(LibrdfQueryTests, TestMoveConstructor) {
    // use valgrind
    LibrdfQuery query1 = LibrdfQuery(query_string);
    LibrdfQuery query2 = std::move(query1);
}

TEST_F(LibrdfQueryTests, TestMoveAssignment) {
    // use valgrind
    LibrdfQuery query1 = LibrdfQuery(query_string);
    LibrdfQuery query2 = LibrdfQuery(query_string);
    query1 = std::move(query2);
    //    ASSERT_NE(query1_int_ptr, query2_int_ptr);
}
