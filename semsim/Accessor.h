# ifndef SEMSIM_SBML_ACCESSORS_H_
# define SEMSIM_SBML_ACCESSORS_H_

# include "Preproc.h"
# include "../third_party/libsbml-5.18.0/INSTALL/include/sbml/SBMLTypes.h"

namespace semsim {

    class Accessor {
    public:
        /// Find a UnitDefinition from a given sid; throw if not found
        static libsbml:: UnitDefinition *findUnitDefinition(
                const std::string &sid,
                libsbml::Model *m) {
            for (unsigned int k = 0; k < m->getNumUnitDefinitions(); ++k) {
                libsbml:: UnitDefinition *u = m->getUnitDefinition(k);
                if (u->isSetIdAttribute() && u->getId() == sid)
                    return u;
            }
            throw std::out_of_range("No such UnitDefinition");
        }

        /// Find a Compartment from a given sid; throw if not found
        static libsbml:: Compartment *findCompartment(
                const std::string &sid,
                libsbml:: Model *m) {
            for (unsigned int k = 0; k < m->getNumCompartments(); ++k) {
                libsbml:: Compartment *c = m->getCompartment(k);
                if (c->isSetIdAttribute() && c->getId() == sid)
                    return c;
            }
            throw new std::out_of_range("No such Compartment");
        }

        /// @return @c true if a compartment with the specified meta id exists
        static  bool hasCompartmentWithMetaId(
                const std::string &metaid,
                libsbml:: Model *m) {
            for (unsigned int k = 0; k < m->getNumCompartments(); ++k) {
                libsbml:: Compartment *c = m->getCompartment(k);
                if (c->isSetMetaId() && c->getMetaId() == metaid)
                    return true;
            }
            return false;
        }
    };
}
# endif
