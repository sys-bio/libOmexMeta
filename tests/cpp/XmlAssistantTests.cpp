//
// Created by Ciaran on 4/14/2020.
//

#include "gtest/gtest.h"
#include "SBMLFactory.h"
#include "semsim/SemsimXmlAssistant.h"
#include <thread>
#include "semsim/HERE.h"

using namespace semsim;

class SemsimXmlAssistantTests : public ::testing::Test{
    
};

TEST_F(SemsimXmlAssistantTests, TestValidElements) {
    MetaID metaId("SemsimMetaid", 0, 4);
    std::string model_string = SBMLFactory::getSBMLString(SBML_ANNOTATED);
    std::cout << model_string << std::endl;
    SemsimXmlAssistant SemsimXmlAssistant(model_string, "ID", 4);
    const std::vector<std::string> &actual = SemsimXmlAssistant.getValidElements();
    std::vector<std::string> expected = {"Any"};
    ASSERT_EQ(expected, actual);
}

TEST_F(SemsimXmlAssistantTests, TestMetaIdsAll) {
    HERE();
    std::string sbml = SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED);
    HERE();
    SemsimXmlAssistant SemsimXmlAssistant(sbml, "SemsimMetaid", 4);
    HERE();
    auto sbml_and_meta_ids = SemsimXmlAssistant.addMetaIds();
    HERE();
    sbml = sbml_and_meta_ids.first;
    HERE();
    std::cout << sbml << std::endl;
    HERE();
    std::string expected = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                           "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version2/core\" level=\"3\" version=\"2\" metaid=\"SemsimMetaid0000\">\n"
                           "  <model id=\"TestModelNotAnnotated\" metaid=\"SemsimMetaid0001\">\n"
                           "    <listOfUnitDefinitions metaid=\"SemsimMetaid0002\">\n"
                           "      <unitDefinition id=\"molar\" metaid=\"SemsimMetaid0003\">\n"
                           "        <listOfUnits metaid=\"SemsimMetaid0004\">\n"
                           "          <unit kind=\"mole\" exponent=\"1\" scale=\"1\" multiplier=\"1\" metaid=\"SemsimMetaid0005\"/>\n"
                           "          <unit kind=\"litre\" exponent=\"-1\" scale=\"1\" multiplier=\"1\" metaid=\"SemsimMetaid0006\"/>\n"
                           "        </listOfUnits>\n"
                           "      </unitDefinition>\n"
                           "    </listOfUnitDefinitions>\n"
                           "    <listOfCompartments metaid=\"SemsimMetaid0007\">\n"
                           "      <compartment metaid=\"cytosol\" id=\"cytosol\" size=\"1\" constant=\"true\"/>\n"
                           "    </listOfCompartments>\n"
                           "    <listOfSpecies metaid=\"SemsimMetaid0008\">\n"
                           "      <species metaid=\"Meta00001\" id=\"X\" compartment=\"cytosol\" initialConcentration=\"10\" substanceUnits=\"molar\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                           "      <species id=\"Y\" compartment=\"cytosol\" initialConcentration=\"20\" substanceUnits=\"molar\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\" metaid=\"SemsimMetaid0009\"/>\n"
                           "      <species id=\"Y\" compartment=\"cytosol\" initialConcentration=\"15\" substanceUnits=\"molar\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\" metaid=\"SemsimMetaid0010\"/>\n"
                           "    </listOfSpecies>\n"
                           "    <listOfReactions metaid=\"SemsimMetaid0011\">\n"
                           "      <reaction id=\"X2Y\" reversible=\"false\" metaid=\"SemsimMetaid0012\">\n"
                           "        <listOfProducts metaid=\"SemsimMetaid0013\">\n"
                           "          <speciesReference species=\"Y\" constant=\"false\" metaid=\"SemsimMetaid0014\"/>\n"
                           "        </listOfProducts>\n"
                           "        <kineticLaw metaid=\"SemsimMetaid0015\">\n"
                           "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\" metaid=\"SemsimMetaid0016\">\n"
                           "            <apply metaid=\"SemsimMetaid0017\">\n"
                           "              <times metaid=\"SemsimMetaid0018\"/>\n"
                           "              <ci metaid=\"SemsimMetaid0019\"> x </ci>\n"
                           "              <ci metaid=\"SemsimMetaid0020\"> kx2y </ci>\n"
                           "            </apply>\n"
                           "          </math>\n"
                           "          <listOfLocalParameters metaid=\"SemsimMetaid0021\">\n"
                           "            <localParameter id=\"kx2y\" value=\"1\" metaid=\"SemsimMetaid0022\"/>\n"
                           "            <localParameter id=\"ky2z\" value=\"1\" metaid=\"SemsimMetaid0023\"/>\n"
                           "          </listOfLocalParameters>\n"
                           "        </kineticLaw>\n"
                           "      </reaction>\n"
                           "      <reaction id=\"y2z\" reversible=\"false\" metaid=\"SemsimMetaid0024\">\n"
                           "        <listOfProducts metaid=\"SemsimMetaid0025\">\n"
                           "          <speciesReference species=\"Z\" constant=\"false\" metaid=\"SemsimMetaid0026\"/>\n"
                           "        </listOfProducts>\n"
                           "        <kineticLaw metaid=\"SemsimMetaid0027\">\n"
                           "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\" metaid=\"SemsimMetaid0028\">\n"
                           "            <apply metaid=\"SemsimMetaid0029\">\n"
                           "              <times metaid=\"SemsimMetaid0030\"/>\n"
                           "              <ci metaid=\"SemsimMetaid0031\"> y </ci>\n"
                           "              <ci metaid=\"SemsimMetaid0032\"> ky2z </ci>\n"
                           "            </apply>\n"
                           "          </math>\n"
                           "        </kineticLaw>\n"
                           "      </reaction>\n"
                           "    </listOfReactions>\n"
                           "  </model>\n"
                           "</sbml>\n";
    ASSERT_STREQ(expected.c_str(), sbml.c_str());
    HERE();
}

