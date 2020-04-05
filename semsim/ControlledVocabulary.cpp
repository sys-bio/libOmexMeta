//
// Created by Ciaran on 4/5/2020.
//

#include "ControlledVocabulary.h"

#include <utility>

namespace semsim {
    ControlledVocabulary::ControlledVocabulary(std::string qualifier) : qualifier(std::move(qualifier)) {}

    const std::string &ControlledVocabulary::getCvNamespace() const {
        return cv_namespace;
    }

    bool ControlledVocabulary::operator==(const ControlledVocabulary &rhs) const {
        return cv_namespace == rhs.cv_namespace &&
               root == rhs.root &&
               qualifier == rhs.qualifier;
    }

    std::ostream &operator<<(std::ostream &os, const ControlledVocabulary &vocabulary) {
        os << vocabulary.getUri().str();
        return os;
    }

    bool ControlledVocabulary::operator!=(const ControlledVocabulary &rhs) const {
        return !(rhs == *this);
    }

    const std::string &ControlledVocabulary::getRoot() const {
        return root;
    }

    const std::string &ControlledVocabulary::getQualifier() const {
        return qualifier;
    }

    const std::vector<std::string> &ControlledVocabulary::getValidTerms() const {
        return valid_terms;
    }

    void ControlledVocabulary::setRoot(const std::string &root) {
        ControlledVocabulary::root = root;
    }

    Uri ControlledVocabulary::getUri() const {
        return Uri(root + qualifier);
    }

    void ControlledVocabulary::setCvNamespace(const std::string &cvNamespace) {
        cv_namespace = cvNamespace;
    }

    void ControlledVocabulary::verify() {
        if (!(std::find(valid_terms.begin(), valid_terms.end(), qualifier) != valid_terms.end())) {
            std::ostringstream os;
            os << "Invalid qualifier given. Qualifiers available for " << cv_namespace
               << " include: ";
            for (auto &i : valid_terms) {
                os << i << ", ";
            }
            throw std::invalid_argument(os.str());
        }
    }

    BiomodelsQualifier::BiomodelsQualifier(const std::string &qualifier)
            : ControlledVocabulary(qualifier) {
        setValidTerms();
        setRoot("http://biomodels.net/biology-qualifiers/");
        setCvNamespace("bqb");
        verify();
    }

    void BiomodelsQualifier::setValidTerms() {
        this->valid_terms = {
                "is",
                "hasPart",
                "isPartOf",
                "isVersionOf",
                "hasVersion",
                "isHomologTo",
                "isDescribedBy",
                "isEncodedBy",
                "encodes",
                "occursIn",
                "hasProperty",
                "isPropertyOf",
                "hasTaxon"
        };
    }
}