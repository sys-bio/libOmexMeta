# ifndef SEMSIM_RESOURCE_H_
# define SEMSIM_RESOURCE_H_


# include "semsim/url.h"

# include <stdexcept>
#include <utility>

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
    class Resource {
    public:
        /**
         * Construct from URI.
         * @param uri The URI of the resource
         */
        explicit Resource(Url url)
                : url_(std::move(url)), element_(nullptr) {}

        /**
         * Construct from string.
         * @param uri The URI of the resource
         */
        explicit Resource( std::string &url)
                : url_(Url(url)), element_(nullptr) {}


        /*
         * Copy constructor
         */
        Resource(Resource &resource);

        /*
         * Copy assignment constructor
         */
        Resource &operator=( Resource &resource);

        /*
         * Move constructor
         */
        Resource(Resource &&resource) noexcept ;

        /*
         * Move assignment constructor
         */
        Resource &operator=(Resource &&resource) noexcept ;

        /**
         * Construct from a Component*.
         * @param element
         */
        explicit Resource(Component *element)
                : element_(element) {}

        std::string toString()  {
            return url_.str();
        }

        /**
         * Get a string representing the (possibly local) URI for this resource.
         * @param base If this resource points to a local @ref Component, this parameter should be the relative path of the SBML document. Otherwise, the default value should be used.
         * @return The URI for this resource.
         */
        Url getURI(Url base = Url()) ;

        /**
         * @return @c true if this resource points to a local @ref Component
         * (as opposed to an external URI).
         */
        bool isLocal()  {
            return element_; //todo: why is this a boolean. Looks like a Component* to me!
        }

        /**
         * Return a human--readable representation of the annotation
         * information. Ontology terms will be replaced with human-readable
         * names.
         */
        std::string humanize() ;

                friend std::ostream &operator<<(std::ostream &os, Resource &resource);

        bool operator==( Resource &rhs) ;

        bool operator!=( Resource &rhs) ;

        /// A URI (for external resources)
        Url url_;
    protected:
        /// A weak pointer to an element in the model (set for internal / local resources)
        Component *element_;
    };
}
# endif
