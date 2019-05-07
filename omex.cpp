#include "omex.h"
#include "pugixml-1.9/src/pugixml.hpp"

void readOMEX(char *OMEXfilename, char *filename, char *model_sbml)
{
    int error(0);
    zip *foo = zip_open(OMEXfilename, 0, &error);
    std::cout << "Success" << std::endl;

    int files_total = zip_get_num_entries(foo, 0);
    printf("Note: we have  %d files in the OMEX file\n",files_total);


    struct zip_stat sb;
    int r, len;
    long long sum;
    char buffer[10000];

    for (int i = 0; i < zip_get_num_entries(foo, 0); i++) {
        if (zip_stat_index(foo, i, 0, &sb) == 0) {
            printf("==================\n");
            printf("Name: [%s], ", sb.name);
            printf("Size: [%llu], ", sb.size);
            printf("Index: [%llu], ", sb.index);
            printf("Valid: [%llu], ", sb.valid);
            printf("mtime: [%u]\n", (unsigned int) sb.mtime);

            if (strcmp(filename, sb.name) == 0) {

                zip_file *zf = zip_fopen_index(foo, i, 0);
                if (!zf) {
                    fprintf(stderr, "boese, boese\n");
                    std::cout << "failed to opne  entry of archive. " << zip_strerror(foo) << std::endl;
                    zip_close(foo);
                }

                sum = 0;
                while (sum != sb.size) {
                    len = zip_fread(zf, buffer, 100);
                    if (len < 0) {
                        fprintf(stderr, "boese, boese\n");
                        exit(102);
                    }
                    printf("%s", buffer, len);
                    sum += len;
                }
                zip_fclose(zf);
                printf("==================\n");
            }
            std::cout<<std::endl;
        }
    }
}

char *readfile(std::string filename, size_t *size) {
    char * buffer;
    size_t result;

    FILE* pFile = fopen (filename.c_str(), "rb" );
    if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

    // obtain file size:
    fseek (pFile , 0 , SEEK_END);
    unsigned int lSize = ftell (pFile);
    rewind (pFile);

    // allocate memory to contain the whole file:
    buffer = (char*) malloc (sizeof(char)*lSize);
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

    // copy the file into the buffer:
    result = fread (buffer,1,lSize,pFile);
    if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

    /* the whole file is now loaded in the memory buffer. */

    // terminate
    fclose (pFile);
    *size = lSize;
    return buffer;

}
zip * get_archive(std::string path, int flags) {
    int error = 0;
    zip *archive = zip_open(path.c_str(), flags , &error);

    if(!archive) {
        std::cout << "could not open or create archive" <<  path << std::endl;
        exit(1) ;
    }
    std::cout << "Done : creating archieve" << path <<  std::endl;
    return archive;
}

void addOMEX(char* path, char* filename) {

    int error = 0;
    zip *archive = zip_open(path, ZIP_CREATE, &error);

    if(error)
    {
        std::cout << "could not open or create archive" << std::endl;
    }

    int index;
    size_t len;
    char *data = readfile(filename, &len);
    //std::cout << "File content \n" << "Name " << filename << "\nSize " << len << "\n" << data << std::endl;

    zip_source *source = zip_source_buffer(archive, data, len, 0);
    if (source == NULL) {
        std::cout << "failed to create source buffer. " << zip_strerror(archive) << std::endl;
        return;
    }

    index = (int)zip_file_add(archive, filename, source, ZIP_FL_ENC_UTF_8);
    //index = (int) zip_add(archive, filename, source);
    if (index < 0) {
        zip_source_free(source);
        std::cout << "failed to add file to archive. " << zip_strerror(archive) << std::endl;
        return;
    }
    zip_close(archive);
}

void
print_element_names(xmlNode * a_node)
{
    xmlNode *cur_node = NULL;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            printf("node type: Element, name: %s, content: %s, childeren: %s \n", cur_node->name, cur_node->content, cur_node->children);
        }

        print_element_names(cur_node->children);
    }
}

xmlNode
*readOMEX(char *SBMLfilename){

    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    /*parse the file and get the DOM */
    doc = xmlReadFile(SBMLfilename, NULL, 0);

    if (doc == NULL) {
        printf("error: could not parse file %s\n", SBMLfilename);
    }

    root_element = xmlDocGetRootElement(doc);

    /*free the document */
    xmlFreeDoc(doc);
    return root_element;


    /*
     *Free the global variables that may
     *have been allocated by the parser.
     */
    xmlCleanupParser();
}

void getXMLelements(char *SBMLfilename) {
    print_element_names(readOMEX(SBMLfilename));
}

