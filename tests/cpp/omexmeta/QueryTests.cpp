//
// Created by Ciaran on 4/28/2020.
//


#include "AnnotationSamples.h"
#include "SBMLFactory.h"
#include "omexmeta/Query.h"
#include "omexmeta/RDF.h"
#include "omexmeta/Triples.h"
#include <gtest/gtest.h>
#include <librdf.h>

class QueryTests : public ::testing::Test {

public:
    AnnotationSamples samples;
    omexmeta::RDF rdf;

    std::string q;

    QueryTests() {
        rdf = omexmeta::RDF::fromString(samples.singular_annotation2);

        q = "SELECT ?x ?y ?z \n"
            "WHERE {\n"
            "  ?x ?y ?z \n"
            "}\n";
    };

    ~QueryTests() {
        //        model.freeModel();
    }
};


TEST_F(QueryTests, TestStr) {
    omexmeta::Query query(rdf.getModel(), q);
    std::string actual = query.resultsAsStr("csv");
    std::cout << actual << std::endl;
    std::string expected = "x,y,z\n"
                           "http://omex-library.org/NewOmex.omex/NewModel.xml#modelmeta1,http://biomodels.net/model-qualifiers/isDescribedBy,https://identifiers.org/pubmed/12991237\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    query.freeQuery();
}

TEST_F(QueryTests, TestRunQueryTwice) {
    omexmeta::Query query(rdf.getModel(), q);// runs the first time automatically
    query.runQuery();                        // now run again
    std::string actual = query.resultsAsStr("csv");
    std::cout << actual << std::endl;
    std::string expected = "x,y,z\n"
                           "http://omex-library.org/NewOmex.omex/NewModel.xml#modelmeta1,http://biomodels.net/model-qualifiers/isDescribedBy,https://identifiers.org/pubmed/12991237\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    query.freeQuery();
}

TEST_F(QueryTests, TestgetResultsAsMap) {
    omexmeta::Query query(rdf.getModel(), q);
    omexmeta::ResultsMap resultsMap = query.resultsAsMap();
    std::string expected = "http://biomodels.net/model-qualifiers/isDescribedBy";
    std::string actual = resultsMap["y"][0];
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    query.freeQuery();
}

TEST_F(QueryTests, BindingNotUsed) {
    std::cout << __FILE__<<":"<<__LINE__<<std::endl;
    std::string queryString = "SELECT ?x ?y ?z \n"
                              "WHERE {\n"
                              "  ?x <http://biomodels.net/model-qualifiers/isDescribedBy> ?z \n"
//                              "  ?x ?y ?z \n"
                              "}\n";
    std::cout << __FILE__<<":"<<__LINE__<<std::endl;
    omexmeta::Query query(rdf.getModel(), queryString);
    std::cout << __FILE__<<":"<<__LINE__<<std::endl;
    omexmeta::ResultsMap resultsMap = query.resultsAsMap();
    std::cout << __FILE__<<":"<<__LINE__<<std::endl;
    std::string expected = "http://biomodels.net/model-qualifiers/isDescribedBy";
    std::cout << __FILE__<<":"<<__LINE__<<std::endl;
    std::string actual = resultsMap["y"][0];
    std::cout << __FILE__<<":"<<__LINE__<<std::endl;
    ASSERT_STREQ("", actual.c_str());
    query.freeQuery();
}

TEST_F(QueryTests, TestgetResultsAsMapTwice) {
    omexmeta::Query query(rdf.getModel(), q);
    omexmeta::ResultsMap resultsMap = query.resultsAsMap();
    omexmeta::ResultsMap resultsMap2 = query.resultsAsMap();
    std::string expected = "http://biomodels.net/model-qualifiers/isDescribedBy";
    std::string actual = resultsMap["y"][0];
    ASSERT_STREQ(expected.c_str(), actual.c_str());
    query.freeQuery();
}

TEST_F(QueryTests, TestResultsAsStream) {
    omexmeta::Query query(rdf.getModel(), q);
    librdf_stream *stream = query.resultsAsLibRdfStream();
    ASSERT_TRUE(stream);// aka not null
    librdf_free_stream(stream);
    query.freeQuery();
}
