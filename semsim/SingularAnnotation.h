# ifndef SEMSIM_SINGULAR_ANNOTATION_H_
# define SEMSIM_SINGULAR_ANNOTATION_H_

# include "semsim/Preproc.h"
# include "semsim/AnnotationBase.h"
# include "semsim/PhysicalProperty.h"
# include "semsim/Entity.h"

namespace semsim {
    /**
     * The singular / "plain" annotation class is designed to represent
     * traditional CV term annotations found in SBML models.
     * These types of annotations are not as expressive
     * as @ref CompositeAnnotation "CompositeAnnotations"
     * and can only point to one or more @ref Resource "Resources"
     * which define the entity.
     * Overusing definition URIs is generally bad practice and,
     * ideally, one should use a single definition URI that best
     * captures the model element.
     */
    class SEMSIM_PUBLIC SingularAnnotation {
      public:
        /// The type used to store the list of definition URIs
        typedef std::vector<Resource> Definitions;
        /**
         * Construct a SingularAnnotation given a definition URL.
         * For example, to create an annotation describing pyruvate:
         *
         * \code{.cpp}
         * # include "semsim/SemSim.h"
         * using namespace semsim;
         * // will automatically get assigned a "bqb:is" relation
         * // pointing to CHEBI:15361
         * SingularAnnotation a(CHEBI::get(15361));
         * \endcode
         *
         * Generally, a model element should be defined using
         * only a single URI.
         */
        SingularAnnotation(const Resource& definition)
          : definitions_(1,definition) {}

        # if __cplusplus >= 201103L
        /// Move-construct from an @ref EntityDescriptor
        SingularAnnotation(Resource&& definition)
          : definitions_({std::move(definition)}) {}
        # endif

        /// Get the number of @ref EntityDescriptor elements contained in this @ref Entity.
        std::size_t getNumDefinitions() const {
          return definitions_.size();
        }

        /// Get the definition at index @p k.
        const Resource& getDefinition(std::size_t k) const {
          return definitions_.at(k);
        }

        /**
         * Get an iterable range of definitions.
         * Treat the return type as opaque, as it may change
         * to some other iterable in a future release.
         *
         * @return An iterable of @ref Resource "Resources".
         */
        const Definitions& getDefinitions() const {
          return definitions_;
        }

        /**
         * Get an iterable range of definitions.
         * Treat the return type as opaque, as it may change
         * to some other iterable in a future release.
         *
         * @return An iterable of @ref Resource "Resources".
         */
        Definitions& getDefinitions() {
          return definitions_;
        }

        /**
         * Add a definition to this annotation.
         */
        void addDefinition(const Resource& definition) {
          definitions_.push_back(definition);
        }

      protected:
        /// Collection of definition URIs for this annotation
        Definitions definitions_;
    };
}

# endif
