//
// Created by Ciaran on 4/8/2020.
//


#include <utility>

#include "gtest/gtest.h"
#include "omexmeta/RDF.h"
#include "AnnotationSamples.h"

#include "curl/curl.h"
#include "SBMLFactory.h"
#include <regex>
#include "omexmeta/SemsimUtils.h"

typedef std::string string;

class ReadAndWriteTests : public ::testing::Test {

public:

    AnnotationSamples samples;

    ReadAndWriteTests() = default;

    static void assertReadAndWrite(const std::string &input_annot, const std::string &input_format,
                                   const std::string &expected_output) {
        omexmeta::RDF rdf = omexmeta::RDF::fromString(input_annot, "rdfxml");
        std::string actual = rdf.toString(input_format, "file://./annotations.rdf");
        std::cout << actual << std::endl;
        ASSERT_STREQ(expected_output.c_str(), actual.c_str());
    }

    static void assertReadAndWriteRegularExpression(
            const std::string &input_annot,
            const std::string &input_format,
            const std::string &regular_expression_that_matches) {
        omexmeta::RDF rdf = omexmeta::RDF::fromString(input_annot, "rdfxml");
        std::string actual = rdf.toString(input_format, "file://./annotations.rdf");
        std::cout << actual << std::endl;
        std::regex r(regular_expression_that_matches);
        bool truth = false;
        if (std::regex_search(actual, r)) {
            truth = true;
            std::cout << "match" << std::endl;
        }
        ASSERT_TRUE(truth);
    }

    static void assertReadAndWriteRegularExpressionSplitByNewline(
            const std::string &input_annot,
            const std::string &input_format,
            const std::string &regular_expression_that_matches) {
        omexmeta::RDF rdf = omexmeta::RDF::fromString(input_annot, "rdfxml");
        std::string actual = rdf.toString(input_format, "file://./annotations.rdf");
        std::vector<std::string> vec = omexmeta::SemsimUtils::splitStringBy(regular_expression_that_matches, '\n');
        // we do search line by line
        for (auto &i : vec) {
            std::regex r(i);
            bool truth = false;
            if (std::regex_search(actual, r)) {
                truth = true;
            }
            if (!truth){
                std::cout << "actual is:\n " << actual << "\n" << std::endl;
                std::cout << "Failed on: \"" <<i << "\"" << std::endl;
            }
            ASSERT_TRUE(truth);
        }
    }

};


TEST_F(ReadAndWriteTests, TestDefaultConstructor) {
    omexmeta::RDF rdf;
    ASSERT_TRUE(true); // If we get this far we've passed
}

/*********************************************************************
 * Tests for singular annotation 1
 */


TEST_F(ReadAndWriteTests, singularannotation1turtle) {
    std::string expected = "@base <file://./annotations.rdf> .\n"
                           "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "\n"
                           "<metaid_1>\n"
                           "    bqbiol:is <https://identifiers.org/uniprot/P0DP23> .\n"
                           "\n"
                           "";
    assertReadAndWrite(samples.singular_annotation1, "turtle", expected);
}

TEST_F(ReadAndWriteTests, singularannotation1rdfxmlxmp) {
    std::string expected = "<x:xmpmeta xmlns:x='adobe:ns:meta/'>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/uniprot/P0DP23\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "</x:xmpmeta>\n";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.singular_annotation1, "rdfxml-xmp", expected);
}

TEST_F(ReadAndWriteTests, singularannotation1rdfxmlabbrev) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"metaid_1\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/uniprot/P0DP23\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.singular_annotation1, "rdfxml-abbrev", expected);
}

TEST_F(ReadAndWriteTests, singularannotation1rdfxml) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"metaid_1\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/uniprot/P0DP23\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.singular_annotation1, "rdfxml", expected);
}

TEST_F(ReadAndWriteTests, singularannotation1dot) {
    std::string expected = "digraph {\n"
                           "\trankdir = LR;\n"
                           "\tcharset=\"utf-8\";\n"
                           "\n"
                           "\t\"Rfile://./metaid_1\" -> \"Rhttps://identifiers.org/uniprot/P0DP23\" [ label=\"bqbiol:is\" ];\n"
                           "\n"
                           "\t// Resources\n"
                           "\t\"Rfile://./metaid_1\" [ label=\"file://./metaid_1\", shape = ellipse, color = blue ];\n"
                           "\t\"Rhttps://identifiers.org/uniprot/P0DP23\" [ label=\"https://identifiers.org/uniprot/P0DP23\", shape = ellipse, color = blue ];\n"
                           "\n"
                           "\t// Anonymous nodes\n"
                           "\n"
                           "\t// Literals\n"
                           "\n"
                           "\tlabel=\"\\n\\nModel:\\nfile://./annotations.rdf\\n\\nNamespaces:\\nbqbiol: http://biomodels.net/biology-qualifiers/\\n\";\n"
                           "}\n"
                           "";
    assertReadAndWrite(samples.singular_annotation1, "dot", expected);
}

TEST_F(ReadAndWriteTests, singularannotation1jsontriples) {
    std::string expected = "{\n"
                           "  \"triples\" : [\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"metaid_1\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://biomodels.net/biology-qualifiers/is\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"https://identifiers.org/uniprot/P0DP23\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      }\n"
                           "    ]\n"
                           "  }\n"
                           "";
    assertReadAndWrite(samples.singular_annotation1, "json-triples", expected);
}

TEST_F(ReadAndWriteTests, singularannotation1json) {
    std::string expected = "\n"
                           "{\n"
                           "  \"metaid_1\" : {\n"
                           "    \"http://biomodels.net/biology-qualifiers/is\" : [ {\n"
                           "        \"value\" : \"https://identifiers.org/uniprot/P0DP23\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  }\n"
                           "";
    assertReadAndWrite(samples.singular_annotation1, "json", expected);
}

TEST_F(ReadAndWriteTests, singularannotation1html) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\"\n"
                           "        \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">\n"
                           "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                           "<head>\n"
                           "  <title>Raptor Graph Serialisation</title>\n"
                           "</head>\n"
                           "<body>\n"
                           "  <table id=\"triples\" border=\"1\">\n"
                           "    <tr>\n"
                           "      <th>Subject</th>\n"
                           "      <th>Predicate</th>\n"
                           "      <th>Object</th>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./metaid_1\">file://./metaid_1</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/is\">http://biomodels.net/biology-qualifiers/is</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"https://identifiers.org/uniprot/P0DP23\">https://identifiers.org/uniprot/P0DP23</a></span></td>\n"
                           "    </tr>\n"
                           "  </table>\n"
                           "  <p>Total number of triples: <span class=\"count\">1</span>.</p>\n"
                           "</body>\n"
                           "</html>\n"
                           "";
    assertReadAndWrite(samples.singular_annotation1, "html", expected);
}

TEST_F(ReadAndWriteTests, singularannotation1nquads) {
    std::string expected = "<file://./metaid_1> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/uniprot/P0DP23> .\n";
    assertReadAndWrite(samples.singular_annotation1, "nquads", expected);
}


/**********************************************************************
 * Tests for samples.singular_annotation2
 */


TEST_F(ReadAndWriteTests, singularannotation2ntriples) {
    std::string expected = "<file://./MyModel.xml#modelmeta1> <http://biomodels.net/model-qualifiers/isDescribedBy> <https://identifiers.org/pubmed/12991237> .\n";
    assertReadAndWrite(samples.singular_annotation2, "ntriples", expected);
}

TEST_F(ReadAndWriteTests, singularannotation2turtle) {
    std::string expected = "@base <file://./annotations.rdf> .\n"
                           "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix bqmodel: <http://biomodels.net/model-qualifiers/> .\n"
                           "\n"
                           "<MyModel.xml#modelmeta1>\n"
                           "    bqmodel:isDescribedBy <https://identifiers.org/pubmed/12991237> .\n"
                           "\n"
                           "";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.singular_annotation2, "turtle", expected);
}

