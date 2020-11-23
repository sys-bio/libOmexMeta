#include "omexmeta/OmexMetaCApi.h"

using namespace omexmeta;

int main(){

    const char* sbml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                       "<model xmlns=\"http://www.cellml.org/cellml/1.1#\" xmlns:cmeta=\"http://www.cellml.org/metadata/1.0#\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:bqs=\"http://www.cellml.org/bqs/1.0#\" xmlns:semsim=\"http://bime.uw.edu/semsim/#\" xmlns:dc=\"https://dublincore.org/specifications/dublin-core/dcmi-terms/\" xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\" name=\"annotation_examples\" cmeta:id=\"annExamples\">\n"
                       "  <component name=\"main\">\n"
                       "    <variable cmeta:id=\"main.Volume\" initial_value=\"100\" name=\"Volume\" units=\"dimensionless\" />\n"
                       "    <variable cmeta:id=\"main.MembraneVoltage\" initial_value=\"-80\" name=\"MembraneVoltage\" units=\"dimensionless\" />\n"
                       "    <variable cmeta:id=\"main.ReactionRate\" initial_value=\"1\" name=\"ReactionRate\" units=\"dimensionless\" />\n"
                       "    <variable cmeta:id=\"main.entity1\" initial_value=\"1\" name=\"entity1\" units=\"dimensionless\" />\n"
                       "    <variable cmeta:id=\"main.entity2\" initial_value=\"1\" name=\"entity2\" units=\"dimensionless\" />\n"
                       "    <variable cmeta:id=\"main.entity3\" initial_value=\"1\" name=\"entity3\" units=\"dimensionless\" />\n"
                       "  </component>\n"
                       "</model>";

    RDF* rdf_ptr = RDF_new();

    //
    Editor* editor_ptr = RDF_toEditor(rdf_ptr, sbml, true, false);

    PhysicalProcess* physical_process_ptr = Editor_newPhysicalProcess(editor_ptr);
    PhysicalProcess_about(physical_process_ptr, "Process", LOCAL_URI);
    PhysicalProcess_addSource(physical_process_ptr, "entity1", LOCAL_URI, 1);
    PhysicalProcess_addSink(physical_process_ptr, "entity2", LOCAL_URI, 1);
    PhysicalProcess_addMediator(physical_process_ptr, "entity3", LOCAL_URI);
    PhysicalProcess_hasPropertyFull(physical_process_ptr, "main.ReactionRate",MODEL_URI, "opb:OPB_00592");

    Editor_addPhysicalProcess(editor_ptr, physical_process_ptr);

    Editor_addPhysicalProcess(editor_ptr, physical_process_ptr);
    char* rdf_string = RDF_toString(rdf_ptr, "turtle");
    printf("%s\n", rdf_string);

    free(rdf_string);
    PhysicalProcess_delete(physical_process_ptr);
    Editor_delete(editor_ptr);
    RDF_delete(rdf_ptr);




    return 0;
}