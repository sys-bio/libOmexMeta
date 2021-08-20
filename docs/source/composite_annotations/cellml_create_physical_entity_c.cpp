#include "omexmeta/OmexMetaCApi.h"

using namespace omexmeta;

int main(){
    const char* sbml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                       "<model xmlns=\"http://www.cellml.org/cellml/1.1#\" xmlns:cmeta=\"http://www.cellml.org/metadata/1.0#\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:bqs=\"http://www.cellml.org/bqs/1.0#\" xmlns:semsim=\"http://bime.uw.edu/semsim/#\" xmlns:dc=\"http://purl.org/dc/terms/\" xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\" name=\"annotation_examples\" cmeta:id=\"annExamples\">\n"
                       "  <component name=\"main\">\n"
                       "    <variable cmeta:id=\"main.Volume\" initial_value=\"100\" name=\"Volume\" units=\"dimensionless\" />\n"
                       "    <variable cmeta:id=\"main.MembraneVoltage\" initial_value=\"-80\" name=\"MembraneVoltage\" units=\"dimensionless\" />\n"
                       "    <variable cmeta:id=\"main.ReactionRate\" initial_value=\"1\" name=\"ReactionRate\" units=\"dimensionless\" />\n"
                       "    <variable cmeta:id=\"main.entity1\" initial_value=\"1\" name=\"entity1\" units=\"dimensionless\" />\n"
                       "    <variable cmeta:id=\"main.entity2\" initial_value=\"1\" name=\"entity2\" units=\"dimensionless\" />\n"
                       "    <variable cmeta:id=\"main.entity3\" initial_value=\"1\" name=\"entity3\" units=\"dimensionless\" />\n"
                       "  </component>\n"
                       "</model>";

    RDF* rdf = RDF_new();

    Editor* editor_ptr = RDF_toEditor(rdf, sbml, true, false);

    PhysicalEntity* entity = Editor_newPhysicalEntity(editor_ptr);
    entity = PhysicalEntity_about(entity, "entity0", LOCAL_URI);
    entity = PhysicalEntity_identity(entity, "fma:9670");
    entity = PhysicalEntity_isPartOf(entity, "fma:18228", IDENTIFIERS_URI);
    entity = PhysicalEntity_hasPropertyFull(entity, "main.Volume", MODEL_URI, "opb:OPB_00154");

    Editor_addPhysicalEntity(editor_ptr, entity);

    Editor_addPhysicalEntity(editor_ptr, entity);
    char* rdf_string = RDF_toString(rdf, "turtle");
    printf("%s\n", rdf_string);

    free(rdf_string);
    PhysicalEntity_delete(entity);
    Editor_delete(editor_ptr);
    RDF_delete(rdf);
    return 0;
}