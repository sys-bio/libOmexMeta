# ifndef SEMSIM_RESOURCE_H_
# define SEMSIM_RESOURCE_H_

# include "semsim/Preproc.h"
# include "semsim/URI.h"

# include <stdexcept>

namespace semsim {
    class Component;

    /**
     * A @ref Resource is an ontology term (
     * the "object" part of an RDF triple).
     * This is an *external resource*.
     * Example:
     *
     * @code{.cpp}
     * // identifies the cytosolic compartment of a cell
     * Resource myresource("https://identifiers.org/GO:0005829");
     * @endcode
     *
     * A @ref Resource can also point to an element of the @ref Model
     * (an *internal resource*, useful in @ref CompositeAnnotation "CompositeAnnotations"),
     * in which case its definition URI will be whatever the element's
     * URI is at the time of serialization.
     */
    class SEMSIM_PUBLIC Resource {
      public:
        /**
         * Construct from URI.
         * @param uri The URI of the resource
         */
        Resource(const URI& uri)
          : uri_(uri), element_(NULL) {}

        # if __cplusplus >= 201103L
        /**
         * Move-construct from URI.
         * @param uri The URI of the resource
         */
        Resource(URI&& uri)
          : uri_(std::move(uri)), element_(NULL) {}
        # endif

        /**
         * Construct from URI.
         * @param uri The URI of the resource
         */
        Resource(Component* element)
          : element_(element) {}

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

        std::string toString() const {
          return uri_.toString();
        }

        /**
         * Get a string representing the (possibly local) URI for this resource.
         * @param base If this resource points to a local @ref Component, this parameter should be the relative path of the SBML document. Otherwise, the default value should be used.
         * @return The URI for this resource.
         */
        URI getURI(const URI& base=URI()) const;

        /**
         * @return @c true if this resource points to a local @ref Component
         * (as opposed to an external URI).
         */
        bool isLocal() const {
          return element_;
        }

        /**
         * Return a human--readable representation of the annotation
         * information. Ontology terms will be replaced with human-readable
         * names.
         */
        std::string humanize() const;

        /**
         * Test whether this @ref Resource instance points to the same
         * object as the other @ref Resource instance.
         * @param other A @ref Resource instance to test against.
         * @return @c true if both instances point to the same object.
         */
        bool operator==(const Resource& other) const {
          if (!isLocal() && !other.isLocal())
            return uri_ == other.uri_;
          else if (isLocal() && other.isLocal())
            return element_ == other.element_;
          else
            return false;
        }

      protected:
        /// A URI (for external resources)
        URI uri_;
        /// A weak pointer to an element in the model (set for internal / local resources)
        Component* element_;
    };
}
# endif
