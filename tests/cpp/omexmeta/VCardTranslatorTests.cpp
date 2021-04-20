//
// Created by Ciaran on 20/04/2021.
//
#include "gtest/gtest.h"

class VCardTranslatorTests: public ::testing::Test {
public:
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
    VCardTranslatorTests() = default;
};

TEST_F(VCardTranslatorTests, t){

}


























