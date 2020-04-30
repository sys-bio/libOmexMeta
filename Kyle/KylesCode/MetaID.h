# ifndef SEMSIM_SBML_METAIDS_H_
# define SEMSIM_SBML_METAIDS_H_


#include <unordered_map>
# include "third_party/libsbml-5.18.0/INSTALL/include/sbml/SBMLTypes.h"


namespace semsim {
    class MetaID {
        libsbml::Model &m;

    public:
        explicit MetaID(libsbml::Model &m) : m(m) {}

        MetaID() = default;

        /**
         * Check whether the model contains a given meta id.
         * @param  m      The SBML model.
         * @param  metaid The meta id to check for.
         * @return        @c true if the model contains the given meta id.
         */

        bool contains(std::string &metaid) {
            // compartments
            for (unsigned int k = 0; k < m.getNumCompartments(); ++k) {
                libsbml::Compartment *x = m.getCompartment(k);
                if (x->isSetMetaId() && x->getMetaId() == metaid)
                    return true;
            }

            // species
            for (unsigned int k = 0; k < m.getNumSpecies(); ++k) {
                libsbml::Species *x = m.getSpecies(k);
                if (x->isSetMetaId() && x->getMetaId() == metaid)
                    return true;
            }

            // reactions
            for (unsigned int k = 0; k < m.getNumReactions(); ++k) {
                libsbml::Reaction *x = m.getReaction(k);
                if (x->isSetMetaId() && x->getMetaId() == metaid)
                    return true;
            }

            // parameters
            for (unsigned int k = 0; k < m.getNumParameters(); ++k) {
                libsbml::Parameter *x = m.getParameter(k);
                if (x->isSetMetaId() && x->getMetaId() == metaid)
                    return true;
            }

            // events
            for (unsigned int k = 0; k < m.getNumEvents(); ++k) {
                libsbml::Event *x = m.getEvent(k);
                if (x->isSetMetaId() && x->getMetaId() == metaid)
                    return true;
            }
            return m.getElementByMetaId(metaid) != nullptr;
        }

        /**
         * Assign meta ids to all annotatable elements of the model
         * that currently lack them. libSemSim requires all annotatable
         * elements to have assigned meta ids.
         * @param m [description]
         */
        void assignMetaIds() {
            for (unsigned int k = 0; k < m.getNumCompartments(); ++k) {
                // get handle to component
                libsbml::Compartment *c = m.getCompartment(k);
                // if the metaid attribute is not set
                if (!c->isSetMetaId()) {
                    // we iterate indefinately
                    for (int j = 0;; ++j) {
                        std::stringstream ss;
                        ss << "compartment" << j;
                        // we check for existence of id. If not
                        // we add the metaid and break out of the
                        // for loop, adding the id to the list
                        // of ids searched for by contains.
                        if (!contains(ss.str())) {
                            c->setMetaId(ss.str());
                            break;
                        }
                    }
                }
            }
            for (unsigned int k = 0; k < m.getNumSpecies(); ++k) {
                libsbml::Species *s = m.getSpecies(k);
                if (!s->isSetMetaId()) {
                    for (int j = 0;; ++j) {
                        std::stringstream ss;
                        ss << "species" << j;
                        if (!contains(ss.str())) {
                            s->setMetaId(ss.str());
                            break;
                        }
                    }
                }
            }
            for (unsigned int k = 0; k < m.getNumReactions(); ++k) {
                libsbml::Reaction *r = m.getReaction(k);
                if (!r->isSetMetaId()) {
                    for (int j = 0;; ++j) {
                        std::stringstream ss;
                        ss << "reaction" << j;
                        if (!contains(ss.str())) {
                            r->setMetaId(ss.str());
                            break;
                        }
                    }
                }
            }
        }

        /**
         * Get meta ids for all annotatable elements of the model.
         * @param m [description]
         */
        std::unordered_map<libsbml::SBase *, std::string *> getMetaIds() {
            std::unordered_map<libsbml::SBase *, std::string *> metaIdMap;

            for (unsigned int k = 0; k < m.getNumCompartments(); ++k) {
                libsbml::Compartment *c = m.getCompartment(k);
                if (c->isSetMetaId()) {
                    metaIdMap[c] = &c->getMetaId();
                } else {
                    metaIdMap[c] = nullptr;
                }
            }
            for (unsigned int k = 0; k < m.getNumSpecies(); ++k) {
                libsbml::Species *s = m.getSpecies(k);
                if (s->isSetMetaId()) {
                    metaIdMap[s] = &s->getMetaId();
                } else {
                    metaIdMap[s] = nullptr;
                }
            }

            for (unsigned int k = 0; k < m.getNumReactions(); ++k) {
                libsbml::Reaction *r = m.getReaction(k);
                if (r->isSetMetaId()) {
                    metaIdMap[r] = &r->getMetaId();
                } else {
                    metaIdMap[r] = nullptr;
                }
            }
            for (unsigned int k = 0; k < m.getNumEvents(); ++k) {
                libsbml::Event *e = m.getEvent(k);
                if (e->isSetMetaId()) {
                    metaIdMap[e] = &e->getMetaId();
                } else {
                    metaIdMap[e] = nullptr;
                }
            }
            for (unsigned int k = 0; k < m.getNumParameters(); ++k) {
                libsbml::Parameter *p = m.getParameter(k);
                if (p->isSetMetaId()) {
                    metaIdMap[p] = &p->getMetaId();
                } else {
                    metaIdMap[p] = nullptr;
                }
            }

            return metaIdMap;
        }

        /*
         * returns true when all annotatable elements
         * have an id. If 1 or more elements do not
         * have a metaid, return false.
         */
        bool hasMetaIds() {
            for (auto it: getMetaIds()) {
                if (!it.second)
                    return false;
            }
            return true;
        }
    };
}

# endif
