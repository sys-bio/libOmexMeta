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
#include "omexmeta/OmexMetaUtils.h"

typedef std::string string;

class ReadAndWriteTests : public ::testing::Test {

public:

    AnnotationSamples samples;

    ReadAndWriteTests() = default;

    static void assertReadAndWrite(const std::string &input_annot, const std::string &input_format,
                                   const std::string &expected_output) {
        omexmeta::RDF rdf = omexmeta::RDF::fromString(input_annot, "rdfxml");
        std::string actual = rdf.toString(input_format);
        std::cout << actual << std::endl;
        ASSERT_STREQ(expected_output.c_str(), actual.c_str());
    }

    static void assertReadAndWriteRegularExpression(
            const std::string &input_annot,
            const std::string &input_format,
            const std::string &regular_expression_that_matches) {
        omexmeta::RDF rdf = omexmeta::RDF::fromString(input_annot, "rdfxml");
        std::string actual = rdf.toString(input_format);
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
        std::string actual = rdf.toString(input_format);
        std::vector<std::string> vec = omexmeta::OmexMetaUtils::splitStringBy(regular_expression_that_matches, '\n');
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
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix myOMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:metaid_1\n"
                           "    bqbiol:is <https://identifiers.org/uniprot/P0DP23> .\n"
                           "\n"
                           "";
    assertReadAndWrite(samples.singular_annotation1, "turtle", expected);
}


TEST_F(ReadAndWriteTests, singularannotation1rdfxmlxmp) {
    std::string expected = "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\"\n"
                           "   xmlns:myOMEXlib=\"http://omex-library.org/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/uniprot/P0DP23\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.singular_annotation1, "rdfxml-xmp", expected);
}

TEST_F(ReadAndWriteTests, singularannotation1rdfxmlabbrev) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\"\n"
                           "   xmlns:myOMEXlib=\"http://omex-library.org/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#metaid_1\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/uniprot/P0DP23\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.singular_annotation1, "rdfxml-abbrev", expected);
}

TEST_F(ReadAndWriteTests, singularannotation1rdfxml) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\" xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\" xmlns:myOMEXlib=\"http://omex-library.org/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#metaid_1\">\n"
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
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#metaid_1\" -> \"Rhttps://identifiers.org/uniprot/P0DP23\" \[ label=\"bqbiol:is\" \];\n"
                           "\n"
                           "\t// Resources\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#metaid_1\" \[ label=\"myOMEXlib:NewOmex.omex/NewModel.rdf#metaid_1\", shape = ellipse, color = blue \];\n"
                           "\t\"Rhttps://identifiers.org/uniprot/P0DP23\" \[ label=\"https://identifiers.org/uniprot/P0DP23\", shape = ellipse, color = blue \];\n"
                           "\n"
                           "\t// Anonymous nodes\n"
                           "\n"
                           "\t// Literals\n"
                           "\n"
                           "\tlabel=\"\\n\\nModel:\\nfile://\\n\\nNamespaces:\\nbqbiol: http://biomodels.net/biology-qualifiers/\\nmyOMEXlib: http://omex-library.org/\\nmyOMEX: http://omex-library.org/NewOmex.omex\\nlocal: http://omex-library.org/NewOmex.omex/NewModel.rdf#\\n\";\n"
                           "}\n"
                           "";
    assertReadAndWrite(samples.singular_annotation1, "dot", expected);
}

TEST_F(ReadAndWriteTests, singularannotation1jsontriples) {
    std::string expected = "{\n"
                           "  \"triples\" : [\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#metaid_1\",\n"
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
                           "  }\n";
    assertReadAndWrite(samples.singular_annotation1, "json-triples", expected);
}

TEST_F(ReadAndWriteTests, singularannotation1json) {
    std::string expected = "\n"
                           "{\n"
                           "  \"http://omex-library.org/NewOmex.omex/NewModel.rdf#metaid_1\" : {\n"
                           "    \"http://biomodels.net/biology-qualifiers/is\" : [ {\n"
                           "        \"value\" : \"https://identifiers.org/uniprot/P0DP23\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  }\n";
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
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#metaid_1\">http://omex-library.org/NewOmex.omex/NewModel.rdf#metaid_1</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/is\">http://biomodels.net/biology-qualifiers/is</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"https://identifiers.org/uniprot/P0DP23\">https://identifiers.org/uniprot/P0DP23</a></span></td>\n"
                           "    </tr>\n"
                           "  </table>\n"
                           "  <p>Total number of triples: <span class=\"count\">1</span>.</p>\n"
                           "</body>\n"
                           "</html>\n";
    assertReadAndWrite(samples.singular_annotation1, "html", expected);
}

TEST_F(ReadAndWriteTests, singularannotation1nquads) {
    std::string expected = "<http://omex-library.org/NewOmex.omex/NewModel.rdf#metaid_1> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/uniprot/P0DP23> .\n";
    assertReadAndWrite(samples.singular_annotation1, "nquads", expected);
}


/**********************************************************************
 * Tests for samples.singular_annotation2
 */


TEST_F(ReadAndWriteTests, singularannotation2ntriples) {
    std::string expected = "<http://omex-library.org/NewOmex.omex/NewModel.rdf#modelmeta1> <http://biomodels.net/model-qualifiers/isDescribedBy> <https://identifiers.org/pubmed/12991237> .\n";
    assertReadAndWrite(samples.singular_annotation2, "ntriples", expected);
}

TEST_F(ReadAndWriteTests, singularannotation2turtle) {
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix bqmodel: <http://biomodels.net/model-qualifiers/> .\n"
                           "@prefix myOMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:modelmeta1\n"
                           "    bqmodel:isDescribedBy <https://identifiers.org/pubmed/12991237> .\n"
                           "\n"
                           "";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.singular_annotation2, "turtle", expected);
}

