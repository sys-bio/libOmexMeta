#include "sbml.h"

//TODO : REMOVE
void sbml_hello()
{
    std::cout << "Hello from sbml" << std::endl;
}

static void
print_element_names(xmlNode * a_node)
{
    xmlNode *cur_node = NULL;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            cout<<("node type: Element, name: %s\n", cur_node->name)<<endl;
        }
        print_element_names(cur_node->children);
    }
}

void parseXML(std::string s){

    xmlNode *root_element = NULL;
    const xmlChar * content = (const unsigned  char *)s.c_str();
    xmlDocPtr doc = xmlReadMemory(s.c_str(), s.length(), "noname.xml", NULL, 0);
    root_element = xmlDocGetRootElement(doc);

    print_element_names(root_element);
    /*free the document */
    xmlFreeDoc(doc);
    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();
//        xmlChar      *uri;
//
//        xmlXPathContext *xpathCtx = xmlXPathNewContext( doc );
//        xmlXPathObject * xpathObj =
//                xmlXPathEvalExpression( (xmlChar*)"/annotation/RDF/isVersionOf/Bag/li", xpathCtx );
//        xmlNode *node = xpathObj->nodesetval->nodeTab[0];

//        cout<<"Test 1:"<<endl;


//
//        cur = cur->xmlChildrenNode;
//        xmlChar *uri;
//        while (cur != NULL) {
//            //const xmlChar *
//            if ((!xmlStrcmp(cur->name, (const xmlChar *)"reference"))) {
//                uri = xmlGetProp(cur, "uri");
//                printf("uri: %s\n", uri);
//                xmlFree(uri);
//            }
//            cur = cur->next;
//        }
//        xmlFreeDoc(doc);
}

void printModel() { std::string mS = "void"; std::cout<<"Usage: Provide SBML file as input parameter"<< std::endl ;}

int printSBMLModel(char* filename){


    SBMLDocument* document = readSBML(filename);

    if (document->getNumErrors() > 0)
    {
        cerr << "Encountered the following SBML errors:" << endl;
        document->printErrors(cerr);
        return 1;
    }



    unsigned int level   = document->getLevel  ();
    unsigned int version = document->getVersion();
    cout << endl
         << " (Level " << level << ", version " << version << ")" << endl;
    Model* model = document->getModel();
    if (model == 0)
    {
        cout << "No model present." << endl;
        return 1;
    }
    cout << "               "
         << (level == 1 ? "name: " : "  id: ")
         << (model->isSetId() ? model->getId() : std::string("(empty)")) << endl;
    if (model->isSetSBOTerm())
        cout << "      model sboTerm: " << model->getSBOTerm() << endl;
    cout << "functionDefinitions: " << model->getNumFunctionDefinitions() << endl;
    cout << "    unitDefinitions: " << model->getNumUnitDefinitions    () << endl;
    cout << "   compartmentTypes: " << model->getNumCompartmentTypes   () << endl;
    cout << "        specieTypes: " << model->getNumSpeciesTypes       () << endl;
    cout << "       compartments: " << model->getNumCompartments       () << endl;
    cout << "            species: " << model->getNumSpecies            () << endl;
    cout << "         parameters: " << model->getNumParameters         () << endl;
    cout << " initialAssignments: " << model->getNumInitialAssignments () << endl;
    cout << "              rules: " << model->getNumRules              () << endl;
    cout << "        constraints: " << model->getNumConstraints        () << endl;
    cout << "          reactions: " << model->getNumReactions          () << endl;
    cout << "             events: " << model->getNumEvents             () << endl;
    cout << endl;
    return 0;
}

void printModel(char* filename) { std::cout<<filename; std::cout<<printSBMLModel(filename)<<std::endl;}
