//
// Created by Ciaran on 4/8/2020.
//


#include "gtest/gtest.h"
#include "semsim/LibRDFModel.h"
#include "semsim/SemSim.h"

class LibRDFModelTests : public ::testing::Test {

public:


    std::string sample_annotation1 = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                                     "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                     "         xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\">\n"
                                     "    <rdf:Description rdf:about=\"#metaid_1\">\n"
                                     "        <bqbiol:is rdf:resource=\"https://identifiers.org/uniprot/P0DP23\"/>\n"
                                     "    </rdf:Description>\n"
                                     "</rdf:RDF>";

    std::string sample_annotation2 = "<annotation>\n"
                                     "    <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                     "             xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                                     "             xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\"\n"
                                     "             xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                                     "             xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\">\n"
                                     "        <rdf:Description rdf:about=\"#metaid_1\">\n"
                                     "            <bqbiol:is>\n"
                                     "                <rdf:Bag>\n"
                                     "                    <rdf:li rdf:resource=\"http://identifiers.org/chebi/CHEBI:15343\"/>\n"
                                     "                </rdf:Bag>\n"
                                     "            </bqbiol:is>\n"
                                     "        </rdf:Description>\n"
                                     "    </rdf:RDF>\n"
                                     "</annotation>";

    std::string sample_annotation3 = "<annotation>\n"
                                     "    <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
                                     "             xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:dcterms=\"http://purl.org/dc/terms/\"\n"
                                     "             xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\"\n"
                                     "             xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\"\n"
                                     "             xmlns:bqmodel=\"http://biomodels.net/model-qualifiers/\">\n"
                                     "        <rdf:Description rdf:about=\"#metaid_2\">\n"
                                     "            <bqbiol:is>\n"
                                     "                <rdf:Bag>\n"
                                     "                    <rdf:li rdf:resource=\"http://identifiers.org/chebi/CHEBI:28907\"/>\n"
                                     "                </rdf:Bag>\n"
                                     "            </bqbiol:is>\n"
                                     "        </rdf:Description>\n"
                                     "    </rdf:RDF>\n"
                                     "</annotation>";

    LibRDFModelTests() = default;


};


TEST_F(LibRDFModelTests, TestDefaultConstructor) {
    semsim::LibRDFModel libRdfModel;
    ASSERT_TRUE(true); // If we get this far we've passed
}


TEST_F(LibRDFModelTests, TestDefaultConstructor2) {
    semsim::LibRDFModel rdfModel;
    rdfModel.fromString(sample_annotation1);
    rdfModel.toString("rdfxml");
}













