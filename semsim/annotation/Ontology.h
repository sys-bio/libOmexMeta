# ifndef SEMSIM_ONTOLOGY_H_
# define SEMSIM_ONTOLOGY_H_

# include "semsim/definitions/ReferenceOntologies.h"
# include <string>
# include <vector>

namespace semsim {
    /**
     * Class representing identifier information about an ontology.
     * This includes the ontology's full name, BioPortal namespace,
     * textual description, etc.
     */
    class Ontology {
      private:
        std::string fullname_;
        std::string abbrev_;
        std::string bioportal_ns_;
        Namespaces namespaces_ = std::vector<std::string>();
        std::string description_;

      public:
        typedef std::vector<std::string> Namespaces;

        /**
         * Main constructor.
         * @param name Full name of ontology
         * @param abbrev Nickname of ontology
         * @param ns Array of namespaces used for this ontology
         * @param description Textual description of ontology
         * @param bpns BioPortal namespace of the ontology
         */
        Ontology(const std::string& name,
                 const std::string& abbrev,
                 const Namespaces& namespaces,
                 const std::string& description,
                 const std::string& bioportal_ns);

        /**
         * Constructor without BioPortal info.
         * @param name Full name of ontology
         * @param abrev Nickname of ontology
         * @param ns Array of namespaces used for this ontology
         * @param description Textual description of ontology
         */
        Ontology(const std::string& name,
                 const std::string& abrev,
                 const Namespaces& namespaces,
                 const std::string& description);

        /**
         * Constructor for creating an {@link Ontology} class
         * from a {@link ReferenceOntology} class
         * @param ro The {@link ReferenceOntology} that will have
         * its information copied to this class.
         */
        // use copy constructor
        // Ontology(ReferenceOntology ro);

        /**
         * @param nspace Namespace to test for association with the ontology
         * @return Whether the namespace is in the array of namespaces associated
         * with this ontology
         */
        virtual bool hasNamespace(const std::string& nspace) const;

        /**
         * @return Full name of ontology
         */
        virtual const std::string& getFullName() const;

        /**
         * @return Abbreviated name of ontology
         */
        virtual const std::string& getAbbreviation() const;

        /**
         * @return The BioPortal namespace of the ontology
         */
        virtual const std::string& getBioPortalNamespace() const;

        /**
         * @return The set of namespaces associated with the ontology
         */
        // virtual std::vector<std::string> getNamespaces();

        /**
         * @return A free-text description of the ontology
         */
        virtual const std::string& getDescription() const;
    };
}

# endif
