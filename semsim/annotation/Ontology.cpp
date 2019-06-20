#include "Ontology.h"

namespace semsim {
    namespace annotation {
        using ReferenceOntology = semsim::definitions::ReferenceOntologies::ReferenceOntology;

        Ontology::Ontology(const std::wstring& name, const std::wstring& abrev, std::vector<std::wstring>& ns, const std::wstring& desc, const std::wstring& bpns) {
            fullname = name;
            nickname = abrev;
            description = desc;
            for (auto s : ns) {
                namespaces.push_back(s.trim());
            }
            bioportalnamespace = bpns;
        }

        Ontology::Ontology(const std::wstring& name, const std::wstring& abrev, std::vector<std::wstring>& ns, const std::wstring& desc) {
            fullname = name;
            nickname = abrev;
            description = desc;
            for (auto s : ns) {
                namespaces.push_back(s.trim());
            }
        }

        Ontology::Ontology(ReferenceOntology ro) {
            fullname = ro.getFullName();
            nickname = ro.getNickName();
            bioportalnamespace = ro.getBioPortalNamespace();
            namespaces = ro.getNamespaces();
            description = ro.getDescription();
        }

        bool Ontology::hasNamespace(const std::wstring& nspace) {
            for (auto ns : namespaces) {
                if (nspace == ns) {
                    return true;
                }
            }
            return false;
        }

        std::wstring Ontology::getFullName() {
            return std::wstring(fullname);
        }

        std::wstring Ontology::getNickName() {
            return std::wstring(nickname);
        }

        std::wstring Ontology::getBioPortalNamespace() {
            return bioportalnamespace;
        }

        std::vector<std::wstring> Ontology::getNameSpaces() {
            return namespaces;
        }

        std::wstring Ontology::getDescription() {
            return description;
        }
    }
}