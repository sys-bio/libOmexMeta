//
// Created by Ciaran on 4/14/2020.
//

#include "gtest/gtest.h"
#include "SBMLFactory.h"
#include "omexmeta/OmexMetaXmlAssistant.h"
#include <thread>

using namespace omexmeta;

class SemsimXmlAssistantTests : public ::testing::Test {

};

TEST_F(SemsimXmlAssistantTests, TestValidElements) {
    MetaID metaId("#OmexMetaId", 0, 4);
    std::string model_string = SBMLFactory::getSBML(SBML_ANNOTATED);
    std::cout << model_string << std::endl;
    OmexMetaXmlAssistant SemsimXmlAssistant(model_string, "ID", 4);
    const std::vector<std::string> &actual = SemsimXmlAssistant.getValidElements();
    std::vector<std::string> expected = {"Any"};
    ASSERT_EQ(expected, actual);
}


TEST_F(SemsimXmlAssistantTests, TestValidElementsSBML) {
    MetaID metaId("#OmexMetaId", 0, 4);
    std::string sbml = SBMLFactory::getSBML(SBML_NOT_ANNOTATED);
    SBMLAssistant assistant(sbml, "ID", 4);
    const std::vector<std::string> &actual = assistant.getValidElements();
    std::vector<std::string> expected = {
            "model",
            "unit",
            "compartment",
            "species",
            "reaction",
            "kineticLaw",
            "localParameter",
    };
    ASSERT_EQ(expected, actual);
}

//TEST_F(SemsimXmlAssistantTests, TestCellMlValidElements) {
//    MetaID metaId("#OmexMetaId", 0, 4);
//    std::string model_string = SBMLFactory::getSBML(SBML_ANNOTATED);
//    std::cout << model_string << std::endl;
//    CellMLAssistant assistant(model_string, "ID", 4);
//    const std::vector<std::string> &actual = assistant.getValidElements();
//    std::vector<std::string> expected = {"model", "unit", "compartment",
//                                         "species", "reaction", "kineticLaw",
//                                         "localParameter"};
//    ASSERT_EQ(expected, actual);
//}