TEST_F(ReadAndWriteTests, singularannotation2rdfxmlxmp) {
    std::string expected = "<x:xmpmeta xmlns:x='adobe:ns:meta/'>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqmodel:isDescribedBy rdf:resource=\"https://identifiers.org/pubmed/12991237\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "</x:xmpmeta>\n";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.singular_annotation2, "rdfxml-xmp", expected);
}

TEST_F(ReadAndWriteTests, singularannotation2rdfxmlabbrev) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"MyModel.xml#modelmeta1\">\n"
                           "    <bqmodel:isDescribedBy rdf:resource=\"https://identifiers.org/pubmed/12991237\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.singular_annotation2, "rdfxml-abbrev", expected);
}

TEST_F(ReadAndWriteTests, singularannotation2rdfxml) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"MyModel.xml#modelmeta1\">\n"
                           "    <bqmodel:isDescribedBy rdf:resource=\"https://identifiers.org/pubmed/12991237\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.singular_annotation2, "rdfxml", expected);
}

TEST_F(ReadAndWriteTests, singularannotation2dot) {
    std::string expected = "digraph \n"
                           "\trankdir = LR;\n"
                           "\tcharset=\"utf-8\";\n"
                           "\t\"Rfile://./MyModel.xml#modelmeta1\" -> \"Rhttps://identifiers.org/pubmed/12991237\".*label=\"bqmodel:isDescribedBy\".*;\n"
                           "\t// Resources\n"
                           "\t\"Rfile://./MyModel.xml#modelmeta1\".*label=\"file://./MyModel.xml#modelmeta1\", shape = ellipse, color = blue.*;\n"
                           "\t\"Rhttps://identifiers.org/pubmed/12991237\".*label=\"https://identifiers.org/pubmed/12991237\", shape = ellipse, color = blue.*;\n"
                           "\t// Anonymous nodes\n"
                           "\t// Literals\n";

    assertReadAndWriteRegularExpressionSplitByNewline(samples.singular_annotation2, "dot", expected);
}

TEST_F(ReadAndWriteTests, singularannotation2jsontriples) {
    std::string expected = "{\n"
                           "  \"triples\" : [\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"MyModel.xml#modelmeta1\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://biomodels.net/model-qualifiers/isDescribedBy\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"https://identifiers.org/pubmed/12991237\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      }\n"
                           "    ]\n"
                           "  }\n";
    assertReadAndWrite(samples.singular_annotation2, "json-triples", expected);
}

TEST_F(ReadAndWriteTests, singularannotation2json) {
    std::string expected = "\n"
                           "{\n"
                           "  \"MyModel.xml#modelmeta1\" : {\n"
                           "    \"http://biomodels.net/model-qualifiers/isDescribedBy\" : [ {\n"
                           "        \"value\" : \"https://identifiers.org/pubmed/12991237\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  }\n";
    assertReadAndWrite(samples.singular_annotation2, "json", expected);
}

TEST_F(ReadAndWriteTests, singularannotation2html) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\"\n"
                           "        \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">\n"
                           "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                           "<head>\n"
                           "  <title>Raptor Graph Serialisation</title>\n"
                           "</head>\n"
                           "<body>\n"
                           "  <table id=\"triples\" border=\"1\">\n"
                           "    <tr>\n"
                           "      <th>Subject</th>\n"
                           "      <th>Predicate</th>\n"
                           "      <th>Object</th>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./MyModel.xml#modelmeta1\">file://./MyModel.xml#modelmeta1</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/model-qualifiers/isDescribedBy\">http://biomodels.net/model-qualifiers/isDescribedBy</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"https://identifiers.org/pubmed/12991237\">https://identifiers.org/pubmed/12991237</a></span></td>\n"
                           "    </tr>\n"
                           "  </table>\n"
                           "  <p>Total number of triples: <span class=\"count\">1</span>.</p>\n"
                           "</body>\n"
                           "</html>\n";
    assertReadAndWrite(samples.singular_annotation2, "html", expected);
}

TEST_F(ReadAndWriteTests, singularannotation2nquads) {
    std::string expected = "<file://./MyModel.xml#modelmeta1> <http://biomodels.net/model-qualifiers/isDescribedBy> <https://identifiers.org/pubmed/12991237> .\n";
    assertReadAndWrite(samples.singular_annotation2, "nquads", expected);
}


/**********************************************************************
 * Tests for samples.singular_annotation3
 */


TEST_F(ReadAndWriteTests, singularannotation3ntriples) {
    std::string expected = "<file://./MyModel.xml#meta1> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/chebi/CHEBI:15422> .\n";
    assertReadAndWrite(samples.singular_annotation3, "ntriples", expected);
}

TEST_F(ReadAndWriteTests, singularannotation3turtle) {
    std::string expected = "@base <file://./annotations.rdf> .\n"
                           "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "\n"
                           "<MyModel.xml#meta1>\n"
                           "    bqbiol:is <https://identifiers.org/chebi/CHEBI:15422> .\n"
                           "\n"
                           "";
    assertReadAndWrite(samples.singular_annotation3, "turtle", expected);
}

TEST_F(ReadAndWriteTests, singularannotation3rdfxmlxmp) {
    std::string expected = "<x:xmpmeta xmlns:x='adobe:ns:meta/'>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/chebi/CHEBI:15422\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "</x:xmpmeta>\n"
                           "";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.singular_annotation3, "rdfxml-xmp", expected);
}

TEST_F(ReadAndWriteTests, singularannotation3rdfxmlabbrev) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"MyModel.xml#meta1\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/chebi/CHEBI:15422\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";

    assertReadAndWrite(samples.singular_annotation3, "rdfxml-abbrev", expected);
}

TEST_F(ReadAndWriteTests, singularannotation3rdfxml) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"MyModel.xml#meta1\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/chebi/CHEBI:15422\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.singular_annotation3, "rdfxml", expected);
}

TEST_F(ReadAndWriteTests, singularannotation3dot) {
    std::string expected = "digraph {\n"
                           "\trankdir = LR;\n"
                           "\tcharset=\"utf-8\";\n"
                           "\n"
                           "\t\"Rfile://./MyModel.xml#meta1\" -> \"Rhttps://identifiers.org/chebi/CHEBI:15422\" [ label=\"bqbiol:is\" ];\n"
                           "\n"
                           "\t// Resources\n"
                           "\t\"Rfile://./MyModel.xml#meta1\" [ label=\"file://./MyModel.xml#meta1\", shape = ellipse, color = blue ];\n"
                           "\t\"Rhttps://identifiers.org/chebi/CHEBI:15422\" [ label=\"https://identifiers.org/chebi/CHEBI:15422\", shape = ellipse, color = blue ];\n"
                           "\n"
                           "\t// Anonymous nodes\n"
                           "\n"
                           "\t// Literals\n"
                           "\n"
                           "\tlabel=\"\\n\\nModel:\\nfile://./annotations.rdf\\n\\nNamespaces:\\nbqbiol: http://biomodels.net/biology-qualifiers/\\n\";\n"
                           "}\n"
                           "";
    assertReadAndWrite(samples.singular_annotation3, "dot", expected);
}

TEST_F(ReadAndWriteTests, singularannotation3jsontriples) {
    std::string expected = "{\n"
                           "  \"triples\" : [\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"MyModel.xml#meta1\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://biomodels.net/biology-qualifiers/is\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"https://identifiers.org/chebi/CHEBI:15422\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      }\n"
                           "    ]\n"
                           "  }\n";
    assertReadAndWrite(samples.singular_annotation3, "json-triples", expected);
}

TEST_F(ReadAndWriteTests, singularannotation3json) {
    std::string expected = "\n"
                           "{\n"
                           "  \"MyModel.xml#meta1\" : {\n"
                           "    \"http://biomodels.net/biology-qualifiers/is\" : [ {\n"
                           "        \"value\" : \"https://identifiers.org/chebi/CHEBI:15422\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  }\n"
                           "";
    assertReadAndWrite(samples.singular_annotation3, "json", expected);
}

