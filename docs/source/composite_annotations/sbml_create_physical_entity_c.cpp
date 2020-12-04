#include "omexmeta/OmexMetaCApi.h"

using namespace omexmeta;

int main(){
    const char* sbml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                       "<!-- Created by libAntimony version v2.12.0 with libSBML version 5.18.1. -->\n"
                       "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">\n"
                       "  <model metaid=\"SimpleRegulation\" id=\"SimpleRegulation\">\n"
                       "    <listOfCompartments>\n"
                       "      <compartment id=\"cell\" spatialDimensions=\"3\" size=\"1\" constant=\"true\" metaid=\"#OmexMetaId0000\"/>\n"
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
                       "      <reaction id=\"R1\" reversible=\"false\" fast=\"false\" metaid=\"Reaction1\">\n"
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
                       "      <reaction id=\"R2\" reversible=\"false\" fast=\"false\" metaid=\"Reaction2\">\n"
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
                       "      <reaction id=\"R3\" reversible=\"false\" fast=\"false\" metaid=\"#OmexMetaId0009\">\n"
                       "        <listOfReactants>\n"
                       "          <speciesReference species=\"C\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfReactants>\n"
                       "        <listOfProducts>\n"
                       "          <speciesReference species=\"D\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfProducts>\n"
                       "        <listOfModifiers>\n"
                       "          <modifierSpeciesReference species=\"B\"/>\n"
                       "        </listOfModifiers>\n"
                       "        <kineticLaw metaid=\"#OmexMetaId0010\">\n"
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
                       "      <reaction id=\"R4\" reversible=\"false\" fast=\"false\" metaid=\"#OmexMetaId0011\">\n"
                       "        <listOfReactants>\n"
                       "          <speciesReference species=\"D\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfReactants>\n"
                       "        <listOfProducts>\n"
                       "          <speciesReference species=\"C\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfProducts>\n"
                       "        <kineticLaw metaid=\"#OmexMetaId0012\">\n"
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

    RDF* rdf = RDF_new();

    Editor* editor = RDF_toEditor(rdf, sbml, true, false);

    PhysicalEntity* physicalEntity = Editor_newPhysicalEntity(editor);
    PhysicalEntity_about(physicalEntity,"SpeciesA", MODEL_URI);
    PhysicalEntity_identity(physicalEntity, "uniprot/PD12345");
    PhysicalEntity_isPartOf(physicalEntity, "fma:1234", IDENTIFIERS_URI);

    // the full signature of has property (no function overloading in C)
    PhysicalEntity_hasPropertyFull(physicalEntity, "EntityProperty", LOCAL_URI, "opb:OPB_12345");

    Editor_addPhysicalEntity(editor, physicalEntity);
    char* rdf_string = RDF_toString(rdf, "turtle");
    printf("%s\n", rdf_string);

    free(rdf_string);
    PhysicalEntity_delete(physicalEntity);
    Editor_delete(editor);
    RDF_delete(rdf);
    return 0;
}