//
// Created by Ciaran on 5/31/2020.
//

#include "gtest/gtest.h"
#include "omexmeta/RDF.h"
#include "AnnotationSamples.h"
#include <filesystem>
#include <fstream>

using namespace semsim;

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

TEST_F(RDFTests, TestFromStringSingularAnnotation2) {
    /*
     * hashes
     * trees
     * memory
     * file
     * uri
     */
//    librdf_new_storage_from_factory()
//    librdf_storage_factory* factory =
//    librdf_storage* storage = librdf_new_storage_from_factory(World::getWorld(),
//            "sqlite", "SQLite", nullptr);
    librdf_storage* storage = librdf_new_storage(World::getWorld(), "sqlite", "db", "new='yes'");
//    RDF *rdf = new RDF();
//    RDF::fromString(rdf, samples.singular_annotation1, "rdfxml", "singular_annotation1_base");
//    int expected = 1;
//    int actual = rdf->size();
//    ASSERT_EQ(expected, actual);
//    delete rdf;
}

TEST_F(RDFTests, TestFromStringTurtleBag) {
    RDF rdf = RDF::fromString(samples.rdf_turtle_bag_example, "turtle");
    int expected = 7;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
}

TEST_F(RDFTests, TestToString) {
    RDF rdf = RDF::fromString(samples.rdf_xml_example7, "rdfxml");
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://\">\n"
                           "  <rdf:Description rdf:about=\"http://www.w3.org/TR/rdf-syntax-grammar\">\n"
                           "    <ns1:editor xmlns:ns1=\"http://example.org/stuff/1.0/\">\n"
                           "      <rdf:Description>\n"
                           "        <ns1:fullName>Dave Beckett</ns1:fullName>\n"
                           "        <ns1:homePage rdf:resource=\"http://purl.org/net/dajobe/\"/>\n"
                           "      </rdf:Description>\n"
                           "    </ns1:editor>\n"
                           "    <ns2:title xmlns:ns2=\"http://purl.org/dc/elements/1.1/\">RDF1.1 XML Syntax</ns2:title>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n"
                           "";
    std::string actual = rdf.toString();
    std::cout << actual << std::endl;
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST(RDFTestsNoFigure, TestRDFCanReadFromTwoStrings) {
    std::string rdf_string1 = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                              "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                              "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                              "   xml:base=\"file://./Annotation.rdf\">\n"
                              "  <rdf:Description rdf:about=\"SemsimMetaid0000\">\n"
                              "    <bqbiol:is rdf:resource=\"https://identifiers.org/fma/FMA_66836\"/>\n"
                              "  </rdf:Description>\n"
                              "</rdf:RDF>\n";
    std::string rdf_string2 = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                              "<rdf:RDF xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                              "   xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                              "   xml:base=\"file://./Annotation.rdf\">\n"
                              "  <rdf:Description rdf:about=\"SemsimMetaid0000\">\n"
                              "    <bqbiol:is rdf:resource=\"https://identifiers.org/fma/FMA_66835\"/>\n"
                              "  </rdf:Description>\n"
                              "</rdf:RDF>\n";

    RDF rdf;// = RDF::fromString(rdf_string1);
    rdf.fromString(rdf_string2);
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
    const char* fname = "/mnt/d/libOmexMeta/tests/cpp/sqlite_db.db";
    RDF rdf("sqlite", fname, "new='yes'");
    rdf.addFromUri(samples.sbml_url1, "rdfxml");
    int expected = 277;
    int actual = rdf.size();
    ASSERT_EQ(expected, actual);
    ASSERT_TRUE(std::filesystem::exists(fname));
    // clean up after ourselves
    std::filesystem::remove(fname);
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
    std::string fname = std::filesystem::current_path().string() + "/TestParseFromFile.rdf";
    std::cout << fname << std::endl;
    std::ofstream f(fname);
    if (f.is_open()){
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

    // clear up file we wrote
    std::remove(fname.c_str());

}

TEST_F(RDFTests, TestParseFromFileNonStatic) {
    // first create a file containing annotations
    std::string fname = std::filesystem::current_path().string() + "/TestParseFromFile.rdf";
    std::cout << fname << std::endl;
    std::ofstream f(fname);
    if (f.is_open()){
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






























