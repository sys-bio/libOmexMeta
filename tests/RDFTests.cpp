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
    int x = rdf.getNamespaces().size();
    ASSERT_EQ(2, x);
}

TEST_F(RDFTests, TestBaseUri){
    semsim::RDF rdf;
    std::string expected = "file://./semsim_model.rdf";
    std::string actual = (const char*) librdf_uri_as_string(rdf.getBaseUri());
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(RDFTests, TestCount) {
    semsim::RDF rdf = semsim::RDF::fromString(samples.rdf_xml_seq_example, "rdfxml");
    int actual = rdf.size();
    int expected = 4;
    ASSERT_EQ(expected, actual);
}

TEST_F(RDFTests, TestToTriples) {
    semsim::RDF rdf = semsim::RDF::fromString(samples.rdf_xml_seq_example, "rdfxml");
    semsim::Triples triples = rdf.toTriples();
    std::ostringstream actual;
    for (auto &it : triples) {
        actual << it.getSubject().str() << it.getPredicatePtr()->str() << it.getResource().str() << std::endl;
    }
    std::string expected = "http://example.org/favourite-fruithttp:/www.w3.org/1999/02/22-rdf-syntax-ns#typehttp://www.w3.org/1999/02/22-rdf-syntax-ns#Seq\n"
                           "http://example.org/favourite-fruithttp:/www.w3.org/1999/02/22-rdf-syntax-ns#_1http://example.org/banana\n"
                           "http://example.org/favourite-fruithttp:/www.w3.org/1999/02/22-rdf-syntax-ns#_2http://example.org/apple\n"
                           "http://example.org/favourite-fruithttp:/www.w3.org/1999/02/22-rdf-syntax-ns#_3http://example.org/pear\n";
    ASSERT_STREQ(expected.c_str(), actual.str().c_str());
}

TEST_F(RDFTests, testQueryResultsAsStr) {
    std::string q = "PREFIX rdf:  <http://www.w3.org/1999/02/22-rdf-syntax-ns#>\n"
                    "SELECT ?x ?y ?z\n"
                    "WHERE {?x ?y ?z }";
    semsim::RDF rdf = semsim::RDF::fromString(samples.singular_annotation4, "rdfxml");
    std::string actual = rdf.queryResultsAsStr(q, "csv");
    std::string expected = "x,y,z\n"
                           "file://./MyModel.xml#meta2,http://purl.org/dc/terms/description,Cardiomyocyte cytosolic ATP concentration\n"
                           "";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(RDFTests, testQueryResultsAsMap) {
    std::string q = "PREFIX rdf:  <http://www.w3.org/1999/02/22-rdf-syntax-ns#>\n"
                    "SELECT ?x ?y ?z\n"
                    "WHERE {?x ?y ?z }";
    semsim::RDF rdf = semsim::RDF::fromString(samples.singular_annotation4, "rdfxml");
    semsim::ResultsMap map = rdf.queryResultsAsMap(q);
    std::string actual = map["x"][0];
    std::string expected = "file://./MyModel.xml#meta2";
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(RDFTests, testQueryResultsAsRDF) {
    std::string q = "PREFIX rdf:  <http://www.w3.org/1999/02/22-rdf-syntax-ns#>\n"
                    "SELECT ?x ?y ?z\n"
                    "WHERE {?x ?y ?z }";
    semsim::RDF rdf = semsim::RDF::fromString(samples.singular_annotation4, "rdfxml");
    semsim::RDF queryrdf = rdf.queryResultsAsRDF(q);

    std::ostringstream os;
    for (auto &it : queryrdf.toTriples()){
        os << it.getSubject().str() << it.getPredicatePtr()->str() << it.getResource().str() << std::endl;
    }
    std::string expected = "";
    std::cout << os.str() << std::endl;
    //todo look into the reason why some subject nodes are being interpreted as blank nodes (i.e. random numbers).
    ASSERT_STREQ(expected.c_str(), os.str().c_str());

}












