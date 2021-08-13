//
// Created by Ciaran on 5/31/2020.
//

#include "AnnotationSamples.h"
#include "SBMLFactory.h"
#include "omexmeta/RDF.h"
#include "gtest/gtest.h"
#include <filesystem>
#include <fstream>
#include <thread>

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

TEST_F(RDFTests, TestFromStringButWrongSyntax) {
    // singular_annotation1 is rdfxml, but we sprcify turtle
    // We let librdf issue a warning, rather than throw
    ASSERT_NO_THROW(
    RDF rdf = RDF::fromString(samples.singular_annotation1, "turtle");
    );
}

TEST_F(RDFTests, TestFromStringTwice) {
    // singular_annotation1 is rdfxml, but we sprcify turtle
    // We let librdf issue a warning, rather than throw
    RDF rdf1 = RDF::fromString(samples.singular_annotation1, "turtle");
    RDF rdf2 = RDF::fromString(samples.singular_annotation1, "turtle");
    ASSERT_EQ(0, rdf2.size());

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
    // note that rdf::bag is auto removed
    RDF rdf = RDF::fromString(samples.rdf_turtle_bag_example, "turtle");
    int expected = 5;// 7 with rdf:bag
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
}

TEST_F(RDFTests, Equality) {
    RDF rdf1 = RDF::fromString(samples.rdf_turtle_basic_example, "turtle");
    RDF rdf2 = RDF::fromString(samples.rdf_turtle_basic_example, "turtle");
    ASSERT_TRUE(rdf1 == rdf2);
}

TEST_F(RDFTests, Inquality) {
    RDF rdf1 = RDF::fromString(samples.rdf_turtle_basic_example, "turtle");
    RDF rdf2 = RDF::fromString(samples.rdf_turtle_bag_example, "turtle");
    ASSERT_FALSE(rdf1 == rdf2);
}

TEST_F(RDFTests, TestToString) {
    RDF rdf = RDF::fromString(samples.rdf_xml_example7, "rdfxml");
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://www.w3.org/TR/rdf-syntax-grammar>\n"
                           "    <http://example.org/stuff/1.0/editor> [\n"
                           "        <http://example.org/stuff/1.0/fullName> \"Dave Beckett\" ;\n"
                           "        <http://example.org/stuff/1.0/homePage> <http://purl.org/net/dajobe/>\n"
                           "    ] ;\n"
                           "    <http://purl.org/dc/elements/1.1/title> \"RDF1.1 XML Syntax\" .\n"
                           "\n"
                           "";
    std::string actual = rdf.toString();
    std::cout << actual << std::endl;
    bool truth = RDF::equals(&rdf, expected, "turtle", true);
    ASSERT_TRUE(truth);
}

