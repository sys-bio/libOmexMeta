# ifndef SEMSIM_H_
# define SEMSIM_H_

// important classes (includes may be redundant - that's okay)
# include "semsim/Preproc.h"
# include "semsim/Relation.h"
# include "semsim/Resource.h"
# include "semsim/EntityBase.h"
# include "semsim/Entity.h"
# include "semsim/PhysicalProperty.h"
# include "semsim/SingularAnnotation.h"
# include "semsim/CompositeAnnotation.h"
# include "semsim/Component.h"
# include "semsim/Model.h"
# include "semsim/sbml/SBMLModel.h"
# include "semsim/sbml/SBMLImporter.h"

# include "semsim/BiomodelsQualifiers.h"
// # include "semsim/SemSimObject.h"

# include "semsim/Ontology.h"
# include "semsim/ontologies/CHEBI.h"
# include "semsim/ontologies/OPB.h"
# include "semsim/ontologies/GO.h"
# include "semsim/ontologies/CL.h"

# include "semsim/omex/OmexOutput.h"

SEMSIM_PUBLIC void libsemgen_hello();
// void cellml_hello();
// void sbml_hello();
// void printModel();
// void printModel(char* filename);
// void printSBMLModelMath(char* filename);
// void updateSpeciesID(char *old_filename, char *new_filename, char *old_sid, char *new_sId);
// void getSBMLAnnotation(char* filename);
// void readOMEX(char *OMEXfilename, char *model_rdf, char *model_sbml);
// void addOMEX(char* path, char* filename);
// void getXMLelements(char *SBMLfilename);
// void notSure(char *filename);
// void getXPATHnamespace(char *filename, char *query);
// void parseXPATH(char *filename, char *query, char *nslist);
// void getAllEntities_RDF(char *filename);
// void getAllEntities_SBML(char *filename);
// void getInfo_SBML(char *filename, char *id);
// void getInfo_RDF(char *filename, char *id);
// void getRDFmodel(char *filename);
// void getRDFmodel_EntityInfo(char *filename, char *subject_query, char *predicate_query);

# endif
