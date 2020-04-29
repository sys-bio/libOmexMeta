//
// Created by Ciaran on 4/8/2020.
//


#include <utility>

#include "gtest/gtest.h"
#include "semsim/RDF.h"
#include "semsim/SemSim.h"
#include "AnnotationSamples.h"

# include "combine/combinearchive.h"
# include "combine/knownformats.h"
# include "combine/omexdescription.h"

#include "curl/curl.h"
#include "SBMLFactory.h"

class RDFTests : public ::testing::Test {

public:

    AnnotationSamples samples;

    RDFTests() = default;

    void TearDown() override {
        samples.removeAllFilesIfTheyExist();
    }
};

TEST_F(RDFTests, TestGetOptions) {
    std::ostringstream os = semsim::RDF::listOptions();
    std::string expected = "option, name, label, domain, value type, url\n"
                           "0,scanForRDF,RDF/XML parser scans for rdf:RDF in XML content,3,0,http://feature.librdf.org/raptor-scanForRDF\n"
                           "1,allowNonNsAttributes,RDF/XML parser allows bare 'name' rather than namespaced 'rdf:name',3,0,http://feature.librdf.org/raptor-allowNonNsAttributes\n"
                           "2,allowOtherParsetypes,RDF/XML parser allows user-defined rdf:parseType values,3,0,http://feature.librdf.org/raptor-allowOtherParsetypes\n"
                           "3,allowBagID,RDF/XML parser allows rdf:bagID,3,0,http://feature.librdf.org/raptor-allowBagID\n"
                           "4,allowRDFtypeRDFlist,RDF/XML parser generates the collection rdf:type rdf:List triple,3,0,http://feature.librdf.org/raptor-allowRDFtypeRDFlist\n"
                           "5,normalizeLanguage,RDF/XML parser normalizes xml:lang values to lowercase,3,0,http://feature.librdf.org/raptor-normalizeLanguage\n"
                           "6,nonNFCfatal,RDF/XML parser makes non-NFC literals a fatal error,3,0,http://feature.librdf.org/raptor-nonNFCfatal\n"
                           "7,warnOtherParseTypes,RDF/XML parser warns about unknown rdf:parseType values,3,0,http://feature.librdf.org/raptor-warnOtherParseTypes\n"
                           "8,checkRdfID,RDF/XML parser checks rdf:ID values for duplicates,3,0,http://feature.librdf.org/raptor-checkRdfID\n"
                           "9,relativeURIs,Serializers write relative URIs wherever possible.,6,0,http://feature.librdf.org/raptor-relativeURIs\n"
                           "13,xmlVersion,Serializers and XML Writer use as XML version to write.,6,1,http://feature.librdf.org/raptor-xmlVersion\n"
                           "14,xmlDeclaration,Serializers and XML Writer write XML declaration.,6,0,http://feature.librdf.org/raptor-xmlDeclaration\n"
                           "15,noNet,Parsers and SAX2 XML Parser deny internal network requests.,3,0,http://feature.librdf.org/raptor-noNet\n"
                           "16,resourceBorder,DOT serializer resource border color,6,2,http://feature.librdf.org/raptor-resourceBorder\n"
                           "17,literalBorder,DOT serializer literal border color,6,2,http://feature.librdf.org/raptor-literalBorder\n"
                           "18,bnodeBorder,DOT serializer blank node border color,6,2,http://feature.librdf.org/raptor-bnodeBorder\n"
                           "19,resourceFill,DOT serializer resource fill color,6,2,http://feature.librdf.org/raptor-resourceFill\n"
                           "20,literalFill,DOT serializer literal fill color,6,2,http://feature.librdf.org/raptor-literalFill\n"
                           "21,bnodeFill,DOT serializer blank node fill color,6,2,http://feature.librdf.org/raptor-bnodeFill\n"
                           "22,htmlTagSoup,GRDDL parser uses a lax HTML parser,3,0,http://feature.librdf.org/raptor-htmlTagSoup\n"
                           "23,microformats,GRDDL parser looks for microformats,3,0,http://feature.librdf.org/raptor-microformats\n"
                           "24,htmlLink,GRDDL parser looks for <link type=\"application/rdf+xml\">,3,0,http://feature.librdf.org/raptor-htmlLink\n"
                           "25,wwwTimeout,Parser WWW request retrieval timeout,3,1,http://feature.librdf.org/raptor-wwwTimeout\n"
                           "26,writeBaseURI,Serializers write a base URI directive @base / xml:base,6,0,http://feature.librdf.org/raptor-writeBaseURI\n"
                           "27,wwwHttpCacheControl,Parser WWW request HTTP Cache-Control: header value,3,2,http://feature.librdf.org/raptor-wwwHttpCacheControl\n"
                           "28,wwwHttpUserAgent,Parser WWW request HTTP User-Agent: header value,3,2,http://feature.librdf.org/raptor-wwwHttpUserAgent\n"
                           "29,jsonCallback,JSON serializer callback function name,6,2,http://feature.librdf.org/raptor-jsonCallback\n"
                           "30,jsonExtraData,JSON serializer callback data parameter,6,2,http://feature.librdf.org/raptor-jsonExtraData\n"
                           "31,rssTriples,Atom and RSS serializers write extra RDF triples,6,2,http://feature.librdf.org/raptor-rssTriples\n"
                           "32,atomEntryUri,Atom serializer writes an atom:entry with this URI (otherwise atom:feed),6,3,http://feature.librdf.org/raptor-atomEntryUri\n"
                           "33,prefixElements,Atom and RSS serializers write namespace-prefixed elements,6,0,http://feature.librdf.org/raptor-prefixElements\n"
                           "34,strict,Operate in strict conformance mode (otherwise lax),3,0,http://feature.librdf.org/raptor-strict\n"
                           "35,wwwCertFilename,SSL client certificate filename,3,2,http://feature.librdf.org/raptor-wwwCertFilename\n"
                           "36,wwwCertType,SSL client certificate type,3,2,http://feature.librdf.org/raptor-wwwCertType\n"
                           "37,wwwCertPassphrase,SSL client certificate passphrase,3,2,http://feature.librdf.org/raptor-wwwCertPassphrase\n"
                           "38,noFile,Parsers and SAX2 deny internal file requests.,3,0,http://feature.librdf.org/raptor-noFile\n"
                           "39,wwwSslVerifyPeer,SSL verify peer certficate,3,1,http://feature.librdf.org/raptor-wwwSslVerifyPeer\n"
                           "40,wwwSslVerifyHost,SSL verify host matching,3,1,http://feature.librdf.org/raptor-wwwSslVerifyHost\n";
    ASSERT_STREQ(expected.c_str(), os.str().c_str());
}

TEST_F(RDFTests, TestNamespacesSize){
    semsim::RDF rdf = semsim::RDF::fromString(
            samples.composite_annotation_pp
            );
    std::string s = rdf.toString("rdfxml-abbrev", "./annotations.rdf");

    std::cout << s << std::endl;
    int x = rdf.getNamespaces().size();
    ASSERT_EQ(2, x);
}