TEST(RDFTestsNoFigure, TestRDFCanReadFromTwoStrings) {
    std::string rdf_string1 = "<?xml version=\"1.1\" encoding=\"utf-8\"?>\n"
                              "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                              "   xmlns:local=\"http://omex-library.org/NewModel.rdf#\"\n"
                              "   xmlns:myOMEX=\"http://omex-library.org/NewModel.omex\"\n"
                              "   xmlns:OMEXlib=\"http://omex-library.org/\"\n"
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

TEST_F(RDFTests, TestParseFromFile) {
    // first create a file containing annotations
    //    raptor_option_uri_prefix;
    std::string fname = (std::filesystem::current_path() / +"TestParseFromFile.rdf").string();
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
    rdf.toFile(fname, "turtle");

    ASSERT_TRUE(std::filesystem::exists(fname));

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

TEST_F(RDFTests, TestReadSBMLModelWithBagFromString) {
    RDF expectedRdf = RDF::fromString(samples.annotationFromSBMLModelWithRDFBag);
    std::string sbml = SBMLFactory::getSBML(SBML_WITH_BAG);
    RDF actualRdf = RDF::fromString(sbml, "rdfxml");

    ASSERT_TRUE(RDF::equals(&actualRdf, &expectedRdf, "turtle"));
}

TEST_F(RDFTests, TestReadSBMLModelWithBagFromFile) {
    std::filesystem::path fname = std::filesystem::current_path() / +"sbml.xml";
    RDF expectedRdf = RDF::fromString(samples.annotationFromSBMLModelWithRDFBag);

    // get sbml as string
    std::string sbml = SBMLFactory::getSBML(SBML_WITH_BAG);

    // write it to file
    std::ofstream f;
    f.open(fname);
    f << sbml;
    f.close();

    RDF actualRdf = RDF::fromFile(fname.string(), "rdfxml");
    ASSERT_TRUE(RDF::equals(&actualRdf, &expectedRdf, "turtle", true));

    // clean up file
    remove(fname);
}

TEST_F(RDFTests, TestRepositoryPrefix) {
    RDF rdf = RDF::fromString(samples.singular_annotation1);
    std::string turtle_string = rdf.toString("turtle");
    std::string arg = "@prefix OMEXlib: <http://omex-library.org/> .";
    ASSERT_TRUE(OmexMetaUtils::isSubString(turtle_string, arg));
}

TEST_F(RDFTests, TestLocalPrefix) {
    RDF rdf = RDF::fromString(samples.singular_annotation1);
    std::string turtle_string = rdf.toString("turtle");
    std::string arg = "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .";
    ASSERT_TRUE(OmexMetaUtils::isSubString(turtle_string, arg));
}

TEST_F(RDFTests, getModelLevelAnnotationUri) {
    RDF rdf = RDF::fromString(samples.singular_annotation1);
    // default string is this:
    std::string expected = "http://omex-library.org/NewOmex.omex/NewModel.xml#NewModel";
    ASSERT_STREQ(expected.c_str(), rdf.getModelLevelAnnotationUri().c_str());
}

TEST_F(RDFTests, setModelMetaid) {
    RDF rdf = RDF::fromString(samples.singular_annotation1);
    rdf.setModelMetaid("ModelMetaid");
    ASSERT_STREQ(rdf.getModelMetaid().c_str(), "ModelMetaid");
    std::string expected = "http://omex-library.org/NewOmex.omex/NewModel.xml#ModelMetaid";
    ASSERT_STREQ(expected.c_str(), rdf.getModelLevelAnnotationUri().c_str());
}


TEST_F(RDFTests, TestSerializeCellMlAnnotationNoTrailingHashes) {
    std::string cellml = "<model xmlns=\"http://www.cellml.org/cellml/1.1#\" xmlns:cmeta=\"http://www.cellml.org/metadata/1.0#\"\n"
                         "      name=\"annotation_examples\" cmeta:id=\"annExamples\">\n"
                         "  <component name=\"main\">\n"
                         "    <variable cmeta:id=\"main.Volume\" initial_value=\"100\" name=\"Volume\" units=\"dimensionless\" />\n"
                         "    <variable cmeta:id=\"main.MembraneVoltage\" initial_value=\"-80\" name=\"MembraneVoltage\" units=\"dimensionless\" />\n"
                         "    <variable cmeta:id=\"main.ReactionRate\" initial_value=\"1\" name=\"ReactionRate\" units=\"dimensionless\" />\n"
                         "  </component>\n"
                         "</model>";

    RDF rdf = RDF();
    rdf.setArchiveUri("my-omex-archive.omex");
    rdf.setModelUri("my-model.cellml");
    Editor editor = rdf.toEditor(cellml, false, false);
    editor.addCreator("0000-0003-4667-9779");
    editor.addTaxon("9895");
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix dc: <http://purl.org/dc/terms/> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix NCBI_Taxon: <https://identifiers.org/taxonomy:> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix local: <http://omex-library.org/my-omex-archive.omex/my-model.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/my-omex-archive.omex/my-model.cellml#annExamples>\n"
                           "    bqbiol:hasTaxon <https://identifiers.org/taxonomy:9895> ;\n"
                           "    dc:creator <https://orcid.org/0000-0003-4667-9779> .";
    ASSERT_TRUE(RDF::equals(&rdf, expected, "turtle", true));
}

TEST_F(RDFTests, TestBagConversion) {
    std::string input = "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                        "                 xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\"\n"
                        "                 xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\"\n"
                        "                 xmlns:dcterms=\"http://purl.org/dc/terms/\" xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\">\n"
                        "            <rdf:Description rdf:about=\"#_272044\">\n"
                        "                <dc:creator>\n"
                        "                    <rdf:Bag>\n"
                        "                        <rdf:li rdf:parseType=\"Resource\">\n"
                        "                            <vCard:N rdf:parseType=\"Resource\">\n"
                        "                                <vCard:Family>Chelliah</vCard:Family>\n"
                        "                                <vCard:Given>Vijayalakshmi</vCard:Given>\n"
                        "                            </vCard:N>\n"
                        "                            <vCard:EMAIL>viji@ebi.ac.uk</vCard:EMAIL>\n"
                        "                            <vCard:ORG rdf:parseType=\"Resource\">\n"
                        "                                <vCard:Orgname>EMBL-EBI</vCard:Orgname>\n"
                        "                            </vCard:ORG>\n"
                        "                        </rdf:li>\n"
                        "                        <rdf:li rdf:parseType=\"Resource\">\n"
                        "                            <vCard:N rdf:parseType=\"Resource\">\n"
                        "                                <vCard:Family>Nikoloski</vCard:Family>\n"
                        "                                <vCard:Given>Zoran</vCard:Given>\n"
                        "                            </vCard:N>\n"
                        "                            <vCard:EMAIL>nikoloski@mpimp-golm.mpg.de</vCard:EMAIL>\n"
                        "                            <vCard:ORG rdf:parseType=\"Resource\">\n"
                        "                                <vCard:Orgname>Institute of Biochemistry and Biology, University of Potsdam, 14476\n"
                        "                                    Potsdam, Germany\n"
                        "                                </vCard:Orgname>\n"
                        "                            </vCard:ORG>\n"
                        "                        </rdf:li>\n"
                        "                        <rdf:li rdf:parseType=\"Resource\">\n"
                        "                            <vCard:N rdf:parseType=\"Resource\">\n"
                        "                                <vCard:Family>Arnold</vCard:Family>\n"
                        "                                <vCard:Given>Anne</vCard:Given>\n"
                        "                            </vCard:N>\n"
                        "                            <vCard:EMAIL>arnold@mpimp-golm.mpg.de</vCard:EMAIL>\n"
                        "                            <vCard:ORG rdf:parseType=\"Resource\">\n"
                        "                                <vCard:Orgname>Max-Planck-Institute of Molecular Plant Physiology</vCard:Orgname>\n"
                        "                            </vCard:ORG>\n"
                        "                        </rdf:li>\n"
                        "                    </rdf:Bag>\n"
                        "                </dc:creator>\n"
                        "                <dcterms:created rdf:parseType=\"Resource\">\n"
                        "                    <dcterms:W3CDTF>2011-10-19T14:51:13Z</dcterms:W3CDTF>\n"
                        "                </dcterms:created>\n"
                        "                <dcterms:modified rdf:parseType=\"Resource\">\n"
                        "                    <dcterms:W3CDTF>2012-04-20T19:52:45Z</dcterms:W3CDTF>\n"
                        "                </dcterms:modified>\n"
                        "                <bqmodel:is>\n"
                        "                    <rdf:Bag>\n"
                        "                        <rdf:li rdf:resource=\"http://identifiers.org/biomodels.db/MODEL1109270001\"/>\n"
                        "                    </rdf:Bag>\n"
                        "                </bqmodel:is>\n"
                        "                <bqmodel:is>\n"
                        "                    <rdf:Bag>\n"
                        "                        <rdf:li rdf:resource=\"http://identifiers.org/biomodels.db/BIOMD0000000385\"/>\n"
                        "                    </rdf:Bag>\n"
                        "                </bqmodel:is>\n"
                        "                <bqmodel:isDescribedBy>\n"
                        "                    <rdf:Bag>\n"
                        "                        <rdf:li rdf:resource=\"http://identifiers.org/pubmed/22001849\"/>\n"
                        "                    </rdf:Bag>\n"
                        "                </bqmodel:isDescribedBy>\n"
                        "                <bqmodel:is>\n"
                        "                    <rdf:Bag>\n"
                        "                        <rdf:li rdf:resource=\"http://identifiers.org/obo.go/GO:0019253\"/>\n"
                        "                    </rdf:Bag>\n"
                        "                </bqmodel:is>\n"
                        "                <bqbiol:hasTaxon>\n"
                        "                    <rdf:Bag>\n"
                        "                        <rdf:li rdf:resource=\"http://identifiers.org/taxonomy/33090\"/>\n"
                        "                    </rdf:Bag>\n"
                        "                </bqbiol:hasTaxon>\n"
                        "            </rdf:Description>\n"
                        "        </rdf:RDF>";
    RDF rdf = RDF::fromString(input, "rdfxml");

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqmodel: <http://biomodels.net/model-qualifiers/> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#_272044>\n"
                           "    bqbiol:hasTaxon <http://identifiers.org/taxonomy/33090> ;\n"
                           "    bqmodel:is <http://identifiers.org/biomodels.db/BIOMD0000000385>, <http://identifiers.org/biomodels.db/MODEL1109270001>, <http://identifiers.org/obo.go/GO:0019253> ;\n"
                           "    bqmodel:isDescribedBy <http://identifiers.org/pubmed/22001849> ;\n"
                           "    <http://purl.org/dc/elements/1.1/creator> [\n"
                           "        <http://xmlns.com/foaf/0.1/Organization> \"EMBL-EBI\" ;\n"
                           "        <http://xmlns.com/foaf/0.1/familyName> \"Chelliah\" ;\n"
                           "        <http://xmlns.com/foaf/0.1/givenName> \"Vijayalakshmi\" ;\n"
                           "        <http://xmlns.com/foaf/0.1/mbox> \"viji@ebi.ac.uk\"\n"
                           "    ], [\n"
                           "        <http://xmlns.com/foaf/0.1/Organization> \"\"\"Institute of Biochemistry and Biology, University of Potsdam, 14476\n"
                           "                                    Potsdam, Germany\n"
                           "                                \"\"\" ;\n"
                           "        <http://xmlns.com/foaf/0.1/familyName> \"Nikoloski\" ;\n"
                           "        <http://xmlns.com/foaf/0.1/givenName> \"Zoran\" ;\n"
                           "        <http://xmlns.com/foaf/0.1/mbox> \"nikoloski@mpimp-golm.mpg.de\"\n"
                           "    ], [\n"
                           "        <http://xmlns.com/foaf/0.1/Organization> \"Max-Planck-Institute of Molecular Plant Physiology\" ;\n"
                           "        <http://xmlns.com/foaf/0.1/familyName> \"Arnold\" ;\n"
                           "        <http://xmlns.com/foaf/0.1/givenName> \"Anne\" ;\n"
                           "        <http://xmlns.com/foaf/0.1/mbox> \"arnold@mpimp-golm.mpg.de\"\n"
                           "    ] ;\n"
                           "    <http://purl.org/dc/terms/created> [\n"
                           "        <http://purl.org/dc/terms/W3CDTF> \"2011-10-19T14:51:13Z\"\n"
                           "    ] ;\n"
                           "    <http://purl.org/dc/terms/modified> [\n"
                           "        <http://purl.org/dc/terms/W3CDTF> \"2012-04-20T19:52:45Z\"\n"
                           "    ] .";
    ASSERT_TRUE(RDF::equals(&rdf, expected, "turtle", true));
}



class ParserReadTesReadFromFileHasPrefixesTests : public ::testing::Test {
public:
    std::string expected = "<?xml version=\"1.1\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:OMEXlib=\"http://omex-library.org/\"\n"
                           "   xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "   xmlns:local=\"http://omex-library.org/NewOmex.omex/NewModel.rdf#\"\n"
                           "   xmlns:myOMEX=\"http://omex-library.org/NewOmex.omex/\"\n"
                           "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n"
                           "  <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#OmexMetaId0000\">\n"
                           "    <bqbiol:is rdf:resource=\"https://identifiers.org/uniprot/PD12345\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    AnnotationSamples samples;
    const std::string &input_string = samples.simple_input_turtle_string;
    ParserReadTesReadFromFileHasPrefixesTests() = default;
};

TEST_F(ParserReadTesReadFromFileHasPrefixesTests, TestReadFromStringHasPrefixes) {
    RDF rdf = RDF::fromString(input_string, "turtle");
    ASSERT_TRUE(RDF::equals(&rdf, expected, "rdfxml"));
}

TEST_F(ParserReadTesReadFromFileHasPrefixesTests, TestReadFromFileHasPrefixes) {
    std::filesystem::path fname = std::filesystem::current_path() / +"annotation_file.rdf";
    std::ofstream annot_file;

    annot_file.open(fname);
    annot_file << samples.simple_input_turtle_string;
    annot_file.close();
    RDF rdf = RDF::fromFile(fname.string(), "turtle");
    std::string output = rdf.toString("rdfxml-abbrev");

    ASSERT_TRUE(RDF::equals(&rdf, expected, "rdfxml"));
    remove(fname.string().c_str());
}
