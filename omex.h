#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xmlmemory.h>
#include <libxml/xpathInternals.h>
#include <libxml/xpath.h>
#include <libxml/xinclude.h>
#include <libxml/xmlIO.h>

#include <pugixml-1.9/src/pugiconfig.hpp>

void readOMEX(char *OMEXfilename, char *model_rdf, char *model_sbml);
void addOMEX(char* path, char* filename);
void getXMLelements(char *SBMLfilename);
void notSure(char *filename);
void getXPATHnamespace(char *filename, char *query);
void parseXPATH(char *filename, char *query, char *nslist);
void getAllEntities_RDF(char *filename);
void getAllEntities_SBML(char *filename);
void getInfo_SBML(char *filename, char *id);
void getInfo_RDF(char *filename, char *id);
void getRDFmodel(char *filename);
void getRDFmodel_EntityInfo(char *filename, char *subject_query, char *predicate_query);
