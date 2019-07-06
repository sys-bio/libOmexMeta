# ifndef SEMSIM_SBML_SPECIES_H_
# define SEMSIM_SBML_SPECIES_H_

# include "semsim/Preproc.h"
# include "semsim/ontologies/OPB.h"
# include "semsim/sbml/Accessors.h"

# include "sbml/SBMLTypes.h"

namespace semsim {

    /**
     * Return @c true if the UnitDefinition is concentration-based,
     * @c false otherwise.
     */
    bool UnitDefIsConc(
      LIBSBML_CPP_NAMESPACE_QUALIFIER UnitDefinition* ud) {
      if (ud->getNumUnits() != 2)
        return false;
      int n_mass=0;
      int d_vol =0;
      for(unsigned int k=0; k<ud->getNumUnits(); ++k) {
        LIBSBML_CPP_NAMESPACE_QUALIFIER Unit* u = ud->getUnit(k);
        if ((!u->isSetExponent() || u->getExponent() == 1) &&
            (u->isMole() || u->isGram() || u->isKilogram() || u->isItem()))
          n_mass++;
        if ((u->isSetExponent() && u->getExponent() == -1) &&
            (u->isLitre()))
          d_vol++;
        if ((u->isSetExponent() && u->getExponent() == -3) &&
            u->isMetre())
          d_vol++;
      }
      return n_mass == 1 && d_vol == 1;
    }

    /**
     * Return true if the SBML UnitDefinition for the
     * "substanceUnits" of this species are concentration-based.
     * Return false if the units are not concentration-based
     * or a deduction cannot be made.
     */
    bool SubstanceUnitsAreConc(
      LIBSBML_CPP_NAMESPACE_QUALIFIER Species* s,
      LIBSBML_CPP_NAMESPACE_QUALIFIER Model* m) {
      try {
        if (s->isSetUnits()) {
          LIBSBML_CPP_NAMESPACE_QUALIFIER UnitDefinition* u = findUnitDefinition(s->getUnits(), m);
          return UnitDefIsConc(u);
        }
      } catch (std::out_of_range) {
        // unit def was not found - SBML is invalid
        return false;
      }
      return false;
    }

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
     * @li If "substanceUnits" is set to "kilgram", "gram", "mole", or "item", the physical property will be *mass*. If the "substanceUnits" are set to a unit defintion in terms of mass/volume, the physical property will be *concentration*.
     *
     * If none of these rules matches, a @c std::domain_error is thrown.
     */
    PhysicalProperty GetSpeciesPhysicalProperty(
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
      else if (s->isSetSubstanceUnits() && SubstanceUnitsAreConc(s, m))
        return PhysicalProperty(OPB::get(425));
      else
        throw std::domain_error("Could not deduce PhysicalProperty");
    }

}

# endif
