//
// Created by Ciaran on 4/14/2020.
//

#include "CellMLFactory.h"
#include "SBMLFactory.h"
#include "omexmeta/OmexMetaXml.h"
#include "gtest/gtest.h"
#include <thread>
using namespace omexmeta;

class OmexMetaXMLTests : public ::testing::Test {
};

TEST_F(OmexMetaXMLTests, TestValidElements) {
    MetaID metaId("#OmexMetaId", 0, 4);
    std::string model_string = SBMLFactory::getSBML(SBML_ANNOTATED);
    std::cout << model_string << std::endl;
    OmexMetaXml SemsimXmlAssistant(model_string, "ID", 4);
    const std::vector<std::string> &actual = SemsimXmlAssistant.getValidElements();
    std::vector<std::string> expected = {"Any"};
    ASSERT_EQ(expected, actual);
}


TEST_F(OmexMetaXMLTests, TestValidElementsSBML) {
    MetaID metaId("#OmexMetaId", 0, 4);
    std::string sbml = SBMLFactory::getSBML(SBML_NOT_ANNOTATED);
    OmexMetaSBML assistant(sbml, "ID", 4);
    const std::vector<std::string> &actual = assistant.getValidElements();
    std::vector<std::string> expected = {
            "model",
            "unit",
            "compartment",
            "species",
            "reaction",
            "kineticLaw",
            "parameter",
    };
    ASSERT_EQ(expected, actual);
}

TEST_F(OmexMetaXMLTests, TestMetaIdsAll) {
    std::string sbml = SBMLFactory::getSBML(SBML_NOT_ANNOTATED);
    OmexMetaXml SemsimXmlAssistant(sbml, "#OmexMetaId", 4, true);
    auto sbml_and_meta_ids = SemsimXmlAssistant.addMetaIds();
    sbml = sbml_and_meta_ids.first;
    std::cout << sbml << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                           "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version2/core\" level=\"3\" version=\"2\" =\"sbml0000\">\n"
                           "  <model id=\"TestModelNotAnnotated\" =\"model0000\">\n"
                           "    <listOfUnitDefinitions =\"listOfUnitDefinitions0000\">\n"
                           "      <unitDefinition id=\"molar\" =\"unitDefinition0000\">\n"
                           "        <listOfUnits =\"listOfUnits0000\">\n"
                           "          <unit kind=\"mole\" exponent=\"1\" scale=\"1\" multiplier=\"1\" =\"unit0000\"/>\n"
                           "          <unit kind=\"litre\" exponent=\"-1\" scale=\"1\" multiplier=\"1\" =\"unit0001\"/>\n"
                           "        </listOfUnits>\n"
                           "      </unitDefinition>\n"
                           "    </listOfUnitDefinitions>\n"
                           "    <listOfCompartments =\"listOfCompartments0001\">\n"
                           "      <compartment metaid=\"#cytosol\" id=\"cytosol\" size=\"1\" constant=\"true\" =\"compartment0000\"/>\n"
                           "    </listOfCompartments>\n"
                           "    <listOfSpecies =\"listOfSpecies0002\">\n"
                           "      <species metaid=\"#Meta00001\" id=\"X\" compartment=\"cytosol\" initialConcentration=\"10\" substanceUnits=\"molar\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\" =\"species0000\"/>\n"
                           "      <species id=\"Y\" compartment=\"cytosol\" initialConcentration=\"20\" substanceUnits=\"molar\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\" =\"species0001\"/>\n"
                           "      <species id=\"Y\" compartment=\"cytosol\" initialConcentration=\"15\" substanceUnits=\"molar\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\" =\"species0002\"/>\n"
                           "    </listOfSpecies>\n"
                           "    <listOfReactions =\"listOfReactions0003\">\n"
                           "      <reaction id=\"X2Y\" reversible=\"false\" =\"reaction0000\">\n"
                           "        <listOfProducts =\"listOfProducts0000\">\n"
                           "          <speciesReference species=\"Y\" constant=\"false\" =\"speciesReference0000\"/>\n"
                           "        </listOfProducts>\n"
                           "        <kineticLaw =\"kineticLaw0001\">\n"
                           "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\" =\"math0000\">\n"
                           "            <apply =\"apply0000\">\n"
                           "              <times =\"times0000\"/>\n"
                           "              <ci =\"ci0001\"> x </ci>\n"
                           "              <ci =\"ci0002\"> kx2y </ci>\n"
                           "            </apply>\n"
                           "          </math>\n"
                           "          <listOfLocalParameters =\"listOfLocalParameters0001\">\n"
                           "            <localParameter id=\"kx2y\" value=\"1\" =\"localParameter0000\"/>\n"
                           "            <localParameter id=\"ky2z\" value=\"1\" =\"localParameter0001\"/>\n"
                           "          </listOfLocalParameters>\n"
                           "        </kineticLaw>\n"
                           "      </reaction>\n"
                           "      <reaction id=\"y2z\" reversible=\"false\" =\"reaction0001\">\n"
                           "        <listOfProducts =\"listOfProducts0001\">\n"
                           "          <speciesReference species=\"Z\" constant=\"false\" =\"speciesReference0001\"/>\n"
                           "        </listOfProducts>\n"
                           "        <kineticLaw =\"kineticLaw0002\">\n"
                           "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\" =\"math0001\">\n"
                           "            <apply =\"apply0001\">\n"
                           "              <times =\"times0001\"/>\n"
                           "              <ci =\"ci0003\"> y </ci>\n"
                           "              <ci =\"ci0004\"> ky2z </ci>\n"
                           "            </apply>\n"
                           "          </math>\n"
                           "        </kineticLaw>\n"
                           "      </reaction>\n"
                           "    </listOfReactions>\n"
                           "  </model>\n"
                           "</sbml>\n";
    ASSERT_STREQ(expected.c_str(), sbml.c_str());
}


