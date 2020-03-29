# ifndef SEMSIM_SBML_ANNOTATIONS_H_
# define SEMSIM_SBML_ANNOTATIONS_H_

# include "Preproc.h"

# include "../third_party/libsbml-5.18.0/INSTALL/include/sbml/SBMLTypes.h"

namespace semsim {

    class Annotation {
    public:
        /**
         * Strip CV terms and SBO terms from an SBML element.
         * @param x The SBML element.
         */
        static inline void stripAnnotationsFromElement(libsbml::SBase *x) {
            if (x->unsetCVTerms() != libsbml::LIBSBML_OPERATION_SUCCESS)
                throw std::runtime_error("Unable to clear CV terms");
            if (x->unsetSBOTerm() != libsbml::LIBSBML_OPERATION_SUCCESS)
                throw std::runtime_error("Unable to clear SBO term");
        }

        /**
         * Strip CV terms and SBO terms from an SBML document in-place.
         * @param d The SBML document.
         */
        static inline void stripAnnotations(libsbml::SBMLDocument *d) {
            libsbml::Model *m = d->getModel();
            stripAnnotationsFromElement(m);
            for (unsigned int k = 0; k < m->getNumCompartments(); ++k) {
                libsbml::Compartment *x = m->getCompartment(k);
                stripAnnotationsFromElement(x);
            }
            for (unsigned int k = 0; k < m->getNumSpecies(); ++k) {
                libsbml::Species *x = m->getSpecies(k);
                stripAnnotationsFromElement(x);
            }
            for (unsigned int k = 0; k < m->getNumReactions(); ++k) {
                libsbml::Reaction *x = m->getReaction(k);
                stripAnnotationsFromElement(x);
            }
            for (unsigned int k = 0; k < m->getNumEvents(); ++k) {
                libsbml::Event *x = m->getEvent(k);
                stripAnnotationsFromElement(x);
            }
            for (unsigned int k = 0; k < m->getNumFunctionDefinitions(); ++k) {
                libsbml::FunctionDefinition *x = m->getFunctionDefinition(k);
                stripAnnotationsFromElement(x);
            }
            for (unsigned int k = 0; k < m->getNumParameters(); ++k) {
                libsbml::Parameter *x = m->getParameter(k);
                stripAnnotationsFromElement(x);
            }

            for (unsigned int k = 0; k < m->getNumRules(); ++k) {
                libsbml::Rule *x = m->getRule(k);
                stripAnnotationsFromElement(x);
            }
            for (unsigned int k = 0; k < m->getNumUnitDefinitions(); ++k) {
                libsbml::UnitDefinition *x = m->getUnitDefinition(k);
                stripAnnotationsFromElement(x);
            }
        }
    };
}
# endif