TEST_F(ReadAndWriteTests, singularannotation3html) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\"\n"
                           "        \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">\n"
                           "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                           "<head>\n"
                           "  <title>Raptor Graph Serialisation</title>\n"
                           "</head>\n"
                           "<body>\n"
                           "  <table id=\"triples\" border=\"1\">\n"
                           "    <tr>\n"
                           "      <th>Subject</th>\n"
                           "      <th>Predicate</th>\n"
                           "      <th>Object</th>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./MyModel.xml#meta1\">file://./MyModel.xml#meta1</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/is\">http://biomodels.net/biology-qualifiers/is</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"https://identifiers.org/chebi/CHEBI:15422\">https://identifiers.org/chebi/CHEBI:15422</a></span></td>\n"
                           "    </tr>\n"
                           "  </table>\n"
                           "  <p>Total number of triples: <span class=\"count\">1</span>.</p>\n"
                           "</body>\n"
                           "</html>\n";
    assertReadAndWrite(samples.singular_annotation3, "html", expected);
}

TEST_F(ReadAndWriteTests, singularannotation3nquads) {
    std::string expected = "<file://./MyModel.xml#meta1> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/chebi/CHEBI:15422> .\n";
    assertReadAndWrite(samples.singular_annotation3, "nquads", expected);
}


/**********************************************************************
 * Tests for samples.singular_annotation4
 */


TEST_F(ReadAndWriteTests, singularannotation4ntriples) {
    std::string expected = "<file://./MyModel.xml#meta2> <http://purl.org/dc/terms/description> \"Cardiomyocyte cytosolic ATP concentration\" .\n";
    assertReadAndWrite(samples.singular_annotation4, "ntriples", expected);
}

TEST_F(ReadAndWriteTests, singularannotation4turtle) {
    std::string expected = "@base <file://./annotations.rdf> .\n"
                           "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix dcterms: <http://purl.org/dc/terms/> .\n"
                           "\n"
                           "<MyModel.xml#meta2>\n"
                           "    dcterms:description \"Cardiomyocyte cytosolic ATP concentration\" .\n"
                           "\n"
                           "";
    assertReadAndWrite(samples.singular_annotation4, "turtle", expected);
}

TEST_F(ReadAndWriteTests, singularannotation4rdfxmlxmp) {
    std::string expected = "<x:xmpmeta xmlns:x='adobe:ns:meta/'>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <dcterms:description>Cardiomyocyte cytosolic ATP concentration</dcterms:description>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "</x:xmpmeta>\n"
                           "";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.singular_annotation4, "rdfxml-xmp", expected);
}

TEST_F(ReadAndWriteTests, singularannotation4rdfxmlabbrev) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"MyModel.xml#meta2\">\n"
                           "    <dcterms:description>Cardiomyocyte cytosolic ATP concentration</dcterms:description>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.singular_annotation4, "rdfxml-abbrev", expected);
}

TEST_F(ReadAndWriteTests, singularannotation4rdfxml) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"MyModel.xml#meta2\">\n"
                           "    <dcterms:description>Cardiomyocyte cytosolic ATP concentration</dcterms:description>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.singular_annotation4, "rdfxml", expected);
}

TEST_F(ReadAndWriteTests, singularannotation4dot) {
    std::string expected = "digraph {\n"
                           "\trankdir = LR;\n"
                           "\tcharset=\"utf-8\";\n"
                           "\n"
                           "\t\"Rfile://./MyModel.xml#meta2\" -> \"LCardiomyocyte cytosolic ATP concentration\" [ label=\"dcterms:description\" ];\n"
                           "\n"
                           "\t// Resources\n"
                           "\t\"Rfile://./MyModel.xml#meta2\" [ label=\"file://./MyModel.xml#meta2\", shape = ellipse, color = blue ];\n"
                           "\n"
                           "\t// Anonymous nodes\n"
                           "\n"
                           "\t// Literals\n"
                           "\t\"LCardiomyocyte cytosolic ATP concentration\" [ label=\"Cardiomyocyte cytosolic ATP concentration\", shape = record ];\n"
                           "\n"
                           "\tlabel=\"\\n\\nModel:\\nfile://./annotations.rdf\\n\\nNamespaces:\\nbqbiol: http://biomodels.net/biology-qualifiers/\\ndcterms: http://purl.org/dc/terms/\\n\";\n"
                           "}\n"
                           "";
    assertReadAndWrite(samples.singular_annotation4, "dot", expected);
}

TEST_F(ReadAndWriteTests, singularannotation4jsontriples) {
    std::string expected = "{\n"
                           "  \"triples\" : [\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"MyModel.xml#meta2\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://purl.org/dc/terms/description\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"Cardiomyocyte cytosolic ATP concentration\",\n"
                           "        \"type\" : \"literal\"\n"
                           "        }\n"
                           "      \n"
                           "      }\n"
                           "    ]\n"
                           "  }\n"
                           "";
    assertReadAndWrite(samples.singular_annotation4, "json-triples", expected);
}

TEST_F(ReadAndWriteTests, singularannotation4json) {
    std::string expected = "\n"
                           "{\n"
                           "  \"MyModel.xml#meta2\" : {\n"
                           "    \"http://purl.org/dc/terms/description\" : [ {\n"
                           "        \"value\" : \"Cardiomyocyte cytosolic ATP concentration\",\n"
                           "        \"type\" : \"literal\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  }\n"
                           "";

    assertReadAndWrite(samples.singular_annotation4, "json", expected);
}

TEST_F(ReadAndWriteTests, singularannotation4html) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\"\n"
                           "        \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">\n"
                           "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                           "<head>\n"
                           "  <title>Raptor Graph Serialisation</title>\n"
                           "</head>\n"
                           "<body>\n"
                           "  <table id=\"triples\" border=\"1\">\n"
                           "    <tr>\n"
                           "      <th>Subject</th>\n"
                           "      <th>Predicate</th>\n"
                           "      <th>Object</th>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./MyModel.xml#meta2\">file://./MyModel.xml#meta2</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://purl.org/dc/terms/description\">http://purl.org/dc/terms/description</a></span></td>\n"
                           "      <td><span class=\"literal\"><span class=\"value\">Cardiomyocyte cytosolic ATP concentration</span></span></td>\n"
                           "    </tr>\n"
                           "  </table>\n"
                           "  <p>Total number of triples: <span class=\"count\">1</span>.</p>\n"
                           "</body>\n"
                           "</html>\n"
                           "";
    assertReadAndWrite(samples.singular_annotation4, "html", expected);
}

TEST_F(ReadAndWriteTests, singularannotation4nquads) {
    std::string expected = "<file://./MyModel.xml#meta2> <http://purl.org/dc/terms/description> \"Cardiomyocyte cytosolic ATP concentration\" .\n";
    assertReadAndWrite(samples.singular_annotation4, "nquads", expected);
}


/**********************************************************************
 * Tests for samples.composite_annotation_pe
 */


TEST_F(ReadAndWriteTests, compositeannotationpentriples) {
    std::string expected = "<file://./VLV> <http://biomodels.net/biology-qualifiers/isVersionOf> <http://identifiers.org/opb/OPB_00154> .\n"
                           "<file://./VLV> <http://biomodels.net/biology-qualifiers/isPropertyOf> <file://./MyModel.rdf#entity_0> .\n"
                           "<file://./MyModel.rdf#entity_0> <http://biomodels.net/biology-qualifiers/is> <http://identifiers.org/fma/FMA:9670> .\n"
                           "<file://./MyModel.rdf#entity_0> <http://biomodels.net/biology-qualifiers/isPartOf> <http://identifiers.org/fma/FMA:18228> .\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pe, "ntriples", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpeturtle) {
    std::string expected = "@base <file://./annotations.rdf> .\n"
                           "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "\n"
                           "<MyModel.rdf#entity_0>\n"
                           "    bqbiol:is <http://identifiers.org/fma/FMA:9670> ;\n"
                           "    bqbiol:isPartOf <http://identifiers.org/fma/FMA:18228> .\n"
                           "\n"
                           "<VLV>\n"
                           "    bqbiol:isPropertyOf <MyModel.rdf#entity_0> ;\n"
                           "    bqbiol:isVersionOf <http://identifiers.org/opb/OPB_00154> .\n"
                           "\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pe, "turtle", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationperdfxmlxmp) {
    std::string expected = "<x:xmpmeta xmlns:x='adobe:ns:meta/'>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:9670\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"http://identifiers.org/fma/FMA:18228\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"MyModel.rdf#entity_0\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"http://identifiers.org/opb/OPB_00154\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "</x:xmpmeta>\n"
                           "";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.composite_annotation_pe, "rdfxml-xmp", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationperdfxmlabbrev) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"MyModel.rdf#entity_0\">\n"
                           "    <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:9670\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"http://identifiers.org/fma/FMA:18228\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"VLV\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"MyModel.rdf#entity_0\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"http://identifiers.org/opb/OPB_00154\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pe, "rdfxml-abbrev", expected);
}


