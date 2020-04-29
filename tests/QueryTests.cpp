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
    semsim::RDF rdf4;

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


TEST_F(QueryTests, TestStr) {
    semsim::Query query(rdf.getWorld(), rdf.getModel(), q);
    std::string actual = query.resultAsStr("csv");
    std::string expected = "x,y,z\r\n"
                           "file://./MyModel.xml#modelmeta1,http://biomodels.net/model-qualifiers/isDescribedBy,https://identifiers.org/pubmed/12991237\r\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(QueryTests, TestgetResultsAsMap) {
    semsim::Query query(rdf3.getWorld(), rdf3.getModel(), q);
    semsim::ResultsMap resultsMap = query.resultsAsMap();
    std::string expected = "http://biomodels.net/biology-qualifiers/is";
    std::string actual = resultsMap["y"][2];
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(QueryTests, TestgetResultsAsMapTwice) {
    semsim::Query query(rdf3.getWorld(), rdf3.getModel(), q);
    semsim::ResultsMap resultsMap = query.resultsAsMap();
    semsim::ResultsMap resultsMap2 = query.resultsAsMap();
    std::string expected = "http://biomodels.net/biology-qualifiers/isPartOf";
    std::string actual = resultsMap["y"][3];
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(QueryTests, TestResultsAsStream) {
    semsim::Query query(rdf3.getWorld(), rdf3.getModel(), q);
    librdf_stream *stream = query.resultsAsLibRdfStream();
    ASSERT_TRUE(stream); // aka not null
}

TEST_F(QueryTests, TestResultsAsRDF) {
    semsim::Query query(rdf2.getWorld(), rdf2.getModel(), q);
    semsim::RDF rdf = query.resultsAsRDF();
    std::string actual = rdf.toString("turtle", "./base.xml");
    std::string expected = "@base <file://./base.xml> .\n"
                           "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "\n"
                           "[]\n"
                           "    a <http://www.w3.org/2001/sw/DataAccess/tests/result-set#ResultSet> ;\n"
                           "    <http://www.w3.org/2001/sw/DataAccess/tests/result-set#resultVariable> \"x\", \"y\", \"z\" ;\n"
                           "    <http://www.w3.org/2001/sw/DataAccess/tests/result-set#solution> [\n"
                           "        <http://www.w3.org/2001/sw/DataAccess/tests/result-set#binding> [\n"
                           "            <http://www.w3.org/2001/sw/DataAccess/tests/result-set#value> <MyModel.xml#meta2> ;\n"
                           "            <http://www.w3.org/2001/sw/DataAccess/tests/result-set#variable> \"x\"\n"
                           "        ], [\n"
                           "            <http://www.w3.org/2001/sw/DataAccess/tests/result-set#value> <http://purl.org/dc/terms/description> ;\n"
                           "            <http://www.w3.org/2001/sw/DataAccess/tests/result-set#variable> \"y\"\n"
                           "        ], [\n"
                           "            <http://www.w3.org/2001/sw/DataAccess/tests/result-set#value> \"Cardiomyocyte cytosolic ATP concentration\" ;\n"
                           "            <http://www.w3.org/2001/sw/DataAccess/tests/result-set#variable> \"z\"\n"
                           "        ]\n"
                           "    ] .\n"
                           "\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(QueryTests, TestgetResultsAsTriples) {
    semsim::Query query(rdf3.getWorld(), rdf3.getModel(), q);
    semsim::Triples triples = query.resultsAsTriples();
    std::ostringstream actual;
    for (auto &it : triples) {
        actual << it.getSubject().str() << std::endl;
    }
    std::string expected = "asdf";
    ASSERT_STREQ(expected.c_str(), actual.str().c_str());
}













