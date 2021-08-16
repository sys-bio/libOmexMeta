//
// Created by ciaran on 16/08/2021.
//
#include "AnnotationSamples.h"
#include "omexmeta/OmexMeta.h"
#include "redland/RedlandAPI.h"
#include "gtest/gtest.h"

using namespace omexmeta;
using namespace redland;

class QueryTests : public ::testing::Test {
public:
    AnnotationSamples samples;
    std::string query_string = "SELECT ?x ?y ?z \n"
                               "WHERE {?x ?y ?z }\n";
    QueryTests() = default;
};

TEST_F(QueryTests, CheckQueryResultsAsMap) {
    RDF rdf = RDF::fromString(samples.singular_annotation1, "rdfxml");
    ResultsMap results = rdf.queryResultsAsMap(query_string);
    ASSERT_EQ(3, results.size());
    ASSERT_EQ(1, results["x"].size());
    ASSERT_EQ(1, results["y"].size());
    ASSERT_EQ(1, results["z"].size());
}


TEST_F(QueryTests, CheckQueryResultsAsString) {
    RDF rdf = RDF::fromString(samples.singular_annotation1, "rdfxml");
    std::string results = rdf.queryResultsAsString(query_string, "turtle");
    // don't test string content - this is rasqals responsibility and is assume to work.
    ASSERT_TRUE(!results.empty());
}

TEST_F(QueryTests, CheckQueryResultsAsMapTwice) {
    RDF rdf = RDF::fromString(samples.singular_annotation1, "rdfxml");
    ResultsMap results1 = rdf.queryResultsAsMap(query_string);
    ResultsMap results2 = rdf.queryResultsAsMap(query_string);
}