TEST_F(OmexMetaXMLTests, TestMetaIdsSBML) {
    std::string sbml = SBMLFactory::getSBML(SBML_NOT_ANNOTATED);
    MetaID metaId("#OmexMetaId", 0, 4);
    OmexMetaSBML assistant(sbml, "#OmexMetaId", 4, true);
    auto sbml_with_metaids = assistant.addMetaIds();
    sbml = sbml_with_metaids.first;
    std::cout << sbml << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                           "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version2/core\" level=\"3\" version=\"2\">\n"
                           "  <model id=\"TestModelNotAnnotated\" metaid=\"model0000\">\n"
                           "    <listOfUnitDefinitions>\n"
                           "      <unitDefinition id=\"molar\">\n"
                           "        <listOfUnits>\n"
                           "          <unit kind=\"mole\" exponent=\"1\" scale=\"1\" multiplier=\"1\" metaid=\"unit0000\"/>\n"
                           "          <unit kind=\"litre\" exponent=\"-1\" scale=\"1\" multiplier=\"1\" metaid=\"unit0001\"/>\n"
                           "        </listOfUnits>\n"
                           "      </unitDefinition>\n"
                           "    </listOfUnitDefinitions>\n"
                           "    <listOfCompartments>\n"
                           "      <compartment metaid=\"#cytosol\" id=\"cytosol\" size=\"1\" constant=\"true\"/>\n"
                           "    </listOfCompartments>\n"
                           "    <listOfSpecies>\n"
                           "      <species metaid=\"#Meta00001\" id=\"X\" compartment=\"cytosol\" initialConcentration=\"10\" substanceUnits=\"molar\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                           "      <species id=\"Y\" compartment=\"cytosol\" initialConcentration=\"20\" substanceUnits=\"molar\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\" metaid=\"species0000\"/>\n"
                           "      <species id=\"Y\" compartment=\"cytosol\" initialConcentration=\"15\" substanceUnits=\"molar\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\" metaid=\"species0001\"/>\n"
                           "    </listOfSpecies>\n"
                           "    <listOfReactions>\n"
                           "      <reaction id=\"X2Y\" reversible=\"false\" metaid=\"reaction0000\">\n"
                           "        <listOfProducts>\n"
                           "          <speciesReference species=\"Y\" constant=\"false\"/>\n"
                           "        </listOfProducts>\n"
                           "        <kineticLaw metaid=\"kineticLaw0000\">\n"
                           "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                           "            <apply>\n"
                           "              <times/>\n"
                           "              <ci> x </ci>\n"
                           "              <ci> kx2y </ci>\n"
                           "            </apply>\n"
                           "          </math>\n"
                           "          <listOfLocalParameters>\n"
                           "            <localParameter id=\"kx2y\" value=\"1\"/>\n"
                           "            <localParameter id=\"ky2z\" value=\"1\"/>\n"
                           "          </listOfLocalParameters>\n"
                           "        </kineticLaw>\n"
                           "      </reaction>\n"
                           "      <reaction id=\"y2z\" reversible=\"false\" metaid=\"reaction0001\">\n"
                           "        <listOfProducts>\n"
                           "          <speciesReference species=\"Z\" constant=\"false\"/>\n"
                           "        </listOfProducts>\n"
                           "        <kineticLaw metaid=\"kineticLaw0001\">\n"
                           "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                           "            <apply>\n"
                           "              <times/>\n"
                           "              <ci> y </ci>\n"
                           "              <ci> ky2z </ci>\n"
                           "            </apply>\n"
                           "          </math>\n"
                           "        </kineticLaw>\n"
                           "      </reaction>\n"
                           "    </listOfReactions>\n"
                           "  </model>\n"
                           "</sbml>\n";
    ASSERT_STREQ(expected.c_str(), sbml.c_str());
}

