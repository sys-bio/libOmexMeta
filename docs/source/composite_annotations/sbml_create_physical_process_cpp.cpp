#include "omexmeta/OmexMeta.h"

using namespace omexmeta;

int main(){

    std::string sbml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                       "<!-- Created by libAntimony version v2.12.0 with libSBML version 5.18.1. -->\n"
                       "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">\n"
                       "  <model metaid=\"SimpleRegulation\" id=\"SimpleRegulation\">\n"
                       "    <listOfCompartments>\n"
                       "      <compartment id=\"cell\" spatialDimensions=\"3\" size=\"1\" constant=\"true\" metaid=\"OmexMetaId0000\"/>\n"
                       "    </listOfCompartments>\n"
                       "    <listOfSpecies>\n"
                       "      <species id=\"A\" compartment=\"cell\" initialConcentration=\"10\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\" metaid=\"SpeciesA\"/>\n"
                       "      <species id=\"B\" compartment=\"cell\" initialConcentration=\"0\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\" metaid=\"SpeciesB\"/>\n"
                       "      <species id=\"C\" compartment=\"cell\" initialConcentration=\"10\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\" metaid=\"SpeciesC\"/>\n"
                       "      <species id=\"D\" compartment=\"cell\" initialConcentration=\"0\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\" metaid=\"SpeciesD\"/>\n"
                       "    </listOfSpecies>\n"
                       "    <listOfParameters>\n"
                       "      <parameter id=\"S\" metaid=\"S\" value=\"0\" constant=\"true\"/>\n"
                       "      <parameter id=\"k1\" metaid=\"k1\" value=\"0.1\" constant=\"true\"/>\n"
                       "      <parameter id=\"k2\" metaid=\"k2\" value=\"0.1\" constant=\"true\"/>\n"
                       "      <parameter id=\"k3\" metaid=\"k4\" value=\"0.1\" constant=\"true\"/>\n"
                       "      <parameter id=\"k4\" value=\"0.1\" constant=\"true\"/>\n"
                       "    </listOfParameters>\n"
                       "    <listOfReactions>\n"
                       "      <reaction id=\"R1\" reversible=\"false\" fast=\"false\" metaid=\"R1\">\n"
                       "        <listOfReactants>\n"
                       "          <speciesReference species=\"A\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfReactants>\n"
                       "        <listOfProducts>\n"
                       "          <speciesReference species=\"B\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfProducts>\n"
                       "        <kineticLaw metaid=\"KineticLawForReaction1\">\n"
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
                       "      <reaction id=\"R2\" reversible=\"false\" fast=\"false\" metaid=\"R2\">\n"
                       "        <listOfReactants>\n"
                       "          <speciesReference species=\"B\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfReactants>\n"
                       "        <listOfProducts>\n"
                       "          <speciesReference species=\"A\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfProducts>\n"
                       "        <kineticLaw metaid=\"KineticLawForReaction2\">\n"
                       "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                       "            <apply>\n"
                       "              <times/>\n"
                       "              <ci> k2 </ci>\n"
                       "              <ci> B </ci>\n"
                       "            </apply>\n"
                       "          </math>\n"
                       "        </kineticLaw>\n"
                       "      </reaction>\n"
                       "      <reaction id=\"R3\" reversible=\"false\" fast=\"false\" metaid=\"R3\">\n"
                       "        <listOfReactants>\n"
                       "          <speciesReference species=\"C\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfReactants>\n"
                       "        <listOfProducts>\n"
                       "          <speciesReference species=\"D\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfProducts>\n"
                       "        <listOfModifiers>\n"
                       "          <modifierSpeciesReference species=\"B\"/>\n"
                       "        </listOfModifiers>\n"
                       "        <kineticLaw metaid=\"KineticLawForReaction3\">\n"
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
                       "      <reaction id=\"R4\" reversible=\"false\" fast=\"false\" metaid=\"R4\">\n"
                       "        <listOfReactants>\n"
                       "          <speciesReference species=\"D\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfReactants>\n"
                       "        <listOfProducts>\n"
                       "          <speciesReference species=\"C\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfProducts>\n"
                       "        <kineticLaw metaid=\"KineticLawForReaction4\">\n"
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
                       "</sbml>";
    RDF rdf = RDF();

    Editor editor = rdf.toEditor(sbml, true);

    PhysicalProcess physicalProcess = editor.newPhysicalProcess();
    physicalProcess.about("R1", MODEL_URI)
            .addSource("SpeciesA", MODEL_URI, 1)
            .addSink("SpeciesB", MODEL_URI, 1)
            .addMediator("SpeciesC", MODEL_URI )
            .hasProperty("opb:OPB_00592")
            .isVersionOf("GO:12345");

    editor.addPhysicalProcess(physicalProcess);


    std::cout << rdf.toString() << std::endl; // turtle default

    return 0;
}