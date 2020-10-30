//
// Created by Ciaran on 5/17/2020.
//
#include "redland/LibrdfStorage.h"
#include "redland/LibrdfModel.h"
#include "redland/LibrdfNode.h"
#include "redland/LibrdfStatement.h"
#include "redland/LibrdfQuery.h"
#include "gtest/gtest.h"
#include "redland/World.h"
#include "redland/LibrdfQueryResults.h"
#include "iostream"


using namespace redland;

class LibrdfQueryResultsTests : public ::testing::Test {

public:

    std::string query_string = "SELECT ?x ?y ?z \n"
                               "WHERE {?x ?y ?z}";
    LibrdfStorage storage;
    LibrdfModel model = LibrdfModel(storage.get());
    LibrdfNode subject = LibrdfNode::fromUriString("subject");
    LibrdfNode predicate = LibrdfNode::fromUriString("predicate");
    LibrdfNode resource = LibrdfNode::fromUriString("resource");
    LibrdfQuery query1;
    LibrdfQuery query2;
    LibrdfStatement statement;

    LibrdfQueryResultsTests() {
        statement = LibrdfStatement(subject, predicate, resource);
        query1 = LibrdfQuery(query_string);
        query2 = LibrdfQuery(query_string);
        model.addStatement(statement.get());
    };

};

TEST_F(LibrdfQueryResultsTests, TestInstantiateQueryResults) {
    LibrdfQueryResults results = model.query(std::move(query1));
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
    LibrdfQueryResults results1 = model.query(query1);
    auto query_int_ptr1 = reinterpret_cast<std::uintptr_t>(results1.get());
    LibrdfQueryResults results2 = std::move(results1);
    auto query_int_ptr2 = reinterpret_cast<std::uintptr_t>(results2.get());
    ASSERT_EQ(query_int_ptr1, query_int_ptr2);

}

TEST_F(LibrdfQueryResultsTests, TestMoveAssignment) {
    LibrdfQueryResults results1 = model.query(std::move(query1));
    auto query_int_ptr1 = reinterpret_cast<std::uintptr_t>(query1.get());
    LibrdfQueryResults results2 = model.query(std::move(query2));
    auto query_int_ptr2 = reinterpret_cast<std::uintptr_t>(results2.get());
    results2 = std::move(results1);
    ASSERT_NE(query_int_ptr1, query_int_ptr2);
    ASSERT_EQ(results1.get(), nullptr);
}