/**
 * Test metaid generation in sbml model. In this test, the generate new metaids flag is false
 * so it should collect existing metaids but not generate new ones.
 */
TEST_F(OmexMetaXMLTests, TestMetaIdsGenerateNewMetaidsFlagFalseSBML) {
    std::string sbml = SBMLFactory::getSBML(SBML_ANNOTATED);
    OmexMetaSBML sbmlAssistant(sbml, "#OmexMetaId", 4, false);
    std::cout << sbmlAssistant.metaIdTagName() << std::endl;
    std::cout << sbmlAssistant.metaIdNamespace() << std::endl;
    auto sbml_and_meta_ids = sbmlAssistant.addMetaIds();
    std::vector<std::string> expected = {"#cytosol", "#glucose"};
    ASSERT_EQ(expected, sbml_and_meta_ids.second);
}

/**
 * Test metaid generation in sbml model. In this test, the generate new metaids flag is true
 * so it should collect existing metaids as well as new ones.
 */
TEST_F(OmexMetaXMLTests, TestMetaIdsGenerateNewMetaidsFlagFalseMetaid) {
    std::string sbml = SBMLFactory::getSBML(SBML_ANNOTATED);
    OmexMetaSBML sbmlAssistant(sbml, "#OmexMetaId", 4, true);
    auto sbml_and_meta_ids = sbmlAssistant.addMetaIds();
    std::cout << sbml_and_meta_ids.second.size();
    std::vector<std::string> metaids = sbml_and_meta_ids.second;
    for (auto &it : metaids) {
        std::cout << it << std::endl;
    }
    std::vector<std::string> expected = {"model0000", "unit0000", "unit0001", "#cytosol",
                                         "#glucose", "reaction0000", "kineticLaw0000"};
    ASSERT_EQ(expected, metaids);
}

/**
 * Test metaid generation in cellml model. In this test, the generate new metaids flag is false
 * so it should collect existing metaids but not generate new ones.
 */
