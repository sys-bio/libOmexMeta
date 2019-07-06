# ifndef SEMSIM_SBML_ACCESSORS_H_
# define SEMSIM_SBML_ACCESSORS_H_

# include "semsim/Preproc.h"
# include "semsim/ontologies/OPB.h"

# include "sbml/SBMLTypes.h"

namespace semsim {
    /// Find a UnitDefinition from a given sid; throw if not found
    inline LIBSBML_CPP_NAMESPACE_QUALIFIER UnitDefinition* findUnitDefinition(
      const std::string& sid,
      LIBSBML_CPP_NAMESPACE_QUALIFIER Model* m) {
      for (unsigned int k=0; k<m->getNumUnitDefinitions(); ++k) {
        LIBSBML_CPP_NAMESPACE_QUALIFIER UnitDefinition* u = m->getUnitDefinition(k);
        if (u->isSetIdAttribute() && u->getId() == sid)
          return u;
      }
      throw new std::out_of_range("No such UnitDefinition");
    }

    /// Find a Compartment from a given sid; throw if not found
    inline LIBSBML_CPP_NAMESPACE_QUALIFIER Compartment* findCompartment(
      const std::string& sid,
      LIBSBML_CPP_NAMESPACE_QUALIFIER Model* m) {
      for (unsigned int k=0; k<m->getNumCompartments(); ++k) {
        LIBSBML_CPP_NAMESPACE_QUALIFIER Compartment* c = m->getCompartment(k);
        if (c->isSetIdAttribute() && c->getId() == sid)
          return c;
      }
      throw new std::out_of_range("No such UnitDefinition");
    }
}
# endif
