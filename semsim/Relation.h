# ifndef SEMSIM_RELATION_H_
# define SEMSIM_RELATION_H_

# include "semsim/Preproc.h"
# include "semsim/URI.h"

namespace semsim {

    /**
     * A resource is an ontology term that forms
     * the "object" part of an RDF triple.
     */
    SEMSIM_PUBLIC class Relation {
      public:
        /**
         * Construct from URI.
         * @param uri The URI of the ontology term
         */
        Resource(const URI& uri)
          : uri_(uri) {}

        # if __cplusplus >= 201103L
        DomainDescriptor(URI&& uri)
          : uri_(std::move(uri)) {}
        # endif

      protected:
        URI uri_;
    };
}
# endif