TEST_F(ReadAndWriteTests, singularannotation2rdfxmlxmp) {
    std::string expected = "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                           "   xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\"\n"
                           "   xmlns:myOMEXlib=\"http://omex-library.org/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqmodel:isDescribedBy rdf:resource=\"https://identifiers.org/pubmed/12991237\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "\n"
                           "";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.singular_annotation2, "rdfxml-xmp", expected);
}

TEST_F(ReadAndWriteTests, singularannotation2rdfxmlabbrev) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                           "   xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\"\n"
                           "   xmlns:myOMEXlib=\"http://omex-library.org/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#modelmeta1\">\n"
                           "    <bqmodel:isDescribedBy rdf:resource=\"https://identifiers.org/pubmed/12991237\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.singular_annotation2, "rdfxml-abbrev", expected);
}

TEST_F(ReadAndWriteTests, singularannotation2rdfxml) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\" xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\" xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\" xmlns:myOMEXlib=\"http://omex-library.org/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#modelmeta1\">\n"
                           "    <bqmodel:isDescribedBy rdf:resource=\"https://identifiers.org/pubmed/12991237\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.singular_annotation2, "rdfxml", expected);
}

TEST_F(ReadAndWriteTests, singularannotation2dot) {
    std::string expected = "digraph {\n"
                           "\trankdir = LR;\n"
                           "\tcharset=\"utf-8\";\n"
                           "\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#modelmeta1\" -> \"Rhttps://identifiers.org/pubmed/12991237\" [ label=\"bqmodel:isDescribedBy\" ];\n"
                           "\n"
                           "\t// Resources\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#modelmeta1\" [ label=\"myOMEXlib:NewOmex.omex/NewModel.rdf#modelmeta1\", shape = ellipse, color = blue ];\n"
                           "\t\"Rhttps://identifiers.org/pubmed/12991237\" [ label=\"https://identifiers.org/pubmed/12991237\", shape = ellipse, color = blue ];\n"
                           "\n"
                           "\t// Anonymous nodes\n"
                           "\n"
                           "\t// Literals\n"
                           "\n"
                           "\tlabel=\"\\n\\nModel:\\nfile://\\n\\nNamespaces:\\nbqbiol: http://biomodels.net/biology-qualifiers/\\nbqmodel: http://biomodels.net/model-qualifiers/\\nmyOMEXlib: http://omex-library.org/\\nmyOMEX: http://omex-library.org/NewOmex.omex\\nlocal: http://omex-library.org/NewOmex.omex/NewModel.rdf#\\n\";\n"
                           "}\n"
                           "";
    assertReadAndWrite(samples.singular_annotation2, "dot", expected);
}

TEST_F(ReadAndWriteTests, singularannotation2jsontriples) {
    std::string expected = "{\n"
                           "  \"triples\" : [\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#modelmeta1\",\n"
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
                           "  }\n"
                           "";
    assertReadAndWrite(samples.singular_annotation2, "json-triples", expected);
}

TEST_F(ReadAndWriteTests, singularannotation2json) {
    std::string expected = "\n"
                           "{\n"
                           "  \"http://omex-library.org/NewOmex.omex/NewModel.rdf#modelmeta1\" : {\n"
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
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#modelmeta1\">http://omex-library.org/NewOmex.omex/NewModel.rdf#modelmeta1</a></span></td>\n"
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
    std::string expected = "<http://omex-library.org/NewOmex.omex/NewModel.rdf#modelmeta1> <http://biomodels.net/model-qualifiers/isDescribedBy> <https://identifiers.org/pubmed/12991237> .\n";
    assertReadAndWrite(samples.singular_annotation2, "nquads", expected);
}


/**********************************************************************
 * Tests for samples.singular_annotation3
 */


TEST_F(ReadAndWriteTests, singularannotation3ntriples) {
    std::string expected = "<http://omex-library.org/NewOmex.omex/NewModel.rdf#meta1> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/chebi/CHEBI:15422> .\n";
    assertReadAndWrite(samples.singular_annotation3, "ntriples", expected);
}

TEST_F(ReadAndWriteTests, singularannotation3turtle) {
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix myOMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:meta1\n"
                           "    bqbiol:is <https://identifiers.org/chebi/CHEBI:15422> .\n"
                           "\n"
                           "";
    assertReadAndWrite(samples.singular_annotation3, "turtle", expected);
}

TEST_F(ReadAndWriteTests, singularannotation3rdfxmlxmp) {
    std::string expected = "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\"\n"
                           "   xmlns:myOMEXlib=\"http://omex-library.org/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/chebi/CHEBI:15422\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.singular_annotation3, "rdfxml-xmp", expected);
}

TEST_F(ReadAndWriteTests, singularannotation3rdfxmlabbrev) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\"\n"
                           "   xmlns:myOMEXlib=\"http://omex-library.org/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#meta1\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/chebi/CHEBI:15422\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.singular_annotation3, "rdfxml-abbrev", expected);
}

TEST_F(ReadAndWriteTests, singularannotation3rdfxml) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\" xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\" xmlns:myOMEXlib=\"http://omex-library.org/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#meta1\">\n"
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
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#meta1\" -> \"Rhttps://identifiers.org/chebi/CHEBI:15422\" [ label=\"bqbiol:is\" ];\n"
                           "\n"
                           "\t// Resources\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#meta1\" [ label=\"myOMEXlib:NewOmex.omex/NewModel.rdf#meta1\", shape = ellipse, color = blue ];\n"
                           "\t\"Rhttps://identifiers.org/chebi/CHEBI:15422\" [ label=\"https://identifiers.org/chebi/CHEBI:15422\", shape = ellipse, color = blue ];\n"
                           "\n"
                           "\t// Anonymous nodes\n"
                           "\n"
                           "\t// Literals\n"
                           "\n"
                           "\tlabel=\"\\n\\nModel:\\nfile://\\n\\nNamespaces:\\nbqbiol: http://biomodels.net/biology-qualifiers/\\nmyOMEXlib: http://omex-library.org/\\nmyOMEX: http://omex-library.org/NewOmex.omex\\nlocal: http://omex-library.org/NewOmex.omex/NewModel.rdf#\\n\";\n"
                           "}\n"
                           "";
    assertReadAndWrite(samples.singular_annotation3, "dot", expected);
}

