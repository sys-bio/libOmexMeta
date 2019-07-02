# ifndef SEMSIM_SINGULAR_ANNOTATION_H_
# define SEMSIM_SINGULAR_ANNOTATION_H_

# include "semsim/Preproc.h"
# include "semsim/AnnotationBase.h"
# include "semsim/PhysicalProperty.h"
# include "semsim/EntityBase.h"
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
    class SEMSIM_PUBLIC SingularAnnotation : public AnnotationBase, public EntityBase {
      public:
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
          : EntityBase(definition) {}

        /// Empty constructor
        SingularAnnotation() {}

        # if __cplusplus >= 201103L
        /// Move-construct from an @ref EntityDescriptor
        SingularAnnotation(Resource&& definition)
          : EntityBase({std::move(definition)}) {}
        # endif

        /// Copy constructor
        SingularAnnotation(const SingularAnnotation& other)
          :EntityBase(other) {}

        # if __cplusplus >= 201103L
        /// Move constructor
        SingularAnnotation(SingularAnnotation&& other)
          :EntityBase(std::move(other)) {}
        # endif

        /// Create a copy of this object using the correct derived class's type.
        virtual AnnotationBase* clone() const {
          return new SingularAnnotation(*this);
        }
    };
}

# endif
