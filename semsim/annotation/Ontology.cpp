#include "Ontology.h"

namespace semsim {
    Ontology::Ontology(const std::string& name,
                       const std::string& abbrev,
                       const Namespaces& namespaces,
                       const std::string& description,
                       const std::string& bioportal_ns)
        : name_(name),
          abbrev_(abbrev),
          namespaces_(namespaces),
          description_(description),
          bioportal_ns_(bioportal_ns)
    {}

    Ontology::Ontology(const std::string& name,
                       const std::string& abbrev,
                       const Namespaces& namespaces,
                       const std::string& description)
        : name_(name),
          abbrev_(abbrev),
          namespaces_(namespaces),
          description_(description)
    {}

    bool Ontology::hasNamespace(const std::string& ns) const {
        for (Namespaces::const_iterator i=namespaces_.begin(); i!=namespaces_.end(); ++i) {
            if (*i == ns)
                return true;
        }
        return false;
    }

    const std::string& Ontology::getName() const {
        return name_;
    }

    const std::string& Ontology::getAbbreviation() const {
        return abbrev_;
    }

    const std::string& Ontology::getBioPortalNamespace() const {
        return bioportal_ns_;
    }

    // std::vector<std::string> Ontology::getNameSpaces() {
    //     return namespaces_;
    // }

    const std::string& Ontology::getDescription() const {
        return description_;
    }
}