TEST_F(RDFTests, TestBaseUri){
    semsim::RDF rdf;
    std::string expected = "file://./semsim_model.rdf";
    std::string actual = (const char*) librdf_uri_as_string(rdf.getBaseUri());
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}



class ReadAndWriteTests : public ::testing::Test {

public:

    AnnotationSamples samples;

    ReadAndWriteTests() = default;

    void assertReadAndWrite(const std::string& input_annot, const std::string& input_format, const std::string &expected_output) {
        semsim::RDF rdf = semsim::RDF::fromString(input_annot, "rdfxml");
        std::string actual = rdf.toString(input_format, "file://./annotations.rdf");
        std::cout << actual << std::endl;
        ASSERT_STREQ(expected_output.c_str(), actual.c_str());
    }

};


TEST_F(ReadAndWriteTests, TestDefaultConstructor) {
    semsim::RDF rdf;
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
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<?xpacket begin='\uFEFF' id='W5M0MpCehiHzreSzNTczkc9d'?>\n"
                           "<x:xmpmeta xmlns:x='adobe:ns:meta/'>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/uniprot/P0DP23\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "</x:xmpmeta>\n"
                           "<?xpacket end='r'?>\n"
                           "";
    assertReadAndWrite(samples.singular_annotation1, "rdfxml-xmp", expected);
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
    assertReadAndWrite(samples.singular_annotation2, "turtle", expected);
}

TEST_F(ReadAndWriteTests, singularannotation2rdfxmlxmp) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<?xpacket begin='\uFEFF' id='W5M0MpCehiHzreSzNTczkc9d'?>\n"
                           "<x:xmpmeta xmlns:x='adobe:ns:meta/'>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqmodel:isDescribedBy rdf:resource=\"https://identifiers.org/pubmed/12991237\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "</x:xmpmeta>\n"
                           "<?xpacket end='r'?>\n"
                           "";
    assertReadAndWrite(samples.singular_annotation2, "rdfxml-xmp", expected);
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
    std::string expected = "digraph {\n"
                           "\trankdir = LR;\n"
                           "\tcharset=\"utf-8\";\n"
                           "\n"
                           "\t\"Rfile://./MyModel.xml#modelmeta1\" -> \"Rhttps://identifiers.org/pubmed/12991237\" [ label=\"bqmodel:isDescribedBy\" ];\n"
                           "\n"
                           "\t// Resources\n"
                           "\t\"Rfile://./MyModel.xml#modelmeta1\" [ label=\"file://./MyModel.xml#modelmeta1\", shape = ellipse, color = blue ];\n"
                           "\t\"Rhttps://identifiers.org/pubmed/12991237\" [ label=\"https://identifiers.org/pubmed/12991237\", shape = ellipse, color = blue ];\n"
                           "\n"
                           "\t// Anonymous nodes\n"
                           "\n"
                           "\t// Literals\n"
                           "\n"
                           "\tlabel=\"\\n\\nModel:\\nfile://./annotations.rdf\\n\\nNamespaces:\\nbqbiol: http://biomodels.net/biology-qualifiers/\\nbqmodel: http://biomodels.net/model-qualifiers/\\n\";\n"
                           "}\n"
                           "";
    assertReadAndWrite(samples.singular_annotation2, "dot", expected);
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
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<?xpacket begin='\uFEFF' id='W5M0MpCehiHzreSzNTczkc9d'?>\n"
                           "<x:xmpmeta xmlns:x='adobe:ns:meta/'>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/chebi/CHEBI:15422\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "</x:xmpmeta>\n"
                           "<?xpacket end='r'?>\n"
                           "";
    assertReadAndWrite(samples.singular_annotation3, "rdfxml-xmp", expected);
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
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<?xpacket begin='\uFEFF' id='W5M0MpCehiHzreSzNTczkc9d'?>\n"
                           "<x:xmpmeta xmlns:x='adobe:ns:meta/'>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <dcterms:description>Cardiomyocyte cytosolic ATP concentration</dcterms:description>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "</x:xmpmeta>\n"
                           "<?xpacket end='r'?>\n"
                           "";
    assertReadAndWrite(samples.singular_annotation4, "rdfxml-xmp", expected);
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
    std::string expected = "<file://./MyModel.xml#VLV> <http://biomodels.net/biology-qualifiers/isVersionOf> <http://identifiers.org/opb/OPB_00154> .\n"
                           "<file://./MyModel.xml#VLV> <http://biomodels.net/biology-qualifiers/isPropertyOf> <file://./annotations.rdf#entity_0> .\n"
                           "<file://./annotations.rdf#entity_0> <http://biomodels.net/biology-qualifiers/is> <http://identifiers.org/fma/FMA:9670> .\n"
                           "<file://./annotations.rdf#entity_0> <http://biomodels.net/biology-qualifiers/isPartOf> <http://identifiers.org/fma/FMA:18228> .\n";
    assertReadAndWrite(samples.composite_annotation_pe, "ntriples", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpeturtle) {
    std::string expected = "@base <file://./annotations.rdf> .\n"
                           "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "\n"
                           "<MyModel.xml#VLV>\n"
                           "    bqbiol:isPropertyOf <#entity_0> ;\n"
                           "    bqbiol:isVersionOf <http://identifiers.org/opb/OPB_00154> .\n"
                           "\n"
                           "<#entity_0>\n"
                           "    bqbiol:is <http://identifiers.org/fma/FMA:9670> ;\n"
                           "    bqbiol:isPartOf <http://identifiers.org/fma/FMA:18228> .\n"
                           "\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pe, "turtle", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationperdfxmlxmp) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<?xpacket begin='\uFEFF' id='W5M0MpCehiHzreSzNTczkc9d'?>\n"
                           "<x:xmpmeta xmlns:x='adobe:ns:meta/'>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"#entity_0\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"http://identifiers.org/opb/OPB_00154\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:9670\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"http://identifiers.org/fma/FMA:18228\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "</x:xmpmeta>\n"
                           "<?xpacket end='r'?>\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pe, "rdfxml-xmp", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationperdfxmlabbrev) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"MyModel.xml#VLV\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"#entity_0\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"http://identifiers.org/opb/OPB_00154\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"#entity_0\">\n"
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
                           "\t\"Rfile://./MyModel.xml#VLV\" -> \"Rhttp://identifiers.org/opb/OPB_00154\" [ label=\"bqbiol:isVersionOf\" ];\n"
                           "\t\"Rfile://./MyModel.xml#VLV\" -> \"Rfile://./annotations.rdf#entity_0\" [ label=\"bqbiol:isPropertyOf\" ];\n"
                           "\t\"Rfile://./annotations.rdf#entity_0\" -> \"Rhttp://identifiers.org/fma/FMA:9670\" [ label=\"bqbiol:is\" ];\n"
                           "\t\"Rfile://./annotations.rdf#entity_0\" -> \"Rhttp://identifiers.org/fma/FMA:18228\" [ label=\"bqbiol:isPartOf\" ];\n"
                           "\n"
                           "\t// Resources\n"
                           "\t\"Rfile://./MyModel.xml#VLV\" [ label=\"file://./MyModel.xml#VLV\", shape = ellipse, color = blue ];\n"
                           "\t\"Rhttp://identifiers.org/opb/OPB_00154\" [ label=\"http://identifiers.org/opb/OPB_00154\", shape = ellipse, color = blue ];\n"
                           "\t\"Rfile://./annotations.rdf#entity_0\" [ label=\"file://./annotations.rdf#entity_0\", shape = ellipse, color = blue ];\n"
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
                           "        \"value\" : \"MyModel.xml#VLV\",\n"
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
                           "        \"value\" : \"MyModel.xml#VLV\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://biomodels.net/biology-qualifiers/isPropertyOf\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"#entity_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"#entity_0\",\n"
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
                           "        \"value\" : \"#entity_0\",\n"
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
                           "  \"MyModel.xml#VLV\" : {\n"
                           "    \"http://biomodels.net/biology-qualifiers/isPropertyOf\" : [ {\n"
                           "        \"value\" : \"#entity_0\",\n"
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
                           "  \"#entity_0\" : {\n"
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
                           "      <td><span class=\"uri\"><a href=\"file://./MyModel.xml#VLV\">file://./MyModel.xml#VLV</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isVersionOf\">http://biomodels.net/biology-qualifiers/isVersionOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://identifiers.org/opb/OPB_00154\">http://identifiers.org/opb/OPB_00154</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./MyModel.xml#VLV\">file://./MyModel.xml#VLV</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isPropertyOf\">http://biomodels.net/biology-qualifiers/isPropertyOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"file://./annotations.rdf#entity_0\">file://./annotations.rdf#entity_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./annotations.rdf#entity_0\">file://./annotations.rdf#entity_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/is\">http://biomodels.net/biology-qualifiers/is</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://identifiers.org/fma/FMA:9670\">http://identifiers.org/fma/FMA:9670</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./annotations.rdf#entity_0\">file://./annotations.rdf#entity_0</a></span></td>\n"
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
    std::string expected = "<file://./MyModel.xml#VLV> <http://biomodels.net/biology-qualifiers/isVersionOf> <http://identifiers.org/opb/OPB_00154> .\n"
                           "<file://./MyModel.xml#VLV> <http://biomodels.net/biology-qualifiers/isPropertyOf> <file://./annotations.rdf#entity_0> .\n"
                           "<file://./annotations.rdf#entity_0> <http://biomodels.net/biology-qualifiers/is> <http://identifiers.org/fma/FMA:9670> .\n"
                           "<file://./annotations.rdf#entity_0> <http://biomodels.net/biology-qualifiers/isPartOf> <http://identifiers.org/fma/FMA:18228> .\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pe, "nquads", expected);
}



