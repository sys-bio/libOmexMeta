# ifndef SEMSIM_SBML_METAIDS_H_
# define SEMSIM_SBML_METAIDS_H_

# include "Preproc.h"

# include "../third_party/libsbml-5.18.0/INSTALL/include/sbml/SBMLTypes.h"


namespace semsim {
    class MetaID {
    public:
        /**
         * Check whether the model contains a given meta id.
         * @param  m      The SBML model.
         * @param  metaid The meta id to check for.
         * @return        @c true if the model contains the given meta id.
         */

        static inline bool modelContainsMetaId(libsbml::Model *m, const std::string &metaid) {
            for (unsigned int k = 0; k < m->getNumSpecies(); ++k) {
                libsbml::Compartment *x = m->getCompartment(k);
                if (x->isSetMetaId() && x->getMetaId() == metaid)
                    return true;
            }
            for (unsigned int k = 0; k < m->getNumSpecies(); ++k) {
                libsbml::Species *x = m->getSpecies(k);
                if (x->isSetMetaId() && x->getMetaId() == metaid)
                    return true;
            }
            for (unsigned int k = 0; k < m->getNumReactions(); ++k) {
                libsbml::Reaction *x = m->getReaction(k);
                if (x->isSetMetaId() && x->getMetaId() == metaid)
                    return true;
            }
            for (unsigned int k = 0; k < m->getNumParameters(); ++k) {
                libsbml::Parameter *x = m->getParameter(k);
                if (x->isSetMetaId() && x->getMetaId() == metaid)
                    return true;
            }
            for (unsigned int k = 0; k < m->getNumEvents(); ++k) {

                libsbml::Event *x = m->getEvent(k);
                if (x->isSetMetaId() && x->getMetaId() == metaid)
                    return true;
            }
            return m->getElementByMetaId(metaid) != NULL;
        }

        /**
         * Assign meta ids to all annotatable elements of the model
         * that currently lack them. libSemSim requires all annotatable
         * elements to have assigned meta ids.
         * @param m [description]
         */

        static inline void assignMetaIds(libsbml::Model *m) {
            for (unsigned int k = 0; k < m->getNumCompartments(); ++k) {
                libsbml::Compartment *c = m->getCompartment(k);
                if (!c->isSetMetaId()) {
                    for (int k = 0;; ++k) {
                        std::stringstream ss;
                        ss << "compartment" << k;
                        if (!modelContainsMetaId(m, ss.str())) {
                            c->setMetaId(ss.str());
                            break;
                        }
                    }
                }
            }
            for (unsigned int k = 0; k < m->getNumSpecies(); ++k) {
                libsbml::Species *s = m->getSpecies(k);
                if (!s->isSetMetaId()) {
                    for (int k = 0;; ++k) {
                        std::stringstream ss;
                        ss << "species" << k;
                        if (!modelContainsMetaId(m, ss.str())) {
                            s->setMetaId(ss.str());
                            break;
                        }
                    }
                }
            }
            for (unsigned int k = 0; k < m->getNumReactions(); ++k) {
                libsbml::Reaction *r = m->getReaction(k);
                if (!r->isSetMetaId()) {
                    for (int k = 0;; ++k) {
                        std::stringstream ss;
                        ss << "reaction" << k;
                        if (!modelContainsMetaId(m, ss.str())) {
                            r->setMetaId(ss.str());
                            break;
                        }
                    }
                }
            }
        }
    };
}
# endif
