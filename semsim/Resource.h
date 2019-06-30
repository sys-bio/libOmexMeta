# ifndef SEMSIM_RESOURCE_H_
# define SEMSIM_RESOURCE_H_

# include "semsim/Preproc.h"
# include "semsim/URI.h"

namespace semsim {

    /**
     * A resource is an ontology term (forms
     * the "object" part of an RDF triple).
     * Example:
     *
     * @code
     * // identifies the cytosolic compartment of a cell
     * Resource myresource("https://identifiers.org/GO:0005829");
     * @endcode
     */
    class SEMSIM_PUBLIC Resource {
      public:
        /**
         * Construct from URI.
         * @param uri The URI of the resource
         */
        Resource(const URI& uri)
          : uri_(uri) {}

        # if __cplusplus >= 201103L
        /**
         * Move-construct from URI.
         * @param uri The URI of the resource
         */
        Resource(URI&& uri)
          : uri_(std::move(uri)) {}
        # endif

        /**
         * Construct directly from the UTF-8 string-encoded URI.
         * @param uri The UTF-8 string-encoded URI of the resource
         */
        // Resource(const std::string& uri)
        //   : uri_(uri) {}

        # if __cplusplus >= 201103L
        /**
         * Move-construct directly from the UTF-8 string-encoded URI.
         * @param uri The UTF-8 string-encoded URI of the resource
         */
        // Resource(std::string&& uri)
        //   : uri_(std::move(uri)) {}
        # endif

      protected:
        URI uri_;
    };
}
# endif