/**********************************************************************
 * Tests for samples.composite_annotation_pp
 */


TEST_F(ReadAndWriteTests, compositeannotationppntriples) {
    std::string expected = "<file://./MyModel.xml#property_metaid_0> <http://biomodels.net/biology-qualifiers/isPropertyOf> <file://./MyModel.xml#process_metaid_0> .\n"
                           "<file://./MyModel.xml#property_metaid_0> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/OPB_00592> .\n"
                           "<file://./MyModel.xml#process_metaid_0> <http://www.bhi.washington.edu/semsim#hasSourceParticipant> <file://./MyModel.xml#source_0> .\n"
                           "<file://./MyModel.xml#process_metaid_0> <http://www.bhi.washington.edu/semsim#hasSinkParticipant> <file://./MyModel.xml#sink_0> .\n"
                           "<file://./MyModel.xml#process_metaid_0> <http://www.bhi.washington.edu/semsim#hasMediatorParticipant> <file://./MyModel.xml#mediator_0> .\n"
                           "<file://./MyModel.xml#source_0> <http://www.bhi.washington.edu/semsim#hasMultiplier> \"1.0\" .\n"
                           "<file://./MyModel.xml#source_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <file://./MyModel.xml#species_metaid_0> .\n"
                           "<file://./MyModel.xml#sink_0> <http://www.bhi.washington.edu/semsim#hasMultiplier> \"2.0\" .\n"
                           "<file://./MyModel.xml#sink_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <file://./MyModel.xml#species_metaid_1> .\n"
                           "<file://./MyModel.xml#mediator_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <file://./MyModel.xml#species_metaid_2> .\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pp, "ntriples", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationppturtle) {
    std::string expected = "@base <file://./annotations.rdf> .\n"
                           "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://www.bhi.washington.edu/semsim#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "\n"
                           "<MyModel.xml#mediator_0>\n"
                           "    semsim:hasPhysicalEntityReference <MyModel.xml#species_metaid_2> .\n"
                           "\n"
                           "<MyModel.xml#process_metaid_0>\n"
                           "    semsim:hasMediatorParticipant <MyModel.xml#mediator_0> ;\n"
                           "    semsim:hasSinkParticipant <MyModel.xml#sink_0> ;\n"
                           "    semsim:hasSourceParticipant <MyModel.xml#source_0> .\n"
                           "\n"
                           "<MyModel.xml#property_metaid_0>\n"
                           "    bqbiol:isPropertyOf <MyModel.xml#process_metaid_0> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/OPB_00592> .\n"
                           "\n"
                           "<MyModel.xml#sink_0>\n"
                           "    semsim:hasMultiplier \"2.0\" ;\n"
                           "    semsim:hasPhysicalEntityReference <MyModel.xml#species_metaid_1> .\n"
                           "\n"
                           "<MyModel.xml#source_0>\n"
                           "    semsim:hasMultiplier \"1.0\" ;\n"
                           "    semsim:hasPhysicalEntityReference <MyModel.xml#species_metaid_0> .\n"
                           "\n";
    assertReadAndWrite(samples.composite_annotation_pp, "turtle", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpprdfxmlxmp) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<?xpacket begin='\uFEFF' id='W5M0MpCehiHzreSzNTczkc9d'?>\n"
                           "<x:xmpmeta xmlns:x='adobe:ns:meta/'>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"MyModel.xml#species_metaid_2\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <semsim:hasMediatorParticipant rdf:resource=\"MyModel.xml#mediator_0\"/>\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"MyModel.xml#sink_0\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"MyModel.xml#source_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"MyModel.xml#process_metaid_0\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_00592\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <semsim:hasMultiplier>2.0</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"MyModel.xml#species_metaid_1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <semsim:hasMultiplier>1.0</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"MyModel.xml#species_metaid_0\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "</x:xmpmeta>\n"
                           "<?xpacket end='r'?>\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pp, "rdfxml-xmp", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpprdfxmlabbrev) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"MyModel.xml#mediator_0\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"MyModel.xml#species_metaid_2\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MyModel.xml#process_metaid_0\">\n"
                           "    <semsim:hasMediatorParticipant rdf:resource=\"MyModel.xml#mediator_0\"/>\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"MyModel.xml#sink_0\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"MyModel.xml#source_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MyModel.xml#property_metaid_0\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"MyModel.xml#process_metaid_0\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_00592\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MyModel.xml#sink_0\">\n"
                           "    <semsim:hasMultiplier>2.0</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"MyModel.xml#species_metaid_1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MyModel.xml#source_0\">\n"
                           "    <semsim:hasMultiplier>1.0</semsim:hasMultiplier>\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"MyModel.xml#species_metaid_0\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pp, "rdfxml-abbrev", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpprdfxml) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\" xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"MyModel.xml#property_metaid_0\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"MyModel.xml#process_metaid_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MyModel.xml#property_metaid_0\">\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_00592\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MyModel.xml#process_metaid_0\">\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"MyModel.xml#source_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MyModel.xml#process_metaid_0\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"MyModel.xml#sink_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MyModel.xml#process_metaid_0\">\n"
                           "    <semsim:hasMediatorParticipant rdf:resource=\"MyModel.xml#mediator_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MyModel.xml#source_0\">\n"
                           "    <semsim:hasMultiplier>1.0</semsim:hasMultiplier>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MyModel.xml#source_0\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"MyModel.xml#species_metaid_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MyModel.xml#sink_0\">\n"
                           "    <semsim:hasMultiplier>2.0</semsim:hasMultiplier>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MyModel.xml#sink_0\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"MyModel.xml#species_metaid_1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MyModel.xml#mediator_0\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"MyModel.xml#species_metaid_2\"/>\n"
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
                           "\t\"RMyModel.xml#property_metaid_0\" -> \"RMyModel.xml#process_metaid_0\" [ label=\"bqbiol:isPropertyOf\" ];\n"
                           "\t\"RMyModel.xml#property_metaid_0\" -> \"Rhttps://identifiers.org/opb/OPB_00592\" [ label=\"bqbiol:isVersionOf\" ];\n"
                           "\t\"RMyModel.xml#process_metaid_0\" -> \"RMyModel.xml#source_0\" [ label=\"semsim:hasSourceParticipant\" ];\n"
                           "\t\"RMyModel.xml#process_metaid_0\" -> \"RMyModel.xml#sink_0\" [ label=\"semsim:hasSinkParticipant\" ];\n"
                           "\t\"RMyModel.xml#process_metaid_0\" -> \"RMyModel.xml#mediator_0\" [ label=\"semsim:hasMediatorParticipant\" ];\n"
                           "\t\"RMyModel.xml#source_0\" -> \"L1.0\" [ label=\"semsim:hasMultiplier\" ];\n"
                           "\t\"RMyModel.xml#source_0\" -> \"RMyModel.xml#species_metaid_0\" [ label=\"semsim:hasPhysicalEntityReference\" ];\n"
                           "\t\"RMyModel.xml#sink_0\" -> \"L2.0\" [ label=\"semsim:hasMultiplier\" ];\n"
                           "\t\"RMyModel.xml#sink_0\" -> \"RMyModel.xml#species_metaid_1\" [ label=\"semsim:hasPhysicalEntityReference\" ];\n"
                           "\t\"RMyModel.xml#mediator_0\" -> \"RMyModel.xml#species_metaid_2\" [ label=\"semsim:hasPhysicalEntityReference\" ];\n"
                           "\n"
                           "\t// Resources\n"
                           "\t\"RMyModel.xml#property_metaid_0\" [ label=\"MyModel.xml#property_metaid_0\", shape = ellipse, color = blue ];\n"
                           "\t\"RMyModel.xml#process_metaid_0\" [ label=\"MyModel.xml#process_metaid_0\", shape = ellipse, color = blue ];\n"
                           "\t\"Rhttps://identifiers.org/opb/OPB_00592\" [ label=\"https://identifiers.org/opb/OPB_00592\", shape = ellipse, color = blue ];\n"
                           "\t\"RMyModel.xml#source_0\" [ label=\"MyModel.xml#source_0\", shape = ellipse, color = blue ];\n"
                           "\t\"RMyModel.xml#sink_0\" [ label=\"MyModel.xml#sink_0\", shape = ellipse, color = blue ];\n"
                           "\t\"RMyModel.xml#mediator_0\" [ label=\"MyModel.xml#mediator_0\", shape = ellipse, color = blue ];\n"
                           "\t\"RMyModel.xml#species_metaid_0\" [ label=\"MyModel.xml#species_metaid_0\", shape = ellipse, color = blue ];\n"
                           "\t\"RMyModel.xml#species_metaid_1\" [ label=\"MyModel.xml#species_metaid_1\", shape = ellipse, color = blue ];\n"
                           "\t\"RMyModel.xml#species_metaid_2\" [ label=\"MyModel.xml#species_metaid_2\", shape = ellipse, color = blue ];\n"
                           "\n"
                           "\t// Anonymous nodes\n"
                           "\n"
                           "\t// Literals\n"
                           "\t\"L1.0\" [ label=\"1.0\", shape = record ];\n"
                           "\t\"L2.0\" [ label=\"2.0\", shape = record ];\n"
                           "\n"
                           "\tlabel=\"\\n\\nModel:\\nfile://./annotations.rdf\\n\\nNamespaces:\\nsemsim: http://www.bhi.washington.edu/semsim#\\nbqbiol: http://biomodels.net/biology-qualifiers/\\n\";\n"
                           "}\n";
    assertReadAndWrite(samples.composite_annotation_pp, "dot", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationppjsontriples) {
    std::string expected = "{\n"
                           "  \"triples\" : [\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"MyModel.xml#property_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://biomodels.net/biology-qualifiers/isPropertyOf\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"MyModel.xml#process_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"MyModel.xml#property_metaid_0\",\n"
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
                           "        \"value\" : \"MyModel.xml#process_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasSourceParticipant\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"MyModel.xml#source_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"MyModel.xml#process_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasSinkParticipant\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"MyModel.xml#sink_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"MyModel.xml#process_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasMediatorParticipant\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"MyModel.xml#mediator_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"MyModel.xml#source_0\",\n"
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
                           "        \"value\" : \"MyModel.xml#source_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"MyModel.xml#species_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"MyModel.xml#sink_0\",\n"
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
                           "        \"value\" : \"MyModel.xml#sink_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"MyModel.xml#species_metaid_1\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"MyModel.xml#mediator_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"MyModel.xml#species_metaid_2\",\n"
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
                           "  \"MyModel.xml#mediator_0\" : {\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\" : [ {\n"
                           "        \"value\" : \"MyModel.xml#species_metaid_2\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  ,\n"
                           "  \"MyModel.xml#process_metaid_0\" : {\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasMediatorParticipant\" : [ {\n"
                           "        \"value\" : \"MyModel.xml#mediator_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ],\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasSinkParticipant\" : [ {\n"
                           "        \"value\" : \"MyModel.xml#sink_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ],\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasSourceParticipant\" : [ {\n"
                           "        \"value\" : \"MyModel.xml#source_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  ,\n"
                           "  \"MyModel.xml#property_metaid_0\" : {\n"
                           "    \"http://biomodels.net/biology-qualifiers/isPropertyOf\" : [ {\n"
                           "        \"value\" : \"MyModel.xml#process_metaid_0\",\n"
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
                           "  \"MyModel.xml#sink_0\" : {\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasMultiplier\" : [ {\n"
                           "        \"value\" : \"2.0\",\n"
                           "        \"type\" : \"literal\"\n"
                           "        }\n"
                           "      \n"
                           "      ],\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\" : [ {\n"
                           "        \"value\" : \"MyModel.xml#species_metaid_1\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  ,\n"
                           "  \"MyModel.xml#source_0\" : {\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasMultiplier\" : [ {\n"
                           "        \"value\" : \"1.0\",\n"
                           "        \"type\" : \"literal\"\n"
                           "        }\n"
                           "      \n"
                           "      ],\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\" : [ {\n"
                           "        \"value\" : \"MyModel.xml#species_metaid_0\",\n"
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
                           "      <td><span class=\"uri\"><a href=\"MyModel.xml#property_metaid_0\">MyModel.xml#property_metaid_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isPropertyOf\">http://biomodels.net/biology-qualifiers/isPropertyOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.xml#process_metaid_0\">MyModel.xml#process_metaid_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.xml#property_metaid_0\">MyModel.xml#property_metaid_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isVersionOf\">http://biomodels.net/biology-qualifiers/isVersionOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"https://identifiers.org/opb/OPB_00592\">https://identifiers.org/opb/OPB_00592</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.xml#process_metaid_0\">MyModel.xml#process_metaid_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasSourceParticipant\">http://www.bhi.washington.edu/semsim#hasSourceParticipant</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.xml#source_0\">MyModel.xml#source_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.xml#process_metaid_0\">MyModel.xml#process_metaid_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasSinkParticipant\">http://www.bhi.washington.edu/semsim#hasSinkParticipant</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.xml#sink_0\">MyModel.xml#sink_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.xml#process_metaid_0\">MyModel.xml#process_metaid_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasMediatorParticipant\">http://www.bhi.washington.edu/semsim#hasMediatorParticipant</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.xml#mediator_0\">MyModel.xml#mediator_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.xml#source_0\">MyModel.xml#source_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasMultiplier\">http://www.bhi.washington.edu/semsim#hasMultiplier</a></span></td>\n"
                           "      <td><span class=\"literal\"><span class=\"value\">1.0</span></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.xml#source_0\">MyModel.xml#source_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\">http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.xml#species_metaid_0\">MyModel.xml#species_metaid_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.xml#sink_0\">MyModel.xml#sink_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasMultiplier\">http://www.bhi.washington.edu/semsim#hasMultiplier</a></span></td>\n"
                           "      <td><span class=\"literal\"><span class=\"value\">2.0</span></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.xml#sink_0\">MyModel.xml#sink_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\">http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.xml#species_metaid_1\">MyModel.xml#species_metaid_1</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.xml#mediator_0\">MyModel.xml#mediator_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\">http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.xml#species_metaid_2\">MyModel.xml#species_metaid_2</a></span></td>\n"
                           "    </tr>\n"
                           "  </table>\n"
                           "  <p>Total number of triples: <span class=\"count\">10</span>.</p>\n"
                           "</body>\n"
                           "</html>\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pp, "html", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationppnquads) {
    std::string expected = "<MyModel.xml#property_metaid_0> <http://biomodels.net/biology-qualifiers/isPropertyOf> <MyModel.xml#process_metaid_0> .\n"
                           "<MyModel.xml#property_metaid_0> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/OPB_00592> .\n"
                           "<MyModel.xml#process_metaid_0> <http://www.bhi.washington.edu/semsim#hasSourceParticipant> <MyModel.xml#source_0> .\n"
                           "<MyModel.xml#process_metaid_0> <http://www.bhi.washington.edu/semsim#hasSinkParticipant> <MyModel.xml#sink_0> .\n"
                           "<MyModel.xml#process_metaid_0> <http://www.bhi.washington.edu/semsim#hasMediatorParticipant> <MyModel.xml#mediator_0> .\n"
                           "<MyModel.xml#source_0> <http://www.bhi.washington.edu/semsim#hasMultiplier> \"1.0\" .\n"
                           "<MyModel.xml#source_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <MyModel.xml#species_metaid_0> .\n"
                           "<MyModel.xml#sink_0> <http://www.bhi.washington.edu/semsim#hasMultiplier> \"2.0\" .\n"
                           "<MyModel.xml#sink_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <MyModel.xml#species_metaid_1> .\n"
                           "<MyModel.xml#mediator_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <MyModel.xml#species_metaid_2> .\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pp, "nquads", expected);
}



/**********************************************************************
 * Tests for samples.composite_annotation_pf
 */


TEST_F(ReadAndWriteTests, compositeannotationpfntriples) {
    std::string expected = "<MyModel.sbml#parameter_metaid_0> <http://biomodels.net/biology-qualifiers/isPropertyOf> <MyModel.sbml#force_0> .\n"
                           "<MyModel.sbml#parameter_metaid_0> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/OPB_01058> .\n"
                           "<MyModel.sbml#force_0> <http://www.bhi.washington.edu/semsim#hasSourceParticipant> <MyModel.sbml#source_0> .\n"
                           "<MyModel.sbml#force_0> <http://www.bhi.washington.edu/semsim#hasSinkParticipant> <MyModel.sbml#sink_0> .\n"
                           "<MyModel.sbml#source_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <MyModel.sbml#species_metaid_0> .\n"
                           "<MyModel.sbml#sink_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <MyModel.sbml#species_metaid_1> .\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pf, "ntriples", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpfturtle) {
    std::string expected = "@base <file://./annotations.rdf> .\n"
                           "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://www.bhi.washington.edu/semsim#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix bqmodel: <http://biomodels.net/model-qualifiers/> .\n"
                           "\n"
                           "<MyModel.sbml#force_0>\n"
                           "    semsim:hasSinkParticipant <MyModel.sbml#sink_0> ;\n"
                           "    semsim:hasSourceParticipant <MyModel.sbml#source_0> .\n"
                           "\n"
                           "<MyModel.sbml#parameter_metaid_0>\n"
                           "    bqbiol:isPropertyOf <MyModel.sbml#force_0> ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/OPB_01058> .\n"
                           "\n"
                           "<MyModel.sbml#sink_0>\n"
                           "    semsim:hasPhysicalEntityReference <MyModel.sbml#species_metaid_1> .\n"
                           "\n"
                           "<MyModel.sbml#source_0>\n"
                           "    semsim:hasPhysicalEntityReference <MyModel.sbml#species_metaid_0> .\n"
                           "\n";

    assertReadAndWrite(samples.composite_annotation_pf, "turtle", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpfrdfxmlxmp) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<?xpacket begin='\uFEFF' id='W5M0MpCehiHzreSzNTczkc9d'?>\n"
                           "<x:xmpmeta xmlns:x='adobe:ns:meta/'>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"MyModel.sbml#sink_0\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"MyModel.sbml#source_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"MyModel.sbml#force_0\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_01058\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"MyModel.sbml#species_metaid_1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"MyModel.sbml#species_metaid_0\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "</x:xmpmeta>\n"
                           "<?xpacket end='r'?>\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pf, "rdfxml-xmp", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpfrdfxmlabbrev) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"MyModel.sbml#force_0\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"MyModel.sbml#sink_0\"/>\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"MyModel.sbml#source_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MyModel.sbml#parameter_metaid_0\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"MyModel.sbml#force_0\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_01058\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MyModel.sbml#sink_0\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"MyModel.sbml#species_metaid_1\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MyModel.sbml#source_0\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"MyModel.sbml#species_metaid_0\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pf, "rdfxml-abbrev", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpfrdfxml) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\" xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"MyModel.sbml#parameter_metaid_0\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"MyModel.sbml#force_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MyModel.sbml#parameter_metaid_0\">\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"https://identifiers.org/opb/OPB_01058\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MyModel.sbml#force_0\">\n"
                           "    <semsim:hasSourceParticipant rdf:resource=\"MyModel.sbml#source_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MyModel.sbml#force_0\">\n"
                           "    <semsim:hasSinkParticipant rdf:resource=\"MyModel.sbml#sink_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MyModel.sbml#source_0\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"MyModel.sbml#species_metaid_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MyModel.sbml#sink_0\">\n"
                           "    <semsim:hasPhysicalEntityReference rdf:resource=\"MyModel.sbml#species_metaid_1\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pf, "rdfxml", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpfdot) {
    std::string expected = "digraph {\n"
                           "\trankdir = LR;\n"
                           "\tcharset=\"utf-8\";\n"
                           "\n"
                           "\t\"RMyModel.sbml#parameter_metaid_0\" -> \"RMyModel.sbml#force_0\" [ label=\"bqbiol:isPropertyOf\" ];\n"
                           "\t\"RMyModel.sbml#parameter_metaid_0\" -> \"Rhttps://identifiers.org/opb/OPB_01058\" [ label=\"bqbiol:isVersionOf\" ];\n"
                           "\t\"RMyModel.sbml#force_0\" -> \"RMyModel.sbml#source_0\" [ label=\"semsim:hasSourceParticipant\" ];\n"
                           "\t\"RMyModel.sbml#force_0\" -> \"RMyModel.sbml#sink_0\" [ label=\"semsim:hasSinkParticipant\" ];\n"
                           "\t\"RMyModel.sbml#source_0\" -> \"RMyModel.sbml#species_metaid_0\" [ label=\"semsim:hasPhysicalEntityReference\" ];\n"
                           "\t\"RMyModel.sbml#sink_0\" -> \"RMyModel.sbml#species_metaid_1\" [ label=\"semsim:hasPhysicalEntityReference\" ];\n"
                           "\n"
                           "\t// Resources\n"
                           "\t\"RMyModel.sbml#parameter_metaid_0\" [ label=\"MyModel.sbml#parameter_metaid_0\", shape = ellipse, color = blue ];\n"
                           "\t\"RMyModel.sbml#force_0\" [ label=\"MyModel.sbml#force_0\", shape = ellipse, color = blue ];\n"
                           "\t\"Rhttps://identifiers.org/opb/OPB_01058\" [ label=\"https://identifiers.org/opb/OPB_01058\", shape = ellipse, color = blue ];\n"
                           "\t\"RMyModel.sbml#source_0\" [ label=\"MyModel.sbml#source_0\", shape = ellipse, color = blue ];\n"
                           "\t\"RMyModel.sbml#sink_0\" [ label=\"MyModel.sbml#sink_0\", shape = ellipse, color = blue ];\n"
                           "\t\"RMyModel.sbml#species_metaid_0\" [ label=\"MyModel.sbml#species_metaid_0\", shape = ellipse, color = blue ];\n"
                           "\t\"RMyModel.sbml#species_metaid_1\" [ label=\"MyModel.sbml#species_metaid_1\", shape = ellipse, color = blue ];\n"
                           "\n"
                           "\t// Anonymous nodes\n"
                           "\n"
                           "\t// Literals\n"
                           "\n"
                           "\tlabel=\"\\n\\nModel:\\nfile://./annotations.rdf\\n\\nNamespaces:\\nsemsim: http://www.bhi.washington.edu/semsim#\\nbqbiol: http://biomodels.net/biology-qualifiers/\\nbqmodel: http://biomodels.net/model-qualifiers/\\n\";\n"
                           "}\n";
    assertReadAndWrite(samples.composite_annotation_pf, "dot", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpfjsontriples) {
    std::string expected = "{\n"
                           "  \"triples\" : [\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"MyModel.sbml#parameter_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://biomodels.net/biology-qualifiers/isPropertyOf\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"MyModel.sbml#force_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"MyModel.sbml#parameter_metaid_0\",\n"
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
                           "        \"value\" : \"MyModel.sbml#force_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasSourceParticipant\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"MyModel.sbml#source_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"MyModel.sbml#force_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasSinkParticipant\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"MyModel.sbml#sink_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"MyModel.sbml#source_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"MyModel.sbml#species_metaid_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"MyModel.sbml#sink_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"MyModel.sbml#species_metaid_1\",\n"
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
                           "  \"MyModel.sbml#force_0\" : {\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasSinkParticipant\" : [ {\n"
                           "        \"value\" : \"MyModel.sbml#sink_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ],\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasSourceParticipant\" : [ {\n"
                           "        \"value\" : \"MyModel.sbml#source_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  ,\n"
                           "  \"MyModel.sbml#parameter_metaid_0\" : {\n"
                           "    \"http://biomodels.net/biology-qualifiers/isPropertyOf\" : [ {\n"
                           "        \"value\" : \"MyModel.sbml#force_0\",\n"
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
                           "  \"MyModel.sbml#sink_0\" : {\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\" : [ {\n"
                           "        \"value\" : \"MyModel.sbml#species_metaid_1\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      \n"
                           "      ]\n"
                           "    }\n"
                           "  ,\n"
                           "  \"MyModel.sbml#source_0\" : {\n"
                           "    \"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\" : [ {\n"
                           "        \"value\" : \"MyModel.sbml#species_metaid_0\",\n"
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
                           "      <td><span class=\"uri\"><a href=\"MyModel.sbml#parameter_metaid_0\">MyModel.sbml#parameter_metaid_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isPropertyOf\">http://biomodels.net/biology-qualifiers/isPropertyOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.sbml#force_0\">MyModel.sbml#force_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.sbml#parameter_metaid_0\">MyModel.sbml#parameter_metaid_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isVersionOf\">http://biomodels.net/biology-qualifiers/isVersionOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"https://identifiers.org/opb/OPB_01058\">https://identifiers.org/opb/OPB_01058</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.sbml#force_0\">MyModel.sbml#force_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasSourceParticipant\">http://www.bhi.washington.edu/semsim#hasSourceParticipant</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.sbml#source_0\">MyModel.sbml#source_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.sbml#force_0\">MyModel.sbml#force_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasSinkParticipant\">http://www.bhi.washington.edu/semsim#hasSinkParticipant</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.sbml#sink_0\">MyModel.sbml#sink_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.sbml#source_0\">MyModel.sbml#source_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\">http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.sbml#species_metaid_0\">MyModel.sbml#species_metaid_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.sbml#sink_0\">MyModel.sbml#sink_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference\">http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"MyModel.sbml#species_metaid_1\">MyModel.sbml#species_metaid_1</a></span></td>\n"
                           "    </tr>\n"
                           "  </table>\n"
                           "  <p>Total number of triples: <span class=\"count\">6</span>.</p>\n"
                           "</body>\n"
                           "</html>\n"
                           "";
    assertReadAndWrite(samples.composite_annotation_pf, "html", expected);
}

TEST_F(ReadAndWriteTests, compositeannotationpfnquads) {
    std::string expected = "<MyModel.sbml#parameter_metaid_0> <http://biomodels.net/biology-qualifiers/isPropertyOf> <MyModel.sbml#force_0> .\n"
                           "<MyModel.sbml#parameter_metaid_0> <http://biomodels.net/biology-qualifiers/isVersionOf> <https://identifiers.org/opb/OPB_01058> .\n"
                           "<MyModel.sbml#force_0> <http://www.bhi.washington.edu/semsim#hasSourceParticipant> <MyModel.sbml#source_0> .\n"
                           "<MyModel.sbml#force_0> <http://www.bhi.washington.edu/semsim#hasSinkParticipant> <MyModel.sbml#sink_0> .\n"
                           "<MyModel.sbml#source_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <MyModel.sbml#species_metaid_0> .\n"
                           "<MyModel.sbml#sink_0> <http://www.bhi.washington.edu/semsim#hasPhysicalEntityReference> <MyModel.sbml#species_metaid_1> .\n";
    assertReadAndWrite(samples.composite_annotation_pf, "nquads", expected);
}



/**********************************************************************
 * Tests for samples.tabular_data1
 */

TEST_F(ReadAndWriteTests, tabulardatantriples) {
    std::string expected = "<MyData.csv#VleftCorArt> <http://biomodels.net/biology-qualifiers/isVersionOf> <http://identifiers.org/opb/OPB_00154> .\n"
                           "<MyData.csv#VleftCorArt> <http://biomodels.net/biology-qualifiers/isPropertyOf> <file://./annotations.rdf.rdf#entity_0> .\n"
                           "<file://./annotations.rdf.rdf#entity_0> <http://biomodels.net/biology-qualifiers/is> <http://identifiers.org/fma/FMA:9670> .\n"
                           "<file://./annotations.rdf.rdf#entity_0> <http://biomodels.net/biology-qualifiers/isPartOf> <http://identifiers.org/fma/FMA:18228> .\n";
    assertReadAndWrite(samples.tabular_data1, "ntriples", expected);
}

TEST_F(ReadAndWriteTests, tabulardataturtle) {
    std::string expected = "@base <file://./annotations.rdf> .\n"
                           "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://www.bhi.washington.edu/semsim#> .\n"
                           "@prefix bqmodel: <http://biomodels.net/model-qualifiers/> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "\n"
                           "<SemsimModel.rdf#entity_0>\n"
                           "    bqbiol:is <http://identifiers.org/fma/FMA:9670> ;\n"
                           "    bqbiol:isPartOf <http://identifiers.org/fma/FMA:18228> .\n"
                           "\n"
                           "<MyData.csv#VleftCorArt>\n"
                           "    bqbiol:isPropertyOf <SemsimModel.rdf#entity_0> ;\n"
                           "    bqbiol:isVersionOf <http://identifiers.org/opb/OPB_00154> .\n"
                           "\n"
                           "";
    assertReadAndWrite(samples.tabular_data1, "turtle", expected);
}

TEST_F(ReadAndWriteTests, tabulardatardfxmlxmp) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<?xpacket begin='\uFEFF' id='W5M0MpCehiHzreSzNTczkc9d'?>\n"
                           "<x:xmpmeta xmlns:x='adobe:ns:meta/'>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:9670\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"http://identifiers.org/fma/FMA:18228\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"SemsimModel.rdf#entity_0\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"http://identifiers.org/opb/OPB_00154\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "</x:xmpmeta>\n"
                           "<?xpacket end='r'?>\n"
                           "";
    assertReadAndWrite(samples.tabular_data1, "rdfxml-xmp", expected);
}

TEST_F(ReadAndWriteTests, tabulardatardfxmlabbrev) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\"\n"
                           "   xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"SemsimModel.rdf#entity_0\">\n"
                           "    <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:9670\"/>\n"
                           "    <bqbiol:isPartOf rdf:resource=\"http://identifiers.org/fma/FMA:18228\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MyData.csv#VleftCorArt\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"SemsimModel.rdf#entity_0\"/>\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"http://identifiers.org/opb/OPB_00154\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    assertReadAndWrite(samples.tabular_data1, "rdfxml-abbrev", expected);
}