TEST_F(OmexMetaXMLTests, TestMetaIdsGenerateNewMetaidsFlagFalseCellML) {
    std::string cellml = CellMLFactory::getCellML(CELLML_TOY);
    OmexMetaCellML cellMlAssistant(cellml, "#OmexMetaId", 4, false);
    auto cellml_metaids = cellMlAssistant.addMetaIds();
    std::vector<std::string> expected = {"annExamples", "main.Volume", "main.MembraneVoltage", "main.ReactionRate"};
    ASSERT_EQ(expected, cellml_metaids.second);
}

/**
 * Test metaid generation in sbml model. In this test, the generate new metaids flag is true
 * so it should collect existing metaids as well as new ones.
 */
TEST_F(OmexMetaXMLTests, TestMetaIdsGenerateNewMetaidsFlagFalseMetaidCellML) {
    std::string cellml = CellMLFactory::getCellML(CELLML_TOY_NO_METAIDS);
    OmexMetaCellML cellMlAssistant(cellml, "#OmexMetaId", 4, true);
    auto cellml_and_meta_ids = cellMlAssistant.addMetaIds();
    std::cout << cellml_and_meta_ids.second.size();
    std::vector<std::string> metaids = cellml_and_meta_ids.second;
    for (auto &it : metaids) {
        std::cout << it << std::endl;
    }
    std::vector<std::string> expected = {"annExamples", "component0000", "variable0000", "variable0001", "variable0002"};
    ASSERT_EQ(expected, metaids);
}

TEST_F(OmexMetaXMLTests, ToStringTest) {
    std::string sbml = SBMLFactory::getSBML(SBML_NOT_ANNOTATED);
    OmexMetaXml xml(sbml, "OmexMetaId", 4, false);
    std::string actual = xml.toString();
    ASSERT_STREQ(sbml.c_str(), actual.c_str());

}

TEST_F(OmexMetaXMLTests, RemoveElement) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                           "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version2/core\" level=\"3\" version=\"2\">\n"
                           "  <model id=\"beta_cell_model\">\n"
                           "    <listOfUnitDefinitions>\n"
                           "      <unitDefinition id=\"molar\">\n"
                           "        \n"
                           "      </unitDefinition>\n"
                           "    </listOfUnitDefinitions>\n"
                           "    <listOfCompartments>\n"
                           "      <compartment metaid=\"#cytosol\" id=\"cytosol\" size=\"1\" constant=\"true\"/>\n"
                           "    </listOfCompartments>\n"
                           "    <listOfSpecies>\n"
                           "      <species metaid=\"#glucose\" id=\"glucose\" compartment=\"cytosol\" initialConcentration=\"0\" substanceUnits=\"molar\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                           "    </listOfSpecies>\n"
                           "    <listOfReactions>\n"
                           "      <reaction id=\"glucose_import\" reversible=\"false\">\n"
                           "        <listOfProducts>\n"
                           "          <speciesReference species=\"glucose\" constant=\"false\"/>\n"
                           "        </listOfProducts>\n"
                           "        <kineticLaw>\n"
                           "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                           "            <ci> glucose_import_rate </ci>\n"
                           "          </math>\n"
                           "          <listOfLocalParameters>\n"
                           "            <localParameter id=\"glucose_import_rate\" value=\"1\"/>\n"
                           "          </listOfLocalParameters>\n"
                           "        </kineticLaw>\n"
                           "      </reaction>\n"
                           "    </listOfReactions>\n"
                           "  </model>\n"
                           "</sbml>\n";
    std::string sbml = SBMLFactory::getSBML(SBML_ANNOTATED);
    OmexMetaXml xml(sbml, "OmexMetaId", 4, false);
    std::string actual = xml.removeElement("listOfUnits");
    ASSERT_STREQ(actual.c_str(), expected.c_str());
}