TEST_F(ReadAndWriteTests, singularannotation3jsontriples) {
    std::string expected = "{\n"
                           "  \"triples\" : [\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#meta1\",\n"
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
                           "  \"http://omex-library.org/NewOmex.omex/NewModel.rdf#meta1\" : {\n"
                           "    \"http://biomodels.net/biology-qualifiers/is\" : [ {\n"
                           "        \"value\" : \"https://identifiers.org/chebi/CHEBI:15422\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  }\n";
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
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#meta1\">http://omex-library.org/NewOmex.omex/NewModel.rdf#meta1</a></span></td>\n"
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
    std::string expected = "<http://omex-library.org/NewOmex.omex/NewModel.rdf#meta1> <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/chebi/CHEBI:15422> .\n";
    assertReadAndWrite(samples.singular_annotation3, "nquads", expected);
}


/**********************************************************************
 * Tests for samples.singular_annotation4
 */


TEST_F(ReadAndWriteTests, singularannotation4ntriples) {
    std::string expected = "<http://omex-library.org/NewOmex.omex/NewModel.rdf#meta2> <http://purl.org/dc/terms/description> \"Cardiomyocyte cytosolic ATP concentration\" .\n";
    assertReadAndWrite(samples.singular_annotation4, "ntriples", expected);
}

TEST_F(ReadAndWriteTests, singularannotation4turtle) {
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix dcterms: <http://purl.org/dc/terms/> .\n"
                           "@prefix myOMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:meta2\n"
                           "    dcterms:description \"Cardiomyocyte cytosolic ATP concentration\" .\n"
                           "\n"
                           "";
    assertReadAndWrite(samples.singular_annotation4, "turtle", expected);
}

TEST_F(ReadAndWriteTests, singularannotation4rdfxmlxmp) {
    std::string expected = "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                           "   xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\"\n"
                           "   xmlns:myOMEXlib=\"http://omex-library.org/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <dcterms:description>Cardiomyocyte cytosolic ATP concentration</dcterms:description>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.singular_annotation4, "rdfxml-xmp", expected);
}

TEST_F(ReadAndWriteTests, singularannotation4rdfxmlabbrev) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                           "   xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\"\n"
                           "   xmlns:myOMEXlib=\"http://omex-library.org/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#meta2\">\n"
                           "    <dcterms:description>Cardiomyocyte cytosolic ATP concentration</dcterms:description>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.singular_annotation4, "rdfxml-abbrev", expected);
}

TEST_F(ReadAndWriteTests, singularannotation4rdfxml) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\" xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\" xmlns:myOMEXlib=\"http://omex-library.org/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#meta2\">\n"
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
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#meta2\" -> \"LCardiomyocyte cytosolic ATP concentration\" [ label=\"dcterms:description\" ];\n"
                           "\n"
                           "\t// Resources\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#meta2\" [ label=\"myOMEXlib:NewOmex.omex/NewModel.rdf#meta2\", shape = ellipse, color = blue ];\n"
                           "\n"
                           "\t// Anonymous nodes\n"
                           "\n"
                           "\t// Literals\n"
                           "\t\"LCardiomyocyte cytosolic ATP concentration\" [ label=\"Cardiomyocyte cytosolic ATP concentration\", shape = record ];\n"
                           "\n"
                           "\tlabel=\"\\n\\nModel:\\nfile://\\n\\nNamespaces:\\nbqbiol: http://biomodels.net/biology-qualifiers/\\ndcterms: http://purl.org/dc/terms/\\nmyOMEXlib: http://omex-library.org/\\nmyOMEX: http://omex-library.org/NewOmex.omex\\nlocal: http://omex-library.org/NewOmex.omex/NewModel.rdf#\\n\";\n"
                           "}\n"
                           "";
    assertReadAndWrite(samples.singular_annotation4, "dot", expected);
}

TEST_F(ReadAndWriteTests, singularannotation4jsontriples) {
    std::string expected = "{\n"
                           "  \"triples\" : [\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#meta2\",\n"
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
                           "  }\n";
    assertReadAndWrite(samples.singular_annotation4, "json-triples", expected);
}

TEST_F(ReadAndWriteTests, singularannotation4json) {
    std::string expected = "\n"
                           "{\n"
                           "  \"http://omex-library.org/NewOmex.omex/NewModel.rdf#meta2\" : {\n"
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
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#meta2\">http://omex-library.org/NewOmex.omex/NewModel.rdf#meta2</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://purl.org/dc/terms/description\">http://purl.org/dc/terms/description</a></span></td>\n"
                           "      <td><span class=\"literal\"><span class=\"value\">Cardiomyocyte cytosolic ATP concentration</span></span></td>\n"
                           "    </tr>\n"
                           "  </table>\n"
                           "  <p>Total number of triples: <span class=\"count\">1</span>.</p>\n"
                           "</body>\n"
                           "</html>\n";
    assertReadAndWrite(samples.singular_annotation4, "html", expected);
}

TEST_F(ReadAndWriteTests, singularannotation4nquads) {
    std::string expected = "<http://omex-library.org/NewOmex.omex/NewModel.rdf#meta2> <http://purl.org/dc/terms/description> \"Cardiomyocyte cytosolic ATP concentration\" .\n";
    assertReadAndWrite(samples.singular_annotation4, "nquads", expected);
}


/**********************************************************************
 * Tests for samples.composite_annotation_pe
 */