void
getReference (xmlDocPtr doc, xmlNodePtr cur) {

    xmlChar *uri;
    cur = cur->xmlChildrenNode;
    while (cur != NULL) {
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"model"))) {
            uri = xmlGetProp(cur, (const xmlChar *)"listOfRules");
            printf("listOfRules: %s\n", uri);
            xmlFree(uri);
        }
        cur = cur->next;
    }
    return;
}

void
parseDoc (char *docname) {

    xmlDocPtr doc;
    xmlNodePtr cur;

    doc = xmlParseFile(docname);

    if (doc == NULL ) {
        fprintf(stderr,"Document not parsed successfully. \n");
        return;
    }

    cur = xmlDocGetRootElement(doc);

    if (cur == NULL) {
        fprintf(stderr,"empty document\n");
        xmlFreeDoc(doc);
        return;
    }

    if (xmlStrcmp(cur->name, (const xmlChar *) "rdf:RDF")) {
        fprintf(stderr,"document of the wrong type, root node != story");
        xmlFreeDoc(doc);
        return;
    }

    getReference (doc, cur);
    xmlFreeDoc(doc);
    return;
}

void notSure(char *filename){
    parseDoc (filename);
}

xmlDocPtr
getdoc (char *docname) {
    xmlDocPtr doc;
    doc = xmlParseFile(docname);

    if (doc == NULL ) {
        fprintf(stderr,"Document not parsed successfully. \n");
        return NULL;
    }

    return doc;
}

//xmlXPathObjectPtr
//getnodeset (xmlDocPtr doc, xmlChar *xpath){
//
//    xmlXPathContextPtr context;
//    xmlXPathObjectPtr result;
//
//    context = xmlXPathNewContext(doc);
//    if (context == NULL) {
//        printf("Error in xmlXPathNewContext\n");
//        return NULL;
//    }
//    result = xmlXPathEvalExpression(xpath, context);
//    xmlXPathFreeContext(context);
//    if (result == NULL) {
//        printf("Error in xmlXPathEvalExpression\n");
//        return NULL;
//    }
//    if(xmlXPathNodeSetIsEmpty(result->nodesetval)){
//        xmlXPathFreeObject(result);
//        printf("No result\n");
//        return NULL;
//    }
//    return result;
//}


// XPATH
//void getXPATH (char *filename, char *query){
//
//    char *docname;
//
//    xmlDocPtr doc = getdoc(filename);
//    xmlChar *xpath = (xmlChar*) query;
//    xmlXPathContextPtr context = xmlXPathNewContext(doc);
//
//    xmlNodeSetPtr nodeset;
//    xmlXPathObjectPtr result;
//    int i;
//    xmlChar *keyword;
//
////    if(xmlXPathRegisterNs(context,  BAD_CAST "rdf", BAD_CAST "http://www.w3.org/1999/02/22-rdf-syntax-ns#") != 0) {
////        std::cout<<"Error: unable to register NS with prefix"<< std::endl;
////    }
//
//    result = getnodeset (doc, xpath);
//    if (result) {
//        nodeset = result->nodesetval;
//        for (i=0; i < nodeset->nodeNr; i++) {
//            keyword = xmlNodeListGetString(doc, nodeset->nodeTab[i]->xmlChildrenNode, 1);
//            printf("keyword: %s\n", keyword);
//            xmlFree(keyword);
//        }
//        xmlXPathFreeObject (result);
//    }
//    xmlFreeDoc(doc);
//    xmlCleanupParser();
//
//}


xmlXPathObjectPtr
getnodeset (xmlDocPtr doc, xmlChar *xpath){

    xmlXPathContextPtr context;
    xmlXPathObjectPtr result;

    context = xmlXPathNewContext(doc);
    if (context == NULL) {
        printf("Error in xmlXPathNewContext\n");
        return NULL;
    }

    if(xmlXPathRegisterNs(context,  BAD_CAST "rdf", BAD_CAST "http://www.w3.org/1999/02/22-rdf-syntax-ns#") != 0) {
        fprintf(stderr,"Error: unable to register NS with prefix");
        return NULL;
    }


    result = xmlXPathEvalExpression(xpath, context);
    xmlXPathFreeContext(context);
    if (result == NULL) {
        printf("Error in xmlXPathEvalExpression\n");
        return NULL;
    }
    if(xmlXPathNodeSetIsEmpty(result->nodesetval)){
        xmlXPathFreeObject(result);
        printf("No result\n");
        return NULL;
    }
    return result;
}


