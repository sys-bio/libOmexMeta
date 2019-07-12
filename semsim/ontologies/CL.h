# ifndef SEMSIM_CL_H_
# define SEMSIM_CL_H_

# include "semsim/Preproc.h"
# include "semsim/Ontology.h"
# include "semsim/PhysicalProperty.h"

namespace semsim {
    /**
     * Class for the Cell Ontology.
     */
    class SEMSIM_PUBLIC CL : public Ontology {
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
          return resolve("https://identifiers.org/CL:", t, 7);
        }
    };
}

# endif
