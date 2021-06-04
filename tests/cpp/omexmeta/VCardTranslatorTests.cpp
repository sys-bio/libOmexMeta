//
// Created by Ciaran on 20/04/2021.
//
#include "gtest/gtest.h"
#include "omexmeta/RDF.h"
#include "omexmeta/VCardTranslator.h"
#include "SBMLFactory.h"

using namespace omexmeta;

class VCardTranslatorTests: public ::testing::Test {
public:
    std::string input = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                        "@prefix bqmodel: <http://biomodels.net/model-qualifiers/> .\n"
                        "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                        "@prefix OMEXlib: <http://omex-library.org/> .\n"
                        "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                        "\n"
                        "<http://omex-library.org/NewOmex.omex/NewModel.xml#_272044>\n"
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
                        "            <http://www.w3.org/2001/vcard-rdf/3.0#EMAIL> \"nikoloski@mpimp-golm.mpg.de\" ;\n"
                        "            <http://www.w3.org/2001/vcard-rdf/3.0#N> [\n"
                        "                <http://www.w3.org/2001/vcard-rdf/3.0#Family> \"Nikoloski\" ;\n"
                        "                <http://www.w3.org/2001/vcard-rdf/3.0#Given> \"Zoran\"\n"
                        "            ] ;\n"
                        "            <http://www.w3.org/2001/vcard-rdf/3.0#ORG> [\n"
                        "                <http://www.w3.org/2001/vcard-rdf/3.0#Orgname> \"\"\"Institute of Biochemistry and Biology, University of Potsdam, 14476\n"
                        "                                    Potsdam, Germany\n"
                        "                                \"\"\"\n"
                        "            ]\n"
                        "        ] ;\n"
                        "        rdf:_3 [\n"
                        "            <http://www.w3.org/2001/vcard-rdf/3.0#EMAIL> \"arnold@mpimp-golm.mpg.de\" ;\n"
                        "            <http://www.w3.org/2001/vcard-rdf/3.0#N> [\n"
                        "                <http://www.w3.org/2001/vcard-rdf/3.0#Family> \"Arnold\" ;\n"
                        "                <http://www.w3.org/2001/vcard-rdf/3.0#Given> \"Anne\"\n"
                        "            ] ;\n"
                        "            <http://www.w3.org/2001/vcard-rdf/3.0#ORG> [\n"
                        "                <http://www.w3.org/2001/vcard-rdf/3.0#Orgname> \"Max-Planck-Institute of Molecular Plant Physiology\"\n"
                        "            ]\n"
                        "        ] ;\n"
                        "        a rdf:Bag\n"
                        "    ] .";

    VCardTranslatorTests() = default;
};


TEST_F(VCardTranslatorTests, purgeNConstruct){
    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix bqmodel: <http://biomodels.net/model-qualifiers/> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#_272044>\n"
                           "    <http://purl.org/dc/elements/1.1/creator> [\n"
                           "        rdf:_1 [\n"
                           "            <http://xmlns.com/foaf/0.1/Organization> \"EMBL-EBI\" ;\n"
                           "            <http://xmlns.com/foaf/0.1/familyName> \"Chelliah\" ;\n"
                           "            <http://xmlns.com/foaf/0.1/givenName> \"Vijayalakshmi\" ;\n"
                           "            <http://xmlns.com/foaf/0.1/mbox> \"viji@ebi.ac.uk\"\n"
                           "        ] ;\n"
                           "        rdf:_2 [\n"
                           "            <http://xmlns.com/foaf/0.1/Organization> \"\"\"Institute of Biochemistry and Biology, University of Potsdam, 14476\n"
                           "                                    Potsdam, Germany\n"
                           "                                \"\"\" ;\n"
                           "            <http://xmlns.com/foaf/0.1/familyName> \"Nikoloski\" ;\n"
                           "            <http://xmlns.com/foaf/0.1/givenName> \"Zoran\" ;\n"
                           "            <http://xmlns.com/foaf/0.1/mbox> \"nikoloski@mpimp-golm.mpg.de\"\n"
                           "        ] ;\n"
                           "        rdf:_3 [\n"
                           "            <http://xmlns.com/foaf/0.1/Organization> \"Max-Planck-Institute of Molecular Plant Physiology\" ;\n"
                           "            <http://xmlns.com/foaf/0.1/familyName> \"Arnold\" ;\n"
                           "            <http://xmlns.com/foaf/0.1/givenName> \"Anne\" ;\n"
                           "            <http://xmlns.com/foaf/0.1/mbox> \"arnold@mpimp-golm.mpg.de\"\n"
                           "        ] ;\n"
                           "        a rdf:Bag\n"
                           "    ] .";
    RDF rdf = RDF::fromString(input);
    // these were inserted into constructor anyway.
//    VCardTranslator vCardTranslator(&rdf);
//    vCardTranslator.translate();
    RDF::equals(&rdf, expected);

}


























