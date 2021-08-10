//
// Created by Ciaran on 4/28/2020.
//


#include "redland/LibrdfQuery.h"
#include "redland/LibrdfQueryResults.h"
#include <gtest/gtest.h>
#include <librdf.h>
#include <redland/LibrdfModel.h>
#include <redland/LibrdfParser.h>
#include <redland/LibrdfStorage.h>

using namespace redland;

/**
 * Note, it makes little sense splitting LibrdfQuery and LibrdfQueryResults
 * since they are so dependent on each other. We test them both here.
 */

class LibrdfQueryTests : public ::testing::Test {

public:
    std::string input = "<?xml version=\"1.0\"?>\n"
                        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                        "            xmlns:dc=\"http://purl.org/dc/elements/1.1/\"\n"
                        "            xmlns:ex=\"http://example.org/stuff/1.0/\">\n"
                        "  <rdf:Description rdf:about=\"http://www.w3.org/TR/rdf-syntax-grammar\"\n"
                        "             dc:title=\"RDF1.1 XML Syntax\">\n"
                        "    <ex:editor>\n"
                        "      <rdf:Description ex:fullName=\"Dave Beckett\">\n"
                        "        <ex:homePage rdf:resource=\"http://purl.org/net/dajobe/\" />\n"
                        "      </rdf:Description>\n"
                        "    </ex:editor>\n"
                        "  </rdf:Description>\n"
                        "</rdf:RDF>\n";

    std::string q = "SELECT ?x ?y ?z \n"
                    "WHERE {\n"
                    "  ?x ?y ?z \n"
                    "}\n";

    LibrdfStorage storage;

    LibrdfQueryTests() = default;
};


TEST_F(LibrdfQueryTests, CheckQueryExecute) {
    LibrdfModel model(storage);
    LibrdfParser parser("rdfxml");
    parser.parseString(input, model, "base");

    LibrdfQuery query(q, model);
    LibrdfQueryResults queryResults = query.execute();

    std::string actual = queryResults.toString("csv");
    std::cout << actual << std::endl;
    std::string expected = "x,y,z\n"
                           "http://omex-library.org/NewOmex.omex/NewModel.xml#modelmeta1,http://biomodels.net/model-qualifiers/isDescribedBy,https://identifiers.org/pubmed/12991237\n";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
}
//
//TEST_F(LibrdfQueryTests, TestRunQueryTwice) {
//    LibrdfQuery query(rdf.getModel(), q);// runs the first time automatically
//    query.runQuery();                        // now run again
//    std::string actual = query.resultsAsStr("csv");
//    std::cout << actual << std::endl;
//    std::string expected = "x,y,z\n"
//                           "http://omex-library.org/NewOmex.omex/NewModel.xml#modelmeta1,http://biomodels.net/model-qualifiers/isDescribedBy,https://identifiers.org/pubmed/12991237\n";
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//    query.freeQuery();
//}
//
//TEST_F(LibrdfQueryTests, TestgetResultsAsMap) {
//    LibrdfQuery query(rdf.getModel(), q);
//    ResultsMap resultsMap = query.resultsAsMap();
//    std::string expected = "http://biomodels.net/model-qualifiers/isDescribedBy";
//    std::string actual = resultsMap["y"][0];
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//    query.freeQuery();
//}
//
//TEST_F(LibrdfQueryTests, BindingNotUsed) {
//    std::cout << __FILE__<<":"<<__LINE__<<std::endl;
//    std::string queryString = "SELECT ?x ?y ?z \n"
//                              "WHERE {\n"
//                              "  ?x <http://biomodels.net/model-qualifiers/isDescribedBy> ?z \n"
////                              "  ?x ?y ?z \n"
//                              "}\n";
//    std::cout << __FILE__<<":"<<__LINE__<<std::endl;
//    LibrdfQuery query(rdf.getModel(), queryString);
//    std::cout << __FILE__<<":"<<__LINE__<<std::endl;
//    ResultsMap resultsMap = query.resultsAsMap();
//    std::cout << __FILE__<<":"<<__LINE__<<std::endl;
//    std::string expected = "http://biomodels.net/model-qualifiers/isDescribedBy";
//    std::cout << __FILE__<<":"<<__LINE__<<std::endl;
//    std::string actual = resultsMap["y"][0];
//    std::cout << __FILE__<<":"<<__LINE__<<std::endl;
//    ASSERT_STREQ("", actual.c_str());
//    query.freeQuery();
//}
//
//TEST_F(LibrdfQueryTests, TestgetResultsAsMapTwice) {
//    LibrdfQuery query(rdf.getModel(), q);
//    ResultsMap resultsMap = query.resultsAsMap();
//    ResultsMap resultsMap2 = query.resultsAsMap();
//    std::string expected = "http://biomodels.net/model-qualifiers/isDescribedBy";
//    std::string actual = resultsMap["y"][0];
//    ASSERT_STREQ(expected.c_str(), actual.c_str());
//    query.freeQuery();
//}

//TEST_F(LibrdfQueryTests, TestResultsAsStream) {
//    LibrdfQuery query(rdf.getModel(), q);
//    librdf_stream *stream = query.resultsAsLibRdfStream();
//    ASSERT_TRUE(stream);// aka not null
//    librdf_free_stream(stream);
//}
