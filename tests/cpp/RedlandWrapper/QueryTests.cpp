//
// Created by Ciaran on 06/08/2021.
//
#include "iostream"
#include "redland/LibrdfQuery.h"
#include "redland/LibrdfWorld.h"
#include "gtest/gtest.h"

using namespace redland;

class QueryTests : public ::testing::Test {

public:
    std::string query_string = "SELECT ?x ?y ?z \n"
                               "WHERE {?x ?y ?z}";

    QueryTests() = default;
};

























