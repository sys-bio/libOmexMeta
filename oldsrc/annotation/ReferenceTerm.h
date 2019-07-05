# ifndef SEMSIM_REFERENCE_TERM_H_
# define SEMSIM_REFERENCE_TERM_H_
# include <string>

namespace semsim {
    /**
     * Interface for physical model classes that are defined against
     * controlled knowledge resource terms.
     *
     *
     */
    class ReferenceTerm {

        /**
         * @param semsimlib A SemSimLibrary instance
         * @return The first {@link ReferenceOntologyAnnotation} found applied to this object
         * that uses an identity relation (e.g., SemSimConstants.HAS_PHYSICAL_DEFINITION_RELATION). */
      public:
        // ReferenceOntologyAnnotation getPhysicalDefinitionReferenceOntologyAnnotation(SemSimLibrary* semsimlib) = 0;
        //
        // /** @return The reference URI */
        // virtual URI* getPhysicalDefinitionURI() = 0;
        //
        // /** @return True if an object has at least one {@link ReferenceOntologyAnnotation}, otherwise false */
        // virtual std::optional<bool> hasPhysicalDefinitionAnnotation() = 0;
        //
        // /** @return The ReferenceTerm's name */
        // virtual std::string getName() = 0;
        //
        // /**
        //  * @param semsimlib A SemSimLibrary instance
        //  * @return The ReferenceTerm's name suffixed with an abbreviation for the ontology containing it */
        // virtual std::string getNamewithOntologyAbreviation(SemSimLibrary* semsimlib) = 0;
        //
        // /** @param semsimlib A SemSimLibrary instance
        //  * @return The name of the ontology containing the ReferenceTerm */
        // virtual std::string getOntologyName(SemSimLibrary* semsimlib) = 0;
        //
        // /** @return The URI of the ReferenceTerm as a string */
        // virtual std::string getTermFragment() = 0;
        //
        // /** @return The description of the ReferenceTerm */
        // virtual std::string getDescription() = 0;
    };
}

# endif
