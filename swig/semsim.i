%module semgen

%{
#define SWIG_FILE_WITH_INIT
#include "semsim/SemSim.h"
%}

// C++ std::string handling
%include "std_string.i"

// C++ std::map handling
%include "std_map.i"

// C++ std::vector handling
%include "std_vector.i"

%include "std_list.i"

//enables better handling of STL exceptions
%include "exception.i"

%include "std_shared_ptr.i"

%include "semsim/Preproc.h"

%ignore semsim::AnnotationBase::makeComposite;
%rename (makeComposite) semsim::AnnotationBase::makeComposite_;

%extend semsim::AnnotationBase {
  AnnotationBase* makeComposite_(const PhysicalProperty& prop) {
    return ($self)->makeComposite(prop).release();
    // return new semsim::CompositeAnnotation(*($self), prop);
  }
}

//%typemap(out) AnnotationBase& Component::getAnnotation {
    //$result = SWIG_NewPointerObj(SWIG_as_voidptr($1), SWIGTYPE_p_semsim__CompositeAnnotation, $owner);
//}

%ignore semsim::SBMLModel::SBMLModel(SBMLDocument*);
%ignore semsim::SBMLModel::setComponentAnnotation;
%ignore semsim::SBMLModel::hasComponent;
%ignore semsim::SBMLModel::getComponent;

%ignore semsim::SBMLImporter::SBMLImporter(SBMLDocument*);
%ignore semsim::SBMLImporter::getRelationFromSBMLQual;

%ignore semsim::stripAnnotationsFromElement;
%ignore semsim::stripAnnotations;

%rename (bqb_wrapper) semsim::bqb;

%include "semsim/Preproc.h"
%include "semsim/util/UniquePtr.h"
%include "semsim/URI.h"
%include "semsim/Relation.h"
%include "semsim/Resource.h"
%include "semsim/Term.h"
%include "semsim/DescriptorTerm.h"
%include "semsim/EntityBase.h"
%include "semsim/PhysicalProperty.h"
%include "semsim/AnnotationBase.h"
%include "semsim/SingularAnnotation.h"
%include "semsim/EntityDescriptor.h"
%include "semsim/Entity.h"
%include "semsim/CompositeAnnotation.h"
%include "semsim/Component.h"
%include "semsim/Model.h"
%include "semsim/sbml/SBMLModel.h"
%include "semsim/sbml/SBMLImporter.h"

%include "biomodels_quals.i"

%include "semsim/Ontology.h"
%include "semsim/ontologies/CHEBI.h"
%include "semsim/ontologies/OPB.h"
%include "semsim/ontologies/GO.h"
%include "semsim/ontologies/CL.h"

%include "semsim/omex/OmexOutput.h"

%include "semsim/SemSim.h"
