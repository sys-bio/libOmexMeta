#include "../definitions/ReferenceOntologies.h"
#include <string>
#include <vector>

namespace semsim {
    namespace definitions {
        class ReferenceOntologies;
    }
}

namespace semsim {
    namespace annotation {


        using ReferenceOntology = semsim::definitions::ReferenceOntologies::ReferenceOntology;

        /**
         * Class representing identifier information about an ontology.
         * This includes the ontology's full name, BioPortal namespace,
         * textual description, etc.
         */
        class Ontology {
          private:
            std::string fullname;
            std::string nickname;
            std::string bioportalnamespace;
            std::vector<std::string> namespaces = std::vector<std::string>();
            std::string description;

          public:
            /**
             * Main constructor.
             * @param name Full name of ontology
             * @param abbrev Nickname of ontology
             * @param ns Array of namespaces used for this ontology
             * @param desc Textual description of ontology
             * @param bpns BioPortal namespace of the ontology
             */
            Ontology(const std::string& name, const std::string& abbrev, std::vector<std::string>& ns, const std::string& desc, const std::string& bpns);

            /**
             * Constructor without BioPortal info.
             * @param name Full name of ontology
             * @param abrev Nickname of ontology
             * @param ns Array of namespaces used for this ontology
             * @param desc Textual description of ontology
             */
            Ontology(const std::string& name, const std::string& abrev, std::vector<std::string>& ns, const std::string& desc);

            /**
             * Constructor for creating an {@link Ontology} class
             * from a {@link ReferenceOntology} class
             * @param ro The {@link ReferenceOntology} that will have
             * its information copied to this class.
             */
            Ontology(ReferenceOntology ro);

            /**
             * @param nspace Namespace to test for association with the ontology
             * @return Whether the namespace is in the array of namespaces associated
             * with this ontology
             */
            virtual bool hasNamespace(const std::string& nspace);

            /**
             * @return Full name of ontology
             */
            virtual std::string getFullName();

            /**
             * @return Abbreviated name of ontology
             */
            virtual std::string getAbbreviation();

            /**
             * @return The BioPortal namespace of the ontology
             */
            virtual std::string getBioPortalNamespace();

            /**
             * @return The set of namespaces associated with the ontology
             */
            virtual std::vector<std::string> getNamespaces();

            /**
             * @return A free-text description of the ontology
             */
            virtual std::string getDescription();
        };

    }
}
