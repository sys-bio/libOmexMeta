# ifndef SEMSIM_SBML_METAIDS_H_
# define SEMSIM_SBML_METAIDS_H_

# include "semsim/Preproc.h"

# include "sbml/SBMLTypes.h"

namespace semsim {

    /**
     * Check whether the model contains a given meta id.
     * @param  m      The SBML model.
     * @param  metaid The meta id to check for.
     * @return        @c true if the model contains the given meta id.
     */
    inline bool modelContainsMetaId(LIBSBML_CPP_NAMESPACE_QUALIFIER Model* m, const std::string& metaid) {
      for(unsigned int k=0; k<m->getNumSpecies(); ++k) {
        LIBSBML_CPP_NAMESPACE_QUALIFIER Compartment* x = m->getCompartment(k);
        if (x->isSetMetaId() && x->getMetaId() == metaid)
          return true;
      }
      for(unsigned int k=0; k<m->getNumSpecies(); ++k) {
        LIBSBML_CPP_NAMESPACE_QUALIFIER Species* x = m->getSpecies(k);
        if (x->isSetMetaId() && x->getMetaId() == metaid)
          return true;
      }
      for(unsigned int k=0; k<m->getNumReactions(); ++k) {
        LIBSBML_CPP_NAMESPACE_QUALIFIER Reaction* x = m->getReaction(k);
        if (x->isSetMetaId() && x->getMetaId() == metaid)
          return true;
      }
      for(unsigned int k=0; k<m->getNumParameters(); ++k) {
        LIBSBML_CPP_NAMESPACE_QUALIFIER Parameter* x = m->getParameter(k);
        if (x->isSetMetaId() && x->getMetaId() == metaid)
          return true;
      }
      for(unsigned int k=0; k<m->getNumEvents(); ++k) {
        LIBSBML_CPP_NAMESPACE_QUALIFIER Event* x = m->getEvent(k);
        if (x->isSetMetaId() && x->getMetaId() == metaid)
          return true;
      }
      return false;
    }

    /**
     * Assign meta ids to all annotatable elements of the model
     * that currently lack them. libSemSim requires all annotatable
     * elements to have assigned meta ids.
     * @param m [description]
     */
    inline void assignMetaIds(LIBSBML_CPP_NAMESPACE_QUALIFIER Model* m) {
      for(unsigned int k=0; k<m->getNumCompartments(); ++k) {
        LIBSBML_CPP_NAMESPACE_QUALIFIER Compartment* c = m->getCompartment(k);
        if (!c->isSetMetaId()) {
          for(int k=0;;++k) {
            std::stringstream ss;
            ss << "compartment" << k;
            if (!modelContainsMetaId(m, ss.str())) {
              c->setMetaId(ss.str());
              break;
            }
          }
        }
      }
      for(unsigned int k=0; k<m->getNumSpecies(); ++k) {
        LIBSBML_CPP_NAMESPACE_QUALIFIER Species* s = m->getSpecies(k);
        if (!s->isSetMetaId()) {
          for(int k=0;;++k) {
            std::stringstream ss;
            ss << "species" << k;
            if (!modelContainsMetaId(m, ss.str())) {
              s->setMetaId(ss.str());
              break;
            }
          }
        }
      }
    }

}

# endif
