#include "Ontology.h"

namespace semsim {
    namespace annotation {
        using ReferenceOntology = semsim::definitions::ReferenceOntologies::ReferenceOntology;

        Ontology::Ontology(const std::string& name,
                           const std::string& abrev,
                           std::vector<std::string>& namespaces,
                           const std::string& description,
                           const std::string& bioportal_ns)
            : fullname_(fullname),
              abbrev_(abbrev),
              namespaces_(namespaces),
              description_(description),
              bioportal_ns_(bioportal_ns)
        {}

        Ontology::Ontology(const std::string& name,
                           const std::string& abrev,
                           std::vector<std::string>& namespaces,
                           const std::string& description)
            : fullname_(fullname),
              abbrev_(abbrev),
              namespaces_(namespaces),
              description_(description)
        {}

        bool Ontology::hasNamespace(const std::string& nspace) {
            for (Namespaces::const_iterator i=namespaces_.begin(); i!=namespaces_.end(); ++i) {
                if (*i == ns)
                    return true;
            }
            return false;
        }

        std::string Ontology::getFullName() {
            return std::string(fullname_);
        }

        std::string Ontology::getNickName() {
            return std::string(abbrev_);
        }

        std::string Ontology::getBioPortalNamespace() {
            return bioportal_ns_;
        }

        // std::vector<std::string> Ontology::getNameSpaces() {
        //     return namespaces_;
        // }

        std::string Ontology::getDescription() {
            return description_;
        }
    }
}