TEST_F(SemsimXmlAssistantTests, TestValidElementsSBML) {
    MetaID metaId("SemsimMetaid", 0, 4);
    std::string sbml = SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED);
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

TEST_F(SemsimXmlAssistantTests, TestMetaIdsSBML) {
    HERE();
    std::string sbml = SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED);
    HERE();
    MetaID metaId("SemsimMetaid", 0, 4);
    HERE();
    SBMLAssistant assistant(sbml, "SemsimMetaid", 4);
    HERE();
    auto sbml_with_metaids = assistant.addMetaIds();
    HERE();
    sbml = sbml_with_metaids.first;
    HERE();
    std::cout << sbml <<  std::endl;
    std::string expected = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                           "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version2/core\" level=\"3\" version=\"2\" metaid=\"SemsimMetaid0000\">\n"
                           "  <model id=\"TestModelNotAnnotated\" metaid=\"SemsimMetaid0001\">\n"
                           "    <listOfUnitDefinitions metaid=\"SemsimMetaid0002\">\n"
                           "      <unitDefinition id=\"molar\" metaid=\"SemsimMetaid0003\">\n"
                           "        <listOfUnits metaid=\"SemsimMetaid0004\">\n"
                           "          <unit kind=\"mole\" exponent=\"1\" scale=\"1\" multiplier=\"1\" metaid=\"SemsimMetaid0005\"/>\n"
                           "          <unit kind=\"litre\" exponent=\"-1\" scale=\"1\" multiplier=\"1\" metaid=\"SemsimMetaid0006\"/>\n"
                           "        </listOfUnits>\n"
                           "      </unitDefinition>\n"
                           "    </listOfUnitDefinitions>\n"
                           "    <listOfCompartments metaid=\"SemsimMetaid0007\">\n"
                           "      <compartment metaid=\"cytosol\" id=\"cytosol\" size=\"1\" constant=\"true\"/>\n"
                           "    </listOfCompartments>\n"
                           "    <listOfSpecies metaid=\"SemsimMetaid0008\">\n"
                           "      <species metaid=\"Meta00001\" id=\"X\" compartment=\"cytosol\" initialConcentration=\"10\" substanceUnits=\"molar\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                           "      <species id=\"Y\" compartment=\"cytosol\" initialConcentration=\"20\" substanceUnits=\"molar\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\" metaid=\"SemsimMetaid0009\"/>\n"
                           "      <species id=\"Y\" compartment=\"cytosol\" initialConcentration=\"15\" substanceUnits=\"molar\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\" metaid=\"SemsimMetaid0010\"/>\n"
                           "    </listOfSpecies>\n"
                           "    <listOfReactions metaid=\"SemsimMetaid0011\">\n"
                           "      <reaction id=\"X2Y\" reversible=\"false\" metaid=\"SemsimMetaid0012\">\n"
                           "        <listOfProducts metaid=\"SemsimMetaid0013\">\n"
                           "          <speciesReference species=\"Y\" constant=\"false\" metaid=\"SemsimMetaid0014\"/>\n"
                           "        </listOfProducts>\n"
                           "        <kineticLaw metaid=\"SemsimMetaid0015\">\n"
                           "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\" metaid=\"SemsimMetaid0016\">\n"
                           "            <apply metaid=\"SemsimMetaid0017\">\n"
                           "              <times metaid=\"SemsimMetaid0018\"/>\n"
                           "              <ci metaid=\"SemsimMetaid0019\"> x </ci>\n"
                           "              <ci metaid=\"SemsimMetaid0020\"> kx2y </ci>\n"
                           "            </apply>\n"
                           "          </math>\n"
                           "          <listOfLocalParameters metaid=\"SemsimMetaid0021\">\n"
                           "            <localParameter id=\"kx2y\" value=\"1\" metaid=\"SemsimMetaid0022\"/>\n"
                           "            <localParameter id=\"ky2z\" value=\"1\" metaid=\"SemsimMetaid0023\"/>\n"
                           "          </listOfLocalParameters>\n"
                           "        </kineticLaw>\n"
                           "      </reaction>\n"
                           "      <reaction id=\"y2z\" reversible=\"false\" metaid=\"SemsimMetaid0024\">\n"
                           "        <listOfProducts metaid=\"SemsimMetaid0025\">\n"
                           "          <speciesReference species=\"Z\" constant=\"false\" metaid=\"SemsimMetaid0026\"/>\n"
                           "        </listOfProducts>\n"
                           "        <kineticLaw metaid=\"SemsimMetaid0027\">\n"
                           "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\" metaid=\"SemsimMetaid0028\">\n"
                           "            <apply metaid=\"SemsimMetaid0029\">\n"
                           "              <times metaid=\"SemsimMetaid0030\"/>\n"
                           "              <ci metaid=\"SemsimMetaid0031\"> y </ci>\n"
                           "              <ci metaid=\"SemsimMetaid0032\"> ky2z </ci>\n"
                           "            </apply>\n"
                           "          </math>\n"
                           "        </kineticLaw>\n"
                           "      </reaction>\n"
                           "    </listOfReactions>\n"
                           "  </model>\n"
                           "</sbml>\n";
    ASSERT_STREQ(expected.c_str(), sbml.c_str());
}


TEST_F(SemsimXmlAssistantTests, TestXmlAssistantFactory) {
    std::string sbml = SBMLFactory::getSBMLString(SBML_NOT_ANNOTATED);
    auto x = SemsimXmlAssistantFactory::generate(sbml, SEMSIM_TYPE_SBML);

}

