TEST_F(ReadAndWriteTests, compositeannotationpedot) {
    std::string expected = "digraph {\n"
                           "\trankdir = LR;\n"
                           "\tcharset=\"utf-8\";\n"
                           "\n"
                           "\t\"Rfile://./VLV\" -> \"Rhttp://identifiers.org/opb/OPB_00154\" [ label=\"bqbiol:isVersionOf\" ];\n"
                           "\t\"Rfile://./VLV\" -> \"Rfile://./MyModel.rdf#entity_0\" [ label=\"bqbiol:isPropertyOf\" ];\n"
                           "\t\"Rfile://./MyModel.rdf#entity_0\" -> \"Rhttp://identifiers.org/fma/FMA:9670\" [ label=\"bqbiol:is\" ];\n"
                           "\t\"Rfile://./MyModel.rdf#entity_0\" -> \"Rhttp://identifiers.org/fma/FMA:18228\" [ label=\"bqbiol:isPartOf\" ];\n"
                           "\n"
                           "\t// Resources\n"
                           "\t\"Rfile://./VLV\" [ label=\"file://./VLV\", shape = ellipse, color = blue ];\n"
                           "\t\"Rhttp://identifiers.org/opb/OPB_00154\" [ label=\"http://identifiers.org/opb/OPB_00154\", shape = ellipse, color = blue ];\n"
                           "\t\"Rfile://./MyModel.rdf#entity_0\" [ label=\"file://./MyModel.rdf#entity_0\", shape = ellipse, color = blue ];\n"
                           "\t\"Rhttp://identifiers.org/fma/FMA:9670\" [ label=\"http://identifiers.org/fma/FMA:9670\", shape = ellipse, color = blue ];\n"
                           "\t\"Rhttp://identifiers.org/fma/FMA:18228\" [ label=\"http://identifiers.org/fma/FMA:18228\", shape = ellipse, color = blue ];\n"
                           "\n"
                           "\t// Anonymous nodes\n"
                           "\n"
                           "\t// Literals\n"
                           "\n"
                           "\tlabel=\"\\n\\nModel:\\nfile://./annotations.rdf\\n\\nNamespaces:\\nbqbiol: http://biomodels.net/biology-qualifiers/\\n\";\n"
                           "}\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pe, "dot", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpejsontriples) {
    std::string expected = "{\n"
                           "  \"triples\" : [\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"VLV\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://biomodels.net/biology-qualifiers/isVersionOf\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"http://identifiers.org/opb/OPB_00154\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"VLV\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://biomodels.net/biology-qualifiers/isPropertyOf\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"MyModel.rdf#entity_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"MyModel.rdf#entity_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://biomodels.net/biology-qualifiers/is\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"http://identifiers.org/fma/FMA:9670\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"MyModel.rdf#entity_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://biomodels.net/biology-qualifiers/isPartOf\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"http://identifiers.org/fma/FMA:18228\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      }\n"
                           "    ]\n"
                           "  }\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pe, "json-triples", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpejson) {
    std::string expected = "\n"
                           "{\n"
                           "  \"MyModel.rdf#entity_0\" : {\n"
                           "    \"http://biomodels.net/biology-qualifiers/is\" : [ {\n"
                           "        \"value\" : \"http://identifiers.org/fma/FMA:9670\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ],\n"
                           "    \"http://biomodels.net/biology-qualifiers/isPartOf\" : [ {\n"
                           "        \"value\" : \"http://identifiers.org/fma/FMA:18228\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  ,\n"
                           "  \"VLV\" : {\n"
                           "    \"http://biomodels.net/biology-qualifiers/isPropertyOf\" : [ {\n"
                           "        \"value\" : \"MyModel.rdf#entity_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ],\n"
                           "    \"http://biomodels.net/biology-qualifiers/isVersionOf\" : [ {\n"
                           "        \"value\" : \"http://identifiers.org/opb/OPB_00154\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  }\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pe, "json", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpehtml) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\"\n"
                           "        \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">\n"
                           "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                           "<head>\n"
                           "  <title>Raptor Graph Serialisation</title>\n"
                           "</head>\n"
                           "<body>\n"
                           "  <table id=\"triples\" border=\"1\">\n"
                           "    <tr>\n"
                           "      <th>Subject</th>\n"
                           "      <th>Predicate</th>\n"
                           "      <th>Object</th>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./VLV\">file://./VLV</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isVersionOf\">http://biomodels.net/biology-qualifiers/isVersionOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://identifiers.org/opb/OPB_00154\">http://identifiers.org/opb/OPB_00154</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./VLV\">file://./VLV</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isPropertyOf\">http://biomodels.net/biology-qualifiers/isPropertyOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"file://./MyModel.rdf#entity_0\">file://./MyModel.rdf#entity_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./MyModel.rdf#entity_0\">file://./MyModel.rdf#entity_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/is\">http://biomodels.net/biology-qualifiers/is</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://identifiers.org/fma/FMA:9670\">http://identifiers.org/fma/FMA:9670</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./MyModel.rdf#entity_0\">file://./MyModel.rdf#entity_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isPartOf\">http://biomodels.net/biology-qualifiers/isPartOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://identifiers.org/fma/FMA:18228\">http://identifiers.org/fma/FMA:18228</a></span></td>\n"
                           "    </tr>\n"
                           "  </table>\n"
                           "  <p>Total number of triples: <span class=\"count\">4</span>.</p>\n"
                           "</body>\n"
                           "</html>\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pe, "html", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpenquads) {
    std::string expected = "<file://./VLV> <http://biomodels.net/biology-qualifiers/isVersionOf> <http://identifiers.org/opb/OPB_00154> .\n"
                           "<file://./VLV> <http://biomodels.net/biology-qualifiers/isPropertyOf> <file://./MyModel.rdf#entity_0> .\n"
                           "<file://./MyModel.rdf#entity_0> <http://biomodels.net/biology-qualifiers/is> <http://identifiers.org/fma/FMA:9670> .\n"
                           "<file://./MyModel.rdf#entity_0> <http://biomodels.net/biology-qualifiers/isPartOf> <http://identifiers.org/fma/FMA:18228> .\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pe, "nquads", expected);
}


/**********************************************************************
 * Tests for samples.composite_annotation_pp
 */


