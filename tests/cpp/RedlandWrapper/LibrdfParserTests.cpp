//
// Created by Ciaran on 5/17/2020.
//
#include "filesystem"
#include "iostream"
#include "raptor2.h"
#include "redland/LibrdfParser.h"
#include "redland/LibrdfWorld.h"
#include "gtest/gtest.h"
#include <fstream>
//#include "AnnotationSamples.h"

using namespace redland;

class LibrdfParserTests : public ::testing::Test {

public:
    //    AnnotationSamples samples;

    LibrdfParserTests() = default;
};

TEST_F(LibrdfParserTests, TestInstantiateParser) {
    LibrdfParser parser1 = LibrdfParser("rdfxml");
    ASSERT_NE(parser1.get(), nullptr);
}


TEST_F(LibrdfParserTests, TestMoveConstructor) {
    LibrdfParser parser1 = LibrdfParser("rdfxml");
    auto parser1_int_ptr = reinterpret_cast<std::uintptr_t>(parser1.get());
    LibrdfParser parser2 = std::move(parser1);
    auto parser2_int_ptr = reinterpret_cast<std::uintptr_t>(parser2.get());
    ASSERT_EQ(parser1_int_ptr, parser2_int_ptr);
}

TEST_F(LibrdfParserTests, TestMoveAssignment) {
    LibrdfParser parser1 = LibrdfParser("rdfxml");
    auto parser1_int_ptr = reinterpret_cast<std::uintptr_t>(parser1.get());
    LibrdfParser parser2 = LibrdfParser("rdfxml");
    auto parser2_int_ptr = reinterpret_cast<std::uintptr_t>(parser2.get());
    parser1 = std::move(parser2);
    ASSERT_NE(parser1_int_ptr, parser2_int_ptr);
}

TEST_F(LibrdfParserTests, TestValidParserName) {
    LibrdfParser parser1 = LibrdfParser("rdfxml");
    std::string actual = parser1.getName();
    std::string expected = "rdfxml";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfParserTests, TestInvalidParserName) {
    ASSERT_THROW(LibrdfParser("parser"), std::invalid_argument);
}

TEST_F(LibrdfParserTests, TestSetName) {
    LibrdfParser parser("rdfxml");
    parser.setName("turtle");
    std::string actual = parser.getName();
    std::string expected = "turtle";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfParserTests, TestGetMimeType) {
    LibrdfParser parser("rdfxml");
    ASSERT_EQ(std::string(), parser.getMimeType());
}

TEST_F(LibrdfParserTests, TestGetMimeType2) {
    LibrdfParser parser(std::string(), "application/rdf+xml");
    ASSERT_EQ("application/rdf+xml", parser.getMimeType());
}

TEST_F(LibrdfParserTests, TestParseFromAFile) {
    LibrdfStorage storage;
    LibrdfModel model(storage);
    std::string rdf_string = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                             "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                             "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                             "   xml:base=\"file://./Annotation.rdf\">\n"
                             "  <rdf:Description rdf:about=\"OmexMetaId0000\">\n"
                             "    <bqbiol:is rdf:resource=\"https://identifiers.org/fma/FMA_66835\"/>\n"
                             "  </rdf:Description>\n"
                             "</rdf:RDF>\n";
    std::string fname = std::filesystem::current_path().string() + "/example_rdf.rdf";

    std::cout << fname << std::endl;

    std::ofstream file(fname);
    if (file.is_open()) {
        file << rdf_string << std::endl;
        file.flush();
        file.close();
    } else {
        throw std::logic_error("File didn't open for writing");
    }

    LibrdfParser parser("rdfxml");
    parser.parseFile(fname, model, "baseUri");

    int actual = model.size();
    int expected = 1;
    ASSERT_EQ(expected, actual);

    // clean up file
    int failed = std::remove(fname.c_str());
    if (failed) {
        throw std::logic_error("didn't remove file");
    }
}


