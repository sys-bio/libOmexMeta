# ifndef SEMSIM_ANNOTATION_BASE_H_
# define SEMSIM_ANNOTATION_BASE_H_

# include "semsim/Preproc.h"
# include "semsim/util/UniquePtr.h"
# include "semsim/PhysicalProperty.h"

# include <raptor2.h>

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

        /**
         * Serialize this annotation to RDF using the Raptor library.
         * The RDF serialization format is chosen when initializing the
         * @c raptor_serializer, and must be done before calling this function.
         * @param sbml_base_uri   The base URI of the SBML document relative to this (e.g. a relative path in a COMBINE archive).
         * @param world      Raptor world object. Must be initialized prior to calling this function.
         * @param serializer Raptor serializer object. Must be initialized prior to calling this function.
         */
        virtual void serializeToRDF(const URI& sbml_base_uri, raptor_world* world, raptor_serializer* serializer) const = 0;

        virtual std::string getRDF(const URI& sbml_base_uri, const std::string& format="rdfxml") const = 0;

        /// Get the meta id for this element
        virtual const std::string& getMetaId() const = 0;

        /**
         * Convert singular annotations to composite annotations
         * by copying their definitions and terms.
         * @param prop The physical property to assign to the composite annotation.
         * @return A new composite annotation
         */
        virtual UniquePtr<AnnotationBase>::type makeComposite(const PhysicalProperty& prop) const = 0;

        /**
         * Return a human--readable representation of the annotation
         * information. Ontology terms will be replaced with human-readable
         * names.
         */
        virtual std::string humanize() const = 0;

        virtual bool isComposite() const = 0;

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