TEST_F(ReadAndWriteTests, compositeannotationpentriples) {
    std::string expected = "<http://omex-library.org/NewOmex.omex/NewModel.rdf#VLV> <http://biomodels.net/biology-qualifiers/isVersionOf> <http://identifiers.org/opb/OPB_00154> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#VLV> <http://biomodels.net/biology-qualifiers/isPropertyOf> <http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0> <http://biomodels.net/biology-qualifiers/is> <http://identifiers.org/fma/FMA:9670> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0> <http://biomodels.net/biology-qualifiers/isPartOf> <http://identifiers.org/fma/FMA:18228> .\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pe, "ntriples", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpeturtle) {
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix myOMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:VLV\n"
                           "    bqbiol:isPropertyOf local:entity_0 ;\n"
                           "    bqbiol:isVersionOf <http://identifiers.org/opb/OPB_00154> .\n"
                           "\n"
                           "local:entity_0\n"
                           "    bqbiol:is <http://identifiers.org/fma/FMA:9670> ;\n"
                           "    bqbiol:isPartOf <http://identifiers.org/fma/FMA:18228> .\n"
                           "\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pe, "turtle", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationperdfxmlxmp) {
    std::string expected = "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\"\n"
                           "   xmlns:myOMEXlib=\"http://omex-library.org/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"http://identifiers.org/opb/OPB_00154\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:9670\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"http://identifiers.org/fma/FMA:18228\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.composite_annotation_pe, "rdfxml-xmp", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationperdfxmlabbrev) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\"\n"
                           "   xmlns:myOMEXlib=\"http://omex-library.org/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#VLV\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"http://identifiers.org/opb/OPB_00154\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0\">\n"
                           "    <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:9670\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"http://identifiers.org/fma/FMA:18228\"/>\n"
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
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#VLV\" -> \"Rhttp://identifiers.org/opb/OPB_00154\" [ label=\"bqbiol:isVersionOf\" ];\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#VLV\" -> \"RmyOMEXlib:NewOmex.omex/NewModel.rdf#entity_0\" [ label=\"bqbiol:isPropertyOf\" ];\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#entity_0\" -> \"Rhttp://identifiers.org/fma/FMA:9670\" [ label=\"bqbiol:is\" ];\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#entity_0\" -> \"Rhttp://identifiers.org/fma/FMA:18228\" [ label=\"bqbiol:isPartOf\" ];\n"
                           "\n"
                           "\t// Resources\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#VLV\" [ label=\"myOMEXlib:NewOmex.omex/NewModel.rdf#VLV\", shape = ellipse, color = blue ];\n"
                           "\t\"Rhttp://identifiers.org/opb/OPB_00154\" [ label=\"http://identifiers.org/opb/OPB_00154\", shape = ellipse, color = blue ];\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#entity_0\" [ label=\"myOMEXlib:NewOmex.omex/NewModel.rdf#entity_0\", shape = ellipse, color = blue ];\n"
                           "\t\"Rhttp://identifiers.org/fma/FMA:9670\" [ label=\"http://identifiers.org/fma/FMA:9670\", shape = ellipse, color = blue ];\n"
                           "\t\"Rhttp://identifiers.org/fma/FMA:18228\" [ label=\"http://identifiers.org/fma/FMA:18228\", shape = ellipse, color = blue ];\n"
                           "\n"
                           "\t// Anonymous nodes\n"
                           "\n"
                           "\t// Literals\n"
                           "\n"
                           "\tlabel=\"\\n\\nModel:\\nfile://\\n\\nNamespaces:\\nbqbiol: http://biomodels.net/biology-qualifiers/\\nmyOMEXlib: http://omex-library.org/\\nmyOMEX: http://omex-library.org/NewOmex.omex\\nlocal: http://omex-library.org/NewOmex.omex/NewModel.rdf#\\n\";\n"
                           "}\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pe, "dot", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpejsontriples) {
    std::string expected = "{\n"
                           "  \"triples\" : [\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#VLV\",\n"
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
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#VLV\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://biomodels.net/biology-qualifiers/isPropertyOf\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0\",\n"
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
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0\",\n"
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
                           "  \"http://omex-library.org/NewOmex.omex/NewModel.rdf#VLV\" : {\n"
                           "    \"http://biomodels.net/biology-qualifiers/isPropertyOf\" : [ {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0\",\n"
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
                           "  \"http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0\" : {\n"
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
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#VLV\">http://omex-library.org/NewOmex.omex/NewModel.rdf#VLV</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isVersionOf\">http://biomodels.net/biology-qualifiers/isVersionOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://identifiers.org/opb/OPB_00154\">http://identifiers.org/opb/OPB_00154</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#VLV\">http://omex-library.org/NewOmex.omex/NewModel.rdf#VLV</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isPropertyOf\">http://biomodels.net/biology-qualifiers/isPropertyOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/is\">http://biomodels.net/biology-qualifiers/is</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://identifiers.org/fma/FMA:9670\">http://identifiers.org/fma/FMA:9670</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0</a></span></td>\n"
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
    std::string expected = "<http://omex-library.org/NewOmex.omex/NewModel.rdf#VLV> <http://biomodels.net/biology-qualifiers/isVersionOf> <http://identifiers.org/opb/OPB_00154> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#VLV> <http://biomodels.net/biology-qualifiers/isPropertyOf> <http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0> <http://biomodels.net/biology-qualifiers/is> <http://identifiers.org/fma/FMA:9670> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0> <http://biomodels.net/biology-qualifiers/isPartOf> <http://identifiers.org/fma/FMA:18228> .\n";
    assertReadAndWrite(samples.composite_annotation_pe, "nquads", expected);
}


/**********************************************************************
 * Tests for samples.composite_annotation_pp
 */


