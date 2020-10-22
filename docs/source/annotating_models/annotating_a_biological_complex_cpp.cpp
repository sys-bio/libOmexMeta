
#include "omexmeta/OmexMeta.h"
#include <iostream>
#include <filesystem>

using namespace omexmeta;


int main() {
    std::cout << std::filesystem::current_path() << std::endl;
    RDF rdf;

    // Here we leave "generate_new_metaids" argument to false and set "sbml_semantic_extraction" to false so that we can annotate ourselves
    Editor editor = rdf.toEditor("models/ComplexBinding.sbml", false, false);


    // Annotate the Shc entity
    PhysicalEntity Shc = editor.newPhysicalEntity();
    Shc
            .about("Shc")                  // corresponds to the metaid for Shc in the SBML source code
            .identity("uniprot/P29353")   // SHC1
            .hasProperty("OPB:OPB_00340");// Were modelling the chemical concentration
    editor.addPhysicalEntity(Shc);

    // We could optionally annotate where we are modelling Shc, for instance nucleus, cytoplasm, skin, bone, etc. Here
    // we do not need to since we are only modelling reactions in the cytoplasm.

    // Annotate the Sos entity
    PhysicalEntity Sos = editor.newPhysicalEntity();
    Sos
            .about("Sos")                 // corresponds to the metaid for Sos in the SBML source code
            .identity("uniprot/Q07889")   // SOS1
            .hasProperty("OPB:OPB_00340");// Were modelling the chemical concentration
    editor.addPhysicalEntity(Sos);

    // Annotate the Grb2 entity
    PhysicalEntity Grb2 = editor.newPhysicalEntity();
    Grb2
            .about("Grb2")                 // corresponds to the metaid for Grb2 in the SBML source code
            .identity("uniprot/P62993")   // GRB2
            .hasProperty("OPB:OPB_00340");// Were modelling the chemical concentration
    editor.addPhysicalEntity(Grb2);


    // Annotate the Complex containing Shc, Sos and Grb2
    PhysicalEntity shc_sos_grb2 = editor.newPhysicalEntity();
    shc_sos_grb2
            .about("Shc_Sos_Grb2")                 // corresponds to the metaid for Grb2 in the SBML source code
            .hasProperty("OPB:OPB_00340")        // Were modelling the chemical concentration
            .hasPart("uniprot/P29353")                   // SHC1
            .hasPart("uniprot/Q07889")                   // SOS1
            .hasPart("uniprot/P62993") ;            // GRB2
    editor.addPhysicalEntity(shc_sos_grb2);

    // annotate the binding reaction
    PhysicalProcess binding_reaction = editor.newPhysicalProcess();
    binding_reaction.about("Binding")
            .hasProperty("OPB:OPB_00340")
            .addSource(1, "Shc")
            .addSource(1, "Grb2")
            .addSource(1, "Sos")
            .addSink(1, "Shc_Sos_Grb2");
    editor.addPhysicalProcess(binding_reaction);

    // annotate the unbinding reaction
    PhysicalProcess unbinding_reaction = editor.newPhysicalProcess();
    unbinding_reaction.about("Unbinding")
            .hasProperty("OPB:OPB_00340")
            .addSource(1, "Shc_Sos_Grb2")
            .addSink(1, "Shc")
            .addSink(1, "Grb2")
            .addSink(1, "Sos");
    editor.addPhysicalProcess(unbinding_reaction);

    std::cout << rdf.toString() << std::endl;
    return 0;
}