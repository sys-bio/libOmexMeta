
#include "omexmeta/OmexMeta.h"
#include <iostream>
#include <filesystem>

using namespace omexmeta;


int main() {

    std::string sbml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
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
    RDF rdf;

    // Here we leave "generate_new_metaids" argument to false and set "sbml_semantic_extraction" to false so that we can annotate ourselves
    Editor editor = rdf.toEditor(sbml, false, false);


    // Annotate the Shc entity
    PhysicalEntity Shc = editor.newPhysicalEntity();
    Shc
            .about("Shc", MODEL_URI)                 // corresponds to the metaid for Shc in the SBML source code
            .identity("uniprot/P29353")   // SHC1
            .hasProperty("OPB:OPB_00340");// Were modelling the chemical concentration
    editor.addPhysicalEntity(Shc);

    // We could optionally annotate where we are modelling Shc, for instance nucleus, cytoplasm, skin, bone, etc. Here
    // we do not need to since we are only modelling reactions in the cytoplasm.

    // Annotate the Sos entity
    PhysicalEntity Sos = editor.newPhysicalEntity();
    Sos
            .about("Sos", MODEL_URI)                 // corresponds to the metaid for Sos in the SBML source code
            .identity("uniprot/Q07889")   // SOS1
            .hasProperty("OPB:OPB_00340");// Were modelling the chemical concentration
    editor.addPhysicalEntity(Sos);

    // Annotate the Grb2 entity
    PhysicalEntity Grb2 = editor.newPhysicalEntity();
    Grb2
            .about("Grb2", MODEL_URI)                // corresponds to the metaid for Grb2 in the SBML source code
            .identity("uniprot/P62993")   // GRB2
            .hasProperty("OPB:OPB_00340");// Were modelling the chemical concentration
    editor.addPhysicalEntity(Grb2);


    // Annotate the Complex containing Shc, Sos and Grb2
    PhysicalEntity shc_sos_grb2 = editor.newPhysicalEntity();
    shc_sos_grb2
            .about("Shc_Sos_Grb2", MODEL_URI)         // corresponds to the metaid for Grb2 in the SBML source code
            .hasProperty("OPB:OPB_00340")  // Were modelling the chemical concentration
            .isPartOf("uniprot/P29353") // SHC1
            .isPartOf("uniprot/Q07889") // SOS1
            .isPartOf("uniprot/P62993") ;            // GRB2
    editor.addPhysicalEntity(shc_sos_grb2);

    // annotate the binding reaction
    PhysicalProcess binding_reaction = editor.newPhysicalProcess();
    binding_reaction.about("Binding", MODEL_URI)
            .hasProperty("OPB:OPB_00340")
            .addSource("Shc",MODEL_URI, 1.0 )
            .addSource("Grb2",MODEL_URI, 1.0 )
            .addSource("Sos",MODEL_URI, 1.0 )
            .addSink("Shc_Sos_Grb2", MODEL_URI, 1.0);
    editor.addPhysicalProcess(binding_reaction);

    // annotate the unbinding reaction
    PhysicalProcess unbinding_reaction = editor.newPhysicalProcess();
    unbinding_reaction.about("Unbinding", MODEL_URI)
            .hasProperty("OPB:OPB_00340")
            .addSource( "Shc_Sos_Grb2", MODEL_URI, 1.0)
            .addSink( "Shc", MODEL_URI, 1.0)
            .addSink( "Grb2", MODEL_URI, 1.0)
            .addSink( "Sos", MODEL_URI, 1.0);
    editor.addPhysicalProcess(unbinding_reaction);

    std::cout << rdf.toString() << std::endl;
    return 0;
}