TEST_F(ReadAndWriteTests, tabulardatardfxml) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\" xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:semsim=\"http://www.bhi.washington.edu/semsim#\" xml:base=\"file://./annotations.rdf\">\n"
                           "  <rdf:Description rdf:about=\"MyData.csv#VleftCorArt\">\n"
                           "    <bqbiol:isVersionOf rdf:resource=\"http://identifiers.org/opb/OPB_00154\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"MyData.csv#VleftCorArt\">\n"
                           "    <bqbiol:isPropertyOf rdf:resource=\"SemsimModel.rdf#entity_0\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SemsimModel.rdf#entity_0\">\n"
                           "    <bqbiol:is rdf:resource=\"http://identifiers.org/fma/FMA:9670\"/>\n"
                           "  </rdf:Description>\n"
                           "  <rdf:Description rdf:about=\"SemsimModel.rdf#entity_0\">\n"
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
                           "\t\"RMyData.csv#VleftCorArt\" -> \"Rhttp://identifiers.org/opb/OPB_00154\" [ label=\"bqbiol:isVersionOf\" ];\n"
                           "\t\"RMyData.csv#VleftCorArt\" -> \"Rfile://./annotations.rdf.rdf#entity_0\" [ label=\"bqbiol:isPropertyOf\" ];\n"
                           "\t\"Rfile://./annotations.rdf.rdf#entity_0\" -> \"Rhttp://identifiers.org/fma/FMA:9670\" [ label=\"bqbiol:is\" ];\n"
                           "\t\"Rfile://./annotations.rdf.rdf#entity_0\" -> \"Rhttp://identifiers.org/fma/FMA:18228\" [ label=\"bqbiol:isPartOf\" ];\n"
                           "\n"
                           "\t// Resources\n"
                           "\t\"RMyData.csv#VleftCorArt\" [ label=\"MyData.csv#VleftCorArt\", shape = ellipse, color = blue ];\n"
                           "\t\"Rhttp://identifiers.org/opb/OPB_00154\" [ label=\"http://identifiers.org/opb/OPB_00154\", shape = ellipse, color = blue ];\n"
                           "\t\"Rfile://./annotations.rdf.rdf#entity_0\" [ label=\"file://./annotations.rdf.rdf#entity_0\", shape = ellipse, color = blue ];\n"
                           "\t\"Rhttp://identifiers.org/fma/FMA:9670\" [ label=\"http://identifiers.org/fma/FMA:9670\", shape = ellipse, color = blue ];\n"
                           "\t\"Rhttp://identifiers.org/fma/FMA:18228\" [ label=\"http://identifiers.org/fma/FMA:18228\", shape = ellipse, color = blue ];\n"
                           "\n"
                           "\t// Anonymous nodes\n"
                           "\n"
                           "\t// Literals\n"
                           "\n"
                           "\tlabel=\"\\n\\nModel:\\nfile://./annotations.rdf\\n\\nNamespaces:\\nsemsim: http://www.bhi.washington.edu/semsim#\\nbqmodel: http://biomodels.net/model-qualifiers/\\nbqbiol: http://biomodels.net/biology-qualifiers/\\n\";\n"
                           "}\n"
                           "";
    assertReadAndWrite(samples.tabular_data1, "dot", expected);
}

