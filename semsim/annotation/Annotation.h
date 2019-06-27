// DEPRECATED
# ifndef SEMSIM_ANNOTATION_H_
# define SEMSIM_ANNOTATION_H_

# include <string>
# include "semsim/annotation/Relation.h"
# include "semsim/annotation/Resource.h"

namespace semsim {
    /**
     * A SemSim annotation provides additional information about
     * a SemSim model or one of its elements. Annotations can be used
     * to define the physical meaning of a SemSim model or model element,
     * identify model authors, link a model to its PubMed ID, etc.
     */
    class Annotationx {
      protected:
        Relation relation_;
        Resource resource_;
        std::string valueDescription_;


      public:
        /// Virtual destructor for base classes
        virtual ~Annotation() {}

        /**
         * Constructor without a free-text description of the annotation.
         * @param relation Indicates the relationship between the object being annotated
         * and the annotation value
         * @param value The annotation value
         */
        Annotation(const Relation& relation, const Resource& value);

        /**
         * Constructor that includes a free-text description of the annotation.
         * @param relation Indicates the relationship between the object being annotated
         * and the annotation value
         * @param value The annotation value
         * @param valueDescription A free-text description of the annotation value
         */
        Annotation(const Relation& relation, const Resource& value, const std::string& valueDescription);

        /**
         * Constructor for copying an Annotation
         * @param tocopy The Annotation to copy
         */
        // Annotation(const Annotation& tocopy);

        /**
         * Set the free-text description for the annotation value
         * @param valueDescription The free-text description
         */
        void setValueDescription(const std::string& valueDescription);

        /**
         * @return The free-text description of the annotation value
         */
        const std::string& getValueDescription() const;

        /**
         * Set the relationship between the object being annotated and the annotation value
         * @param relation The relation (AKA predicate, qualifier) between the object being annotated and the annotation value
         */
        void setRelation(const Relation& relation);

        /** @return The relationship between the object being annotated and the annotation value */
        const Relation& getRelation() const;

        /**
         * Set the annotation value
         * @param value The annotation value
         */
        void setResource(const Resource& value);

        /**
         * @return The annotation value
         */
        const Resource& getResource() const;
    };
}

# endif
