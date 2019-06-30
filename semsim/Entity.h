# ifndef SEMSIM_ENTITY_H_
# define SEMSIM_ENTITY_H_

# include "semsim/Preproc.h"
# include "semsim/EntityDescriptor.h"

# include <string>

namespace semsim {

    /**
     * An @ref Entity is one of the two parts of a composite annotation.
     * The entity describes "what" a model element is and "where" it
     * is located in the physical world through a linear chain of descriptor terms
     * contained in the @ref EntityDescriptor element.
     *
     * An @ref Entity contains one or more *definition terms* (i.e. ontology resource URIs)
     * that define what the entity is.
     * A valid definition term could be <a href="https://identifiers.org/CHEBI:17234">CHEBI:17234</a>, which represents glucose
     * (in the case of a chemical reaction network model) or
     * <a href="http://identifiers.org/fma/FMA:9670">FMA:9670</a>, which represents blood
     * (in the case of a physiological model).
     *
     * An @ref Entity also has @ref EntityDescriptor "EntityDescriptors", which
     * serve to refine the entity by e.g. describing "where" it is in the physical world.
     * Currently, an @ref Entity can have zero or one @ref EntityDescriptor elements.
     * In the future, this may be extended to allow multiple @ref EntityDescriptor elements.
     */
    class SEMSIM_PUBLIC Entity {
      public:
        typedef std::vector<EntityDescriptor> Descriptors;

        /// Default constructor - initialize to empty
        Entity() {}

        /// Construct from an @ref EntityDescriptor
        Entity(const EntityDescriptor& d)
          : descriptors_(1,d) {}

        # if __cplusplus >= 201103L
        /// Move-construct from an @ref EntityDescriptor
        Entity(EntityDescriptor&& d)
          : descriptors_({std::move(d)}) {}
        # endif

        /// Get the number of @ref EntityDescriptor elements contained in this @ref Entity.
        std::size_t getNumDescriptors() const {
          return descriptors_.size();
        }

        /**
         * Get an iterable range of entity descriptors.
         * Treat the return type as opaque, as it may change
         * to some other iterable in a future release.
         *
         * @code
         * Entity e();
         * // C++11 range-based for
         * for(const EntityDescriptor& d : e.getDescriptors()) {
         *   // do something with d
         * }
         * @endcode
         * @return An iterable range of contained @ref EntityDescriptor elements.
         */
        const Descriptors& getDescriptors() const {
          return descriptors_;
        }

        /**
         * Get an iterable range of entity descriptors.
         * Treat the return type as opaque, as it may change
         * to some other iterable in a future release.
         *
         * @code
         * Entity e();
         * // C++11 range-based for
         * for(const EntityDescriptor& d : e.getDescriptors()) {
         *   // do something with d
         * }
         * @endcode
         * @return An iterable range of contained @ref EntityDescriptor elements.
         */
        Descriptors& getDescriptors() {
          return descriptors_;
        }

        /// Get the @ref EntityDescriptor at index @p k.
        const EntityDescriptor& getDescriptor(std::size_t k) const {
          return descriptors_.at(k);
        }

        /// Get the @ref EntityDescriptor reference at index @p k.
        EntityDescriptor& getDescriptor(std::size_t k) {
          return descriptors_.at(k);
        }

        /// @return Whether this @ref Entity is empty (i.e. has no descriptors) or not.
        bool isEmpty() const {
          return !descriptors_.size();
        }

      protected:
        Descriptors descriptors_;
    };

}

# endif