TEST_F(ReadAndWriteTests, compositeannotationppntriples) {
    std::string expected = "<file://./property_metaid_0> <http://biomodels.net/biology-qualifiers/isPropertyOf> <file://./process_metaid_0> .\n"
                           "<file://./property_metaid_0> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/OPB_00592> .\n"
                           "<file://./process_metaid_0> <http://www.bhi.washington.edu/semsim#hasSourceParticipant> <file://./source_0> .\n"
                           "<file://./process_metaid_0> <http://www.bhi.washington.edu/semsim#hasSinkParticipant> <file://./sink_0> .\n"
                           "<file://./process_metaid_0> <http://www.bhi.washington.edu/semsim#hasMediatorParticipant> <file://./mediator_0> .\n"
                           "<file://./source_0> <http://www.bhi.washington.edu/semsim#hasMultiplier> \"1.0\" .\n"
                           "<file://./source_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <file://./species_metaid_0> .\n"
                           "<file://./sink_0> <http://www.bhi.washington.edu/semsim#hasMultiplier> \"2.0\" .\n"
                           "<file://./sink_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <file://./species_metaid_1> .\n"
                           "<file://./mediator_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <file://./species_metaid_2> .\n"
                           "";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.composite_annotation_pp, "ntriples", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationppturtle) {
    std::string expected = "@base <file://./annotations.rdf> .\n"
                           "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://www.bhi.washington.edu/semsim#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "\n"
                           "<mediator_0>\n"
                           "    semsim:hasPhysicalEntityReference <species_metaid_2> .\n"
                           "\n"
                           "<process_metaid_0>\n"
                           "    semsim:hasMediatorParticipant <mediator_0> ;\n"
                           "    semsim:hasSinkParticipant <sink_0> ;\n"
                           "    semsim:hasSourceParticipant <source_0> .\n"
                           "\n"
                           "<property_metaid_0>\n"
                           "    bqbiol:isPropertyOf <process_metaid_0> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/OPB_00592> .\n"
                           "\n"
                           "<sink_0>\n"
                           "    semsim:hasMultiplier \"2.0\" ;\n"
                           "    semsim:hasPhysicalEntityReference <species_metaid_1> .\n"
                           "\n"
                           "<source_0>\n"
                           "    semsim:hasMultiplier \"1.0\" ;\n"
                           "    semsim:hasPhysicalEntityReference <species_metaid_0> .\n"
                           "\n"
                           "";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.composite_annotation_pp, "turtle", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpprdfxmlxmp) {
    std::string expected = "<x:xmpmeta xmlns:x='adobe:ns:meta/'>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"species_metaid_2\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <semsim:hasMediatorParticipant rdf:resource=\"mediator_0\"/>\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"sink_0\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"source_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"process_metaid_0\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_00592\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <semsim:hasMultiplier>2.0</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"species_metaid_1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <semsim:hasMultiplier>1.0</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"species_metaid_0\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "</x:xmpmeta>\n"
                           ;
    assertReadAndWriteRegularExpressionSplitByNewline(samples.composite_annotation_pp, "rdfxml-xmp", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpprdfxmlabbrev) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"mediator_0\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"species_metaid_2\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"process_metaid_0\">\n"
                           "    <semsim:hasMediatorParticipant rdf:resource=\"mediator_0\"/>\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"sink_0\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"source_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"property_metaid_0\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"process_metaid_0\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_00592\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"sink_0\">\n"
                           "    <semsim:hasMultiplier>2.0</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"species_metaid_1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"source_0\">\n"
                           "    <semsim:hasMultiplier>1.0</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"species_metaid_0\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pp, "rdfxml-abbrev", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpprdfxml) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\" xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"property_metaid_0\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"process_metaid_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"property_metaid_0\">\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_00592\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"process_metaid_0\">\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"source_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"process_metaid_0\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"sink_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"process_metaid_0\">\n"
                           "    <semsim:hasMediatorParticipant rdf:resource=\"mediator_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"source_0\">\n"
                           "    <semsim:hasMultiplier>1.0</semsim:hasMultiplier>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"source_0\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"species_metaid_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"sink_0\">\n"
                           "    <semsim:hasMultiplier>2.0</semsim:hasMultiplier>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"sink_0\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"species_metaid_1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"mediator_0\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"species_metaid_2\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pp, "rdfxml", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationppdot) {
    std::string expected = "digraph \n"
                           "\trankdir = LR;\n"
                           "\tcharset=\"utf-8\";\n"
                           "\n"
                           "\t\"Rfile://./property_metaid_0\" -> \"Rfile://./process_metaid_0\" .* label=\"bqbiol:isPropertyOf\" .*;\n"
                           "\t\"Rfile://./property_metaid_0\" -> \"Rhttps://identifiers.org/opb/OPB_00592\" .* label=\"bqbiol:isVersionOf\" .*;\n"
                           "\t\"Rfile://./process_metaid_0\" -> \"Rfile://./source_0\" .* label=\"semsim:hasSourceParticipant\" .*;\n"
                           "\t\"Rfile://./process_metaid_0\" -> \"Rfile://./sink_0\" .* label=\"semsim:hasSinkParticipant\" .*;\n"
                           "\t\"Rfile://./process_metaid_0\" -> \"Rfile://./mediator_0\" .* label=\"semsim:hasMediatorParticipant\" .*;\n"
                           "\t\"Rfile://./source_0\" -> \"L1.0\" .* label=\"semsim:hasMultiplier\" .*;\n"
                           "\t\"Rfile://./source_0\" -> \"Rfile://./species_metaid_0\" .* label=\"semsim:hasPhysicalEntityReference\" .*;\n"
                           "\t\"Rfile://./sink_0\" -> \"L2.0\" .* label=\"semsim:hasMultiplier\" .*;\n"
                           "\t\"Rfile://./sink_0\" -> \"Rfile://./species_metaid_1\" .* label=\"semsim:hasPhysicalEntityReference\" .*;\n"
                           "\t\"Rfile://./mediator_0\" -> \"Rfile://./species_metaid_2\" .* label=\"semsim:hasPhysicalEntityReference\" .*;\n"
                           "\n"
                           "\t// Resources\n"
                           "\t\"Rfile://./property_metaid_0\" .* label=\"file://./property_metaid_0\", shape = ellipse, color = blue .*;\n"
                           "\t\"Rfile://./process_metaid_0\" .* label=\"file://./process_metaid_0\", shape = ellipse, color = blue .*;\n"
                           "\t\"Rhttps://identifiers.org/opb/OPB_00592\" .* label=\"https://identifiers.org/opb/OPB_00592\", shape = ellipse, color = blue .*;\n"
                           "\t\"Rfile://./source_0\" .* label=\"file://./source_0\", shape = ellipse, color = blue .*;\n"
                           "\t\"Rfile://./sink_0\" .* label=\"file://./sink_0\", shape = ellipse, color = blue .*;\n"
                           "\t\"Rfile://./mediator_0\" .* label=\"file://./mediator_0\", shape = ellipse, color = blue .*;\n"
                           "\t\"Rfile://./species_metaid_0\" .* label=\"file://./species_metaid_0\", shape = ellipse, color = blue .*;\n"
                           "\t\"Rfile://./species_metaid_1\" .* label=\"file://./species_metaid_1\", shape = ellipse, color = blue .*;\n"
                           "\t\"Rfile://./species_metaid_2\" .* label=\"file://./species_metaid_2\", shape = ellipse, color = blue .*;\n"
                           "\n"
                           "\t// Anonymous nodes\n"
                           "\n"
                           "\t// Literals\n"
                           "\t\"L1.0\" .* label=\"1.0\", shape = record .*;\n"
                           "\t\"L2.0\" .* label=\"2.0\", shape = record .*;\n";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.composite_annotation_pp, "dot", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationppjsontriples) {
    std::string expected = "{\n"
                           "  \"triples\" : [\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"property_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://biomodels.net/biology-qualifiers/isPropertyOf\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"process_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"property_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://biomodels.net/biology-qualifiers/isVersionOf\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"https://identifiers.org/opb/OPB_00592\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"process_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasSourceParticipant\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"source_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"process_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasSinkParticipant\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"sink_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"process_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasMediatorParticipant\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"mediator_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"source_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasMultiplier\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"1.0\",\n"
                           "        \"type\" : \"literal\"\n"
                           "        }\n"
                           "      \n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"source_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"species_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"sink_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasMultiplier\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"2.0\",\n"
                           "        \"type\" : \"literal\"\n"
                           "        }\n"
                           "      \n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"sink_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"species_metaid_1\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"mediator_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"species_metaid_2\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      }\n"
                           "    ]\n"
                           "  }\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pp, "json-triples", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationppjson) {
    std::string expected = "\n"
                           "{\n"
                           "  \"mediator_0\" : {\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\" : [ {\n"
                           "        \"value\" : \"species_metaid_2\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  ,\n"
                           "  \"process_metaid_0\" : {\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasMediatorParticipant\" : [ {\n"
                           "        \"value\" : \"mediator_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ],\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasSinkParticipant\" : [ {\n"
                           "        \"value\" : \"sink_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ],\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasSourceParticipant\" : [ {\n"
                           "        \"value\" : \"source_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  ,\n"
                           "  \"property_metaid_0\" : {\n"
                           "    \"http://biomodels.net/biology-qualifiers/isPropertyOf\" : [ {\n"
                           "        \"value\" : \"process_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ],\n"
                           "    \"http://biomodels.net/biology-qualifiers/isVersionOf\" : [ {\n"
                           "        \"value\" : \"https://identifiers.org/opb/OPB_00592\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  ,\n"
                           "  \"sink_0\" : {\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasMultiplier\" : [ {\n"
                           "        \"value\" : \"2.0\",\n"
                           "        \"type\" : \"literal\"\n"
                           "        }\n"
                           "      \n"
                           "      ],\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\" : [ {\n"
                           "        \"value\" : \"species_metaid_1\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  ,\n"
                           "  \"source_0\" : {\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasMultiplier\" : [ {\n"
                           "        \"value\" : \"1.0\",\n"
                           "        \"type\" : \"literal\"\n"
                           "        }\n"
                           "      \n"
                           "      ],\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\" : [ {\n"
                           "        \"value\" : \"species_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  }\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pp, "json", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpphtml) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\"\n"
                           "        \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">\n"
                           "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                           "<head>\n"
                           "  <title>Raptor Graph Serialisation</title>\n"
                           "</head>\n"
                           "<body>\n"
                           "  <table id=\"triples\" border=\"1\">\n"
                           "    <tr>\n"
                           "      <th>Subject</th>\n"
                           "      <th>Predicate</th>\n"
                           "      <th>Object</th>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./property_metaid_0\">file://./property_metaid_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isPropertyOf\">http://biomodels.net/biology-qualifiers/isPropertyOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"file://./process_metaid_0\">file://./process_metaid_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./property_metaid_0\">file://./property_metaid_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isVersionOf\">http://biomodels.net/biology-qualifiers/isVersionOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"https://identifiers.org/opb/OPB_00592\">https://identifiers.org/opb/OPB_00592</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./process_metaid_0\">file://./process_metaid_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasSourceParticipant\">http://www.bhi.washington.edu/semsim#hasSourceParticipant</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"file://./source_0\">file://./source_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./process_metaid_0\">file://./process_metaid_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasSinkParticipant\">http://www.bhi.washington.edu/semsim#hasSinkParticipant</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"file://./sink_0\">file://./sink_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./process_metaid_0\">file://./process_metaid_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasMediatorParticipant\">http://www.bhi.washington.edu/semsim#hasMediatorParticipant</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"file://./mediator_0\">file://./mediator_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./source_0\">file://./source_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasMultiplier\">http://www.bhi.washington.edu/semsim#hasMultiplier</a></span></td>\n"
                           "      <td><span class=\"literal\"><span class=\"value\">1.0</span></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./source_0\">file://./source_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\">http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"file://./species_metaid_0\">file://./species_metaid_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./sink_0\">file://./sink_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasMultiplier\">http://www.bhi.washington.edu/semsim#hasMultiplier</a></span></td>\n"
                           "      <td><span class=\"literal\"><span class=\"value\">2.0</span></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./sink_0\">file://./sink_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\">http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"file://./species_metaid_1\">file://./species_metaid_1</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./mediator_0\">file://./mediator_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\">http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"file://./species_metaid_2\">file://./species_metaid_2</a></span></td>\n"
                           "    </tr>\n"
                           "  </table>\n"
                           "  <p>Total number of triples: <span class=\"count\">10</span>.</p>\n"
                           "</body>\n"
                           "</html>\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pp, "html", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationppnquads) {
    std::string expected = "<file://./property_metaid_0> <http://biomodels.net/biology-qualifiers/isPropertyOf> <file://./process_metaid_0> .\n"
                           "<file://./property_metaid_0> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/OPB_00592> .\n"
                           "<file://./process_metaid_0> <http://www.bhi.washington.edu/semsim#hasSourceParticipant> <file://./source_0> .\n"
                           "<file://./process_metaid_0> <http://www.bhi.washington.edu/semsim#hasSinkParticipant> <file://./sink_0> .\n"
                           "<file://./process_metaid_0> <http://www.bhi.washington.edu/semsim#hasMediatorParticipant> <file://./mediator_0> .\n"
                           "<file://./source_0> <http://www.bhi.washington.edu/semsim#hasMultiplier> \"1.0\" .\n"
                           "<file://./source_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <file://./species_metaid_0> .\n"
                           "<file://./sink_0> <http://www.bhi.washington.edu/semsim#hasMultiplier> \"2.0\" .\n"
                           "<file://./sink_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <file://./species_metaid_1> .\n"
                           "<file://./mediator_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <file://./species_metaid_2> .\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pp, "nquads", expected);
}


