# ifndef SEMSIM_ONTOLOGY_H_
# define SEMSIM_ONTOLOGY_H_

# include "semsim/Preproc.h"
# include "semsim/PhysicalProperty.h"

namespace semsim {
    /// Numeric type used to represent an ontology term (e.g. 5623 in https://identifiers.org/GO:0005623).
    typedef unsigned int OntologyTerm;

    /**
     * Base class for all ontologies.
     */
    class SEMSIM_PUBLIC Ontology {
      public:
        /**
         * Given a root URI (usually from identifiers.org), a numeric term, and the
         * number of digits used in URIs, this function returns the correct **full**
         * URI for the resource.
         * @param  root     The root URI of the ontology (using identifiers.org if available).
         * @param  t        The numeric value of the ontology term.
         * @param  n_digits The number of digits in the URI format of the ontology term.
         * @return          The correct full URI for the resource in the ontology.
         */
        static Resource resolve(const std::string& root, OntologyTerm t, int n_digits) {
          std::stringstream ss;
          ss << root << std::setfill('0') << std::setw(n_digits) << t;
          return  Resource(ss.str());
        }
    };
}

# endif
