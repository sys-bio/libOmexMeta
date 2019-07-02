# ifndef SEMSIM_ANNOTATION_BASE_H_
# define SEMSIM_ANNOTATION_BASE_H_

# include "semsim/Preproc.h"
# include "semsim/util/UniquePtr.h"

namespace semsim {
    /**
     * The base class for annotations.
     */
    class SEMSIM_PUBLIC AnnotationBase {
      public:
        /// Virtual destructor
        virtual ~AnnotationBase() {}

        /**
         * Create a copy of this object using the correct derived class's type.
         * The object's type will depend on the runtime type of the callee,
         * but will be returned as a pointer to the base class @ref AnnotationBase.
         */
        virtual AnnotationBase* clone() const = 0;

      protected:
    };

    /**
     * An owning pointer for any annotation class
     * (either @ref CompositeAnnotation or @ref SingularAnnotation).
     * @see UniquePtr.
     */
    typedef UniquePtr<AnnotationBase>::type AnnotationPtr;
}

# endif