TEST_F(ReadAndWriteTests, compositeannotationppntriples) {
    std::string expected = "<http://omex-library.org/NewOmex.omex/NewModel.rdf#property_metaid_0> <http://biomodels.net/biology-qualifiers/isPropertyOf> <http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#property_metaid_0> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/OPB_00592> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0> <http://www.bhi.washington.edu/semsim#hasSourceParticipant> <http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0> <http://www.bhi.washington.edu/semsim#hasSinkParticipant> <http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0> <http://www.bhi.washington.edu/semsim#hasMediatorParticipant> <http://omex-library.org/NewOmex.omex/NewModel.rdf#mediator_0> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0> <http://www.bhi.washington.edu/semsim#hasMultiplier> \"1.0\" .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_0> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0> <http://www.bhi.washington.edu/semsim#hasMultiplier> \"2.0\" .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_1> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#mediator_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_2> .\n"
                           "";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.composite_annotation_pp, "ntriples", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationppturtle) {
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://www.bhi.washington.edu/semsim#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix myOMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:mediator_0\n"
                           "    semsim:hasPhysicalEntityReference local:special_metaid_2 .\n"
                           "\n"
                           "local:process_metaid_0\n"
                           "    semsim:hasMediatorParticipant local:mediator_0 ;\n"
                           "    semsim:hasSinkParticipant local:sink_0 ;\n"
                           "    semsim:hasSourceParticipant local:source_0 .\n"
                           "\n"
                           "local:property_metaid_0\n"
                           "    bqbiol:isPropertyOf local:process_metaid_0 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/OPB_00592> .\n"
                           "\n"
                           "local:sink_0\n"
                           "    semsim:hasMultiplier \"2.0\" ;\n"
                           "    semsim:hasPhysicalEntityReference local:special_metaid_1 .\n"
                           "\n"
                           "local:source_0\n"
                           "    semsim:hasMultiplier \"1.0\" ;\n"
                           "    semsim:hasPhysicalEntityReference local:special_metaid_0 .\n"
                           "\n";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.composite_annotation_pp, "turtle", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpprdfxmlxmp) {
    std::string expected = "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\"\n"
                           "   xmlns:myOMEXlib=\"http://omex-library.org/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_2\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <semsim:hasMediatorParticipant rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#mediator_0\"/>\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_00592\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <semsim:hasMultiplier>2.0</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <semsim:hasMultiplier>1.0</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_0\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.composite_annotation_pp, "rdfxml-xmp", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpprdfxmlabbrev) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\"\n"
                           "   xmlns:myOMEXlib=\"http://omex-library.org/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\">\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#mediator_0\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_2\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0\">\n"
                           "    <semsim:hasMediatorParticipant rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#mediator_0\"/>\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#property_metaid_0\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_00592\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0\">\n"
                           "    <semsim:hasMultiplier>2.0</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0\">\n"
                           "    <semsim:hasMultiplier>1.0</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_0\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pp, "rdfxml-abbrev", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpprdfxml) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\" xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\" xmlns:myOMEXlib=\"http://omex-library.org/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\">\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#property_metaid_0\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#property_metaid_0\">\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_00592\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0\">\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0\">\n"
                           "    <semsim:hasMediatorParticipant rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#mediator_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0\">\n"
                           "    <semsim:hasMultiplier>1.0</semsim:hasMultiplier>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0\">\n"
                           "    <semsim:hasMultiplier>2.0</semsim:hasMultiplier>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#mediator_0\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_2\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pp, "rdfxml", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationppdot) {
    std::string expected = "digraph {\n"
                           "\trankdir = LR;\n"
                           "\tcharset=\"utf-8\";\n"
                           "\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#property_metaid_0\" -> \"RmyOMEXlib:NewOmex.omex/NewModel.rdf#process_metaid_0\" [ label=\"bqbiol:isPropertyOf\" ];\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#property_metaid_0\" -> \"Rhttps://identifiers.org/opb/OPB_00592\" [ label=\"bqbiol:isVersionOf\" ];\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#process_metaid_0\" -> \"RmyOMEXlib:NewOmex.omex/NewModel.rdf#source_0\" [ label=\"semsim:hasSourceParticipant\" ];\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#process_metaid_0\" -> \"RmyOMEXlib:NewOmex.omex/NewModel.rdf#sink_0\" [ label=\"semsim:hasSinkParticipant\" ];\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#process_metaid_0\" -> \"RmyOMEXlib:NewOmex.omex/NewModel.rdf#mediator_0\" [ label=\"semsim:hasMediatorParticipant\" ];\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#source_0\" -> \"L1.0\" [ label=\"semsim:hasMultiplier\" ];\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#source_0\" -> \"RmyOMEXlib:NewOmex.omex/NewModel.rdf#special_metaid_0\" [ label=\"semsim:hasPhysicalEntityReference\" ];\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#sink_0\" -> \"L2.0\" [ label=\"semsim:hasMultiplier\" ];\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#sink_0\" -> \"RmyOMEXlib:NewOmex.omex/NewModel.rdf#special_metaid_1\" [ label=\"semsim:hasPhysicalEntityReference\" ];\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#mediator_0\" -> \"RmyOMEXlib:NewOmex.omex/NewModel.rdf#special_metaid_2\" [ label=\"semsim:hasPhysicalEntityReference\" ];\n"
                           "\n"
                           "\t// Resources\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#property_metaid_0\" [ label=\"myOMEXlib:NewOmex.omex/NewModel.rdf#property_metaid_0\", shape = ellipse, color = blue ];\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#process_metaid_0\" [ label=\"myOMEXlib:NewOmex.omex/NewModel.rdf#process_metaid_0\", shape = ellipse, color = blue ];\n"
                           "\t\"Rhttps://identifiers.org/opb/OPB_00592\" [ label=\"https://identifiers.org/opb/OPB_00592\", shape = ellipse, color = blue ];\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#source_0\" [ label=\"myOMEXlib:NewOmex.omex/NewModel.rdf#source_0\", shape = ellipse, color = blue ];\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#sink_0\" [ label=\"myOMEXlib:NewOmex.omex/NewModel.rdf#sink_0\", shape = ellipse, color = blue ];\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#mediator_0\" [ label=\"myOMEXlib:NewOmex.omex/NewModel.rdf#mediator_0\", shape = ellipse, color = blue ];\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#special_metaid_0\" [ label=\"myOMEXlib:NewOmex.omex/NewModel.rdf#special_metaid_0\", shape = ellipse, color = blue ];\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#special_metaid_1\" [ label=\"myOMEXlib:NewOmex.omex/NewModel.rdf#special_metaid_1\", shape = ellipse, color = blue ];\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#special_metaid_2\" [ label=\"myOMEXlib:NewOmex.omex/NewModel.rdf#special_metaid_2\", shape = ellipse, color = blue ];\n"
                           "\n"
                           "\t// Anonymous nodes\n"
                           "\n"
                           "\t// Literals\n"
                           "\t\"L1.0\" [ label=\"1.0\", shape = record ];\n"
                           "\t\"L2.0\" [ label=\"2.0\", shape = record ];\n"
                           "\n"
                           "\tlabel=\"\\n\\nModel:\\nfile://\\n\\nNamespaces:\\nsemsim: http://www.bhi.washington.edu/semsim#\\nbqbiol: http://biomodels.net/biology-qualifiers/\\nmyOMEXlib: http://omex-library.org/\\nmyOMEX: http://omex-library.org/NewOmex.omex\\nlocal: http://omex-library.org/NewOmex.omex/NewModel.rdf#\\n\";\n"
                           "}\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pp, "dot", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationppjsontriples) {
    std::string expected = "{\n"
                           "  \"triples\" : [\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#property_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://biomodels.net/biology-qualifiers/isPropertyOf\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#property_metaid_0\",\n"
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
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasSourceParticipant\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasSinkParticipant\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasMediatorParticipant\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#mediator_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0\",\n"
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
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0\",\n"
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
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_1\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#mediator_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_2\",\n"
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
                           "  \"http://omex-library.org/NewOmex.omex/NewModel.rdf#mediator_0\" : {\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\" : [ {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_2\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  ,\n"
                           "  \"http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0\" : {\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasMediatorParticipant\" : [ {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#mediator_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ],\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasSinkParticipant\" : [ {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ],\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasSourceParticipant\" : [ {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  ,\n"
                           "  \"http://omex-library.org/NewOmex.omex/NewModel.rdf#property_metaid_0\" : {\n"
                           "    \"http://biomodels.net/biology-qualifiers/isPropertyOf\" : [ {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0\",\n"
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
                           "  \"http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0\" : {\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasMultiplier\" : [ {\n"
                           "        \"value\" : \"2.0\",\n"
                           "        \"type\" : \"literal\"\n"
                           "        }\n"
                           "      \n"
                           "      ],\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\" : [ {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_1\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  ,\n"
                           "  \"http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0\" : {\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasMultiplier\" : [ {\n"
                           "        \"value\" : \"1.0\",\n"
                           "        \"type\" : \"literal\"\n"
                           "        }\n"
                           "      \n"
                           "      ],\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\" : [ {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_0\",\n"
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
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#property_metaid_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#property_metaid_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isPropertyOf\">http://biomodels.net/biology-qualifiers/isPropertyOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#property_metaid_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#property_metaid_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isVersionOf\">http://biomodels.net/biology-qualifiers/isVersionOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"https://identifiers.org/opb/OPB_00592\">https://identifiers.org/opb/OPB_00592</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasSourceParticipant\">http://www.bhi.washington.edu/semsim#hasSourceParticipant</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasSinkParticipant\">http://www.bhi.washington.edu/semsim#hasSinkParticipant</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasMediatorParticipant\">http://www.bhi.washington.edu/semsim#hasMediatorParticipant</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#mediator_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#mediator_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasMultiplier\">http://www.bhi.washington.edu/semsim#hasMultiplier</a></span></td>\n"
                           "      <td><span class=\"literal\"><span class=\"value\">1.0</span></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\">http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasMultiplier\">http://www.bhi.washington.edu/semsim#hasMultiplier</a></span></td>\n"
                           "      <td><span class=\"literal\"><span class=\"value\">2.0</span></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\">http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_1\">http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_1</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#mediator_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#mediator_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\">http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_2\">http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_2</a></span></td>\n"
                           "    </tr>\n"
                           "  </table>\n"
                           "  <p>Total number of triples: <span class=\"count\">10</span>.</p>\n"
                           "</body>\n"
                           "</html>\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pp, "html", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationppnquads) {
    std::string expected = "<http://omex-library.org/NewOmex.omex/NewModel.rdf#property_metaid_0> <http://biomodels.net/biology-qualifiers/isPropertyOf> <http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#property_metaid_0> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/OPB_00592> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0> <http://www.bhi.washington.edu/semsim#hasSourceParticipant> <http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0> <http://www.bhi.washington.edu/semsim#hasSinkParticipant> <http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#process_metaid_0> <http://www.bhi.washington.edu/semsim#hasMediatorParticipant> <http://omex-library.org/NewOmex.omex/NewModel.rdf#mediator_0> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0> <http://www.bhi.washington.edu/semsim#hasMultiplier> \"1.0\" .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_0> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0> <http://www.bhi.washington.edu/semsim#hasMultiplier> \"2.0\" .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_1> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#mediator_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_2> .\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pp, "nquads", expected);
}


