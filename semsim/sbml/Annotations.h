# ifndef SEMSIM_SBML_ANNOTATIONS_H_
# define SEMSIM_SBML_ANNOTATIONS_H_

# include "semsim/Preproc.h"

# include "sbml/SBMLTypes.h"

namespace semsim {
    /**
     * Strip CV terms and SBO terms from an SBML element.
     * @param x The SBML element.
     */
    inline void stripAnnotationsFromElement(LIBSBML_CPP_NAMESPACE_QUALIFIER SBase* x) {
      if (x->unsetCVTerms() != LIBSBML_CPP_NAMESPACE_QUALIFIER LIBSBML_OPERATION_SUCCESS)
        throw std::runtime_error("Unable to clear CV terms");
      if (x->unsetSBOTerm() != LIBSBML_CPP_NAMESPACE_QUALIFIER LIBSBML_OPERATION_SUCCESS)
        throw std::runtime_error("Unable to clear SBO term");
    }

    /**
     * Strip CV terms and SBO terms from an SBML document in-place.
     * @param d The SBML document.
     */
    inline void stripAnnotations(LIBSBML_CPP_NAMESPACE_QUALIFIER SBMLDocument* d) {
      LIBSBML_CPP_NAMESPACE_QUALIFIER Model* m = d->getModel();
      stripAnnotationsFromElement(m);
      for(unsigned int k=0; k<m->getNumCompartments(); ++k) {
        LIBSBML_CPP_NAMESPACE_QUALIFIER Compartment* x = m->getCompartment(k);
        stripAnnotationsFromElement(x);
      }
      for(unsigned int k=0; k<m->getNumSpecies(); ++k) {
        LIBSBML_CPP_NAMESPACE_QUALIFIER Species* x = m->getSpecies(k);
        stripAnnotationsFromElement(x);
      }
      for(unsigned int k=0; k<m->getNumReactions(); ++k) {
        LIBSBML_CPP_NAMESPACE_QUALIFIER Reaction* x = m->getReaction(k);
        stripAnnotationsFromElement(x);
      }
      for(unsigned int k=0; k<m->getNumEvents(); ++k) {
        LIBSBML_CPP_NAMESPACE_QUALIFIER Event* x = m->getEvent(k);
        stripAnnotationsFromElement(x);
      }
      for(unsigned int k=0; k<m->getNumFunctionDefinitions(); ++k) {
        LIBSBML_CPP_NAMESPACE_QUALIFIER FunctionDefinition* x = m->getFunctionDefinition(k);
        stripAnnotationsFromElement(x);
      }
      for(unsigned int k=0; k<m->getNumParameters(); ++k) {
        LIBSBML_CPP_NAMESPACE_QUALIFIER Parameter* x = m->getParameter(k);
        stripAnnotationsFromElement(x);
      }
      for(unsigned int k=0; k<m->getNumParameters(); ++k) {
        LIBSBML_CPP_NAMESPACE_QUALIFIER Parameter* x = m->getParameter(k);
        stripAnnotationsFromElement(x);
      }
      for(unsigned int k=0; k<m->getNumRules(); ++k) {
        LIBSBML_CPP_NAMESPACE_QUALIFIER Rule* x = m->getRule(k);
        stripAnnotationsFromElement(x);
      }
      for(unsigned int k=0; k<m->getNumUnitDefinitions(); ++k) {
        LIBSBML_CPP_NAMESPACE_QUALIFIER UnitDefinition* x = m->getUnitDefinition(k);
        stripAnnotationsFromElement(x);
      }
    }
}
# endif
