#include "omexmeta/OmexMeta.h"

using namespace omexmeta;

int main(){

    std::string sbml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
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
    RDF rdf = RDF();

    Editor editor = rdf.toEditor(sbml, true);

    PhysicalProcess physicalProcess = editor.newPhysicalProcess();
    physicalProcess.about("Process", LOCAL_URI)
            .addSource("entity1", LOCAL_URI, 1)
            .addSink("entity2", LOCAL_URI, 1)
            .addMediator("entity3", LOCAL_URI)
            .hasProperty("main.ReactionRate", MODEL_URI, "opb:OPB_00592");
    editor.addPhysicalProcess(physicalProcess);

    editor.addPhysicalProcess(physicalProcess);

    std::cout << rdf.toString() << std::endl; // turtle default

    return 0;
}