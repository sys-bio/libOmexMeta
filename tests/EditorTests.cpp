//
// Created by Ciaran on 4/15/2020.
//
#include "gtest/gtest.h"
#include "SBMLFactory.h"
#include "semsim/Editor.h"
#include "semsim/XmlAssistant.h"

class EditorTests : public ::testing::Test {

public:

    EditorTests() {
    };
};


TEST_F(EditorTests, TestMetaIds) {
    // todo this is a weak test: I should really go and get all the metaids using libxml for comparison
    semsim::Editor editor(SBMLFactory::getModelStr(SBML_NOT_ANNOTATED), semsim::ASSISTANT_TYPE_SBML);
    const auto& metaids = editor.getMetaids();
    std::vector<std::string> expected = {"SemsimMetaid0000", "SemsimMetaid0001", "SemsimMetaid0002", "cytosol",
                                         "Meta00001", "SemsimMetaid0003", "SemsimMetaid0004", "SemsimMetaid0005",
                                         "SemsimMetaid0006", "SemsimMetaid0007", "SemsimMetaid0008", "SemsimMetaid0009",
                                         "SemsimMetaid0010"};
    ASSERT_EQ(expected, metaids);
}

TEST_F(EditorTests, TestAddAnnotation) {
//        std::string singular_annotation1 = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
//                                       "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\"\n"
//                                       "         xmlns:bqbiol=\"http://biomodels.net/biology-qualifiers/\">\n"
//                                       "    <rdf:Description rdf:about=\"#metaid_1\">\n"
//                                       "        <bqbiol:is rdf:resource=\"https://identifiers.org/uniprot/P0DP23\"/>\n"
//                                       "    </rdf:Description>\n"
//                                       "</rdf:RDF>\n";
    // todo this is a weak test: I should really go and get all the metaids using libxml for comparison
    semsim::Editor editor(SBMLFactory::getModelStr(SBML_NOT_ANNOTATED), semsim::ASSISTANT_TYPE_SBML);

    editor.addAnnotation("SemsimMetaid0010", semsim::BiomodelsQualifier("is"), "https://identifiers.org/uniprot/P0DP23");
    editor.addAnnotation("SemsimMetaid0010", semsim::BiomodelsQualifier("is"), semsim::Resource("uniprot:P0DP23"));
}

