TEST_F(ReadAndWriteTests, tabulardatajsontriples) {
    std::string expected = "{\n"
                           "  \"triples\" : [\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"MyData.csv#VleftCorArt\",\n"
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
                           "        \"value\" : \"MyData.csv#VleftCorArt\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"predicate\" : {\n"
                           "        \"value\" : \"http://biomodels.net/biology-qualifiers/isPropertyOf\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        },\n"
                           "      \"object\" : {\n"
                           "        \"value\" : \"SemsimModel.rdf#entity_0\",\n"
                           "        \"type\" : \"uri\"\n"
                           "        }\n"
                           "      },\n"
                           "    {\n"
                           "      \"subject\" : {\n"
                           "        \"value\" : \"SemsimModel.rdf#entity_0\",\n"
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
                           "        \"value\" : \"SemsimModel.rdf#entity_0\",\n"
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
                           "  }\n";
    assertReadAndWrite(samples.tabular_data1, "json-triples", expected);
}

TEST_F(ReadAndWriteTests, tabulardatajson) {
    std::string expected = "\n"
                           "{\n"
                           "  \"SemsimModel.rdf#entity_0\" : {\n"
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
                           "  \"MyData.csv#VleftCorArt\" : {\n"
                           "    \"http://biomodels.net/biology-qualifiers/isPropertyOf\" : [ {\n"
                           "        \"value\" : \"SemsimModel.rdf#entity_0\",\n"
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
                           "      <td><span class=\"uri\"><a href=\"MyData.csv#VleftCorArt\">MyData.csv#VleftCorArt</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isVersionOf\">http://biomodels.net/biology-qualifiers/isVersionOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://identifiers.org/opb/OPB_00154\">http://identifiers.org/opb/OPB_00154</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"MyData.csv#VleftCorArt\">MyData.csv#VleftCorArt</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/isPropertyOf\">http://biomodels.net/biology-qualifiers/isPropertyOf</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"file://./annotations.rdf.rdf#entity_0\">file://./annotations.rdf.rdf#entity_0</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./annotations.rdf.rdf#entity_0\">file://./annotations.rdf.rdf#entity_0</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://biomodels.net/biology-qualifiers/is\">http://biomodels.net/biology-qualifiers/is</a></span></td>\n"
                           "      <td><span class=\"uri\"><a href=\"http://identifiers.org/fma/FMA:9670\">http://identifiers.org/fma/FMA:9670</a></span></td>\n"
                           "    </tr>\n"
                           "    <tr class=\"triple\">\n"
                           "      <td><span class=\"uri\"><a href=\"file://./annotations.rdf.rdf#entity_0\">file://./annotations.rdf.rdf#entity_0</a></span></td>\n"
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
    std::string expected = "<MyData.csv#VleftCorArt> <http://biomodels.net/biology-qualifiers/isVersionOf> <http://identifiers.org/opb/OPB_00154> .\n"
                           "<MyData.csv#VleftCorArt> <http://biomodels.net/biology-qualifiers/isPropertyOf> <file://./annotations.rdf.rdf#entity_0> .\n"
                           "<file://./annotations.rdf.rdf#entity_0> <http://biomodels.net/biology-qualifiers/is> <http://identifiers.org/fma/FMA:9670> .\n"
                           "<file://./annotations.rdf.rdf#entity_0> <http://biomodels.net/biology-qualifiers/isPartOf> <http://identifiers.org/fma/FMA:18228> .\n";
    assertReadAndWrite(samples.tabular_data1, "nquads", expected);
}

