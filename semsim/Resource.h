# ifndef SEMSIM_RESOURCE_H_
# define SEMSIM_RESOURCE_H_


# include "semsim/url.h"

# include <stdexcept>
#include <utility>

// todo consider breaking Resource functionality up into internal and external (single responsibility principle SRP)

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
        explicit Resource(const std::string &url)
                : url_(Url(url)), element_(nullptr) {}

        /*
         * copy constructor
         */
        Resource(const Resource &resource) {
            if (this != &resource) {
                this->url_ = resource.url_;
                this->element_ = resource.element_;
            }
        }

        /*
         * move constructor
         */
        Resource(Resource &&resource) noexcept {
            if (this != &resource) {
                this->url_ = std::move(resource.url_);
                this->element_ = resource.element_;
            }
        }

        /*
         * copy assignment operator
         */
        Resource &operator=(const Resource &resource) {
            if (this != &resource) {
                this->url_ = resource.url_;
                this->element_ = resource.element_;
            }
            return *this;
        }

        /*
         * move assignment operator
         */
        Resource &operator=(Resource &&resource) noexcept {
            if (this != &resource) {
                this->url_ = resource.url_;
                this->element_ = resource.element_;
            }
            return *this;
        }

        /**
         * Construct from element.
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

        Component* getElement(){
            return element_;
        }

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

        friend std::ostream &operator<<(std::ostream &os, Resource &resource);

    protected:
        /// A URI (for external resources)
        Url url_;
        /// A weak pointer to an element in the model (set for internal / local resources)
        Component *element_;
    };
}
# endif
