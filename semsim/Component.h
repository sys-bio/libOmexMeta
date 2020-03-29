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
        explicit Component(const SingularAnnotation &annotation)
                : annotation_(new SingularAnnotation(annotation)) {}

        /// Move-construct from a singular annotation
        explicit Component(SingularAnnotation &&annotation)
                : annotation_(new SingularAnnotation(std::move(annotation))) {}

        /// Construct from a composite annotation
        explicit Component(const CompositeAnnotation &annotation)
                : annotation_(new CompositeAnnotation(annotation)) {}

        /// Move-construct from a composite annotation
        explicit Component(CompositeAnnotation &&annotation)
                : annotation_(new CompositeAnnotation(std::move(annotation))) {}

        Component(const Component &other)
                : annotation_(other.hasAnnotation() ? other.getAnnotation().clone() : nullptr) {}

        /// Move-construct from a component
        Component(Component &&other) noexcept : annotation_(std::move(other.annotation_)) {}

        /// Virtual destructor
        ~Component() = default;

        /// Create a copy of this component
        /// todo should this just be the copy constructor?
        virtual Component *clone() const {
            return new Component(*this);
        }

        /// @return @c true if the component has an annotation (singular or composite).
        bool hasAnnotation() const {
            return !!annotation_;
        }

        /// @return @c true if the component has a composite annotation
        bool hasCompositeAnnotation() const {
            return annotation_ && annotation_->isComposite();
        }

        /// @return @c true if the component has a singular annotation
        bool hasSingularAnnotation() const {
            return annotation_ && !annotation_->isComposite();
        }

        /**
         * Get this component's annotation.
         * The component may have a singular or composite annotation,
         * but it will be returned as a pointer to the base
         * class for annotations.
         */
        const AnnotationBase &getAnnotation() const {
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
        AnnotationBase &getAnnotation() {
            if (!annotation_)
                throw std::runtime_error("No annotation set");
            return *annotation_;
        }

        /**
         * Get this component's annotation and cast it
         * to a composite annotation.
         * It is an error to call this method unless
         * the component's annotation is a composite annotation.
         */
        const CompositeAnnotation &getCompositeAnnotation() const {
            if (!annotation_)
                throw std::runtime_error("No annotation set");
            if (!annotation_->isComposite())
                throw std::runtime_error("Annotation is not composite");
            return dynamic_cast<const CompositeAnnotation &>(*annotation_);
        }

        /**
         * Get this component's annotation and cast it
         * to a composite annotation.
         * It is an error to call this method unless
         * the component's annotation is a composite annotation.
         */
        CompositeAnnotation &getCompositeAnnotation() {
            if (!annotation_)
                throw std::runtime_error("No annotation set");
            if (!annotation_->isComposite())
                throw std::runtime_error("Annotation is not composite");
            return dynamic_cast<CompositeAnnotation &>(*annotation_);
        }

        /**
         * Manually set the annotation (from a raw pointer).
         * This @ref Component will own the passed raw pointer.
         * If the @ref Component currently has an annotation set,
         * it will be freed.
         * @param annotation The annotation for this @ref Component to own.
         */
        void setAnnotation(AnnotationBase *annotation) {
            annotation_.reset(annotation);
        }

        /**
         * Manually set the annotation (copy the passed annotation).
         * If the @ref Component currently has an annotation set,
         * it will be freed.
         * @param annotation The annotation for this @ref Component to own.
         */
        void setAnnotation(const AnnotationBase &annotation) {
            annotation_.reset(annotation.clone());
        }

        /**
         * Manually set the annotation.
         * If the @ref Object currently has an annotation set,
         * it will be freed.
         * @param annotation The annotation for this @ref Object to own.
         */
        void setAnnotation(AnnotationPtr &&annotation) {
            annotation_ = std::move(annotation);
        }

        /**
         * Return a human--readable representation of the annotation
         * information. Ontology terms will be replaced with human-readable
         * names.
         */
        std::string humanize() const {
            if (annotation_)
                return annotation_->humanize();
            else
                return "";
        }

        /// Return @c true if this component has a meta id (required for serialization).
        bool hasMetaId() const {
            if (annotation_)
                return true;
            else return !metaid_.empty();
        }

        /// Get the meta id of this component.
        const std::string &getMetaId() const {
            if (!metaid_.empty())
                return metaid_;
            else if (annotation_)
                return annotation_->getMetaId();
            else
                throw std::runtime_error("Meta id of component is not set.");
        }

        /// Set the meta id of this component.
        void setMetaId(const std::string &metaid) {
            metaid_ = metaid;
        }

        /// Get the local URI of this component
        virtual URI getURI(const URI &base) const {
            return base.withFrag(getMetaId());
        }

        /**
         * Serialize this annotation to RDF using the Raptor library.
         * @param sbml_base_uri   The base URI of the SBML document relative to this (e.g. a relative path in a COMBINE archive).
         * @param world      Raptor world object. Must be initialized prior to calling this function.
         * @param serializer Raptor serializer object. Must be initialized prior to calling this function.
         * @return the URI for this entity.
         */
        virtual void
        serializeToRDF(const URI &sbml_base_uri, raptor_world *world, raptor_serializer *serializer) const {
            if (annotation_)
                getAnnotation().serializeToRDF(sbml_base_uri, world, serializer);
        }

        virtual bool isProcess() const {
            return false;
        }

        virtual bool containsMetaId(const std::string &metaid) const {
            return metaid_ == metaid;
        }

        std::string getRDF(const URI &sbml_base_uri, const std::string &format = "rdfxml") const {
            if (hasAnnotation())
                return annotation_->getRDF(sbml_base_uri, format);
            else
                throw std::runtime_error("No annotation");
        }

    protected:
        AnnotationPtr annotation_;
        std::string metaid_;
    };

    /**
     * An owning pointer for a @ref Component.
     * Automatically uses std::unique_ptr or std::tr1::shared_ptr depending on C++ standard.
     * @see UniquePtr.
     */
    typedef std::unique_ptr<Component> ComponentPtr;

}

# endif
