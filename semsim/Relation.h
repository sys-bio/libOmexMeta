# ifndef SEMSIM_RELATION_H_
# define SEMSIM_RELATION_H_

# include "semsim/Preproc.h"
# include "semsim/URI.h"

namespace semsim {

    /**
     * A relation is the predicate part of an RDF triple.
     * SemSim uses the
     * <a href="http://co.mbine.org/standards/qualifiers">BioModels biology qualifiers</a>
     * for describing model elements.
     */
    class SEMSIM_PUBLIC Relation {
      public:
        /**
         * Construct from URI.
         * @param uri The URI of the ontology term
         */
        Relation(const URI& uri)
          : uri_(uri) {}

        # if __cplusplus >= 201103L
        Relation(URI&& uri)
          : uri_(std::move(uri)) {}
        # endif

      protected:
        URI uri_;
    };
}
# endif
