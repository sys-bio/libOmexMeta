# ifndef SEMSIM_ENTITY_H_
# define SEMSIM_ENTITY_H_

# include "semsim/Preproc.h"
# include "semsim/Resource.h"
# include "semsim/EntityBase.h"
# include "semsim/EntityDescriptor.h"
# include "semsim/SingularAnnotation.h"

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
     * SemSim allows multiple definition URIs, but it is general best practice
     * to annotate a model element with a single definition URI that best
     * captures the model element, i.e. a single ChEBI entity (for molecules)
     * or a single FMA entity (for physiological variables).
     *
     * An @ref Entity also has @ref EntityDescriptor "EntityDescriptors", which
     * serve to refine the entity by describing "where" it is in the physical world.
     * Currently, an @ref Entity can have zero or one @ref EntityDescriptor elements.
     * In the future, this may be extended to allow multiple @ref EntityDescriptor elements.
     */
    class SEMSIM_PUBLIC Entity : public EntityBase {
      public:
        /// The type used to store the list of entity descriptors. Treat as opaque.
        typedef std::vector<EntityDescriptor> Descriptors;

        /// Empty constructot
        Entity(const std::string& metaid) : EntityBase(metaid) {}

        /// Construct from a definition URI
        Entity(const std::string& metaid, const Resource& definition)
          : EntityBase(metaid, definition) {}

        /// Construct from an @ref EntityDescriptor
        Entity(const std::string& metaid, const Resource& definition, const EntityDescriptor& d)
          : EntityBase(metaid, definition), descriptors_(1,d) {}

        # if __cplusplus >= 201103L
        /// Move-construct from an @ref EntityDescriptor
        Entity(const std::string& metaid, Resource&& definition, EntityDescriptor&& d)
          : EntityBase(metaid, {std::move(definition)}), descriptors_({std::move(d)}) {}
        # endif

        /// Construct from a singular annotation. Copy all definitions and terms.
        Entity(const SingularAnnotation& annotation)
          : EntityBase(annotation) {}

        /// Get the number of @ref EntityDescriptor elements contained in this @ref Entity.
        std::size_t getNumDescriptors() const {
          return descriptors_.size();
        }

        /**
         * Get an iterable range of entity descriptors.
         * Treat the return type as opaque, as it may change
         * to some other iterable in a future release.
         *
         * @code{.cpp}
         * Entity e();
         * // C++11 range-based for
         * for(const EntityDescriptor& d : e.getDescriptors()) {
         *   // do something with d
         * }
         * @endcode
         * @return An iterable of @ref EntityDescriptor elements.
         */
        const Descriptors& getDescriptors() const {
          return descriptors_;
        }

        /**
         * Get an iterable range of entity descriptors.
         * Treat the return type as opaque, as it may change
         * to some other iterable in a future release.
         *
         * @code{.cpp}
         * Entity e();
         * // C++11 range-based for
         * for(const EntityDescriptor& d : e.getDescriptors()) {
         *   // do something with d
         * }
         * @endcode
         * @return An iterable of @ref EntityDescriptor elements.
         */
        Descriptors& getDescriptors() {
          return descriptors_;
        }

        /**
         * Add an @ref EntityDescriptor to this @ref Entity (copy).
         * @param d The descriptor to add.
         */
        void addDescriptor(const EntityDescriptor& d) {
          descriptors_.push_back(d);
        }

        # if __cplusplus >= 201103L
        /**
         * Add an @ref EntityDescriptor to this @ref Entity (move).
         * @param d The descriptor to add.
         */
        void addDescriptor(EntityDescriptor&& d) {
          descriptors_.emplace_back(std::move(d));
        }
        # endif

        /// Get the @ref EntityDescriptor at index @p k.
        const EntityDescriptor& getDescriptor(std::size_t k) const {
          return descriptors_.at(k);
        }

        /// Get the @ref EntityDescriptor reference at index @p k.
        EntityDescriptor& getDescriptor(std::size_t k) {
          return descriptors_.at(k);
        }

        /**
         * Serialize this entity to RDF using the Raptor library.
         * The RDF serialization format is chosen when initializing the
         * @c raptor_serializer, and must be done before calling this function.
         * @param base_uri   The base URI of this object (usually the metaid of the component this is attached to).
         * @param world      Raptor world object. Must be initialized prior to calling this function.
         * @param serializer Raptor serializer object. Must be initialized prior to calling this function.
         * @return the URI for this entity.
         */
        void serializeToRDF(const URI& sbml_base_uri, raptor_world* world, raptor_serializer* serializer) const {
          EntityBase::serializeToRDF(sbml_base_uri, world, serializer);
          for (Descriptors::const_iterator i(descriptors_.begin()); i!=descriptors_.end(); ++i)
            i->serializeToRDF(sbml_base_uri, metaid_, world, serializer);
        }

      protected:
        /// Stores all descriptors.
        Descriptors descriptors_;
    };

}

# endif
