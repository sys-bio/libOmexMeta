# ifndef SEMSIM_RESOURCE_H_
# define SEMSIM_RESOURCE_H_

# include <string>

namespace semsim {

    /**
     * A resource is an ontology term that forms
     * the "object" part of an RDF triple.
     */
    class Resource {
      public:
        /**
         * Construct from URI.
         * @param uri The URI of the ontology term
         */
        Resource(const URI& uri)
            : uri_(uri) {}

      protected:
        URI uri_;
    };
}
# endif