void getXPATHnamespace(char *filename, char *query){

    char *docname;
    xmlDocPtr doc;
    xmlChar *xpath = (xmlChar*) query;
    xmlNodeSetPtr nodeset;
    xmlXPathObjectPtr result;
    int i;
    xmlChar *keyword;

    doc = getdoc(filename);
    result = getnodeset (doc, xpath);
    if (result) {
        nodeset = result->nodesetval;
        for (i=0; i < nodeset->nodeNr; i++) {
            keyword = xmlNodeListGetString(doc, nodeset->nodeTab[i]->xmlChildrenNode, 1);

            std::cout<<nodeset->nodeTab[i]->name<<" = "<<keyword<<std::endl;
            //std::cout<<"keyword: "<<nodeset->nodeTab[i]->xmlChildrenNode->content<<keyword<<std::endl;
            //xmlFree(keyword);
        }
        xmlXPathFreeObject (result);
    }

    xmlFreeDoc(doc);
    xmlCleanupParser();

}



// New try


static void usage(const char *name);
int  execute_xpath_expression(const char* filename, const xmlChar* xpathExpr, const xmlChar* nsList);
int  register_namespaces(xmlXPathContextPtr xpathCtx, const xmlChar* nsList);
void print_xpath_nodes(xmlNodeSetPtr nodes, FILE* output);

/**
 * usage:
 * @name:		the program name.
 *
 * Prints usage information.
 */
static void
usage(const char *name) {
    assert(name);

    fprintf(stderr, "Usage: %s <xml-file> <xpath-expr> [<known-ns-list>]\n", name);
    fprintf(stderr, "where <known-ns-list> is a list of known namespaces\n");
    fprintf(stderr, "in \"<prefix1>=<href1> <prefix2>=href2> ...\" format\n");
}

/**
 * execute_xpath_expression:
 * @filename:		the input XML filename.
 * @xpathExpr:		the xpath expression for evaluation.
 * @nsList:		the optional list of known namespaces in
 *			"<prefix1>=<href1> <prefix2>=href2> ..." format.
 *
 * Parses input XML file, evaluates XPath expression and prints results.
 *
 * Returns 0 on success and a negative value otherwise.
 */
int
execute_xpath_expression(const char* filename, const xmlChar* xpathExpr, const xmlChar* nsList) {
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;

    assert(filename);
    assert(xpathExpr);

    /* Load XML document */
    doc = xmlParseFile(filename);
    if (doc == NULL) {
        fprintf(stderr, "Error: unable to parse file \"%s\"\n", filename);
        return(-1);
    }

    /* Create xpath evaluation context */
    xpathCtx = xmlXPathNewContext(doc);
    if(xpathCtx == NULL) {
        fprintf(stderr,"Error: unable to create new XPath context\n");
        xmlFreeDoc(doc);
        return(-1);
    }

    /* Register namespaces from list (if any) */
    if((nsList != NULL) && (register_namespaces(xpathCtx, nsList) < 0)) {
        fprintf(stderr,"Error: failed to register namespaces list \"%s\"\n", nsList);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return(-1);
    }

    /* Evaluate xpath expression */
    xpathObj = xmlXPathEvalExpression(xpathExpr, xpathCtx);
    if(xpathObj == NULL) {
        fprintf(stderr,"Error: unable to evaluate xpath expression \"%s\"\n", xpathExpr);
        xmlXPathFreeContext(xpathCtx);
        xmlFreeDoc(doc);
        return(-1);
    }

    /* Print results */
    print_xpath_nodes(xpathObj->nodesetval, stdout);

    /* Cleanup */
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx);
    xmlFreeDoc(doc);

    return(0);
}

/**
 * register_namespaces:
 * @xpathCtx:		the pointer to an XPath context.
 * @nsList:		the list of known namespaces in
 *			"<prefix1>=<href1> <prefix2>=href2> ..." format.
 *
 * Registers namespaces from @nsList in @xpathCtx.
 *
 * Returns 0 on success and a negative value otherwise.
 */
