# ifndef SEMSIM_ANNOTATABLE_H_
# define SEMSIM_ANNOTATABLE_H_

# include <string>
# include <set>

namespace semsim {
    namespace annotation {
        class Annotation;
    }
}

namespace semsim {
    /**
     * Interface providing methods for annotating
     * SemSim model elements.
     *
     */
    class Annotatable {
        /** @return All SemSim Annotations applied to this object */
      public:
        typedef set<Annotation> Annotations;

        virtual const Annotations&* getAnnotations() = 0;
        /**
         * Set the SemSim Annotations for an object
         * @param annset The set of annotations to apply
         */
        virtual void setAnnotations(const Annotations& annset) = 0;
        /**
         * Add a SemSim {@link Annotation} to this object
         * @param ann The {@link Annotation} to add (will be copied).
         */
        virtual void addAnnotation(const Annotation& ann) = 0;

        /**
         * Add a SemSim {@link ReferenceOntologyAnnotation} to an object
         *
         * @param relation The {@link SemSimRelation} that qualifies the
         * relationship between the object and what it's annotated against
         * @param uri The URI of the reference ontology term used for
         * annotation
         * @param description A free-text description of the reference
         * ontology term (obtained from the ontology itself whenever possible).
         * @param lib A SemSimLibrary instance
         */
        // virtual void addReferenceOntologyAnnotation(Relation *relation, URI *uri, const std::wstring &description, SemSimLibrary *lib) = 0;
        /**
         * Get all SemSim {@link ReferenceOntologyAnnotation}s applied to an object
         * that use a specific {@link SemSimRelation}.
         * @param relation The {@link SemSimRelation} that filters the annotations
         * to return
         * @return All SemSim {@link ReferenceOntologyAnnotation}s applied to an object
         * that use the specified {@link SemSimRelation}.
         */
        // virtual Set<ReferenceOntologyAnnotation*> *getReferenceOntologyAnnotations(Relation *relation) = 0;
        /**
         * Delete all {@link ReferenceOntologyAnnotation}s applied to this object
         */
        // virtual void removeAllReferenceAnnotations() = 0;
        /**
         * @return True if an object has at least one {@link Annotation}, otherwise false.
         */
        bool isAnnotated() = 0;


        /**
         * @return True if an object has at least one {@link ReferenceOntologyAnnotation}, otherwise false;
         */
        bool hasPhysicalDefinitionAnnotation() = 0;
    };

}
