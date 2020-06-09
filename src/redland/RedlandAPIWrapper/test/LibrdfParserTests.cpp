//
// Created by Ciaran on 5/17/2020.
//
#include <fstream>
#include "gtest/gtest.h"
#include "World.h"
#include "LibrdfParser.h"
#include "iostream"
#include <experimental/filesystem>

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
    LibrdfModel model(storage.get());
    std::string rdf_string = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                             "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                             "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                             "   xml:base=\"file://./Annotation.rdf\">\n"
                             "  <rdf:Description rdf:about=\"SemsimMetaid0000\">\n"
                             "    <bqbiol:is rdf:resource=\"https://identifiers.org/fma/FMA_66835\"/>\n"
                             "  </rdf:Description>\n"
                             "</rdf:RDF>\n";
    std::string fname = std::experimental::filesystem::current_path().string() + "/example_rdf.rdf";
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
    parser.parseFile(fname, model);

    int actual = model.size();
    int expected = 1;
    ASSERT_EQ(expected, actual);

    // clean up file
    int failed = std::remove(fname.c_str());
    if (failed) {
        throw std::logic_error("didn't remove file");
    }
    storage.freeStorage();
    model.freeModel();
    /* parser has its own destructor */

}

TEST_F(LibrdfParserTests, TestParserFromUrl) {
    LibrdfStorage storage;
    LibrdfModel model(storage.get());

    std::string sbml_url1 = "https://www.ebi.ac.uk/biomodels/model/download/BIOMD0000000064.2?filename=BIOMD0000000064_url.xml";
    LibrdfParser parser("rdfxml");
    parser.parseUri(sbml_url1, model);

    int expected = 277;
    int actual = model.size();
    ASSERT_EQ(expected, actual);

    storage.freeStorage();
    model.freeModel();

    // parser releases itself

}














