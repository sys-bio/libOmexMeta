//
// Created by Ciaran on 29/08/2020.
//


#include "gtest/gtest.h"
#include "omexmeta/OmexMeta.h"

using namespace omexmeta;


class EditorSBMLExtractTests1 : public ::testing::Test {
public:
    /*
     * ant = """
      model SBMLExtractionTestModel
          r1: A -> B; k1*A*S;
          r2: B -> A; k2*B;
          r3: C -> D; k3*C*B;
          r4: D -> C; k4*D;
          k1 = 0.1;
          k2 = 0.1;
          k3 = 0.1;
          k4 = 0.1;
          A = 100;
          B = 0;
          C = 100;
          D = 0;
          S = 1;
          compartment nucleus = 1;
          compartment cytosol = 1;
          A in nucleus;
          B in nucleus
          C in cytosol
          D in cytosol
      end
      """
     *
     * m = te.loada(ant)
     * sbml = m.getSBML()
     *
     * The sbml was then printed out and metaids were added manually to bits that need them
     *
     */

    std::string sbml_string = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                              "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">\n"
                              "  <model metaid=\"SBMLExtractionTestModel\" id=\"SBMLExtractionTestModel\">\n"
                              "    <listOfCompartments>\n"
                              "      <compartment id=\"nucleus\" metaid=\"Compartment_nucleus\" spatialDimensions=\"3\" size=\"1\" constant=\"true\"/>\n"
                              "      <compartment id=\"cytosol\" metaid=\"Compartment_cytosol\" spatialDimensions=\"3\" size=\"1\" constant=\"true\"/>\n"
                              "    </listOfCompartments>\n"
                              "    <listOfSpecies>\n"
                              "      <species id=\"A\" compartment=\"nucleus\" metaid=\"SpeciesA\" initialConcentration=\"100\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                              "      <species id=\"B\" compartment=\"nucleus\" metaid=\"SpeciesB\" initialConcentration=\"0\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                              "      <species id=\"C\" compartment=\"cytosol\" metaid=\"SpeciesC\" initialConcentration=\"100\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                              "      <species id=\"D\" compartment=\"cytosol\" metaid=\"SpeciesD\" initialConcentration=\"0\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                              "    </listOfSpecies>\n"
                              "    <listOfParameters>\n"
                              "      <parameter id=\"k1\" metaid=\"Parameterk1\"  value=\"0.1\" constant=\"true\"/>\n"
                              "      <parameter id=\"S\"  metaid=\"ParameterS\"  value=\"1\" constant=\"true\"/>\n"
                              "      <parameter id=\"k2\" metaid=\"Parameterk2\"  value=\"0.1\" constant=\"true\"/>\n"
                              "      <parameter id=\"k3\" metaid=\"Parameterk3\"  value=\"0.1\" constant=\"true\"/>\n"
                              "      <parameter id=\"k4\" metaid=\"Parameterk4\"  value=\"0.1\" constant=\"true\"/>\n"
                              "    </listOfParameters>\n"
                              "    <listOfReactions>\n"
                              "      <reaction id=\"r1\" metaid=\"Reaction_r1\" reversible=\"true\" fast=\"false\">\n"
                              "        <listOfReactants>\n"
                              "          <speciesReference species=\"A\" stoichiometry=\"1\" constant=\"true\"/>\n"
                              "        </listOfReactants>\n"
                              "        <listOfProducts>\n"
                              "          <speciesReference species=\"B\" stoichiometry=\"1\" constant=\"true\"/>\n"
                              "        </listOfProducts>\n"
                              "        <kineticLaw>\n"
                              "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                              "            <apply>\n"
                              "              <times/>\n"
                              "              <ci> k1 </ci>\n"
                              "              <ci> A </ci>\n"
                              "              <ci> S </ci>\n"
                              "            </apply>\n"
                              "          </math>\n"
                              "        </kineticLaw>\n"
                              "      </reaction>\n"
                              "      <reaction id=\"r2\" metaid=\"Reaction_r2\" reversible=\"true\" fast=\"false\">\n"
                              "        <listOfReactants>\n"
                              "          <speciesReference species=\"B\" stoichiometry=\"1\" constant=\"true\"/>\n"
                              "        </listOfReactants>\n"
                              "        <listOfProducts>\n"
                              "          <speciesReference species=\"A\" stoichiometry=\"1\" constant=\"true\"/>\n"
                              "        </listOfProducts>\n"
                              "        <kineticLaw>\n"
                              "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                              "            <apply>\n"
                              "              <times/>\n"
                              "              <ci> k2 </ci>\n"
                              "              <ci> B </ci>\n"
                              "            </apply>\n"
                              "          </math>\n"
                              "        </kineticLaw>\n"
                              "      </reaction>\n"
                              "      <reaction id=\"r3\" metaid=\"Reaction_r3\" reversible=\"true\" fast=\"false\">\n"
                              "        <listOfReactants>\n"
                              "          <speciesReference species=\"C\" stoichiometry=\"1\" constant=\"true\"/>\n"
                              "        </listOfReactants>\n"
                              "        <listOfProducts>\n"
                              "          <speciesReference species=\"D\" stoichiometry=\"1\" constant=\"true\"/>\n"
                              "        </listOfProducts>\n"
                              "        <listOfModifiers>\n"
                              "          <modifierSpeciesReference species=\"B\"/>\n"
                              "        </listOfModifiers>\n"
                              "        <kineticLaw>\n"
                              "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                              "            <apply>\n"
                              "              <times/>\n"
                              "              <ci> k3 </ci>\n"
                              "              <ci> C </ci>\n"
                              "              <ci> B </ci>\n"
                              "            </apply>\n"
                              "          </math>\n"
                              "        </kineticLaw>\n"
                              "      </reaction>\n"
                              "      <reaction id=\"r4\" metaid=\"Reaction_r4\" reversible=\"true\" fast=\"false\">\n"
                              "        <listOfReactants>\n"
                              "          <speciesReference species=\"D\" stoichiometry=\"1\" constant=\"true\"/>\n"
                              "        </listOfReactants>\n"
                              "        <listOfProducts>\n"
                              "          <speciesReference species=\"C\" stoichiometry=\"1\" constant=\"true\"/>\n"
                              "        </listOfProducts>\n"
                              "        <kineticLaw>\n"
                              "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                              "            <apply>\n"
                              "              <times/>\n"
                              "              <ci> k4 </ci>\n"
                              "              <ci> D </ci>\n"
                              "            </apply>\n"
                              "          </math>\n"
                              "        </kineticLaw>\n"
                              "      </reaction>\n"
                              "    </listOfReactions>\n"
                              "  </model>\n"
                              "</sbml>\n";

