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
        /// Empty constructor
        Component() {}

        /// Construct from a singular annotation
        Component(const SingularAnnotation& annotation)
          : annotation_(new SingularAnnotation(annotation)) {}

        # if __cplusplus >= 201103L
        /// Move-construct from a singular annotation
        Component(SingularAnnotation&& annotation)
          : annotation_(new SingularAnnotation(std::move(annotation))) {}
        # endif

        /// Construct from a composite annotation
        Component(const CompositeAnnotation& annotation)
          : annotation_(new CompositeAnnotation(annotation)) {}

        # if __cplusplus >= 201103L
        /// Move-construct from a composite annotation
        Component(CompositeAnnotation&& annotation)
          : annotation_(new CompositeAnnotation(std::move(annotation))) {}
        # endif

        Component(const Component& other)
          : annotation_(other.hasAnnotation() ? other.getAnnotation().clone() : NULL) {}

        # if __cplusplus >= 201103L
        /// Move-construct from a composite annotation
        Component(Component&& other)
          : annotation_(std::move(other.annotation_)) {}
        # endif

        bool hasAnnotation() const {
          return !!annotation_;
        }

        /**
         * Get this component's annotation.
         * The component may have a singular or composite annotation,
         * but it will be returned as a pointer to the base
         * class for annotations.
         */
        const AnnotationBase& getAnnotation() const {
          if (!annotation_)
            throw std::runtime_error("No annotation set");
          return *annotation_;
        }

      /**
       * Get this component's annotation.
       * The component may have a singular or composite annotation,
       * but it will be returned as a pointer to the base
       * class for annotations.
       */
      AnnotationBase& getAnnotation() {
        if (!annotation_)
          throw std::runtime_error("No annotation set");
        return *annotation_;
      }

      /**
       * Manually set the annotation (from a raw pointer).
       * This @ref Component will own the passed raw pointer.
       * If the @ref Component currently has an annotation set,
       * it will be freed.
       * @param annotation The annotation for this @ref Component to own.
       */
      void setAnnotation(AnnotationBase* annotation) {
        annotation_.reset(annotation);
      }

      /**
       * Manually set the annotation (copy the passed annotation).
       * If the @ref Component currently has an annotation set,
       * it will be freed.
       * @param annotation The annotation for this @ref Component to own.
       */
      void setAnnotation(const AnnotationBase& annotation) {
        annotation_.reset(annotation.clone());
      }

      # if __cplusplus >= 201103L
      /**
       * Manually set the annotation.
       * If the @ref Object currently has an annotation set,
       * it will be freed.
       * @param annotation The annotation for this @ref Object to own.
       */
      void setAnnotation(AnnotationPtr&& annotation) {
        annotation_ = std::move(annotation);
      }
      # endif

      protected:
        AnnotationPtr annotation_;
    };

    /**
     * An owning pointer for a @ref Component.
     * Automatically uses std::unique_ptr or std::tr1::shared_ptr depending on C++ standard.
     * @see UniquePtr.
     */
    typedef UniquePtr<Component>::type ComponentPtr;

}

# endif