TEST_F(LibrdfParserTests, TestRelativeBaseUriResolvesCorrectly) {
    std::string input = "<?xml version=\"1.0\"?>\n"
                        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                        "     xmlns:dc=\"http://purl.org/dc/elements/1.1/\"\n"
                        "     xml:base=\"https://www.dajobe.org/net/this/is/the/base\">\n"
                        "  <rdf:Description rdf:about=\"#dajobe\">\n"
                        "    <dc:title>Dave Beckett's Home Page</dc:title>\n"
                        "    <dc:creator>Dave Beckett</dc:creator>\n"
                        "    <dc:description>The generic home page of Dave Beckett.</dc:description>\n"
                        "  </rdf:Description> \n"
                        "</rdf:RDF>";
    std::filesystem::path storage_fname = std::filesystem::current_path() /= "LibrdfParserTests_TestBaseUri.db";
    LibrdfStorage storage("sqlite", storage_fname.string(), "new='yes'");
    LibrdfModel model(storage);
    LibrdfParser parser("rdfxml");
    parser.parseString(input, model, "LibrdfParserTests_TestBaseUri");
    std::cout << storage_fname << std::endl;

    std::string expected = "https://www.dajobe.org/net/this/is/the/base#dajobe";

    LibrdfStream stream = model.toStream();
    LibrdfStatement statement = stream.getStatement();
    LibrdfNode node = statement.getSubjectNode();
    std::string actual = node.str();
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(LibrdfParserTests, TestParserString) {
    std::string input = "<?xml version=\"1.0\"?>\n"
                        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                        "     xmlns:dc=\"http://purl.org/dc/elements/1.1/\"\n"
                        "     xml:base=\"https://www.dajobe.org/net/this/is/the/base\">\n"
                        "  <rdf:Description rdf:about=\"#dajobe\">\n"
                        "    <dc:title>Dave Beckett's Home Page</dc:title>\n"
                        "    <dc:creator>Dave Beckett</dc:creator>\n"
                        "    <dc:description>The generic home page of Dave Beckett.</dc:description>\n"
                        "  </rdf:Description> \n"
                        "</rdf:RDF>";
    std::filesystem::path storage_fname = std::filesystem::current_path() /= "LibrdfParserTests_TestBaseUri.db";
    LibrdfStorage storage;
    LibrdfModel model(storage);
    {
        LibrdfParser parser("turtle");
        parser.parseString(input, model, "LibrdfParserTests_TestBaseUri");
    }
    {
        LibrdfParser parser("turtle");
        parser.parseString(input, model, "LibrdfParserTests_TestBaseUri");
    }


    //
    //    LibrdfStream stream = model.toStream();
    //    LibrdfStatement statement =  stream.getStatement();
    //    LibrdfNode node = statement.getSubjectNode();
    //    std::string actual = node.str();
    //    std::cout << actual << std::endl;
}


TEST_F(LibrdfParserTests, TestFeatures) {
    LibrdfStorage storage;
    LibrdfModel model(storage);
    LibrdfParser parser("turtle");

    LibrdfUri scanForRDFUri("http://feature.librdf.org/raptor-scanForRDF");
    auto scanForRDFNode = LibrdfNode(librdf_parser_get_feature(parser.get(), scanForRDFUri.get()));

    LibrdfUri allowNonNsAttributesUri("http://feature.librdf.org/raptor-allowNonNsAttributes");
    auto allowNonNsAttributesNode = LibrdfNode(
            librdf_parser_get_feature(parser.get(), allowNonNsAttributesUri.get()));

    LibrdfUri allowOtherParsetypesUri("http://feature.librdf.org/raptor-allowOtherParsetypes");
    auto allowOtherParsetypesNode = LibrdfNode(
            librdf_parser_get_feature(parser.get(), allowOtherParsetypesUri.get()));

    LibrdfUri allowBagIDUri("http://feature.librdf.org/raptor-allowBagID");
    auto allowBagIDNode = LibrdfNode(librdf_parser_get_feature(parser.get(), allowBagIDUri.get()));

    LibrdfUri allowRDFtypeRDFlistUri("http://feature.librdf.org/raptor-allowRDFtypeRDFlist");
    auto allowRDFtypeRDFlistNode = LibrdfNode(
            librdf_parser_get_feature(parser.get(), allowRDFtypeRDFlistUri.get()));

    LibrdfUri normalizeLanguageUri("http://feature.librdf.org/raptor-normalizeLanguage");
    auto normalizeLanguageNode = LibrdfNode(librdf_parser_get_feature(parser.get(), normalizeLanguageUri.get()));

    LibrdfUri nonNFCfatalUri("http://feature.librdf.org/raptor-nonNFCfatal");
    auto nonNFCfatalNode = LibrdfNode(librdf_parser_get_feature(parser.get(), nonNFCfatalUri.get()));

    LibrdfUri warnOtherParseTypesUri("http://feature.librdf.org/raptor-warnOtherParseTypes");
    auto warnOtherParseTypesNode = LibrdfNode(
            librdf_parser_get_feature(parser.get(), warnOtherParseTypesUri.get()));

    LibrdfUri checkRdfIDUri("http://feature.librdf.org/raptor-checkRdfID");
    auto checkRdfIDNode = LibrdfNode(librdf_parser_get_feature(parser.get(), checkRdfIDUri.get()));

    ASSERT_EQ("1", scanForRDFNode.str());
    ASSERT_EQ("0", allowNonNsAttributesNode.str());
    ASSERT_EQ("1", allowOtherParsetypesNode.str());
    ASSERT_EQ("0", allowBagIDNode.str());
    ASSERT_EQ("1", allowRDFtypeRDFlistNode.str());
    ASSERT_EQ("1", normalizeLanguageNode.str());
    ASSERT_EQ("0", nonNFCfatalNode.str());
    ASSERT_EQ("1", warnOtherParseTypesNode.str());
    ASSERT_EQ("1", checkRdfIDNode.str());
}

/**
 * This scenario caused a horendous uninit value bug.
 *
 */
TEST_F(LibrdfParserTests, CheckTweiceFirstFailThenParseAgain) {
    std::string singular_annotation1 = "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                                       "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                       "   xmlns:OMEXlib=\"http://omex-library.org/\"\n"
                                       "   xmlns:myOMEX=\"http://omex-library.org/NewModel.omex/\"\n"
                                       "   xmlns:local=\"http://omex-library.org/NewModel.rdf\"\n"
                                       "   xml:base=\"file://./NewModel.rdf\">\n"
                                       "    <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#metaid_1\">\n"
                                       "        <bqbiol:is rdf:resource=\"https://identifiers.org/uniprot/P0DP23\"/>\n"
                                       "    </rdf:Description>\n"
                                       "</rdf:RDF>\n";
    // singular_annotation1 is rdfxml, but we sprcify turtle
    // We let librdf issue a warning, rather than throw

    std::string query = "SELECT ?x ?y ?z\n"
                        "WHERE  {?x ?y ?z}\n";
    LibrdfStorage storage;
    LibrdfModel model(storage);
    LibrdfUri u("base");
    {
        LibrdfParser parser("rdfxml");
        parser.parseString(singular_annotation1, model, u);
        LibrdfQuery q1(query, model);
        LibrdfQueryResults re1 = q1.execute();
        auto m1 = re1.map();
    }
    {
        LibrdfParser parser("turtle");
        // had a bug here, but only after the previous {}
        parser.parseString(singular_annotation1, model, u);
    }

    ASSERT_EQ(1, model.size());
}


//
//
//TEST_F(LibrdfParserTests, CheckTweiceFirstFailThenParseAgain2) {
//    std::string singular_annotation1 = "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
//                                       "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
//                                       "   xmlns:OMEXlib=\"http://omex-library.org/\"\n"
//                                       "   xmlns:myOMEX=\"http://omex-library.org/NewModel.omex/\"\n"
//                                       "   xmlns:local=\"http://omex-library.org/NewModel.rdf\"\n"
//                                       "   xml:base=\"file://./NewModel.rdf\">\n"
//                                       "    <rdf:Description rdf:about=\"http://omex-library.org/NewOmex.omex/NewModel.xml#metaid_1\">\n"
//                                       "        <bqbiol:is rdf:resource=\"https://identifiers.org/uniprot/P0DP23\"/>\n"
//                                       "    </rdf:Description>\n"
//                                       "</rdf:RDF>\n";
//    // singular_annotation1 is rdfxml, but we sprcify turtle
//    // We let librdf issue a warning, rather than throw
//
//    std::string qstring2 = "SELECT  ?subjectBlank ?resourceBlank ?vCardPred ?literal\n"
//                    "WHERE {\n"
//                    "?subjectBlank <http://www.w3.org/2001/vcard-rdf/3.0#N> ?resourceBlank .\n"
//                    "?resourceBlank ?vCardPred ?literal\n"
//                    "}\n";
////    librdf_world* world = librdf_new_world();
//    librdf_storage* storage = librdf_new_storage(LibrdfWorld::getWorld(),"memory", "m", nullptr );
//    librdf_model* model = librdf_new_model(LibrdfWorld::getWorld(), storage, nullptr);
//    librdf_uri* u = librdf_new_uri(LibrdfWorld::getWorld(), (const unsigned char*) "base");
////    LibrdfUri u2("base");
//    {
//        librdf_parser* parser = librdf_new_parser(LibrdfWorld::getWorld(), "rdfxml", nullptr, nullptr);
//        librdf_parser_parse_string_into_model(parser, (const unsigned char*) singular_annotation1.c_str(), u, model);
//        std::string query = "SELECT ?x ?y ?z\n"
//                            "WHERE  {?x ?y ?z}\n";
//        librdf_query* q = librdf_new_query(
//                LibrdfWorld::getWorld(),
//                "sparql",
//                nullptr,
//                (const unsigned char *) query.c_str(),
//                nullptr);
//
////        librdf_query_results *qr = librdf_query_execute(q, model.getWithoutIncrement());
//
//        librdf_free_query(q);
//        librdf_free_parser(parser);
//
//    }
//    {
//        librdf_parser* parser = librdf_new_parser(LibrdfWorld::getWorld(), "turtle", nullptr, nullptr);
//        librdf_parser_parse_string_into_model(parser, (const unsigned char*) singular_annotation1.c_str(), u, model);
//        librdf_free_parser(parser);
//
//    }
//
//    //    ASSERT_EQ(1, model.size());
//    librdf_free_uri(u);
//    librdf_free_model(model);
//    librdf_free_storage(storage);
//}