    EditorSBMLExtractTests1(){
    }

    ~ EditorSBMLExtractTests1() = default;
};

TEST_F(EditorSBMLExtractTests1, test){
    RDF rdf;
    Editor editor = rdf.toEditor(sbml_string);
    std::string turtle_string = rdf.toString();

    std::cout << turtle_string << std::endl;

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://www.bhi.washington.edu/semsim#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:MediatorParticipant0000\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#SpeciesB> .\n"
                           "\n"
                           "local:PhysicalProcess0000\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0000 .\n"
                           "\n"
                           "local:PhysicalProcess0001\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0001 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0001 .\n"
                           "\n"
                           "local:PhysicalProcess0002\n"
                           "    semsim:hasMediatorParticipant local:MediatorParticipant0000 ;\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0002 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0002 .\n"
                           "\n"
                           "local:PhysicalProcess0003\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0003 ;\n"
                           "    semsim:hasSourceParticipant local:SourceParticipant0003 .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#SpeciesB> .\n"
                           "\n"
                           "local:SinkParticipant0001\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#SpeciesA> .\n"
                           "\n"
                           "local:SinkParticipant0002\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#SpeciesD> .\n"
                           "\n"
                           "local:SinkParticipant0003\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#SpeciesC> .\n"
                           "\n"
                           "local:SourceParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#SpeciesA> .\n"
                           "\n"
                           "local:SourceParticipant0001\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#SpeciesB> .\n"
                           "\n"
                           "local:SourceParticipant0002\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#SpeciesC> .\n"
                           "\n"
                           "local:SourceParticipant0003\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#SpeciesD> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#Reaction_r1>\n"
                           "    bqbiol:isPropertyOf local:PhysicalProcess0000 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/OPB_00592> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#Reaction_r2>\n"
                           "    bqbiol:isPropertyOf local:PhysicalProcess0001 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/OPB_00592> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#Reaction_r3>\n"
                           "    bqbiol:isPropertyOf local:PhysicalProcess0002 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/OPB_00592> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#Reaction_r4>\n"
                           "    bqbiol:isPropertyOf local:PhysicalProcess0003 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/OPB_00592> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#SpeciesA>\n"
                           "    bqbiol:isPartOf <http://omex-library.org/NewOmex.omex/NewModel.xml#nucleus> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#SpeciesB>\n"
                           "    bqbiol:isPartOf <http://omex-library.org/NewOmex.omex/NewModel.xml#nucleus> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#SpeciesC>\n"
                           "    bqbiol:isPartOf <http://omex-library.org/NewOmex.omex/NewModel.xml#cytosol> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#SpeciesD>\n"
                           "    bqbiol:isPartOf <http://omex-library.org/NewOmex.omex/NewModel.xml#cytosol> .\n"
                           "\n";

    ASSERT_STREQ(expected.c_str(), turtle_string.c_str());
}

