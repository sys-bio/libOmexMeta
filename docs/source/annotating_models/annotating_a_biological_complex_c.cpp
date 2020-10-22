
#include "omexmeta/OmexMetaCApi.h"
#include <iostream>

using namespace omexmeta;


int main() {
    RDF* rdf = RDF_new();

    // Here we leave "generate_new_metaids" argument to false and set "sbml_semantic_extraction" to false so that we can annotate ourselves
    Editor* editor = RDF_toEditor(rdf, "models/ComplexBinding.sbml", false, false);


    // Annotate the Shc entity
    PhysicalEntity* Shc = PhysicalEntity_new(editor);
    PhysicalEntity_about(Shc, "Shc"); // corresponds to the metaid for Shc in the SBML source code
    PhysicalEntity_identity(Shc, "uniprot/P29353"); // SHC1
    PhysicalEntity_hasProperty(Shc, "OPB:OPB_00340"); // We're modelling the chemical concentration
    Editor_addPhysicalEntity(editor, Shc); // add to the RDF graph


    // We could optionally annotate where we are modelling Shc, for instance nucleus, cytoplasm, skin, bone, etc. Here
    // we do not need to since we are only modelling reactions in the cytoplasm.

    // Annotate the Sos entity
    PhysicalEntity* Sos = PhysicalEntity_new(editor);
    PhysicalEntity_about(Sos, "Sos"); // corresponds to the metaid for Shc in the SBML source code
    PhysicalEntity_identity(Sos, "uniprot/Q07889"); // SOS1
    PhysicalEntity_hasProperty(Sos, "OPB:OPB_00340"); // We're modelling the chemical concentration
    Editor_addPhysicalEntity(editor, Sos); // add to the RDF graph

    // Annotate the Grb2 entity
    PhysicalEntity* Grb2 = PhysicalEntity_new(editor);
    PhysicalEntity_about(Grb2, "Grb2"); // corresponds to the metaid for Shc in the SBML source code
    PhysicalEntity_identity(Grb2, "uniprot/P62993"); // Grb2
    PhysicalEntity_hasProperty(Grb2, "OPB:OPB_00340"); // We're modelling the chemical concentration
    Editor_addPhysicalEntity(editor, Grb2); // add to the RDF graph

    // Annotate the shc_sos_grb2 entity
    PhysicalEntity* shc_sos_grb2 = PhysicalEntity_new(editor);
    PhysicalEntity_about(shc_sos_grb2, "shc_sos_grb2"); // corresponds to the metaid for Shc in the SBML source code
    PhysicalEntity_hasProperty(shc_sos_grb2, "OPB:OPB_00340"); // We're modelling the chemical concentration
    PhysicalEntity_hasPart(shc_sos_grb2, "uniprot/P29353"); // We're modelling the chemical concentration
    PhysicalEntity_hasPart(shc_sos_grb2, "uniprot/Q07889"); // We're modelling the chemical concentration
    PhysicalEntity_hasPart(shc_sos_grb2, "uniprot/P62993"); // We're modelling the chemical concentration
    Editor_addPhysicalEntity(editor, shc_sos_grb2); // add to the RDF graph


    // annotate the binding reaction
    PhysicalProcess* binding_reaction = PhysicalProcess_new(editor);
    PhysicalProcess_about(binding_reaction, "Binding");
    PhysicalProcess_hasProperty(binding_reaction, "OPB:OPB_00340");
    PhysicalProcess_addSource(binding_reaction, 1, "Shc");
    PhysicalProcess_addSource(binding_reaction, 1, "Sos");
    PhysicalProcess_addSource(binding_reaction, 1, "Grb2");
    PhysicalProcess_addSink(binding_reaction, 1, "Shc_Sos_Grb2");
    Editor_addPhysicalProcess(editor, binding_reaction);

    // annotate the binding reaction
    PhysicalProcess* unbinding_reaction = PhysicalProcess_new(editor);
    PhysicalProcess_about(unbinding_reaction, "Unbinding");
    PhysicalProcess_hasProperty(unbinding_reaction, "OPB:OPB_00340");
    PhysicalProcess_addSource(unbinding_reaction, 1, "Shc_Sos_Grb2");
    PhysicalProcess_addSink(unbinding_reaction, 1, "Shc");
    PhysicalProcess_addSink(unbinding_reaction, 1, "Sos");
    PhysicalProcess_addSink(unbinding_reaction, 1, "Grb2");
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