# ifndef SEMSIM_OPB_H_
# define SEMSIM_OPB_H_

# include "semsim/Preproc.h"
# include "semsim/Ontology.h"
# include "semsim/PhysicalProperty.h"

namespace semsim {
    /**
     * Class for the <a href="http://bioportal.bioontology.org/ontologies/OPB">Ontology of Physics for Biology</a>.
     * Holds static members that represent terms.
     */
    class SEMSIM_PUBLIC OPB : public Ontology {
      public:
        SEMSIM_CONSTEXPR static std::string root = "http://identifiers.org/opb/OPB_";

        static Resource get(const OntologyTerm& t) {
          return resolve(root, t, 5);
        }

        SEMSIM_CONSTEXPR static Resource fluid_volume = get(154);
    };
}

# endif
