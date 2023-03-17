// Information, warnings and errors are logged to console by default
#include "omexmeta/OmexMetaCApi.h"

using namespace omexmeta;

int main() {
    const char *cellml = "<?xml version=\"1.1\" encoding=\"UTF-8\"?>\n"
                         "            <model xmlns=\"http://www.cellml.org/cellml/1.1#\" xmlns:cmeta=\"http://www.cellml.org/metadata/1.0#\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:bqs=\"http://www.cellml.org/bqs/1.0#\" xmlns:semsim=\"http://bime.uw.edu/semsim/#\" xmlns:dc=\"http://purl.org/dc/terms/\" xmlns:vCard=\"http://www.w3.org/2001/vcard-rdf/3.0#\" name=\"annotation_examples\" cmeta:id=\"annExamples\">\n"
                         "              <component name=\"main\">\n"
                         "                <variable cmeta:id=\"main.Volume\" initial_value=\"100\" name=\"Volume\" units=\"dimensionless\" />\n"
                         "                <variable cmeta:id=\"main.MembraneVoltage\" initial_value=\"-80\" name=\"MembraneVoltage\" units=\"dimensionless\" />\n"
                         "                <variable cmeta:id=\"main.ReactionRate\" initial_value=\"1\" name=\"ReactionRate\" units=\"dimensionless\" />\n"
                         "              </component>\n"
                         "            </model>";


    // oops - did a whoops. Parsing rdfxml as turtle
    RDF *rdf = RDF_fromString(cellml, "turtle");// See console

    assert(Logger_size() == 1);

    // get the message
    Message *message = Logger_getMessageI(0);

    // collect message content / level
    char *messageString = Message_getMessage(message);// remember to free returned char*

    // output message content to stdout
    printf("%s\n", messageString);

    // get the message level
    int messageLevel = Message_getLevel(message);

    printf("messageString: %s\n", messageString);
    printf("messageLevel: %i\n", messageLevel);

    // now clear the logger
    Logger_clear();

    assert(Logger_size() == 0);

    Message_deleteMessage(message);
    free(messageString);
    return 0;
}