TEST_F(SemsimXmlAssistantTests, TestMetaIdsAll) {
    std::string sbml = SBMLFactory::getSBML(SBML_NOT_ANNOTATED);
    OmexMetaXmlAssistant SemsimXmlAssistant(sbml, "#OmexMetaId", 4, true);
    auto sbml_and_meta_ids = SemsimXmlAssistant.addMetaIds();
    sbml = sbml_and_meta_ids.first;
    std::cout << sbml << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                           "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version2/core\" level=\"3\" version=\"2\" metaid=\"#OmexMetaId0000\">\n"
                           "  <model id=\"TestModelNotAnnotated\" metaid=\"#OmexMetaId0001\">\n"
                           "    <listOfUnitDefinitions metaid=\"#OmexMetaId0002\">\n"
                           "      <unitDefinition id=\"molar\" metaid=\"#OmexMetaId0003\">\n"
                           "        <listOfUnits metaid=\"#OmexMetaId0004\">\n"
                           "          <unit kind=\"mole\" exponent=\"1\" scale=\"1\" multiplier=\"1\" metaid=\"#OmexMetaId0005\"/>\n"
                           "          <unit kind=\"litre\" exponent=\"-1\" scale=\"1\" multiplier=\"1\" metaid=\"#OmexMetaId0006\"/>\n"
                           "        </listOfUnits>\n"
                           "      </unitDefinition>\n"
                           "    </listOfUnitDefinitions>\n"
                           "    <listOfCompartments metaid=\"#OmexMetaId0007\">\n"
                           "      <compartment metaid=\"#cytosol\" id=\"cytosol\" size=\"1\" constant=\"true\"/>\n"
                           "    </listOfCompartments>\n"
                           "    <listOfSpecies metaid=\"#OmexMetaId0008\">\n"
                           "      <species metaid=\"#Meta00001\" id=\"X\" compartment=\"cytosol\" initialConcentration=\"10\" substanceUnits=\"molar\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                           "      <species id=\"Y\" compartment=\"cytosol\" initialConcentration=\"20\" substanceUnits=\"molar\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\" metaid=\"#OmexMetaId0009\"/>\n"
                           "      <species id=\"Y\" compartment=\"cytosol\" initialConcentration=\"15\" substanceUnits=\"molar\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\" metaid=\"#OmexMetaId0010\"/>\n"
                           "    </listOfSpecies>\n"
                           "    <listOfReactions metaid=\"#OmexMetaId0011\">\n"
                           "      <reaction id=\"X2Y\" reversible=\"false\" metaid=\"#OmexMetaId0012\">\n"
                           "        <listOfProducts metaid=\"#OmexMetaId0013\">\n"
                           "          <speciesReference species=\"Y\" constant=\"false\" metaid=\"#OmexMetaId0014\"/>\n"
                           "        </listOfProducts>\n"
                           "        <kineticLaw metaid=\"#OmexMetaId0015\">\n"
                           "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\" metaid=\"#OmexMetaId0016\">\n"
                           "            <apply metaid=\"#OmexMetaId0017\">\n"
                           "              <times metaid=\"#OmexMetaId0018\"/>\n"
                           "              <ci metaid=\"#OmexMetaId0019\"> x </ci>\n"
                           "              <ci metaid=\"#OmexMetaId0020\"> kx2y </ci>\n"
                           "            </apply>\n"
                           "          </math>\n"
                           "          <listOfLocalParameters metaid=\"#OmexMetaId0021\">\n"
                           "            <localParameter id=\"kx2y\" value=\"1\" metaid=\"#OmexMetaId0022\"/>\n"
                           "            <localParameter id=\"ky2z\" value=\"1\" metaid=\"#OmexMetaId0023\"/>\n"
                           "          </listOfLocalParameters>\n"
                           "        </kineticLaw>\n"
                           "      </reaction>\n"
                           "      <reaction id=\"y2z\" reversible=\"false\" metaid=\"#OmexMetaId0024\">\n"
                           "        <listOfProducts metaid=\"#OmexMetaId0025\">\n"
                           "          <speciesReference species=\"Z\" constant=\"false\" metaid=\"#OmexMetaId0026\"/>\n"
                           "        </listOfProducts>\n"
                           "        <kineticLaw metaid=\"#OmexMetaId0027\">\n"
                           "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\" metaid=\"#OmexMetaId0028\">\n"
                           "            <apply metaid=\"#OmexMetaId0029\">\n"
                           "              <times metaid=\"#OmexMetaId0030\"/>\n"
                           "              <ci metaid=\"#OmexMetaId0031\"> y </ci>\n"
                           "              <ci metaid=\"#OmexMetaId0032\"> ky2z </ci>\n"
                           "            </apply>\n"
                           "          </math>\n"
                           "        </kineticLaw>\n"
                           "      </reaction>\n"
                           "    </listOfReactions>\n"
                           "  </model>\n"
                           "</sbml>\n";
    ASSERT_STREQ(expected.c_str(), sbml.c_str());
}


