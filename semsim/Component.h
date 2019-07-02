# ifndef SEMSIM_COMPONENT_H_
# define SEMSIM_COMPONENT_H_

# include "semsim/Preproc.h"
# include "semsim/AnnotationBase.h"
# include "semsim/SingularAnnotation.h"
# include "semsim/CompositeAnnotation.h"

# include <string>

namespace semsim {

    /**
     * A @ref Component is any element of an SBML or CellML model.
     * It can represent an SBML species, reaction, or compartment.
     */
    class SEMSIM_PUBLIC Component {
      public:
        // Construct from a singular annotation
        Component(const SingularAnnotation& annotation)
          : annotation_(new SingularAnnotation(annotation)) {}

        # if __cplusplus >= 201103L
        // Move-construct from a singular annotation
        Component(SingularAnnotation&& annotation)
          : annotation_(new SingularAnnotation(std::move(annotation))) {}
        # endif

        // Construct from a composite annotation
        Component(const CompositeAnnotation& annotation)
          : annotation_(new CompositeAnnotation(annotation)) {}

        # if __cplusplus >= 201103L
        // Move-construct from a composite annotation
        Component(CompositeAnnotation&& annotation)
          : annotation_(new CompositeAnnotation(std::move(annotation))) {}
        # endif

        Component(const Component& other)
          : annotation_(other.getAnnotation().clone()) {}

        /**
         * Get this component's annotation.
         * The component may have a singular or composite annotation,
         * but it will be returned as a pointer to the base
         * class for annotations.
         */
        const AnnotationBase& getAnnotation() const {
          return *annotation_;
        }

      /**
       * Get this component's annotation.
       * The component may have a singular or composite annotation,
       * but it will be returned as a pointer to the base
       * class for annotations.
       */
      AnnotationBase& getAnnotation() {
        return *annotation_;
      }

      protected:
        AnnotationPtr annotation_;
    };

}

# endif
