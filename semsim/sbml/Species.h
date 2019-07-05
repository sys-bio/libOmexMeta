# ifndef SEMSIM_SBML_SPECIES_H_
# define SEMSIM_SBML_SPECIES_H_

# include "semsim/Preproc.h"
# include "semsim/ontologies/OPB.h"

# include "sbml/SBMLTypes.h"

namespace semsim {

    /**
     * Try to deduce the @ref PhysicalProperty(amount or concentration)
     * from an SBML species.
     * There are two possible deductions:
     * @li A *mass-based qualtity* (https://identifiers.org/opb/OPB_01389, "mass" hereafter)
     * @li A *concentration-based quantity* (https://identifiers.org/opb/OPB_00425, "concentration" hereafter)
     *
     * The deduction is made using the following rules:
     * @li Is "hasOnlySubstanceUnits" set? If it is @c true, the physical property will be *mass*. If it is @c false, it will be *concentration*.
     * @li Is "initialAmount" or "initialConcentration" set? If so, the physical property will be *mass* or *concentration* resp. If they are both set (not valid SBML), skip to the next rule.
     * @li If "substanceUnits" is set to "kilgram", "gram", "mole", or "item", the physical property will be *mass*.
     *
     * If none of these rules matches, a @c std::domain_error is thrown.
     */
    PhysicalProperty SpeciesUnitsToPhysicalProperty(
      LIBSBML_CPP_NAMESPACE_QUALIFIER Species* s,
      LIBSBML_CPP_NAMESPACE_QUALIFIER Model* m) {
      if (s->isSetHasOnlySubstanceUnits() && s->getHasOnlySubstanceUnits())
        return PhysicalProperty(OPB::get(1389));
      if (s->isSetHasOnlySubstanceUnits() && !s->getHasOnlySubstanceUnits())
        return PhysicalProperty(OPB::get(425));
      else if ( s->isSetInitialAmount() && !s->isSetInitialConcentration())
        return PhysicalProperty(OPB::get(1389));
      else if (!s->isSetInitialAmount() &&  s->isSetInitialConcentration())
        return PhysicalProperty(OPB::get(425));
      else if (
        s->isSetSubstanceUnits() && (
        s->getSubstanceUnits() == "kilgram" ||
        s->getSubstanceUnits() == "gram" ||
        s->getSubstanceUnits() == "mole" ||
        s->getSubstanceUnits() == "item"))
        return PhysicalProperty(OPB::get(1389));
      else
        throw std::domain_error("Could not deduce PhysicalProperty");
    }

}

# endif
