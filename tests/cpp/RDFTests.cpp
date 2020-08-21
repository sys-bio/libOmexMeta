//
// Created by Ciaran on 5/31/2020.
//

#include "gtest/gtest.h"
#include "omexmeta/RDF.h"
#include "AnnotationSamples.h"
#include <filesystem>
#include <fstream>
#include <thread>
#include "SBMLFactory.h"

using namespace omexmeta;

class RDFTests : public ::testing::Test {

public:

    AnnotationSamples samples;

    RDFTests() = default;

    void TearDown() override {
        samples.removeAllFilesIfTheyExist();
    }
};

TEST_F(RDFTests, TestCreateEmptyRDF) {
    RDF rdf;
    ASSERT_EQ(0, rdf.size());
    ASSERT_TRUE(rdf.empty());
}

TEST_F(RDFTests, TestListOptions) {
    std::string actual = RDF::listOptions().str();
    std::string expected = "option, name, label, domain, value type, uri\n"
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
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(RDFTests, TestFromStringSingularAnnotation) {
    RDF rdf = RDF::fromString(samples.singular_annotation1);
    int expected = 1;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
}

TEST_F(RDFTests, TestFromStringSingularAnnotationSqlite) {
//    "hashes", "test", "hash-type='bdb',dir='.'")
//    librdf_new_storage()
    RDF rdf("sqlite", "semsim_store", "new='yes'");//"hash-type=sqlite,dir=mnt/d/libomexmeta/tests/cpp");
    rdf.addFromString(samples.singular_annotation1, "rdfxml");
    rdf.commitTransaction();
    int expected = 1;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
}

TEST_F(RDFTests, TestFromStringTurtleBag) {
    RDF rdf = RDF::fromString(samples.rdf_turtle_bag_example, "turtle");
    int expected = 7;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
}

TEST_F(RDFTests, TestToString) {
    RDF rdf = RDF::fromString(samples.rdf_xml_example7, "rdfxml");
    std::string expected = "<?xml version=\"1.1\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex\"\n"
                           "   xmlns:myOMEXlib=\"http://omex-library.org/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"http://www.w3.org/TR/rdf-syntax-grammar\">\n"
                           "    <ns1:editor xmlns:ns1=\"http://example.org/stuff/1.0/\">\n"
                           "      <rdf:Description>\n"
                           "        <ns1:fullName>Dave Beckett</ns1:fullName>\n"
                           "        <ns1:homePage rdf:resource=\"http://purl.org/net/dajobe/\"/>\n"
                           "      </rdf:Description>\n"
                           "    </ns1:editor>\n"
                           "    <ns2:title xmlns:ns2=\"http://purl.org/dc/elements/1.1/\">RDF1.1 XML Syntax</ns2:title>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    std::string actual = rdf.toString();
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST(RDFTestsNoFigure, TestRDFCanReadFromTwoStrings) {
    std::string rdf_string1 = "<?xml version=\"1.1\" encoding=\"utf-8\"?>\n"
                              "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                              "   xmlns:local=\"http://omex-library.org/NewModel.rdf#\"\n"
                              "   xmlns:myOMEX=\"http://omex-library.org/NewModel.omex\"\n"
                              "   xmlns:myOMEXlib=\"http://omex-library.org/\"\n"
                              "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                              "   xml:base=\"/mnt/d/libOmexMeta/cmake-docs-build-debug-wsl-ubuntu1804-gcc101/bin/\">\n"
                              "  <rdf:Description rdf:about=\"http://omex-library.org/NewModel.omex#OmexMetaId0000\">\n"
                              "    <bqbiol:is rdf:resource=\"https://identifiers.org/fma/FMA_66835\"/>\n"
                              "  </rdf:Description>\n"
                              "</rdf:RDF>";
    std::string rdf_string2 = "<?xml version=\"1.1\" encoding=\"utf-8\"?>\n"
                              "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                              "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                              "   xml:base=\"file://./Annotation.rdf\">\n"
                              "  <rdf:Description rdf:about=\"OmexMetaId0000\">\n"
                              "    <bqbiol:is rdf:resource=\"https://identifiers.org/fma/FMA_66835\"/>\n"
                              "  </rdf:Description>\n"
                              "</rdf:RDF>\n";

    RDF rdf = RDF::fromString(rdf_string1);
    std::cout << rdf.toString() << std::endl;


}

TEST_F(RDFTests, TestAddFromString) {
    RDF rdf;
    rdf.addFromString(samples.singular_annotation4);
    int expected = 1;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
}

TEST_F(RDFTests, TestAddFromStringMultipleTimes) {
    RDF rdf;
    rdf.addFromString(samples.singular_annotation1);
    rdf.addFromString(samples.singular_annotation2);
    rdf.addFromString(samples.singular_annotation3);
    rdf.addFromString(samples.singular_annotation4);
    int expected = 4;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
}

TEST_F(RDFTests, TestParseFromUri) {
    RDF rdf = RDF::fromUri(samples.sbml_url1, "rdfxml");
    int expected = 277;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
}


TEST_F(RDFTests, TestParseFromUriNonStatic) {
    RDF rdf;
    rdf.addFromUri(samples.sbml_url1, "rdfxml");
    int expected = 277;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
}

TEST_F(RDFTests, TestSqliteStorageWithUriParse) {
    std::filesystem::path fname = std::filesystem::current_path() += "sqlite_db";
    if (std::filesystem::exists(fname)) {
        std::filesystem::remove(fname);
    }
    RDF rdf("sqlite", fname.string(), "new='yes'");
    rdf.addFromUri(samples.sbml_url1, "rdfxml");
    int expected = 277;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
    ASSERT_TRUE(std::filesystem::exists(fname));
    // clean up after ourselves
    // but windows holds the sqlite db file open so we can't delete
    // on windows so on this instance we have to deal with test databases clogging up
    // the test folder.
    try {
        std::filesystem::remove(fname);
    } catch (std::exception &e) {
        //
    }
}


/*
 * Will take some effort to learn how to use
 * postgresql.
 */
//TEST_F(RDFTests, TestPostgresStorageWithUriParse) {
//    const char* fname = "/mnt/d/libOmexMeta/tests/cpp/sqlite_db.db";
//    RDF rdf("postgresql", "postgresdb",
//            "new='yes',host='localhost',database='ATestDB',user='ciaran',password=''");
//    rdf.addFromUri(samples.sbml_url1, "rdfxml");
//    int expected = 277;
//    int actual = rdf.size();
//    ASSERT_EQ(expected, actual);
//    ASSERT_TRUE(std::filesystem::exists(fname));
//    // clean up after ourselves
//    std::filesystem::remove(fname);
//}

/*
 * This test takes too long. No use. Must use a different database.
 */
//TEST_F(RDFTests, TestSqliteStorageLarseFile) {
//    const char* xmlf = "/mnt/d/libOmexMeta/tests/cpp/brenda_parameters_1.xml";
//    const char* fname = "/mnt/d/libOmexMeta/tests/cpp/sqlite_db.db";
//    RDF rdf("sqlite", fname, "new='yes'");
//    rdf.addFromFile(xmlf, "rdfxml");
//    int expected = 277;
//    int actual = rdf.size();
//    ASSERT_EQ(expected, actual);
//    ASSERT_TRUE(std::filesystem::exists(fname));
//    // clean up after ourselves
////    std::filesystem::remove(fname);
//}

//TEST_F(RDFTests, TestBDBStorageLarseFile) {
//    const char* xmlf = "/mnt/d/libOmexMeta/tests/cpp/brenda_parameters_1.xml";
//    const char* fname = "/mnt/d/libOmexMeta/tests/cpp/sqlite_db.db";
//    RDF rdf("hashes", "BdbLargeFileTest.db",
//                             "new='yes',hash-type='bdb',dir='/mnt/d/libOmexMeta/tests/cpp'");
//    rdf.addFromFile(xmlf, "rdfxml");
//    int expected = 277;
//    int actual = rdf.size();
//    ASSERT_EQ(expected, actual);
//    ASSERT_TRUE(std::filesystem::exists(fname));
//    // clean up after ourselves
////    std::filesystem::remove(fname);
//}

TEST_F(RDFTests, TestParseFromFile) {
    // first create a file containing annotations
//    raptor_option_uri_prefix;
    std::string fname = std::filesystem::current_path().string() += "TestParseFromFile.rdf";
    std::cout << fname << std::endl;
    std::ofstream f(fname);
    if (f.is_open()) {
        f << samples.composite_annotation_pe << std::endl;
        f.flush();
        f.close();
    } else {
        throw std::logic_error("No file was opened for test");
    }

    RDF rdf = RDF::fromFile(fname, "rdfxml");
    int expected = 4;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);

    std::cout << rdf.toString("turtle") << std::endl;

    // clear up file we wrote
    std::remove(fname.c_str());

}

TEST_F(RDFTests, TestParseFromFileCollectedFromBiomodels) {
    // first create a file containing annotations
//    raptor_option_uri_prefix;
    std::string fname = std::filesystem::current_path().string() += "TestParseFromFile.rdf";
    std::cout << fname << std::endl;
    std::ofstream f(fname);
    if (f.is_open()) {
        f << SBMLFactory::getSBML(SBML_BIOMD204) << std::endl;
        f.flush();
        f.close();
    } else {
        throw std::logic_error("No file was opened for test");
    }

    RDF rdf = RDF::fromFile(fname, "rdfxml");
    std::string expected = rdf.toString("turtle");
    std::string actual = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                         "@prefix myOMEXlib: <http://omex-library.org/> .\n"
                         "@prefix myOMEX: <http://omex-library.org/NewOmex.omex> .\n"
                         "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                         "\n"
                         "local:metaid_0000002\n"
                         "    <http://biomodels.net/biology-qualifiers/hasTaxon> [\n"
                         "        rdf:_1 <http://identifiers.org/taxonomy/9606> ;\n"
                         "        rdf:_2 <http://identifiers.org/taxonomy/10090> ;\n"
                         "        a rdf:Bag\n"
                         "    ] ;\n"
                         "    <http://biomodels.net/biology-qualifiers/isVersionOf> [\n"
                         "        rdf:_1 <http://identifiers.org/obo.go/GO:0048863> ;\n"
                         "        a rdf:Bag\n"
                         "    ] ;\n"
                         "    <http://biomodels.net/model-qualifiers/is> [\n"
                         "        rdf:_1 <http://identifiers.org/biomodels.db/MODEL7957942740> ;\n"
                         "        a rdf:Bag\n"
                         "    ], [\n"
                         "        rdf:_1 <http://identifiers.org/biomodels.db/BIOMD0000000204> ;\n"
                         "        a rdf:Bag\n"
                         "    ] ;\n"
                         "    <http://biomodels.net/model-qualifiers/isDescribedBy> [\n"
                         "        rdf:_1 <http://identifiers.org/pubmed/16978048> ;\n"
                         "        a rdf:Bag\n"
                         "    ] ;\n"
                         "    <http://purl.org/dc/elements/1.1/creator> [\n"
                         "        rdf:_1 [\n"
                         "            <http://www.w3.org/2001/vcard-rdf/3.0#EMAIL> \"viji@ebi.ac.uk\" ;\n"
                         "            <http://www.w3.org/2001/vcard-rdf/3.0#N> [\n"
                         "                <http://www.w3.org/2001/vcard-rdf/3.0#Family> \"Chelliah\" ;\n"
                         "                <http://www.w3.org/2001/vcard-rdf/3.0#Given> \"Vijayalakshmi\"\n"
                         "            ] ;\n"
                         "            <http://www.w3.org/2001/vcard-rdf/3.0#ORG> [\n"
                         "                <http://www.w3.org/2001/vcard-rdf/3.0#Orgname> \"EMBL-EBI\"\n"
                         "            ]\n"
                         "        ] ;\n"
                         "        rdf:_2 [\n"
                         "            <http://www.w3.org/2001/vcard-rdf/3.0#EMAIL> \"llukas@ebi.ac.uk\" ;\n"
                         "            <http://www.w3.org/2001/vcard-rdf/3.0#N> [\n"
                         "                <http://www.w3.org/2001/vcard-rdf/3.0#Family> \"Endler\" ;\n"
                         "                <http://www.w3.org/2001/vcard-rdf/3.0#Given> \"Lukas\"\n"
                         "            ] ;\n"
                         "            <http://www.w3.org/2001/vcard-rdf/3.0#ORG> [\n"
                         "                <http://www.w3.org/2001/vcard-rdf/3.0#Orgname> \"EMBL-EBI\"\n"
                         "            ]\n"
                         "        ] ;\n"
                         "        rdf:_3 [\n"
                         "            <http://www.w3.org/2001/vcard-rdf/3.0#EMAIL> \"vchickar@caltech.edu\" ;\n"
                         "            <http://www.w3.org/2001/vcard-rdf/3.0#N> [\n"
                         "                <http://www.w3.org/2001/vcard-rdf/3.0#Family> \"Chickarmane\" ;\n"
                         "                <http://www.w3.org/2001/vcard-rdf/3.0#Given> \"Vijay\"\n"
                         "            ] ;\n"
                         "            <http://www.w3.org/2001/vcard-rdf/3.0#ORG> [\n"
                         "                <http://www.w3.org/2001/vcard-rdf/3.0#Orgname> \"Keck Graduate Institute, California\"\n"
                         "            ]\n"
                         "        ] ;\n"
                         "        rdf:_4 [\n"
                         "            <http://www.w3.org/2001/vcard-rdf/3.0#EMAIL> \"carsten@thep.lu.se\" ;\n"
                         "            <http://www.w3.org/2001/vcard-rdf/3.0#N> [\n"
                         "                <http://www.w3.org/2001/vcard-rdf/3.0#Family> \"Peterson\" ;\n"
                         "                <http://www.w3.org/2001/vcard-rdf/3.0#Given> \"Carsten\"\n"
                         "            ] ;\n"
                         "            <http://www.w3.org/2001/vcard-rdf/3.0#ORG> [\n"
                         "                <http://www.w3.org/2001/vcard-rdf/3.0#Orgname> \"Lund Strategic Research Centre for Stem Cell Biology and Cell Therapy, Lund University, Sweden.\"\n"
                         "            ]\n"
                         "        ] ;\n"
                         "        a rdf:Bag\n"
                         "    ] ;\n"
                         "    <http://purl.org/dc/terms/created> [\n"
                         "        <http://purl.org/dc/terms/W3CDTF> \"2008-11-26T13:10:43Z\"\n"
                         "    ] ;\n"
                         "    <http://purl.org/dc/terms/modified> [\n"
                         "        <http://purl.org/dc/terms/W3CDTF> \"2013-06-05T16:57:58Z\"\n"
                         "    ] .\n"
                         "\n"
                         "local:metaid_0000035\n"
                         "    <http://biomodels.net/biology-qualifiers/isVersionOf> [\n"
                         "        rdf:_1 <http://identifiers.org/obo.go/GO:0005623> ;\n"
                         "        a rdf:Bag\n"
                         "    ] .\n"
                         "\n"
                         "local:metaid_0000036\n"
                         "    <http://biomodels.net/biology-qualifiers/encodes> [\n"
                         "        rdf:_1 <http://identifiers.org/uniprot/Q01860> ;\n"
                         "        a rdf:Bag\n"
                         "    ] ;\n"
                         "    <http://biomodels.net/biology-qualifiers/isVersionOf> [\n"
                         "        rdf:_1 <http://identifiers.org/ensembl/ENSG00000204531> ;\n"
                         "        a rdf:Bag\n"
                         "    ] .\n"
                         "\n"
                         "local:metaid_0000037\n"
                         "    <http://biomodels.net/biology-qualifiers/encodes> [\n"
                         "        rdf:_1 <http://identifiers.org/uniprot/Q8N7R0> ;\n"
                         "        a rdf:Bag\n"
                         "    ] ;\n"
                         "    <http://biomodels.net/biology-qualifiers/isVersionOf> [\n"
                         "        rdf:_1 <http://identifiers.org/ensembl/ENSG00000176654> ;\n"
                         "        a rdf:Bag\n"
                         "    ] .\n"
                         "\n"
                         "local:metaid_0000038\n"
                         "    <http://biomodels.net/biology-qualifiers/encodes> [\n"
                         "        rdf:_1 <http://identifiers.org/uniprot/Q6ZRP7> ;\n"
                         "        a rdf:Bag\n"
                         "    ] ;\n"
                         "    <http://biomodels.net/biology-qualifiers/isVersionOf> [\n"
                         "        rdf:_1 <http://identifiers.org/ensembl/ENSG00000165661> ;\n"
                         "        a rdf:Bag\n"
                         "    ] .\n"
                         "\n"
                         "local:metaid_0000041\n"
                         "    <http://biomodels.net/biology-qualifiers/isVersionOf> [\n"
                         "        rdf:_1 <http://identifiers.org/uniprot/P04637> ;\n"
                         "        a rdf:Bag\n"
                         "    ] .\n"
                         "\n"
                         "local:metaid_0000043\n"
                         "    <http://biomodels.net/biology-qualifiers/isVersionOf> [\n"
                         "        rdf:_1 <http://identifiers.org/uniprot/Q01860> ;\n"
                         "        a rdf:Bag\n"
                         "    ] .\n"
                         "\n"
                         "local:metaid_0000044\n"
                         "    <http://biomodels.net/biology-qualifiers/isVersionOf> [\n"
                         "        rdf:_1 <http://identifiers.org/uniprot/Q6ZRP7> ;\n"
                         "        a rdf:Bag\n"
                         "    ] .\n"
                         "\n"
                         "local:metaid_0000045\n"
                         "    <http://biomodels.net/biology-qualifiers/isVersionOf> [\n"
                         "        rdf:_1 <http://identifiers.org/uniprot/Q8N7R0> ;\n"
                         "        a rdf:Bag\n"
                         "    ] .\n"
                         "\n"
                         "local:metaid_0000046\n"
                         "    <http://biomodels.net/biology-qualifiers/hasPart> [\n"
                         "        rdf:_1 <http://identifiers.org/uniprot/Q01860> ;\n"
                         "        rdf:_2 <http://identifiers.org/uniprot/Q6ZRP7> ;\n"
                         "        a rdf:Bag\n"
                         "    ] .\n"
                         "\n"
                         "local:metaid_0000048\n"
                         "    <http://biomodels.net/biology-qualifiers/isVersionOf> [\n"
                         "        rdf:_1 <http://identifiers.org/obo.go/GO:0010467> ;\n"
                         "        a rdf:Bag\n"
                         "    ] .\n"
                         "\n"
                         "local:metaid_0000049\n"
                         "    <http://biomodels.net/biology-qualifiers/isVersionOf> [\n"
                         "        rdf:_1 <http://identifiers.org/obo.go/GO:0030163> ;\n"
                         "        a rdf:Bag\n"
                         "    ] .\n"
                         "\n"
                         "local:metaid_0000050\n"
                         "    <http://biomodels.net/biology-qualifiers/isVersionOf> [\n"
                         "        rdf:_1 <http://identifiers.org/obo.go/GO:0010467> ;\n"
                         "        a rdf:Bag\n"
                         "    ] .\n"
                         "\n"
                         "local:metaid_0000051\n"
                         "    <http://biomodels.net/biology-qualifiers/isVersionOf> [\n"
                         "        rdf:_1 <http://identifiers.org/obo.go/GO:0030163> ;\n"
                         "        a rdf:Bag\n"
                         "    ] .\n"
                         "\n"
                         "local:metaid_0000052\n"
                         "    <http://biomodels.net/biology-qualifiers/isVersionOf> [\n"
                         "        rdf:_1 <http://identifiers.org/obo.go/GO:0006461> ;\n"
                         "        a rdf:Bag\n"
                         "    ] .\n"
                         "\n"
                         "local:metaid_0000053\n"
                         "    <http://biomodels.net/biology-qualifiers/isVersionOf> [\n"
                         "        rdf:_1 <http://identifiers.org/obo.go/GO:0030163> ;\n"
                         "        a rdf:Bag\n"
                         "    ] .\n"
                         "\n"
                         "local:metaid_0000054\n"
                         "    <http://biomodels.net/biology-qualifiers/isVersionOf> [\n"
                         "        rdf:_1 <http://identifiers.org/obo.go/GO:0010467> ;\n"
                         "        a rdf:Bag\n"
                         "    ] .\n"
                         "\n"
                         "local:metaid_0000055\n"
                         "    <http://biomodels.net/biology-qualifiers/isVersionOf> [\n"
                         "        rdf:_1 <http://identifiers.org/obo.go/GO:0030163> ;\n"
                         "        a rdf:Bag\n"
                         "    ] .\n"
                         "\n"
                         "local:metaid_0000056\n"
                         "    <http://biomodels.net/biology-qualifiers/isVersionOf> [\n"
                         "        rdf:_1 <http://identifiers.org/obo.go/GO:0010467> ;\n"
                         "        a rdf:Bag\n"
                         "    ] .\n"
                         "\n"
                         "local:metaid_0000057\n"
                         "    <http://biomodels.net/biology-qualifiers/isVersionOf> [\n"
                         "        rdf:_1 <http://identifiers.org/obo.go/GO:0030163> ;\n"
                         "        a rdf:Bag\n"
                         "    ] .\n"
                         "\n";

    ASSERT_STREQ(expected.c_str(), actual.c_str());
    // clear up file we wrote
    std::remove(fname.c_str());

}

TEST_F(RDFTests, TestParseFromFileNonStatic) {
    // first create a file containing annotations
    std::string fname = std::filesystem::current_path().string() + "/TestParseFromFile.rdf";
    std::cout << fname << std::endl;
    std::ofstream f(fname);
    if (f.is_open()) {
        f << samples.composite_annotation_pe << std::endl;
        f.flush();
        f.close();
    } else {
        throw std::logic_error("No file was opened for test");
    }

    RDF rdf;
    rdf.addFromFile(fname, "rdfxml");
    int expected = 4;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);

    // clear up file we wrote
    std::remove(fname.c_str());
}

TEST_F(RDFTests, TestWriteToFile) {
    // first create a file containing annotations
    std::string fname = std::filesystem::current_path().string() + "/TestParseFromFile.rdf";
    RDF rdf = RDF::fromString(samples.singular_annotation4);
    int expected = 1;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
    rdf.toFile("turtle", fname);

    std::filesystem::exists(fname);

    // clear up file we wrote
    std::remove(fname.c_str());
}


TEST_F(RDFTests, TestReadFromSBMLWithExtraction) {
    std::string sbml = SBMLFactory::getSBML(SBML_BIOMD204);
    // first create a file containing annotations
    RDF rdf = RDF::fromString(sbml, "rdfxml");
    std::string expected = "";
    std::string actual = rdf.toString("turtle");
    std::cout << actual << std::endl;
//    ASSERT_STREQ(expected.c_str(), actual.c_str());

}






























