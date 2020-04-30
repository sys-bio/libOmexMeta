# ifndef SEMSIM_SBO_H_
# define SEMSIM_SBO_H_


# include "Ontology.h"

namespace semsim {
    /**
     * Class for the <a href="http://bioportal.bioontology.org/ontologies/OPB">Ontology of Physics for Biology</a>.
     */
    class SBO : public Ontology {
    public:
        /**
         * Get the full URI of an ontology term given its numeric value.
         * @param  t The numeric value of the ontology term.
         * @return   The correct full URI for the resource in OPB.
         *
         * @code{.cpp}
         * // returns "https://identifiers.org/opb/OPB_00154" (fluid volume)
         * Resource r = OPB::get(154);
         * @endcode
         */
        static Resource get(OntologyTerm t) {
            return resolve("https://identifiers.org/sbo/SBO:", t, 7);
        }

    };
}

# endif
