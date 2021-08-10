//
// Created by Ciaran on 4/28/2020.
//


#include "redland/LibrdfQuery.h"
#include "redland/LibrdfQueryResults.h"
#include <gtest/gtest.h>
#include <librdf.h>
#include <redland/LibrdfModel.h>
#include <redland/LibrdfParser.h>
#include <redland/LibrdfSerializer.h>
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

    std::string turtleResultsString = "@prefix xsd:     <http://www.w3.org/2001/XMLSchema#> .\n"
                                      "@prefix rs:      <http://www.w3.org/2001/sw/DataAccess/tests/result-set#> .\n"
                                      "@prefix rdf:     <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                                      "\n"
                                      "[]    rdf:type      rs:ResultSet ;\n"
                                      "      rs:resultVariable  \"x\" ;\n"
                                      "      rs:resultVariable  \"y\" ;\n"
                                      "      rs:resultVariable  \"z\" ;\n"
                                      "      rs:solution   [ rs:binding    [ rs:variable   \"x\" ;\n"
                                      "                                      rs:value      <http://www.w3.org/TR/rdf-syntax-grammar>\n"
                                      "                                    ] ; \n"
                                      "                      rs:binding    [ rs:variable   \"y\" ;\n"
                                      "                                      rs:value      <http://purl.org/dc/elements/1.1/title>\n"
                                      "                                    ] ; \n"
                                      "                      rs:binding    [ rs:variable   \"z\" ;\n"
                                      "                                      rs:value      \"RDF1.1 XML Syntax\"\n"
                                      "                                    ] \n"
                                      "      ] ;\n"
                                      "      rs:solution   [ rs:binding    [ rs:variable   \"x\" ;\n"
                                      "                                      rs:value      _:r1r25180r1\n"
                                      "                                    ] ; \n"
                                      "                      rs:binding    [ rs:variable   \"y\" ;\n"
                                      "                                      rs:value      <http://example.org/stuff/1.0/fullName>\n"
                                      "                                    ] ; \n"
                                      "                      rs:binding    [ rs:variable   \"z\" ;\n"
                                      "                                      rs:value      \"Dave Beckett\"\n"
                                      "                                    ] \n"
                                      "      ] ;\n"
                                      "      rs:solution   [ rs:binding    [ rs:variable   \"x\" ;\n"
                                      "                                      rs:value      _:r1r25180r1\n"
                                      "                                    ] ; \n"
                                      "                      rs:binding    [ rs:variable   \"y\" ;\n"
                                      "                                      rs:value      <http://example.org/stuff/1.0/homePage>\n"
                                      "                                    ] ; \n"
                                      "                      rs:binding    [ rs:variable   \"z\" ;\n"
                                      "                                      rs:value      <http://purl.org/net/dajobe/>\n"
                                      "                                    ] \n"
                                      "      ] ;\n"
                                      "      rs:solution   [ rs:binding    [ rs:variable   \"x\" ;\n"
                                      "                                      rs:value      <http://www.w3.org/TR/rdf-syntax-grammar>\n"
                                      "                                    ] ; \n"
                                      "                      rs:binding    [ rs:variable   \"y\" ;\n"
                                      "                                      rs:value      <http://example.org/stuff/1.0/editor>\n"
                                      "                                    ] ; \n"
                                      "                      rs:binding    [ rs:variable   \"z\" ;\n"
                                      "                                      rs:value      _:r1r25180r1\n"
                                      "                                    ] \n"
                                      "      ] .";

    std::string q = "SELECT ?x ?y ?z \n"
                    "WHERE {\n"
                    "  ?x ?y ?z \n"
                    "}\n";

    /**
     * @brief stores the expected results in a model
     */
    LibrdfStorage *expectedStorage = nullptr;
    LibrdfModel *expectedModel = nullptr;

    /**
     * @brief storage and model for actually making the query from the input string
     */
    LibrdfStorage *storage = nullptr;
    LibrdfModel *model = nullptr;

    /**
      * @brief after we query, we have a string which can be parsed back into an rdf model
      * for programatic comparison with expected. We need another set of model and storage for this
      */
    LibrdfStorage *actualStorage = nullptr;
    LibrdfModel *actualModel = nullptr;


    LibrdfQueryTests() {
        // storage and model for creating the query
        storage = new LibrdfStorage;
        model = new LibrdfModel(*storage);
        LibrdfParser parser("rdfxml");
        parser.parseString(input, *model, "https://rdf-graph.org");


        // expected results
        expectedStorage = new LibrdfStorage();
        expectedModel = new LibrdfModel(*expectedStorage);
        LibrdfParser expectedResultsParser("turtle");
        expectedResultsParser.parseString(turtleResultsString, *expectedModel, "https://expected-results.org");


        // for acctual results
        actualStorage = new LibrdfStorage;
        actualModel = new LibrdfModel(*actualStorage);
    };

    ~LibrdfQueryTests() override {
        if (expectedStorage) {
            delete expectedStorage;
            expectedStorage = nullptr;
        }

        if (expectedModel) {
            delete expectedModel;
            expectedModel = nullptr;
        }

        if (model) {
            delete model;
            model = nullptr;
        }

        if (storage) {
            delete storage;
            storage = nullptr;
        }

        if (actualModel) {
            delete actualModel;
            actualModel = nullptr;
        }

        if (actualStorage) {
            delete actualStorage;
            actualStorage = nullptr;
        }
    }
};


