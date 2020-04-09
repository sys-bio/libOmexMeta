//
// Created by Ciaran on 4/8/2020.
//


#include "gtest/gtest.h"
#include "semsim/RDF.h"
#include "semsim/SemSim.h"
#include "AnnotationSamples.h"

class RDFTests : public ::testing::Test {

public:

    AnnoationSamples samples;

    RDFTests() = default;


};


TEST_F(RDFTests, TestDefaultConstructor) {
    semsim::RDF rdf;
    ASSERT_TRUE(true); // If we get this far we've passed
}

TEST_F(RDFTests, TestWriteToTurtleString) {
    semsim::RDF rdf;
    rdf.fromString(samples.sample_annotation1);
    std::string actual = rdf.toString("turtle");
    std::string expected = "@base <./SemsimModel> .\n"
                           "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqb: <http://biomodels.net/biology-qualifiers> .\n"
                           "\n"
                           "<Test.xml#metaid_1>\n"
                           "    <http://biomodels.net/biology-qualifiers/is> <https://identifiers.org/uniprot/P0DP23> .\n\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(RDFTests, TestWriteToTurtleString2) {
    semsim::RDF rdf;
    rdf.fromString(samples.sample_annotation2);
    std::string actual = rdf.toString("turtle");
    std::string expected = "@base <./SemsimModel> .\n"
                           "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqb: <http://biomodels.net/biology-qualifiers> .\n"
                           "\n"
                           "<Test.xml#metaid_1>\n"
                           "    <http://biomodels.net/biology-qualifiers/is> [\n"
                           "        rdf:_1 <http://identifiers.org/chebi/CHEBI:15343> ;\n"
                           "        a rdf:Bag\n"
                           "    ] .\n\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}

TEST_F(RDFTests, TestWriteToTurtleString3) {
    semsim::RDF rdf;
    rdf.fromString(samples.sample_annotation3);
    std::string actual = rdf.toString("turtle");
    std::string expected = "@base <./SemsimModel> .\n"
                           "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqb: <http://biomodels.net/biology-qualifiers> .\n"
                           "\n"
                           "<Test.xml#metaid_2>\n"
                           "    <http://biomodels.net/biology-qualifiers/is> [\n"
                           "        rdf:_1 <http://identifiers.org/chebi/CHEBI:28907> ;\n"
                           "        a rdf:Bag\n"
                           "    ] .\n\n";
    ASSERT_STREQ(expected.c_str(), actual.c_str());
}


TEST_F(RDFTests, TestThatMakeSerializerFunctionBreaksWithWrongFormatArgument){

}