/**********************************************************************
 * Tests for samples.composite_annotation_pf
 */


TEST_F(ReadAndWriteTests, compositeannotationpfntriples) {
    std::string expected = "<http://omex-library.org/NewOmex.omex/NewModel.rdf#parameter_metaid_0> <http://biomodels.net/biology-qualifiers/isPropertyOf> <http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#parameter_metaid_0> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/OPB_01058> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0> <http://www.bhi.washington.edu/semsim#hasSourceParticipant> <http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0> <http://www.bhi.washington.edu/semsim#hasSinkParticipant> <http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_0> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_1> .\n";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.composite_annotation_pf, "ntriples", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpfturtle) {
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://www.bhi.washington.edu/semsim#> .\n"
                           "@prefix bqmodel: <http://biomodels.net/model-qualifiers/> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix myOMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:force_0\n"
                           "    semsim:hasSinkParticipant local:sink_0 ;\n"
                           "    semsim:hasSourceParticipant local:source_0 .\n"
                           "\n"
                           "local:parameter_metaid_0\n"
                           "    bqbiol:isPropertyOf local:force_0 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/OPB_01058> .\n"
                           "\n"
                           "local:sink_0\n"
                           "    semsim:hasPhysicalEntityReference local:special_metaid_1 .\n"
                           "\n"
                           "local:source_0\n"
                           "    semsim:hasPhysicalEntityReference local:special_metaid_0 .\n"
                           "";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.composite_annotation_pf, "turtle", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpfrdfxmlxmp) {
    std::string expected = "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                           "   xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\"\n"
                           "   xmlns:myOMEXlib=\"http://omex-library.org/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_01058\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_0\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.composite_annotation_pf, "rdfxml-xmp", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpfrdfxmlabbrev) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                           "   xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\"\n"
                           "   xmlns:myOMEXlib=\"http://omex-library.org/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\">\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#parameter_metaid_0\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_01058\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_0\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
                           assertReadAndWrite(samples.composite_annotation_pf, "rdfxml-abbrev", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpfrdfxml) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\" xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\" xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\" xmlns:myOMEXlib=\"http://omex-library.org/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\">\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#parameter_metaid_0\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#parameter_metaid_0\">\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_01058\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0\">\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_1\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pf, "rdfxml", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpfdot) {
    std::string expected = "";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.composite_annotation_pf, "dot", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpfjsontriples) {
    std::string expected = "{\n"
                           "  \"triples\" : [\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#parameter_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://biomodels.net/biology-qualifiers/isPropertyOf\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#parameter_metaid_0\",\n"
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
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasSourceParticipant\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasSinkParticipant\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_1\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      }\n"
                           "    ]\n"
                           "  }\n";
    assertReadAndWrite(samples.composite_annotation_pf, "json-triples", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpfjson) {
    std::string expected = "\n"
                           "{\n"
                           "  \"http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0\" : {\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasSinkParticipant\" : [ {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ],\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasSourceParticipant\" : [ {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  ,\n"
                           "  \"http://omex-library.org/NewOmex.omex/NewModel.rdf#parameter_metaid_0\" : {\n"
                           "    \"http://biomodels.net/biology-qualifiers/isPropertyOf\" : [ {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0\",\n"
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
                           "  \"http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0\" : {\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\" : [ {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_1\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  ,\n"
                           "  \"http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0\" : {\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\" : [ {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  }\n";
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
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#parameter_metaid_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#parameter_metaid_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isPropertyOf\">http://biomodels.net/biology-qualifiers/isPropertyOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#parameter_metaid_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#parameter_metaid_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isVersionOf\">http://biomodels.net/biology-qualifiers/isVersionOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"https://identifiers.org/opb/OPB_01058\">https://identifiers.org/opb/OPB_01058</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasSourceParticipant\">http://www.bhi.washington.edu/semsim#hasSourceParticipant</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasSinkParticipant\">http://www.bhi.washington.edu/semsim#hasSinkParticipant</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\">http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\">http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_1\">http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_1</a></span></td>\n"
                           "    </tr>\n"
                           "  </table>\n"
                           "  <p>Total number of triples: <span class=\"count\">6</span>.</p>\n"
                           "</body>\n"
                           "</html>\n";
    assertReadAndWrite(samples.composite_annotation_pf, "html", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpfnquads) {
    std::string expected = "<http://omex-library.org/NewOmex.omex/NewModel.rdf#parameter_metaid_0> <http://biomodels.net/biology-qualifiers/isPropertyOf> <http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#parameter_metaid_0> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/OPB_01058> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0> <http://www.bhi.washington.edu/semsim#hasSourceParticipant> <http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#force_0> <http://www.bhi.washington.edu/semsim#hasSinkParticipant> <http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#source_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_0> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#sink_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <http://omex-library.org/NewOmex.omex/NewModel.rdf#special_metaid_1> .\n";
    assertReadAndWrite(samples.composite_annotation_pf, "nquads", expected);
}


/**********************************************************************
 * Tests for samples.tabular_data1
 */

TEST_F(ReadAndWriteTests, tabulardatantriples) {
    std::string expected = "<http://omex-library.org/NewOmex.omex/NewModel.rdf#VleftCorArt> <http://biomodels.net/biology-qualifiers/isVersionOf> <http://identifiers.org/opb/OPB_00154> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#VleftCorArt> <http://biomodels.net/biology-qualifiers/isPropertyOf> <http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0> <http://biomodels.net/biology-qualifiers/is> <http://identifiers.org/fma/FMA:9670> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0> <http://biomodels.net/biology-qualifiers/isPartOf> <http://identifiers.org/fma/FMA:18228> .\n"
                           "";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.tabular_data1, "ntriples", expected);
}

