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
        SEMSIM_CONSTEXPR static std::string root = "http://identifiers.org/CHEBI:";

        static Resource get(const OntologyTerm& t) {
          return resolve(root, t, 5);
        }
    };
}

# endif
