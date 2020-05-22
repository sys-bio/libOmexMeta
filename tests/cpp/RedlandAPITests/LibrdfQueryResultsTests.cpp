//
// Created by Ciaran on 5/17/2020.
//
#include "gtest/gtest.h"
#include "semsim/RedlandAPIWrappers/LibrdfWorld.h"
#include "semsim/RedlandAPIWrappers/LibrdfQueryResults.h"
#include "iostream"

class LibrdfQueryResultsTests : public ::testing::Test {

public:

    std::string query_string = "SELECT ?x ?y ?z \n"
                               "WHERE {?x ?y ?z}";
    semsim::LibrdfWorld world;
    semsim::LibrdfStorage storage = world.newStorage();
    semsim::LibrdfModel model = world.newModel(storage);
    semsim::LibrdfNode subject = world.newNodeUriString("subject");
    semsim::LibrdfNode predicate = world.newNodeUriString("predicate");
    semsim::LibrdfNode resource = world.newNodeUriString("resource");
    semsim::LibrdfStatement statement = world.newStatementFromNodes(
            subject, predicate, resource
    );
    semsim::LibrdfQuery query = world.newQuery(query_string);

    LibrdfQueryResultsTests() {
        model.addStatement(statement);
    };

};

TEST_F(LibrdfQueryResultsTests, TestInstantiateQueryResults) {
    semsim::LibrdfQueryResults results = model.query(query);
    ASSERT_NE(results.get(), nullptr);
}

//TEST_F(LibrdfQueryResultsTests, TestCopyConstructor) {
//    semsim::LibrdfWorld world;
//    semsim::LibrdfQueryResults query = world.newQuery(query_string);
//    semsim::LibrdfQueryResults queryResults2 = query;
//    ASSERT_EQ(query, queryResults2);
//}
//
//TEST_F(LibrdfQueryResultsTests, TestCopyAssignment) {
//    semsim::LibrdfWorld world;
//    semsim::LibrdfQueryResults query = world.newQuery(query_string);
//    semsim::LibrdfQueryResults queryResults2 = world.newQuery(query_string);
//    queryResults2 = query;
//    ASSERT_EQ(query, queryResults2);
//}
//
//
//TEST_F(LibrdfQueryResultsTests, TestMoveConstructor) {
//    semsim::LibrdfWorld world;
//    semsim::LibrdfQueryResults query = world.newQuery(query_string);
//    auto query_int_ptr = reinterpret_cast<std::uintptr_t>(query.get());
//    semsim::LibrdfQueryResults queryResults2 = std::move(query);
//    auto queryResults2_int_ptr = reinterpret_cast<std::uintptr_t>(queryResults2.get());
//    ASSERT_EQ(query.getQueryResults(), nullptr);
//    ASSERT_EQ(query_int_ptr, queryResults2_int_ptr);
//}
//
//TEST_F(LibrdfQueryResultsTests, TestMoveAssignment) {
//    semsim::LibrdfWorld world;
//    semsim::LibrdfQueryResults query = world.newQuery(query_string);
//    auto query_int_ptr = reinterpret_cast<std::uintptr_t>(query.get());
//    semsim::LibrdfQueryResults queryResults2 = world.newQuery(query_string);
//    auto queryResults2_int_ptr = reinterpret_cast<std::uintptr_t>(queryResults2.get());
//    query = std::move(queryResults2);
//    ASSERT_NE(query_int_ptr, queryResults2_int_ptr);
//    ASSERT_EQ(queryResults2.getQueryResults(), nullptr);
//}
//