TEST_F(ReadAndWriteTests, tabulardataturtle) {
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqmodel: <http://biomodels.net/model-qualifiers/> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix semsim: <http://www.bhi.washington.edu/semsim#> .\n"
                           "@prefix myOMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:VleftCorArt\n"
                           "    bqbiol:isPropertyOf local:entity_0 ;\n"
                           "    bqbiol:isVersionOf <http://identifiers.org/opb/OPB_00154> .\n"
                           "\n"
                           "local:entity_0\n"
                           "    bqbiol:is <http://identifiers.org/fma/FMA:9670> ;\n"
                           "    bqbiol:isPartOf <http://identifiers.org/fma/FMA:18228> .\n"
                           "\n"
                           "";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.tabular_data1, "turtle", expected);
}

TEST_F(ReadAndWriteTests, tabulardatardfxmlxmp) {
    std::string expected = "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                           "   xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\"\n"
                           "   xmlns:myOMEXlib=\"http://omex-library.org/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"http://identifiers.org/opb/OPB_00154\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:9670\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"http://identifiers.org/fma/FMA:18228\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWriteRegularExpressionSplitByNewline(samples.tabular_data1, "rdfxml-xmp", expected);
}

TEST_F(ReadAndWriteTests, tabulardatardfxmlabbrev) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                           "   xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\"\n"
                           "   xmlns:myOMEXlib=\"http://omex-library.org/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\">\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#VleftCorArt\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"http://identifiers.org/opb/OPB_00154\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0\">\n"
                           "    <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:9670\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"http://identifiers.org/fma/FMA:18228\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    assertReadAndWrite(samples.tabular_data1, "rdfxml-abbrev", expected);
}