/**********************************************************************
 * Tests for samples.composite_annotation_pf
 */


TEST_F(ReadAndWriteTests, compositeannotationpfntriples) {
    std::string expected = "<file://./parameter_metaid_0> <http://biomodels.net/biology-qualifiers/isPropertyOf> <file://./force_0> .\n"
                           "<file://./parameter_metaid_0> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/OPB_01058> .\n"
                           "<file://./force_0> <http://www.bhi.washington.edu/semsim#hasSourceParticipant> <file://./source_0> .\n"
                           "<file://./force_0> <http://www.bhi.washington.edu/semsim#hasSinkParticipant> <file://./sink_0> .\n"
                           "<file://./source_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <file://./species_metaid_0> .\n"
                           "<file://./sink_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <file://./species_metaid_1> .\n"
                           "";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.composite_annotation_pf, "ntriples", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpfturtle) {
    std::string expected = "@base <file://./annotations.rdf> .\n"
                           "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://www.bhi.washington.edu/semsim#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix bqmodel: <http://biomodels.net/model-qualifiers/> .\n"
                           "\n"
                           "<force_0>\n"
                           "    semsim:hasSinkParticipant <sink_0> ;\n"
                           "    semsim:hasSourceParticipant <source_0> .\n"
                           "\n"
                           "<parameter_metaid_0>\n"
                           "    bqbiol:isPropertyOf <force_0> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/OPB_01058> .\n"
                           "\n"
                           "<sink_0>\n"
                           "    semsim:hasPhysicalEntityReference <species_metaid_1> .\n"
                           "\n"
                           "<source_0>\n"
                           "    semsim:hasPhysicalEntityReference <species_metaid_0> .\n"
                           "\n"
                           "";

    assertReadAndWriteRegularExpressionSplitByNewline(samples.composite_annotation_pf, "turtle", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpfrdfxmlxmp) {
    std::string expected = "<x:xmpmeta xmlns:x='adobe:ns:meta/'>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"sink_0\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"source_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"force_0\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_01058\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"species_metaid_1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"species_metaid_0\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "</x:xmpmeta>\n"
                           "";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.composite_annotation_pf, "rdfxml-xmp", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpfrdfxmlabbrev) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"force_0\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"sink_0\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"source_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"parameter_metaid_0\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"force_0\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_01058\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"sink_0\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"species_metaid_1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"source_0\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"species_metaid_0\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pf, "rdfxml-abbrev", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpfrdfxml) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\" xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"parameter_metaid_0\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"force_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"parameter_metaid_0\">\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_01058\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"force_0\">\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"source_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"force_0\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"sink_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"source_0\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"species_metaid_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"sink_0\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"species_metaid_1\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pf, "rdfxml", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpfdot) {
    std::string expected = "\trankdir = LR;\n"
                           "\tcharset=\"utf-8\";\n"
                           "\t\"Rfile://./parameter_metaid_0\" -> \"Rfile://./force_0\" .* label=\"bqbiol:isPropertyOf\" .*;\n"
                           "\t\"Rfile://./parameter_metaid_0\" -> \"Rhttps://identifiers.org/opb/OPB_01058\" .* label=\"bqbiol:isVersionOf\" .*;\n"
                           "\t\"Rfile://./force_0\" -> \"Rfile://./source_0\" .* label=\"semsim:hasSourceParticipant\" .*;\n"
                           "\t\"Rfile://./force_0\" -> \"Rfile://./sink_0\" .* label=\"semsim:hasSinkParticipant\" .*;\n"
                           "\t\"Rfile://./source_0\" -> \"Rfile://./species_metaid_0\" .* label=\"semsim:hasPhysicalEntityReference\" .*;\n"
                           "\t\"Rfile://./sink_0\" -> \"Rfile://./species_metaid_1\" .* label=\"semsim:hasPhysicalEntityReference\" .*;\n"
                           "\t// Resources\n"
                           "\t\"Rfile://./parameter_metaid_0\" .* label=\"file://./parameter_metaid_0\", shape = ellipse, color = blue .*;\n"
                           "\t\"Rfile://./force_0\" .* label=\"file://./force_0\", shape = ellipse, color = blue .*;\n"
                           "\t\"Rhttps://identifiers.org/opb/OPB_01058\" .* label=\"https://identifiers.org/opb/OPB_01058\", shape = ellipse, color = blue .*;\n"
                           "\t\"Rfile://./source_0\" .* label=\"file://./source_0\", shape = ellipse, color = blue .*;\n"
                           "\t\"Rfile://./sink_0\" .* label=\"file://./sink_0\", shape = ellipse, color = blue .*;\n"
                           "\t\"Rfile://./species_metaid_0\" .* label=\"file://./species_metaid_0\", shape = ellipse, color = blue .*;\n"
                           "\t\"Rfile://./species_metaid_1\" .* label=\"file://./species_metaid_1\", shape = ellipse, color = blue .*;\n"
                           "\t// Anonymous nodes\n"
                           "\t// Literals\n";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.composite_annotation_pf, "dot", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpfjsontriples) {
    std::string expected = "{\n"
                           "  \"triples\" : [\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"parameter_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://biomodels.net/biology-qualifiers/isPropertyOf\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"force_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"parameter_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://biomodels.net/biology-qualifiers/isVersionOf\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"https://identifiers.org/opb/OPB_01058\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"force_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasSourceParticipant\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"source_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"force_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasSinkParticipant\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"sink_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"source_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"species_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"sink_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"species_metaid_1\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      }\n"
                           "    ]\n"
                           "  }\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pf, "json-triples", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpfjson) {
    std::string expected = "\n"
                           "{\n"
                           "  \"force_0\" : {\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasSinkParticipant\" : [ {\n"
                           "        \"value\" : \"sink_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ],\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasSourceParticipant\" : [ {\n"
                           "        \"value\" : \"source_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  ,\n"
                           "  \"parameter_metaid_0\" : {\n"
                           "    \"http://biomodels.net/biology-qualifiers/isPropertyOf\" : [ {\n"
                           "        \"value\" : \"force_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ],\n"
                           "    \"http://biomodels.net/biology-qualifiers/isVersionOf\" : [ {\n"
                           "        \"value\" : \"https://identifiers.org/opb/OPB_01058\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  ,\n"
                           "  \"sink_0\" : {\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\" : [ {\n"
                           "        \"value\" : \"species_metaid_1\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  ,\n"
                           "  \"source_0\" : {\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\" : [ {\n"
                           "        \"value\" : \"species_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  }\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pf, "json", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpfhtml) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\"\n"
                           "        \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">\n"
                           "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                           "<head>\n"
                           "  <title>Raptor Graph Serialisation</title>\n"
                           "</head>\n"
                           "<body>\n"
                           "  <table id=\"triples\" border=\"1\">\n"
                           "    <tr>\n"
                           "      <th>Subject</th>\n"
                           "      <th>Predicate</th>\n"
                           "      <th>Object</th>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./parameter_metaid_0\">file://./parameter_metaid_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isPropertyOf\">http://biomodels.net/biology-qualifiers/isPropertyOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"file://./force_0\">file://./force_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./parameter_metaid_0\">file://./parameter_metaid_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isVersionOf\">http://biomodels.net/biology-qualifiers/isVersionOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"https://identifiers.org/opb/OPB_01058\">https://identifiers.org/opb/OPB_01058</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./force_0\">file://./force_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasSourceParticipant\">http://www.bhi.washington.edu/semsim#hasSourceParticipant</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"file://./source_0\">file://./source_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./force_0\">file://./force_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasSinkParticipant\">http://www.bhi.washington.edu/semsim#hasSinkParticipant</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"file://./sink_0\">file://./sink_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./source_0\">file://./source_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\">http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"file://./species_metaid_0\">file://./species_metaid_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./sink_0\">file://./sink_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\">http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"file://./species_metaid_1\">file://./species_metaid_1</a></span></td>\n"
                           "    </tr>\n"
                           "  </table>\n"
                           "  <p>Total number of triples: <span class=\"count\">6</span>.</p>\n"
                           "</body>\n"
                           "</html>\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pf, "html", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpfnquads) {
    std::string expected = "<file://./parameter_metaid_0> <http://biomodels.net/biology-qualifiers/isPropertyOf> <file://./force_0> .\n"
                           "<file://./parameter_metaid_0> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/OPB_01058> .\n"
                           "<file://./force_0> <http://www.bhi.washington.edu/semsim#hasSourceParticipant> <file://./source_0> .\n"
                           "<file://./force_0> <http://www.bhi.washington.edu/semsim#hasSinkParticipant> <file://./sink_0> .\n"
                           "<file://./source_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <file://./species_metaid_0> .\n"
                           "<file://./sink_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <file://./species_metaid_1> .\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pf, "nquads", expected);
}


