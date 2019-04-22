#include <string>
using namespace std;


void libsemgen_hello();
void cellml_hello();
void sbml_hello();
void printModel();
void printModel(char* filename);
void printSBMLModelMath(char* filename);
void updateSpeciesID(char *old_filename, char *new_filename, char *old_sid, char *new_sId);
void getSBMLAnnotation(char* filename);