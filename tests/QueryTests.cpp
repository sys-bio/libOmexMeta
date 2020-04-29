//
// Created by Ciaran on 4/28/2020.
//


#include <librdf.h>
#include <gtest/gtest.h>
#include <semsim/RDF.h>
#include <semsim/Triples.h>
#include "SBMLFactory.h"
#include "AnnotationSamples.h"
#include "semsim/Query.h"

class QueryTests : public ::testing::Test {

public:

    AnnotationSamples samples;

    librdf_world *world;
    raptor_world *raptorWorld;
    librdf_storage *storage;
    librdf_model *model;

    semsim::RDF rdf;
    semsim::RDF rdf2;
    semsim::RDF rdf3;

    std::string q;

    QueryTests() {
        auto initializer = semsim::RDF::init();
        world = std::get<0>(initializer);
        raptorWorld = std::get<1>(initializer);
        storage = std::get<2>(initializer);
        model = std::get<3>(initializer);

        rdf = semsim::RDF::fromString(
                samples.singular_annotation2
        );

        rdf2 = semsim::RDF::fromString(
                samples.singular_annotation4
        );


        rdf3 = semsim::RDF::fromString(
                samples.composite_annotation_pe
        );

        q = "SELECT ?x ?y ?z \n"
            "WHERE {\n"
            "  ?x ?y ?z \n"
            "}\n";
    };
};


TEST_F(QueryTests, TestgetResultsAsMap) {
    semsim::Query query(rdf3.getWorld(), rdf3.getModel(), q);
    semsim::ResultsMap resultsMap = query.resultsAsMap();
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    std::string actual = resultsMap["y"][2];
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(QueryTests, TestgetResultsAsTriples) {
    semsim::Query query(rdf3.getWorld(), rdf3.getModel(), q);
    semsim::Triples triples = query.resultsAsTriples();

}


TEST_F(QueryTests, TestStr){
    semsim::Query query(rdf.getWorld(), rdf.getModel(), q);
    std::string actual  = query.resultAsStr("csv");
    std::string expected = "x,y,z\r\n"
                           "file://./MyModel.xml#modelmeta1,http://biomodels.net/model-qualifiers/isDescribedBy,https://identifiers.org/pubmed/12991237\r\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}












