# ifndef SEMSIM_CHEBI_H_
# define SEMSIM_CHEBI_H_

# include "semsim/Preproc.h"
# include "semsim/Ontology.h"
# include "semsim/PhysicalProperty.h"

namespace semsim {
    /**
     * Class for the Chemical Entities of Biological Interest (<a href="https://www.ebi.ac.uk/chebi/">CHEBI</a>) database.
     */
    class SEMSIM_PUBLIC CHEBI : public Ontology {
      public:
        // const static std::string root = "http://identifiers.org/CHEBI:";

        /**
         * Get the full URI of an ontology term given its numeric value.
         * @param  t The numeric value of the ontology term.
         * @return   The correct full URI for the resource in ChEBI.
         *
         * @code{.cpp}
         * // returns "https://identifiers.org/CHEBI:17234" (glucose)
         * Resource r = CHEBI::get(17234);
         * @endcode
         */
        static Resource get(OntologyTerm t) {
          return resolve("https://identifiers.org/CHEBI:", t, 5);
        }
    };
}

# endif
