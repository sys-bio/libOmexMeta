#include "Ontology.h"

namespace semsim {
    namespace annotation {
        using ReferenceOntology = semsim::definitions::ReferenceOntologies::ReferenceOntology;

        Ontology::Ontology(const std::string& name,
                           const std::string& abrev,
                           std::vector<std::string>& ns,
                           const std::string& desc,
                           const std::string& bpns) {
            fullname_ = name;
            abbrev_ = abrev;
            description_ = desc;
            for (auto s : ns) {
                namespaces_.push_back(s.trim());
            }
            bioportal_namespace_ = bpns;
        }

        Ontology::Ontology(const std::string& name,
                           const std::string& abrev,
                           std::vector<std::string>& ns,
                           const std::string& desc) {
            fullname_ = name;
            abbrev_ = abrev;
            description_ = desc;
            for (auto s : ns) {
                namespaces_.push_back(s.trim());
            }
        }

        Ontology::Ontology(ReferenceOntology ro) {
            fullname_ = ro.getFullName();
            abbrev_ = ro.getNickName();
            bioportal_namespace_ = ro.getBioPortalNamespace();
            namespaces_ = ro.getNamespaces();
            description_ = ro.getDescription();
        }

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
            return bioportal_namespace_;
        }

        // std::vector<std::string> Ontology::getNameSpaces() {
        //     return namespaces_;
        // }

        std::string Ontology::getDescription() {
            return description_;
        }
    }
}