class EditorSBMLExtractTests2 : public ::testing::Test {
public:
    /*
     * ant = """
      model SBMLExtractionTestModel
          r1:  -> A ; k1;
          k1 = 0.1;
          A = 0;
          compartment nucleus = 1;
          A in nucleus;
      end
      """
     *
     * m = te.loada(ant)
     * sbml = m.getSBML()
     *
     * The sbml was then printed out and metaids were added manually to bits that need them
     *
     */

    std::string sbml_string = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                              "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">\n"
                              "  <model metaid=\"SBMLExtractionTestModel\" id=\"SBMLExtractionTestModel\">\n"
                              "    <listOfCompartments>\n"
                              "      <compartment id=\"nucleus\" metaid=\"CompartmentNucleus\" spatialDimensions=\"3\" size=\"1\" constant=\"true\"/>\n"
                              "    </listOfCompartments>\n"
                              "    <listOfSpecies>\n"
                              "      <species id=\"A\" compartment=\"nucleus\" metaid=\"SpeciesA\" initialConcentration=\"0\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                              "    </listOfSpecies>\n"
                              "    <listOfParameters>\n"
                              "      <parameter id=\"k1\" metaid=\"Parameter_k1\" value=\"0.1\" constant=\"true\"/>\n"
                              "    </listOfParameters>\n"
                              "    <listOfReactions>\n"
                              "      <reaction id=\"r1\" metaid=\"Reaction_r1\" reversible=\"true\" fast=\"false\">\n"
                              "        <listOfProducts>\n"
                              "          <speciesReference species=\"A\" stoichiometry=\"1\" constant=\"true\"/>\n"
                              "        </listOfProducts>\n"
                              "        <kineticLaw>\n"
                              "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                              "            <ci> k1 </ci>\n"
                              "          </math>\n"
                              "        </kineticLaw>\n"
                              "      </reaction>\n"
                              "    </listOfReactions>\n"
                              "  </model>\n"
                              "</sbml>";

    EditorSBMLExtractTests2(){
    }

    ~ EditorSBMLExtractTests2() = default;
};

TEST_F(EditorSBMLExtractTests2, test){
    RDF rdf;
    Editor editor = rdf.toEditor(sbml_string);
    std::string turtle_string = rdf.toString();

    std::cout << turtle_string << std::endl;

    std::string expected = "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                           "@prefix semsim: <http://www.bhi.washington.edu/semsim#> .\n"
                           "@prefix bqbiol: <http://biomodels.net/biology-qualifiers/> .\n"
                           "@prefix OMEXlib: <http://omex-library.org/> .\n"
                           "@prefix myOMEX: <http://omex-library.org/NewOmex.omex/> .\n"
                           "@prefix local: <http://omex-library.org/NewOmex.omex/NewModel.rdf#> .\n"
                           "\n"
                           "local:PhysicalProcess0000\n"
                           "    semsim:hasSinkParticipant local:SinkParticipant0000 .\n"
                           "\n"
                           "local:SinkParticipant0000\n"
                           "    semsim:hasMultiplier \"1\"^^rdf:int ;\n"
                           "    semsim:hasPhysicalEntityReference <http://omex-library.org/NewOmex.omex/NewModel.xml#SpeciesA> .\n"
                           "\n"
                           "<http://omex-library.org/NewOmex.omex/NewModel.xml#Reaction_r1>\n"
                           "    bqbiol:isPropertyOf local:PhysicalProcess0000 ;\n"
                           "    bqbiol:isVersionOf <https://identifiers.org/opb/OPB_00592> .\n"
                           "\n";

    ASSERT_STREQ(expected.c_str(), turtle_string.c_str());

}





