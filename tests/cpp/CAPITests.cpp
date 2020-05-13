//
// Created by Ciaran on 5/12/2020.
//

#include "gtest/gtest.h"


#include "gtest/gtest.h"
#include "AnnotationSamples.h"
#include "semsim/SemsimCApi.h"
#include "semsim/RDF.h"

class CAPITests : public ::testing::Test {
public:

    AnnotationSamples samples = AnnotationSamples();

    CAPITests() = default;

    void TearDown() override {
    };

};


TEST_F(CAPITests, RDFSize) {
    semsim::RDF *rdf_ptr = semsim::RDF_new_ptr();
    semsim::RDF_fromString(rdf_ptr, samples.singular_annotation1.c_str(), "rdfxml");
    int actual = semsim::RDF_size(rdf_ptr);
    int expected = 1;
    semsim::RDF_free(rdf_ptr);
    ASSERT_EQ(expected, actual);
}

TEST_F(CAPITests, RDFfromString) {
    semsim::RDF *rdf_ptr = semsim::RDF_new_ptr();
    semsim::RDF_fromString(rdf_ptr, samples.rdf_xml_seq_example.c_str(), "rdfxml");
    int actual = semsim::RDF_size(rdf_ptr);
    int expected = 4;
    semsim::RDF_free(rdf_ptr);
    ASSERT_EQ(expected, actual);
}

TEST_F(CAPITests, RDFToString) {
    semsim::RDF *rdf_ptr = semsim::RDF_new_ptr();
    semsim::RDF_fromString(rdf_ptr, samples.singular_annotation1.c_str(), "rdfxml");
    std::string actual = rdf_ptr->toString("rdfxml-abbrev", "annotation.rdf");
    std::string expected = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
                           "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                           "   xml:base=\"file://annotation.rdf\">\n"
                           "  <rdf:Description rdf:about=\"file://./metaid_1\">\n"
                           "    <ns1:is xmlns:ns1=\"http://biomodels.net/biology-qualifiers/\"\n"
                           "       rdf:resource=\"https://identifiers.org/uniprot/P0DP23\"/>\n"
                           "  </rdf:Description>\n"
                           "</rdf:RDF>\n";
    semsim::RDF_free(rdf_ptr);
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(CAPITests, RDFsetBaseUriAsString) {
    semsim::RDF *rdf_ptr = semsim::RDF_new_ptr();
    semsim::RDF_fromString(rdf_ptr, samples.singular_annotation1.c_str(), "rdfxml");
    semsim::RDF_setBaseUri(rdf_ptr, "annotation.rdf");
    const char *actual = semsim::RDF_getBaseUri(rdf_ptr);
    const char *expected = "annotation.rdf";
    semsim::RDF_free(rdf_ptr);
    ASSERT_STREQ(expected, actual);
}

TEST_F(CAPITests, RDFqueryResultsAsStr) {
    semsim::RDF *rdf_ptr = semsim::RDF_new_ptr();
    semsim::RDF_fromString(rdf_ptr, samples.composite_annotation_pe.c_str(), "rdfxml");

    const char *query = "SELECT ?x ?y ?z \n"
                        "WHERE { ?x ?y ?z }";
    const char *results = semsim::RDF_queryResultsAsStr(rdf_ptr, query, "csv");
    semsim::RDF_free(rdf_ptr);
    std::string expected = "x,y,z\r\n"
                           "file://./VLV,http://biomodels.net/biology-qualifiers/isVersionOf,http://identifiers.org/opb/OPB_00154\r\n"
                           "file://./VLV,http://biomodels.net/biology-qualifiers/isPropertyOf,file://./MyModel.rdf#entity_0\r\n"
                           "file://./MyModel.rdf#entity_0,http://biomodels.net/biology-qualifiers/is,http://identifiers.org/fma/FMA:9670\r\n"
                           "file://./MyModel.rdf#entity_0,http://biomodels.net/biology-qualifiers/isPartOf,http://identifiers.org/fma/FMA:18228\r\n";
    ASSERT_STREQ(expected.c_str(), results);
}


















































