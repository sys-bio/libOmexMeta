# ifndef SEMSIM_OPB_H_
# define SEMSIM_OPB_H_

# include "semsim/Preproc.h"
# include "semsim/Ontology.h"
# include "semsim/PhysicalProperty.h"

namespace semsim {
    /**
     * Class for the Ontology of Physics in Biology.
     * Holds static members that represent terms.
     */
    SEMSIM_PUBLIC class OPB : public Ontology {
      public:
        SEMSIM_CONSTEXPR static std::string root = "http://identifiers.org/opb/OPB_";

        static Resource get(const OntologyTerm& t) {
          return resolve(root, t, 5);
        }

        SEMSIM_CONSTEXPR static Resource fluid_volume = get(154);
    }
}

# endif
