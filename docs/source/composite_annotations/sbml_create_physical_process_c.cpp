#include "omexmeta/OmexMetaCApi.h"

using namespace omexmeta;

int main(){

    const char* sbml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
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

    RDF* rdf_ptr = RDF_new();

    //
    Editor* editor_ptr = RDF_toEditor(rdf_ptr, sbml, true, false);

    PhysicalProcess* process = Editor_newPhysicalProcess(editor_ptr);
    PhysicalProcess_about(process, "R1", MODEL_URI);
    PhysicalProcess_addSource(process, "SpeciesA", MODEL_URI, 1.0);
    PhysicalProcess_addSink(process, "SpeciesB", MODEL_URI, 1.0);
    PhysicalProcess_addMediator(process, "SpeciesC", MODEL_URI);
    PhysicalProcess_hasPropertyisVersionOf(process, "opb:OPB_00592");
    PhysicalProcess_isVersionOf(process, "GO:12345", eUriType::IDENTIFIERS_URI);

    Editor_addPhysicalProcess(editor_ptr, process);
    char* rdf_string = RDF_toString(rdf_ptr, "turtle");
    printf("%s\n", rdf_string);

    free(rdf_string);
    PhysicalProcess_delete(process);
    Editor_delete(editor_ptr);
    RDF_delete(rdf_ptr);




    return 0;
}