int
register_namespaces(xmlXPathContextPtr xpathCtx, const xmlChar* nsList) {
    xmlChar* nsListDup;
    xmlChar* prefix;
    xmlChar* href;
    xmlChar* next;

    assert(xpathCtx);
    assert(nsList);

    nsListDup = xmlStrdup(nsList);
    if(nsListDup == NULL) {
        fprintf(stderr, "Error: unable to strdup namespaces list\n");
        return(-1);
    }

    next = nsListDup;
    while(next != NULL) {
        /* skip spaces */
        while((*next) == ' ') next++;
        if((*next) == '\0') break;

        /* find prefix */
        prefix = next;
        next = (xmlChar*)xmlStrchr(next, '=');
        if(next == NULL) {
            fprintf(stderr,"Error: invalid namespaces list format\n");
            xmlFree(nsListDup);
            return(-1);
        }
        *(next++) = '\0';

        /* find href */
        href = next;
        next = (xmlChar*)xmlStrchr(next, ' ');
        if(next != NULL) {
            *(next++) = '\0';
        }

        /* do register namespace */
        if(xmlXPathRegisterNs(xpathCtx, prefix, href) != 0) {
            fprintf(stderr,"Error: unable to register NS with prefix=\"%s\" and href=\"%s\"\n", prefix, href);
            xmlFree(nsListDup);
            return(-1);
        }
    }

    xmlFree(nsListDup);
    return(0);
}

/**
 * print_xpath_nodes:
 * @nodes:		the nodes set.
 * @output:		the output file handle.
 *
 * Prints the @nodes content to @output.
 */
void
print_xpath_nodes(xmlNodeSetPtr nodes, FILE* output) {
    xmlNodePtr cur;
    int size;
    int i;

    assert(output);
    size = (nodes) ? nodes->nodeNr : 0;

    fprintf(output, "Result (%d nodes):\n", size);
    for(i = 0; i < size; ++i) {
        assert(nodes->nodeTab[i]);

        if(nodes->nodeTab[i]->type == XML_NAMESPACE_DECL) {
            xmlNsPtr ns;

            ns = (xmlNsPtr)nodes->nodeTab[i];
            cur = (xmlNodePtr)ns->next;
            if(cur->ns) {
                fprintf(output, "= namespace \"%s\"=\"%s\" for node %s:%s\n",
                        ns->prefix, ns->href, cur->ns->href, cur->name);
            } else {
                fprintf(output, "= namespace \"%s\"=\"%s\" for node %s\n",
                        ns->prefix, ns->href, cur->name);
            }
        } else if(nodes->nodeTab[i]->type == XML_ELEMENT_NODE) {
            cur = nodes->nodeTab[i];
            if(cur->ns) {
                std::cout<<xmlNodeGetContent(cur);
                fprintf(output, "= element node \"%s:%s\"\n",
                        cur->ns->href, cur->name);
            } else {
                fprintf(output, "= element node \"%s\"\n",
                        cur->name);
            }
        } else {
            cur = nodes->nodeTab[i];
            fprintf(output, "= node \"%s\": value %s\n", cur->name, cur->xmlChildrenNode->content);
        }
    }
}

void parseXPATH(char *filename, char *query, char *nslist){

    /* Init libxml */
    xmlInitParser();
    LIBXML_TEST_VERSION

    /* Do the main job */
    if(execute_xpath_expression(filename, BAD_CAST query, BAD_CAST nslist) < 0) {
        std::cout<<"Error"<<std::endl;
    }

}


// Final Helper Functions

void getAllEntities_RDF(char *filename){
    getXPATHnamespace(filename, "//rdf:Description/@rdf:about" );
}

void getAllEntities_SBML(char *filename){

    getXPATHnamespace(filename, "/*[local-name()='sbml']/*[local-name()='model']/*[local-name()='listOfParameters']//@id");
}


void getInfo_SBML(char *filename, char *id){

    std::string str = "";
    str = "/*[local-name()='sbml']/*[local-name()='model']/*[local-name()='listOfParameters']/*[@id='";
    str += id;
    str += "']/@*";
    char query[str.size() + 1];
    strcpy(query, str.c_str());

    getXPATHnamespace(filename, query);

}

void getInfo_RDF(char *filename, char *id){

    std::string str = "";
    //rdf:Description[@rdf:about='./bind2_sbml.sbml#sink_1']
    str = "//rdf:Description[@rdf:about='./bind2_sbml.sbml#";
    str += id;
    str += "']//@*";
    char query[str.size() + 1];
    strcpy(query, str.c_str());

    std::cout<<"new\n";
    parseXPATH(filename, query, "dcterms=http://purl.org/dc/terms/ "
                                "semsim=http://www.bhi.washington.edu/SemSim# "
                                "rdf=http://www.w3.org/1999/02/22-rdf-syntax-ns# "
                                "bqmodel=http://biomodels.net/model-qualifiers/ "
                                "bqbiol=http://biomodels.net/biology-qualifiers/ "
                                "ro=http://www.obofoundry.org/ro/ro.owl#" );

    std::cout<<"old\n";
    getXPATHnamespace(filename, query);
}


