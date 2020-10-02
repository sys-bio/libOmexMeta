#include "omexmeta/OmexMetaCApi.h"

using namespace omexmeta;

int main(){

    /*
     * import tellurim as te
     * ant = """
     * model SBMLExtractionTestModel
     *     r1: A -> B; k1*A*S;
     *     r2: B -> A; k2*B;
     *     r3: C -> D; k3*C*B;
     *     r4: D -> C; k4*D;
     *     k1 = 0.1;
     *     k2 = 0.1;
     *     k3 = 0.1;
     *     k4 = 0.1;
     *     A = 100;
     *     B = 0;
     *     C = 100;
     *     D = 0;
     *     S = 1;
     *     compartment nucleus = 1;
     *     compartment cytosol = 1;
     *     A in nucleus;
     *     B in nucleus
     *     C in cytosol
     *     D in cytosol
     * end
     * """
     *
     * m = te.loada(ant)
     * print(m.getSBML())
     *
     * # now modify add metaids to the bits that need them
     */

    const char* sbml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
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
                       "      <parameter id=\"k1\"  metaid=\"Parameterk1\" value=\"0.1\" constant=\"true\"/>\n"
                       "      <parameter id=\"S \"  metaid=\"ParameterS\" value=\"1\" constant=\"true\"/>\n"
                       "      <parameter id=\"k2\"  metaid=\"Parameterk2\" value=\"0.1\" constant=\"true\"/>\n"
                       "      <parameter id=\"k3\"  metaid=\"Parameterk3\" value=\"0.1\" constant=\"true\"/>\n"
                       "      <parameter id=\"k4\"  metaid=\"Parameterk4\" value=\"0.1\" constant=\"true\"/>\n"
                       "    </listOfParameters>\n"
                       "    <listOfReactions>\n"
                       "      <reaction id=\"r1\" metaid=\"reaction_r1\" reversible=\"true\" fast=\"false\">\n"
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
                       "      <reaction id=\"r2\" metaid=\"reaction_r2\" reversible=\"true\" fast=\"false\">\n"
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
                       "      <reaction id=\"r3\" metaid=\"reaction_r3\" reversible=\"true\" fast=\"false\">\n"
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
                       "      <reaction id=\"r4\" metaid=\"reaction_r4\" reversible=\"true\" fast=\"false\">\n"
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

    RDF* rdf_ptr = RDF_new();

    //
    Editor* editor_ptr = RDF_toEditor(rdf_ptr, sbml, true, false);

    PhysicalProcess* process = PhysicalProcess_new(editor_ptr);
    PhysicalProcess_setAbout(process, "OmexMeta0000");
    PhysicalProcess_hasProperty(process, "OPB:OPB_00340");
    PhysicalProcess_isVersionOf(process, "GO:12345");
    PhysicalProcess_addSource(process, 1, "OmexMeta0001");
    PhysicalProcess_addSink(process, 1, "OmexMeta0002");
    PhysicalProcess_addMediator(process,"OmexMeta0003");




    return 0;
}