TEST_F(OmexMetaXMLTests, RemoveElementCalledAnnotation) {
    std::string expected = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                           "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">\n"
                           "    <model metaid=\"ToyModel\" id=\"ToyModel\">\n"
                           "        <listOfCompartments>\n"
                           "            <compartment id=\"cytosol\" metaid=\"comp1\" spatialDimensions=\"3\" size=\"1\" constant=\"true\"/>\n"
                           "            <compartment id=\"extraCell\" metaid=\"comp2\" spatialDimensions=\"3\" size=\"10\" constant=\"true\"/>\n"
                           "        </listOfCompartments>\n"
                           "        <listOfSpecies>\n"
                           "            <species id=\"A\" metaid=\"sp_1\" compartment=\"cytosol\" initialConcentration=\"10\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\">\n"
                           "                \n"
                           "            </species>\n"
                           "            <species id=\"B\" metaid=\"sp_2\" compartment=\"cytosol\" initialConcentration=\"0\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                           "            <species id=\"Ca\" metaid=\"sp_3\" compartment=\"cytosol\" initialConcentration=\"2\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                           "            <species id=\"PlasmaCa\" metaid=\"sp_4\" compartment=\"extraCell\" initialConcentration=\"3\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                           "            <species id=\"Enzyme\" metaid=\"sp_5\" compartment=\"cytosol\" initialConcentration=\"2\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                           "        </listOfSpecies>\n"
                           "        <listOfParameters>\n"
                           "            <parameter id=\"k1\" value=\"0.1\" constant=\"true\"/>\n"
                           "            <parameter id=\"k2\" value=\"0.1\" constant=\"true\"/>\n"
                           "        </listOfParameters>\n"
                           "        <listOfReactions>\n"
                           "            <reaction id=\"r1\" metaid=\"react1\" reversible=\"false\" fast=\"false\">\n"
                           "                <listOfReactants>\n"
                           "                    <speciesReference species=\"B\" stoichiometry=\"1\" constant=\"true\"/>\n"
                           "                </listOfReactants>\n"
                           "                <listOfProducts>\n"
                           "                    <speciesReference species=\"A\" stoichiometry=\"2\" constant=\"true\"/>\n"
                           "                </listOfProducts>\n"
                           "                <kineticLaw>\n"
                           "                    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                           "                        <apply>\n"
                           "                            <times/>\n"
                           "                            <ci>k2</ci>\n"
                           "                            <ci>B</ci>\n"
                           "                        </apply>\n"
                           "                    </math>\n"
                           "                </kineticLaw>\n"
                           "            </reaction>\n"
                           "            <reaction id=\"r2\" metaid=\"react2\" reversible=\"false\" fast=\"false\">\n"
                           "                <listOfReactants>\n"
                           "                    <speciesReference species=\"Ca\" stoichiometry=\"1\" constant=\"true\"/>\n"
                           "                    <speciesReference species=\"A\" stoichiometry=\"1\" constant=\"true\"/>\n"
                           "                </listOfReactants>\n"
                           "                <listOfProducts>\n"
                           "                    <speciesReference species=\"PlasmaCa\" stoichiometry=\"1\" constant=\"true\"/>\n"
                           "                </listOfProducts>\n"
                           "                <listOfModifiers>\n"
                           "                    <modifierSpeciesReference species=\"Enzyme\"/>\n"
                           "                </listOfModifiers>\n"
                           "                <kineticLaw>\n"
                           "                    <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                           "                        <apply>\n"
                           "                            <times/>\n"
                           "                            <ci>k2</ci>\n"
                           "                            <ci>Ca</ci>\n"
                           "                        </apply>\n"
                           "                    </math>\n"
                           "                </kineticLaw>\n"
                           "            </reaction>\n"
                           "        </listOfReactions>\n"
                           "    </model>\n"
                           "</sbml>\n";
    std::string sbml = SBMLFactory::getSBML(SBML_Semantic_Extraction_Model);
    OmexMetaXml xml(sbml, "OmexMetaId", 4, false);
    std::string actual = xml.removeElement("annotation");
    ASSERT_STREQ(actual.c_str(), expected.c_str());
}



















