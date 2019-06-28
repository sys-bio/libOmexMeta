# ifndef SEMSIM_OPB_H_
# define SEMSIM_OPB_H_

# include "semsim/Preproc.h"
# include "semsim/PhysicalProperty.h"

namespace semsim {
    /// Numeric type used to represent an ontology term (e.g. 5623 in https://identifiers.org/GO:0005623).
    typedef OntologyTerm unsigned int;

    /**
     * Class for the Ontology of Physics in Biology.
     * Holds static members that represent terms.
     */
    SEMSIM_PUBLIC class OPB : public Ontology {
      protected:
        static Resource resolve(const std::string& root, const OntologyTerm& t, int n_digits) {
          std::stringstream ss;
          ss << root << t;
          return  Resource(ss.str());
        }
    };
}

# endif