TEST_F(LibrdfQueryTests, CheckQueryExecute) {

    // create a query on the model
    LibrdfQuery query(q, *model);
    // get the results as a turtle string
    auto queryResults = query.execute();
    std::cout << queryResults.toString("turtle") << std::endl;
    // note :  count the number of query results seen so far in the results.
    // It'll be 0 if toString has not been called.
    ASSERT_EQ(4, queryResults.count());
}

TEST_F(LibrdfQueryTests, CheckQueryResultsBindingsCount) {

    // create a query on the model
    LibrdfQuery query(q, *model);
    // get the results as a turtle string
    auto queryResults = query.execute();
    ASSERT_EQ(3, queryResults.getBindingsCount());
}


TEST_F(LibrdfQueryTests, IsBinding) {
    LibrdfQuery query(q, *model);
    auto results = query.execute();
    ASSERT_TRUE(results.isBindings());
}

TEST_F(LibrdfQueryTests, IsGraph) {
    LibrdfQuery query(q, *model);
    auto results = query.execute();
    ASSERT_FALSE(results.isGraph());
}

TEST_F(LibrdfQueryTests, IsBoolean) {
    LibrdfQuery query(q, *model);
    auto results = query.execute();
    ASSERT_FALSE(results.isBoolean());
}

TEST_F(LibrdfQueryTests, IsFinished) {
    LibrdfQuery query(q, *model);
    auto results = query.execute();
    ASSERT_FALSE(results.isFinished());
}

TEST_F(LibrdfQueryTests, size) {
    LibrdfQuery query(q, *model);
    auto results = query.execute();
    ASSERT_EQ(5, results.size());
}
TEST_F(LibrdfQueryTests, isNull) {
    LibrdfQuery query(q, *model);
    auto results = query.execute();
    ASSERT_FALSE(results.isNull());
}


TEST_F(LibrdfQueryTests, getBindingsName) {
    LibrdfQuery query(q, *model);
    auto results = query.execute();
    std::string name = results.getBindingsName(0);
    ASSERT_STREQ("x", name.c_str());
}

TEST_F(LibrdfQueryTests, getBindingsNames) {
    LibrdfQuery query(q, *model);
    auto results = query.execute();
    std::vector<std::string> names = results.getBindingsNames();
    std::vector<std::string> expected({"x", "y", "z"});
    ASSERT_EQ(expected, names);
}

TEST_F(LibrdfQueryTests, TestRunQueryTwice) {
    LibrdfQuery query(q, *model);
    auto results1 = query.execute();
    auto results2 = query.execute();
    ASSERT_EQ(5, results1.size());
    ASSERT_EQ(5, results2.size());
}

TEST_F(LibrdfQueryTests, getBindingValueByName) {
    LibrdfQuery query(q, *model);
    auto results = query.execute();
    std::vector<std::string> bindingNames = results.getBindingsNames();
    std::vector<std::string> bindingValues;
    for (const auto &name : bindingNames) {
        std::string value = results.getBindingValueByName(name);
        bindingValues.push_back(value);
    }
    std::vector<std::string> expectedBindingValues(
            {"http://www.w3.org/TR/rdf-syntax-grammar",
             "http://purl.org/dc/elements/1.1/title",
             "RDF1.1 XML Syntax"});
    ASSERT_EQ(expectedBindingValues, bindingValues);
}

TEST_F(LibrdfQueryTests, TestgetResultsAsMap) {
    LibrdfQuery query(q, *model);
    auto results = query.execute();
    ResultsMap resultsMap = results.map();
    std::string expected = "http://purl.org/dc/elements/1.1/title";
    std::string actual = resultsMap["y"][0];
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfQueryTests, BindingNotUsed) {
    std::string s = "SELECT ?x ?y ?z \n"
                    "WHERE {\n"
                    "  ?x ?y <http://purl.org/net/dajobe/> \n"
                    "}\n";
    LibrdfQuery query(q, *model);
    auto results = query.execute();
    ResultsMap resultsMap = results.map();
    std::string expected = "http://purl.org/dc/elements/1.1/title";
    std::string actual = resultsMap["y"][0];
    ASSERT_STREQ("", actual.c_str());
}

