#include <sstream>
#include <string>
#include <iostream>
#include <sbml/SBMLTypes.h>
#include <sbml/common/extern.h>
#include <sbml/xml/XMLNode.h>
#include <sbml/annotation/CVTerm.h>
#include <sbml/annotation/ModelHistory.h>
#include "util.h"


#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>
#include <libxml/xpath.h>

using namespace std;

LIBSBML_CPP_NAMESPACE_USE

#ifndef LIBSEMGEN_SBML_H
#define LIBSEMGEN_SBML_H

#endif //LIBSEMGEN_SBML_H

void sbml_hello();
void printModel();
void printModel(char* filename);
void printSBMLModelMath(char* filename);
void updateSpeciesID(char *old_filename, char *new_filename, char *old_sid, char *new_sId);
void getSBMLAnnotation(char* filename);
