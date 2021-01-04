#include "omexmeta/OmexMeta.h"

using namespace omexmeta;

int main() {

    std::string sbml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                       "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">\n"
                       "  <model metaid=\"EnergyDiff\" id=\"EnergyDiff\">\n"
                       "    <listOfCompartments>\n"
                       "      <compartment id=\"cytoplasm\" metaid=\"cytoplasm\" spatialDimensions=\"3\" size=\"1\" constant=\"true\"/>\n"
                       "      <compartment id=\"extracellular\" metaid=\"extracellular\" spatialDimensions=\"3\" size=\"1\" constant=\"true\"/>\n"
                       "    </listOfCompartments>\n"
                       "    <listOfSpecies>\n"
                       "      <species id=\"Ca_ex\" metaid=\"Ca_ex\" compartment=\"extracellular\" initialConcentration=\"1\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                       "      <species id=\"Ca_cyt\" metaid=\"Ca_cyt\" compartment=\"cytoplasm\" initialConcentration=\"0.3\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                       "    </listOfSpecies>\n"
                       "    <listOfParameters>\n"
                       "      <parameter id=\"k1\" metaid=\"k1\" value=\"0.1\" constant=\"true\"/>\n"
                       "      <parameter id=\"k2\" metaid=\"k2\" value=\"0.1\" constant=\"true\"/>\n"
                       "      <parameter id=\"N_Ca\" metaid=\"NernstPotential\"/>\n"
                       "    </listOfParameters>\n"
                       "    <listOfReactions>\n"
                       "      <reaction id=\"NernstReversalPotential_in\" metaid=\"NernstReversalPotential_in\" reversible=\"false\" fast=\"false\">\n"
                       "        <listOfReactants>\n"
                       "          <speciesReference species=\"Ca_ex\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfReactants>\n"
                       "        <listOfProducts>\n"
                       "          <speciesReference species=\"Ca_cyt\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfProducts>\n"
                       "        <kineticLaw>\n"
                       "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                       "            <apply>\n"
                       "              <times/>\n"
                       "              <ci> cytoplasm </ci>\n"
                       "              <ci> k1 </ci>\n"
                       "              <ci> Ca_ex </ci>\n"
                       "            </apply>\n"
                       "          </math>\n"
                       "        </kineticLaw>\n"
                       "      </reaction>\n"
                       "      <reaction id=\"NernstReversalPotential_out\" metaid=\"NernstReversalPotential_out\" reversible=\"false\" fast=\"false\">\n"
                       "        <listOfReactants>\n"
                       "          <speciesReference species=\"Ca_cyt\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfReactants>\n"
                       "        <listOfProducts>\n"
                       "          <speciesReference species=\"Ca_ex\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfProducts>\n"
                       "        <kineticLaw>\n"
                       "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                       "            <apply>\n"
                       "              <times/>\n"
                       "              <ci> extracellular </ci>\n"
                       "              <ci> k2 </ci>\n"
                       "              <ci> Ca_cyt </ci>\n"
                       "            </apply>\n"
                       "          </math>\n"
                       "        </kineticLaw>\n"
                       "      </reaction>\n"
                       "    </listOfReactions>\n"
                       "  </model>\n"
                       "</sbml>";


    RDF rdf;
    Editor editor = rdf.toEditor(sbml, false, false);

    EnergyDiff energyDiff = editor.newEnergyDiff();
    energyDiff
            // this could be named anything provided it is unique to the rdf graph because it is a LOCAL_URI
            .about("MembranePotential", LOCAL_URI)
            .addSource("Ca_ex", MODEL_URI)
            .addSink("Ca_cyt", MODEL_URI)
            // for energy differentials we use the full signature of hasProperty.
            // The arguments are as follows:
            //  - NernstPotential: the "about" value that is used for the property associated with the energy differential
            //  - MODEL_URI: the uri type for the previous argument. In SBML this is a <parameter> and therefore a MODEL_URI
            //      while in CellML this is a construct local to the rdf document (so LOCAL_URI)
            //  - OPB:OPB_01581: the OPB term associated with the property (isVersionOf)
            .hasProperty("NernstPotential", MODEL_URI, "OPB:OPB_01581");
    editor.addEnergyDiff(energyDiff);

    std::cout << rdf.toString() << std::endl;

    return 0;
}