/**********************************************************************
 * Tests for samples.tabular_data1
 */

TEST_F(ReadAndWriteTests, tabulardatantriples) {
    std::string expected = "<file://./VleftCorArt> <http://biomodels.net/biology-qualifiers/isVersionOf> <http://identifiers.org/opb/OPB_00154> .\n"
                           "<file://./VleftCorArt> <http://biomodels.net/biology-qualifiers/isPropertyOf> <file://./entity_0> .\n"
                           "<file://./entity_0> <http://biomodels.net/biology-qualifiers/is> <http://identifiers.org/fma/FMA:9670> .\n"
                           "<file://./entity_0> <http://biomodels.net/biology-qualifiers/isPartOf> <http://identifiers.org/fma/FMA:18228> .\n"
                           "";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.tabular_data1, "ntriples", expected);
}

TEST_F(ReadAndWriteTests, tabulardataturtle) {
    std::string expected = "@base <file://./annotations.rdf> .\n"
                           "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://www.bhi.washington.edu/semsim#> .\n"
                           "@prefix bqmodel: <http://biomodels.net/model-qualifiers/> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "\n"
                           "<VleftCorArt>\n"
                           "    bqbiol:isPropertyOf <entity_0> ;\n"
                           "    bqbiol:isVersionOf <http://identifiers.org/opb/OPB_00154> .\n"
                           "\n"
                           "<entity_0>\n"
                           "    bqbiol:is <http://identifiers.org/fma/FMA:9670> ;\n"
                           "    bqbiol:isPartOf <http://identifiers.org/fma/FMA:18228> .\n"
                           "\n"
                           "";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.tabular_data1, "turtle", expected);
}

TEST_F(ReadAndWriteTests, tabulardatardfxmlxmp) {
    std::string expected = "<x:xmpmeta xmlns:x='adobe:ns:meta/'>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"entity_0\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"http://identifiers.org/opb/OPB_00154\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:9670\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"http://identifiers.org/fma/FMA:18228\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "</x:xmpmeta>\n"
                           "";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.tabular_data1, "rdfxml-xmp", expected);
}