/******************************************************************************
 * ReadAndWriteTests for sbml files
 */

TEST_F(ReadAndWriteTests, SBML1) {
    semsim::SemsimUtils::download(samples.sbml_url1, samples.sbml_filename1);
    semsim::RDF rdf = semsim::RDF::fromXML(samples.sbml_filename1, "rdfxml");
    std::string extracted = rdf.toString("rdfxml", "file://./annotations.rdf");
    std::cout << extracted << std::endl;
    int expected = 32;
    int actual = sizeof(extracted);
    ASSERT_EQ(expected, actual);
}

TEST_F(ReadAndWriteTests, tesjhbt) {
    std::string q = "PREFIX rdf:  <http://www.w3.org/1999/02/22-rdf-syntax-ns#>\n"
                    "SELECT ?x ?y ?z\n"
                    "WHERE {?x ?y ?z }";
    semsim::RDF rdf = semsim::RDF::fromString(samples.composite_annotation_pp, "rdfxml");
//    std::cout << rdf.toString("turtle") << std::endl;
    semsim::RDF subrdf = rdf.query(q);
    std::cout << subrdf.toString("rdfxml", "file://./annotations.rdf") << std::endl;


}

//TEST_F(ReadAndWriteTests, CELLML1) {
//    semsim::SemsimUtils::download(samples.cellml_url1, samples.cellml_filename1);
//    semsim::RDF rdf = semsim::RDF::fromXML(samples.cellml_filename1, "turtle");
//    std::string extracted = rdf.toString("rdfxml");
//    std::cout << extracted << std::endl;
////    int expected = 32;
////    int actual = sizeof(extracted);
////    ASSERT_EQ(expected, actual);
//}
//
//








