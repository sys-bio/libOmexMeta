
#include "omexmeta/OmexMetaCApi.h"
#include <iostream>

using namespace omexmeta;


int main() {

    const char* sbml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                       "<sbml xmlns=\"http://www.sbml.org/sbml/level3/version1/core\" level=\"3\" version=\"1\">\n"
                       "  <model metaid=\"ComplexBinding\" id=\"ComplexBinding\">\n"
                       "    <listOfCompartments>\n"
                       "      <compartment id=\"cytoplasm\" spatialDimensions=\"3\" size=\"1\" constant=\"true\"/>\n"
                       "    </listOfCompartments>\n"
                       "    <listOfSpecies>\n"
                       "      <species id=\"Shc\"  metaid=\"Shc\" compartment=\"cytoplasm\" initialConcentration=\"1\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                       "      <species id=\"Sos\"  metaid=\"Sos\" compartment=\"cytoplasm\" initialConcentration=\"1\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                       "      <species id=\"Grb2\" metaid=\"Grb2\" compartment=\"cytoplasm\" initialConcentration=\"1\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                       "      <species id=\"Shc_Sos_Grb2\" metaid=\"Shc_Sos_Grb2\" compartment=\"cytoplasm\" initialConcentration=\"0\" hasOnlySubstanceUnits=\"false\" boundaryCondition=\"false\" constant=\"false\"/>\n"
                       "    </listOfSpecies>\n"
                       "    <listOfParameters>\n"
                       "      <parameter id=\"k_bind\" metaid=\"k_bind\" value=\"0.1\" constant=\"true\"/>\n"
                       "      <parameter id=\"k_unbind\" metaid=\"k_unbind\" value=\"0.1\" constant=\"true\"/>\n"
                       "    </listOfParameters>\n"
                       "    <listOfReactions>\n"
                       "      <reaction id=\"Binding\" metaid=\"Binding\" reversible=\"false\" fast=\"false\">\n"
                       "        <listOfReactants>\n"
                       "          <speciesReference species=\"Shc\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "          <speciesReference species=\"Sos\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "          <speciesReference species=\"Grb2\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfReactants>\n"
                       "        <listOfProducts>\n"
                       "          <speciesReference species=\"Shc_Sos_Grb2\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfProducts>\n"
                       "        <kineticLaw>\n"
                       "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                       "            <apply>\n"
                       "              <times/>\n"
                       "              <ci> cytoplasm </ci>\n"
                       "              <ci> k_bind </ci>\n"
                       "              <ci> Shc </ci>\n"
                       "              <ci> Sos </ci>\n"
                       "              <ci> Grb2 </ci>\n"
                       "            </apply>\n"
                       "          </math>\n"
                       "        </kineticLaw>\n"
                       "      </reaction>\n"
                       "      <reaction id=\"Unbinding\" metaid=\"Unbinding\" reversible=\"false\" fast=\"false\">\n"
                       "        <listOfReactants>\n"
                       "          <speciesReference species=\"Shc_Sos_Grb2\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfReactants>\n"
                       "        <listOfProducts>\n"
                       "          <speciesReference species=\"Shc\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "          <speciesReference species=\"Sos\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "          <speciesReference species=\"Grb2\" stoichiometry=\"1\" constant=\"true\"/>\n"
                       "        </listOfProducts>\n"
                       "        <kineticLaw>\n"
                       "          <math xmlns=\"http://www.w3.org/1998/Math/MathML\">\n"
                       "            <apply>\n"
                       "              <times/>\n"
                       "              <ci> cytoplasm </ci>\n"
                       "              <ci> k_unbind </ci>\n"
                       "              <ci> Shc_Sos_Grb2 </ci>\n"
                       "            </apply>\n"
                       "          </math>\n"
                       "        </kineticLaw>\n"
                       "      </reaction>\n"
                       "    </listOfReactions>\n"
                       "  </model>\n"
                       "</sbml>";
    RDF* rdf = RDF_new();

    // Here we leave "generate_new_metaids" argument to false and set "sbml_semantic_extraction" to false so that we can annotate ourselves
    Editor* editor = RDF_toEditor(rdf, sbml, false, false);


    // Annotate the Shc entity
    PhysicalEntity* Shc = Editor_newPhysicalEntity(editor);
    PhysicalEntity_about(Shc, "Shc", MODEL_URI); // corresponds to the metaid for Shc in the SBML source code
    PhysicalEntity_identity(Shc, "uniprot/P29353"); // SHC1
    PhysicalEntity_hasPropertyisVersionOf(Shc, "OPB:OPB_00340"); // We're modelling the chemical concentration
    Editor_addPhysicalEntity(editor, Shc); // add to the RDF graph


    // We could optionally annotate where we are modelling Shc, for instance nucleus, cytoplasm, skin, bone, etc. Here
    // we do not need to since we are only modelling reactions in the cytoplasm.

    // Annotate the Sos entity
    PhysicalEntity* Sos = Editor_newPhysicalEntity(editor);
    PhysicalEntity_about(Sos, "Sos", MODEL_URI); // corresponds to the metaid for Shc in the SBML source code
    PhysicalEntity_identity(Sos, "uniprot/Q07889"); // SOS1
    PhysicalEntity_hasPropertyisVersionOf(Sos, "OPB:OPB_00340"); // We're modelling the chemical concentration
    Editor_addPhysicalEntity(editor, Sos); // add to the RDF graph

    // Annotate the Grb2 entity
    PhysicalEntity* Grb2 = Editor_newPhysicalEntity(editor);
    PhysicalEntity_about(Grb2, "Grb2", MODEL_URI); // corresponds to the metaid for Shc in the SBML source code
    PhysicalEntity_identity(Grb2, "uniprot/P62993"); // Grb2
    PhysicalEntity_hasPropertyisVersionOf(Grb2, "OPB:OPB_00340"); // We're modelling the chemical concentration
    Editor_addPhysicalEntity(editor, Grb2); // add to the RDF graph

    // Annotate the shc_sos_grb2 entity
    PhysicalEntity* shc_sos_grb2 = Editor_newPhysicalEntity(editor);
    PhysicalEntity_about(shc_sos_grb2, "Shc_Sos_Grb2", MODEL_URI); // corresponds to the metaid for Shc in the SBML source code
    PhysicalEntity_hasPropertyisVersionOf(shc_sos_grb2, "OPB:OPB_00340"); // We're modelling the chemical concentration
    PhysicalEntity_hasPart(shc_sos_grb2, "uniprot/P29353"); // We're modelling the chemical concentration
    PhysicalEntity_hasPart(shc_sos_grb2, "uniprot/Q07889"); // We're modelling the chemical concentration
    PhysicalEntity_hasPart(shc_sos_grb2, "uniprot/P62993"); // We're modelling the chemical concentration
    Editor_addPhysicalEntity(editor, shc_sos_grb2); // add to the RDF graph


    // annotate the binding reaction
    PhysicalProcess* binding_reaction = Editor_newPhysicalProcess(editor);
    PhysicalProcess_about(binding_reaction, "Binding");
    PhysicalProcess_hasPropertyisVersionOf(binding_reaction, "OPB:OPB_00340");
    PhysicalProcess_addSource(binding_reaction,  "Shc", MODEL_URI, 1.0);
    PhysicalProcess_addSource(binding_reaction,  "Sos", MODEL_URI, 1.0);
    PhysicalProcess_addSource(binding_reaction,  "Grb2", MODEL_URI, 1.0);
    PhysicalProcess_addSink(binding_reaction,  "Shc_Sos_Grb2", MODEL_URI, 1.0);
    Editor_addPhysicalProcess(editor, binding_reaction);

    // annotate the binding reaction
    PhysicalProcess* unbinding_reaction = Editor_newPhysicalProcess(editor);
    PhysicalProcess_about(unbinding_reaction, "Unbinding");
    PhysicalProcess_hasPropertyisVersionOf(unbinding_reaction, "OPB:OPB_00340");
    PhysicalProcess_addSource(unbinding_reaction,  "Shc_Sos_Grb2", MODEL_URI, 1.0);
    PhysicalProcess_addSink(unbinding_reaction,  "Shc", MODEL_URI, 1.0);
    PhysicalProcess_addSink(unbinding_reaction,  "Sos", MODEL_URI, 1.0);
    PhysicalProcess_addSink(unbinding_reaction,  "Grb2", MODEL_URI, 1.0);
    Editor_addPhysicalProcess(editor, unbinding_reaction);

    char* rdf_string = RDF_toString(rdf, "turtle");
    printf("%s\n", rdf_string);
    free(rdf_string);

    // clean up
    PhysicalEntity_delete(Shc);
    PhysicalEntity_delete(Sos);
    PhysicalEntity_delete(Grb2);
    PhysicalEntity_delete(shc_sos_grb2);
    PhysicalProcess_delete(binding_reaction);
    PhysicalProcess_delete(unbinding_reaction);
    Editor_delete(editor);
    RDF_delete(rdf);
    return 0;
}