TEST_F(ReadAndWriteTests, tabulardatardfxmlabbrev) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"VleftCorArt\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"entity_0\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"http://identifiers.org/opb/OPB_00154\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"entity_0\">\n"
                           "    <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:9670\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"http://identifiers.org/fma/FMA:18228\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.tabular_data1, "rdfxml-abbrev", expected);
}

TEST_F(ReadAndWriteTests, tabulardatardfxml) {
    std::string expected = "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\" xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"VleftCorArt\">\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"http://identifiers.org/opb/OPB_00154\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"VleftCorArt\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"entity_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"entity_0\">\n"
                           "    <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:9670\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"entity_0\">\n"
                           "    <bqbiol:isPartOf rdf:resource=\"http://identifiers.org/fma/FMA:18228\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.tabular_data1, "rdfxml", expected);
}

TEST_F(ReadAndWriteTests, tabulardatadot) {
    std::string expected = "\trankdir = LR;\n"
                           "\tcharset=\"utf-8\";\n"
                           "\t\"Rfile://./VleftCorArt\" -> \"Rhttp://identifiers.org/opb/OPB_00154\" .* label=\"bqbiol:isVersionOf\" .*;\n"
                           "\t\"Rfile://./VleftCorArt\" -> \"Rfile://./entity_0\" .* label=\"bqbiol:isPropertyOf\" .*;\n"
                           "\t\"Rfile://./entity_0\" -> \"Rhttp://identifiers.org/fma/FMA:9670\" .* label=\"bqbiol:is\" .*;\n"
                           "\t\"Rfile://./entity_0\" -> \"Rhttp://identifiers.org/fma/FMA:18228\" .* label=\"bqbiol:isPartOf\" .*;\n"
                           "\n"
                           "\t// Resources\n"
                           "\t\"Rfile://./VleftCorArt\" .* label=\"file://./VleftCorArt\", shape = ellipse, color = blue .*;\n"
                           "\t\"Rhttp://identifiers.org/opb/OPB_00154\" .* label=\"http://identifiers.org/opb/OPB_00154\", shape = ellipse, color = blue .*;\n"
                           "\t\"Rfile://./entity_0\" .* label=\"file://./entity_0\", shape = ellipse, color = blue .*;\n"
                           "\t\"Rhttp://identifiers.org/fma/FMA:9670\" .* label=\"http://identifiers.org/fma/FMA:9670\", shape = ellipse, color = blue .*;\n"
                           "\t\"Rhttp://identifiers.org/fma/FMA:18228\" .* label=\"http://identifiers.org/fma/FMA:18228\", shape = ellipse, color = blue .*;\n"
                           "\t// Anonymous nodes\n"
                           "\t// Literals\n";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.tabular_data1, "dot", expected);
}

TEST_F(ReadAndWriteTests, tabulardatajsontriples) {
    std::string expected = "{\n"
                           "  \"triples\" : [\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"VleftCorArt\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://biomodels.net/biology-qualifiers/isVersionOf\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"http://identifiers.org/opb/OPB_00154\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"VleftCorArt\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://biomodels.net/biology-qualifiers/isPropertyOf\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"entity_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"entity_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://biomodels.net/biology-qualifiers/is\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"http://identifiers.org/fma/FMA:9670\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"entity_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://biomodels.net/biology-qualifiers/isPartOf\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"http://identifiers.org/fma/FMA:18228\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      }\n"
                           "    ]\n"
                           "  }\n"
                           "";
    assertReadAndWrite(samples.tabular_data1, "json-triples", expected);
}

TEST_F(ReadAndWriteTests, tabulardatajson) {
    std::string expected = "\n"
                           "{\n"
                           "  \"VleftCorArt\" : {\n"
                           "    \"http://biomodels.net/biology-qualifiers/isPropertyOf\" : [ {\n"
                           "        \"value\" : \"entity_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ],\n"
                           "    \"http://biomodels.net/biology-qualifiers/isVersionOf\" : [ {\n"
                           "        \"value\" : \"http://identifiers.org/opb/OPB_00154\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  ,\n"
                           "  \"entity_0\" : {\n"
                           "    \"http://biomodels.net/biology-qualifiers/is\" : [ {\n"
                           "        \"value\" : \"http://identifiers.org/fma/FMA:9670\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ],\n"
                           "    \"http://biomodels.net/biology-qualifiers/isPartOf\" : [ {\n"
                           "        \"value\" : \"http://identifiers.org/fma/FMA:18228\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  }\n"
                           "";
    assertReadAndWrite(samples.tabular_data1, "json", expected);
}

TEST_F(ReadAndWriteTests, tabulardatahtml) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\"\n"
                           "        \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">\n"
                           "<html xmlns=\"http://www.w3.org/1999/xhtml\">\n"
                           "<head>\n"
                           "  <title>Raptor Graph Serialisation</title>\n"
                           "</head>\n"
                           "<body>\n"
                           "  <table id=\"triples\" border=\"1\">\n"
                           "    <tr>\n"
                           "      <th>Subject</th>\n"
                           "      <th>Predicate</th>\n"
                           "      <th>Object</th>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./VleftCorArt\">file://./VleftCorArt</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isVersionOf\">http://biomodels.net/biology-qualifiers/isVersionOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://identifiers.org/opb/OPB_00154\">http://identifiers.org/opb/OPB_00154</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./VleftCorArt\">file://./VleftCorArt</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isPropertyOf\">http://biomodels.net/biology-qualifiers/isPropertyOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"file://./entity_0\">file://./entity_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./entity_0\">file://./entity_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/is\">http://biomodels.net/biology-qualifiers/is</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://identifiers.org/fma/FMA:9670\">http://identifiers.org/fma/FMA:9670</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./entity_0\">file://./entity_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isPartOf\">http://biomodels.net/biology-qualifiers/isPartOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://identifiers.org/fma/FMA:18228\">http://identifiers.org/fma/FMA:18228</a></span></td>\n"
                           "    </tr>\n"
                           "  </table>\n"
                           "  <p>Total number of triples: <span class=\"count\">4</span>.</p>\n"
                           "</body>\n"
                           "</html>\n"
                           "";
    assertReadAndWrite(samples.tabular_data1, "html", expected);
}

TEST_F(ReadAndWriteTests, tabulardatanquads) {
    std::string expected = "<file://./VleftCorArt> <http://biomodels.net/biology-qualifiers/isVersionOf> <http://identifiers.org/opb/OPB_00154> .\n"
                           "<file://./VleftCorArt> <http://biomodels.net/biology-qualifiers/isPropertyOf> <file://./entity_0> .\n"
                           "<file://./entity_0> <http://biomodels.net/biology-qualifiers/is> <http://identifiers.org/fma/FMA:9670> .\n"
                           "<file://./entity_0> <http://biomodels.net/biology-qualifiers/isPartOf> <http://identifiers.org/fma/FMA:18228> .\n"
                           "";
    assertReadAndWrite(samples.tabular_data1, "nquads", expected);
}

/******************************************************************************
 * ReadAndWriteTests for sbml files
 */

//TEST_F(ReadAndWriteTests, SBML1) {
//    omexmeta::SemsimUtils::download(samples
//                                          .sbml_url1, samples.sbml_filename1);
//    omexmeta::RDF rdf = omexmeta::RDF::fromXML(samples.sbml_filename1, "rdfxml");
//    std::string extracted = rdf.toString("rdfxml", "file://./annotations.rdf");
//    std::cout << extracted <<
//              std::endl;
//    int expected = 32;
//    int actual = sizeof(extracted);
//    ASSERT_EQ(expected, actual
//    );
//}




//TEST_F(ReadAndWriteTests, CELLML1) {
//    omexmeta::SemsimUtils::download(samples.cellml_url1, samples.cellml_filename1);
//    omexmeta::RDF rdf = omexmeta::RDF::fromXML(samples.cellml_filename1, "turtle");
//    std::string extracted = rdf.toString("rdfxml");
//    std::cout << extracted << std::endl;
////    int expected = 32;
////    int actual = sizeof(extracted);
////    ASSERT_EQ(expected, actual);
//}
//
//