TEST_F(SemsimXmlAssistantTests, TestMetaIdsSBML) {
    std::string sbml = SBMLFactory::getSBML(SBML_NOT_ANNOTATED);
    MetaID metaId("#OmexMetaId", 0, 4);
    SBMLAssistant assistant(sbml, "#OmexMetaId", 4, true);
    auto sbml_with_metaids = assistant.addMetaIds();
    sbml = sbml_with_metaids.first;
    std::cout << sbml << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                           "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version2/core\" level=\"3\" version=\"2\">\n"
                           "  <model id=\"TestModelNotAnnotated\" metaid=\"#OmexMetaId0000\">\n"
                           "    <listOfUnitDefinitions>\n"
                           "      <unitDefinition id=\"molar\">\n"
                           "        <listOfUnits>\n"
                           "          <unit kind=\"mole\" exponent=\"1\" scale=\"1\" multiplier=\"1\" metaid=\"#OmexMetaId0001\"/>\n"
                           "          <unit kind=\"litre\" exponent=\"-1\" scale=\"1\" multiplier=\"1\" metaid=\"#OmexMetaId0002\"/>\n"
                           "        </listOfUnits>\n"
                           "      </unitDefinition>\n"
                           "    </listOfUnitDefinitions>\n"
                           "    <listOfCompartments>\n"
                           "      <compartment metaid=\"#cytosol\" id=\"cytosol\" size=\"1\" constant=\"true\"/>\n"
                           "    </listOfCompartments>\n"
                           "    <listOfSpecies>\n"
                           "      <species metaid=\"#Meta00001\" id=\"X\" compartment=\"cytosol\" initialConcentration=\"10\" substanceUnits=\"molar\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                           "      <species id=\"Y\" compartment=\"cytosol\" initialConcentration=\"20\" substanceUnits=\"molar\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\" metaid=\"#OmexMetaId0003\"/>\n"
                           "      <species id=\"Y\" compartment=\"cytosol\" initialConcentration=\"15\" substanceUnits=\"molar\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\" metaid=\"#OmexMetaId0004\"/>\n"
                           "    </listOfSpecies>\n"
                           "    <listOfReactions>\n"
                           "      <reaction id=\"X2Y\" reversible=\"false\" metaid=\"#OmexMetaId0005\">\n"
                           "        <listOfProducts>\n"
                           "          <speciesReference species=\"Y\" constant=\"false\"/>\n"
                           "        </listOfProducts>\n"
                           "        <kineticLaw metaid=\"#OmexMetaId0006\">\n"
                           "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                           "            <apply>\n"
                           "              <times/>\n"
                           "              <ci> x </ci>\n"
                           "              <ci> kx2y </ci>\n"
                           "            </apply>\n"
                           "          </math>\n"
                           "          <listOfLocalParameters>\n"
                           "            <localParameter id=\"kx2y\" value=\"1\" metaid=\"#OmexMetaId0007\"/>\n"
                           "            <localParameter id=\"ky2z\" value=\"1\" metaid=\"#OmexMetaId0008\"/>\n"
                           "          </listOfLocalParameters>\n"
                           "        </kineticLaw>\n"
                           "      </reaction>\n"
                           "      <reaction id=\"y2z\" reversible=\"false\" metaid=\"#OmexMetaId0009\">\n"
                           "        <listOfProducts>\n"
                           "          <speciesReference species=\"Z\" constant=\"false\"/>\n"
                           "        </listOfProducts>\n"
                           "        <kineticLaw metaid=\"#OmexMetaId0010\">\n"
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

TEST_F(SemsimXmlAssistantTests, TestMetaIdsGenerateNewMetaidsFlagFalseSBML) {
    std::string sbml = SBMLFactory::getSBML(SBML_ANNOTATED);
    OmexMetaXmlAssistant SemsimXmlAssistant(sbml, "#OmexMetaId", 4, false);
    auto sbml_and_meta_ids = SemsimXmlAssistant.addMetaIds();
    sbml = sbml_and_meta_ids.first;
    std::cout << sbml << std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                           "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version2/core\" level=\"3\" version=\"2\">\n"
                           "  <model id=\"beta_cell_model\">\n"
                           "    <listOfUnitDefinitions>\n"
                           "      <unitDefinition id=\"molar\">\n"
                           "        <listOfUnits>\n"
                           "          <unit kind=\"mole\" exponent=\"1\" scale=\"1\" multiplier=\"1\"/>\n"
                           "          <unit kind=\"litre\" exponent=\"-1\" scale=\"1\" multiplier=\"1\"/>\n"
                           "        </listOfUnits>\n"
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
    ASSERT_STREQ(expected.c_str(), sbml.c_str());
}

TEST_F(SemsimXmlAssistantTests, TestMetaIdsGenerateNewMetaidsFlagFalseMetaid) {
    std::string sbml = SBMLFactory::getSBML(SBML_ANNOTATED);
    OmexMetaXmlAssistant SemsimXmlAssistant(sbml, "#OmexMetaId", 4, false);
    auto sbml_and_meta_ids = SemsimXmlAssistant.addMetaIds();
    std::vector<std::string> metaids = sbml_and_meta_ids.second;
    for (auto &it: metaids) {
        std::cout << it << std::endl;
    }
    std::vector<std::string> expected = {"#cytosol", "#glucose"};
    ASSERT_EQ(expected, metaids);
}


TEST_F(SemsimXmlAssistantTests, TestXmlAssistantFactory) {
    std::string sbml = SBMLFactory::getSBML(SBML_NOT_ANNOTATED);
    auto x = OmexMetaXmlAssistantFactory::generate(sbml, OMEXMETA_TYPE_SBML);

}

