TEST_F(ReadAndWriteTests, tabulardatardfxml) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\" xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\" xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\" xmlns:myOMEXlib=\"http://omex-library.org/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\">\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#VleftCorArt\">\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"http://identifiers.org/opb/OPB_00154\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#VleftCorArt\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0\">\n"
                           "    <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:9670\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0\">\n"
                           "    <bqbiol:isPartOf rdf:resource=\"http://identifiers.org/fma/FMA:18228\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.tabular_data1, "rdfxml", expected);
}

TEST_F(ReadAndWriteTests, tabulardatadot) {
    std::string expected = "digraph {\n"
                           "\trankdir = LR;\n"
                           "\tcharset=\"utf-8\";\n"
                           "\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#VleftCorArt\" -> \"Rhttp://identifiers.org/opb/OPB_00154\" [ label=\"bqbiol:isVersionOf\" ];\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#VleftCorArt\" -> \"RmyOMEXlib:NewOmex.omex/NewModel.rdf#entity_0\" [ label=\"bqbiol:isPropertyOf\" ];\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#entity_0\" -> \"Rhttp://identifiers.org/fma/FMA:9670\" [ label=\"bqbiol:is\" ];\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#entity_0\" -> \"Rhttp://identifiers.org/fma/FMA:18228\" [ label=\"bqbiol:isPartOf\" ];\n"
                           "\n"
                           "\t// Resources\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#VleftCorArt\" [ label=\"myOMEXlib:NewOmex.omex/NewModel.rdf#VleftCorArt\", shape = ellipse, color = blue ];\n"
                           "\t\"Rhttp://identifiers.org/opb/OPB_00154\" [ label=\"http://identifiers.org/opb/OPB_00154\", shape = ellipse, color = blue ];\n"
                           "\t\"RmyOMEXlib:NewOmex.omex/NewModel.rdf#entity_0\" [ label=\"myOMEXlib:NewOmex.omex/NewModel.rdf#entity_0\", shape = ellipse, color = blue ];\n"
                           "\t\"Rhttp://identifiers.org/fma/FMA:9670\" [ label=\"http://identifiers.org/fma/FMA:9670\", shape = ellipse, color = blue ];\n"
                           "\t\"Rhttp://identifiers.org/fma/FMA:18228\" [ label=\"http://identifiers.org/fma/FMA:18228\", shape = ellipse, color = blue ];\n"
                           "\n"
                           "\t// Anonymous nodes\n"
                           "\n"
                           "\t// Literals\n"
                           "\n"
                           "\tlabel=\"\\n\\nModel:\\nfile://\\n\\nNamespaces:\\nbqmodel: http://biomodels.net/model-qualifiers/\\nbqbiol: http://biomodels.net/biology-qualifiers/\\nsemsim: http://www.bhi.washington.edu/semsim#\\nmyOMEXlib: http://omex-library.org/\\nmyOMEX: http://omex-library.org/NewOmex.omex\\nlocal: http://omex-library.org/NewOmex.omex/NewModel.rdf#\\n\";\n"
                           "}\n";
    assertReadAndWrite(samples.tabular_data1, "dot", expected);
}

TEST_F(ReadAndWriteTests, tabulardatajsontriples) {
    std::string expected = "{\n"
                           "  \"triples\" : [\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#VleftCorArt\",\n"
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
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#VleftCorArt\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://biomodels.net/biology-qualifiers/isPropertyOf\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0\",\n"
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
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0\",\n"
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
                           "  \"http://omex-library.org/NewOmex.omex/NewModel.rdf#VleftCorArt\" : {\n"
                           "    \"http://biomodels.net/biology-qualifiers/isPropertyOf\" : [ {\n"
                           "        \"value\" : \"http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0\",\n"
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
                           "  \"http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0\" : {\n"
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
                           "  }\n";
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
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#VleftCorArt\">http://omex-library.org/NewOmex.omex/NewModel.rdf#VleftCorArt</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isVersionOf\">http://biomodels.net/biology-qualifiers/isVersionOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://identifiers.org/opb/OPB_00154\">http://identifiers.org/opb/OPB_00154</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#VleftCorArt\">http://omex-library.org/NewOmex.omex/NewModel.rdf#VleftCorArt</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isPropertyOf\">http://biomodels.net/biology-qualifiers/isPropertyOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/is\">http://biomodels.net/biology-qualifiers/is</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://identifiers.org/fma/FMA:9670\">http://identifiers.org/fma/FMA:9670</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0\">http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0</a></span></td>\n"
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
    std::string expected = "<http://omex-library.org/NewOmex.omex/NewModel.rdf#VleftCorArt> <http://biomodels.net/biology-qualifiers/isVersionOf> <http://identifiers.org/opb/OPB_00154> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#VleftCorArt> <http://biomodels.net/biology-qualifiers/isPropertyOf> <http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0> <http://biomodels.net/biology-qualifiers/is> <http://identifiers.org/fma/FMA:9670> .\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.rdf#entity_0> <http://biomodels.net/biology-qualifiers/isPartOf> <http://identifiers.org/fma/FMA:18228> .\n";
    assertReadAndWrite(samples.tabular_data1, "nquads", expected);
}

/******************************************************************************
 * ReadAndWriteTests for sbml files
 */

//TEST_F(ReadAndWriteTests, SBML1) {
//    omexmeta::OmexMetaUtils::download(samples
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
//    omexmeta::OmexMetaUtils::download(samples.cellml_url1, samples.cellml_filename1);
//    omexmeta::RDF rdf = omexmeta::RDF::fromXML(samples.cellml_filename1, "turtle");
//    std::string extracted = rdf.toString("rdfxml");
//    std::cout << extracted << std::endl;
////    int expected = 32;
////    int actual = sizeof(extracted);
////    ASSERT_EQ(expected, actual);
//}
//
//








