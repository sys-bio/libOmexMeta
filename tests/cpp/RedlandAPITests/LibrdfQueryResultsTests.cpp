//
// Created by Ciaran on 5/17/2020.
//
#include <src/semsim/RedlandAPIWrapper/LibrdfStorage.h>
#include <src/semsim/RedlandAPIWrapper/LibrdfModel.h>
#include <src/semsim/RedlandAPIWrapper/LibrdfNode.h>
#include <src/semsim/RedlandAPIWrapper/LibrdfStatement.h>
#include <src/semsim/RedlandAPIWrapper/LibrdfQuery.h>
#include "gtest/gtest.h"
#include "semsim/RedlandAPIWrapper/World.h"
#include "semsim/RedlandAPIWrapper/LibrdfQueryResults.h"
#include "iostream"

using namespace semsim;

class LibrdfQueryResultsTests : public ::testing::Test {

public:

    std::string query_string = "SELECT ?x ?y ?z \n"
                               "WHERE {?x ?y ?z}";
    LibrdfStorage storage;
    LibrdfModel model = LibrdfModel(std::move(storage));
    LibrdfNode subject = LibrdfNode::fromUriString("subject");
    LibrdfNode predicate = LibrdfNode::fromUriString("predicate");
    LibrdfNode resource = LibrdfNode::fromUriString("resource");
    LibrdfQuery query;
    LibrdfStatement statement;

    LibrdfQueryResultsTests() {
        statement = LibrdfStatement(std::move(subject), std::move(predicate), std::move(resource));
        query = LibrdfQuery(query_string);
        model.addStatement(statement);
    };

};

TEST_F(LibrdfQueryResultsTests, TestInstantiateQueryResults) {
    LibrdfQueryResults results = model.query(std::move(query));
    ASSERT_NE(results.get(), nullptr);
}

//TEST_F(LibrdfQueryResultsTests, TestCopyConstructor) {
//    LibrdfWorld world;
//    LibrdfQueryResults query = world.newQuery(query_string);
//    LibrdfQueryResults queryResults2 = query;
//    ASSERT_EQ(query, queryResults2);
//}
//
//TEST_F(LibrdfQueryResultsTests, TestCopyAssignment) {
//    LibrdfWorld world;
//    LibrdfQueryResults query = world.newQuery(query_string);
//    LibrdfQueryResults queryResults2 = world.newQuery(query_string);
//    queryResults2 = query;
//    ASSERT_EQ(query, queryResults2);
//}
//

TEST_F(LibrdfQueryResultsTests, TestMoveConstructor) {
    LibrdfQueryResults results1 = model.query(std::move(query));
    auto query_int_ptr = reinterpret_cast<std::uintptr_t>(query.get());
    LibrdfQueryResults results2 = model.query(std::move(query));
    auto queryResults2_int_ptr = reinterpret_cast<std::uintptr_t>(results1.get());
    ASSERT_EQ(query.get(), nullptr);
    ASSERT_EQ(query_int_ptr, queryResults2_int_ptr);
}

TEST_F(LibrdfQueryResultsTests, TestMoveAssignment) {
    LibrdfQueryResults results1 = model.query(std::move(query));
    auto query_int_ptr1 = reinterpret_cast<std::uintptr_t>(query.get());
    LibrdfQueryResults results2 = model.query(std::move(query));
    auto query_int_ptr2 = reinterpret_cast<std::uintptr_t>(results1.get());
    results2 = std::move(results1);
    ASSERT_NE(query_int_ptr1, query_int_ptr2);
    ASSERT_EQ(results1.get(), nullptr);
}
//














