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
<<<<<<< HEAD
        static inline bool modelContainsMetaId(libsbml:: Model *m, const std::string &metaid) {
            for (unsigned int k = 0; k < m->getNumSpecies(); ++k) {
                libsbml:: Compartment *x = m->getCompartment(k);
=======
        static inline bool modelContainsMetaId(libsbml::Model *m, const std::string &metaid) {
            for (unsigned int k = 0; k < m->getNumSpecies(); ++k) {
                libsbml::Compartment *x = m->getCompartment(k);
>>>>>>> ciaran-develop
                if (x->isSetMetaId() && x->getMetaId() == metaid)
                    return true;
            }
            for (unsigned int k = 0; k < m->getNumSpecies(); ++k) {
<<<<<<< HEAD
                libsbml:: Species *x = m->getSpecies(k);
=======
                libsbml::Species *x = m->getSpecies(k);
>>>>>>> ciaran-develop
                if (x->isSetMetaId() && x->getMetaId() == metaid)
                    return true;
            }
            for (unsigned int k = 0; k < m->getNumReactions(); ++k) {
<<<<<<< HEAD
                libsbml:: Reaction *x = m->getReaction(k);
=======
                libsbml::Reaction *x = m->getReaction(k);
>>>>>>> ciaran-develop
                if (x->isSetMetaId() && x->getMetaId() == metaid)
                    return true;
            }
            for (unsigned int k = 0; k < m->getNumParameters(); ++k) {
<<<<<<< HEAD
                libsbml:: Parameter *x = m->getParameter(k);
=======
                libsbml::Parameter *x = m->getParameter(k);
>>>>>>> ciaran-develop
                if (x->isSetMetaId() && x->getMetaId() == metaid)
                    return true;
            }
            for (unsigned int k = 0; k < m->getNumEvents(); ++k) {
<<<<<<< HEAD
                libsbml:: Event *x = m->getEvent(k);
=======
                libsbml::Event *x = m->getEvent(k);
>>>>>>> ciaran-develop
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
<<<<<<< HEAD
        static inline void assignMetaIds(libsbml:: Model *m) {
            for (unsigned int k = 0; k < m->getNumCompartments(); ++k) {
                libsbml:: Compartment *c = m->getCompartment(k);
=======
        static inline void assignMetaIds(libsbml::Model *m) {
            for (unsigned int k = 0; k < m->getNumCompartments(); ++k) {
                libsbml::Compartment *c = m->getCompartment(k);
>>>>>>> ciaran-develop
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
<<<<<<< HEAD
                libsbml:: Species *s = m->getSpecies(k);
=======
                libsbml::Species *s = m->getSpecies(k);
>>>>>>> ciaran-develop
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
<<<<<<< HEAD
                libsbml:: Reaction *r = m->getReaction(k);
=======
                libsbml::Reaction *r = m->getReaction(k);
>>>>>>> ciaran-develop
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
