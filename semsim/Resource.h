# ifndef SEMSIM_RESOURCE_H_
# define SEMSIM_RESOURCE_H_


# include "semsim/url.h"

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
     * A @ref Resource can also point to an element of the @ref SemsimModel
     * (an *internal resource*, useful in @ref CompositeAnnotation "CompositeAnnotations"),
     * in which case its definition URI will be whatever the element's
     * URI is at the time of serialization.
     */
    class  Resource {
    public:
        /**
         * Construct from URI.
         * @param uri The URI of the resource
         */
        Resource(const Url &url)
                : url_(url), element_(nullptr) {}


        /**
         * Move-construct from URI.
         * @param uri The URI of the resource
         */
        Resource(Url &&uri)
                : url_(std::move(uri)), element_(nullptr) {}


        /**
         * Construct from URI.
         * @param uri The URI of the resource
         */
        Resource(Component *element)
                : element_(element) {}

        std::string toString() const {
            return url_.str();
        }

        /**
         * Get a string representing the (possibly local) URI for this resource.
         * @param base If this resource points to a local @ref Component, this parameter should be the relative path of the SBML document. Otherwise, the default value should be used.
         * @return The URI for this resource.
         */
        Url getURI(Url base = Url()) const;

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
        bool operator==(const Resource &other) const {
            if (!isLocal() && !other.isLocal())
                return url_.str() == other.url_.str();
            else if (isLocal() && other.isLocal())
                return element_ == other.element_;
            else
                return false;
        }

    protected:
        /// A URI (for external resources)
        Url url_;
        /// A weak pointer to an element in the model (set for internal / local resources)
        Component *element_;
    };
}
# endif
