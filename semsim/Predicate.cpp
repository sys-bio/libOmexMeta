//
// Created by Ciaran on 4/5/2020.
//

#include "Predicate.h"

#include <iostream>
#include <memory>


//todo should I relabel Predicate to Term???
namespace semsim {
    Predicate::Predicate(std::string qualifier) : qualifier(std::move(qualifier)) {}

    const std::string &Predicate::getCvNamespace() const {
        return cv_namespace;
    }

    bool Predicate::operator==(const Predicate &rhs) const {
        return cv_namespace == rhs.cv_namespace &&
               root == rhs.root &&
               qualifier == rhs.qualifier;
    }

    std::ostream &operator<<(std::ostream &os, const Predicate &vocabulary) {
        os << vocabulary.getUri().str();
        return os;
    }

    bool Predicate::operator!=(const Predicate &rhs) const {
        return !(rhs == *this);
    }

    const std::string &Predicate::getRoot() const {
        return root;
    }

    const std::string &Predicate::getQualifier() const {
        return qualifier;
    }

    const std::vector<std::string> &Predicate::getValidTerms() const {
        return valid_terms;
    }

    void Predicate::setRoot(const std::string &root) {
        Predicate::root = root;
    }

    Uri Predicate::getUri() const {
        return Uri(root + qualifier);
    }

    void Predicate::setCvNamespace(const std::string &cvNamespace) {
        cv_namespace = cvNamespace;
    }

    void Predicate::verify() {
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

    void Predicate::setValidTerms() {}

    std::shared_ptr<Predicate> Predicate::make_shared() {
        return std::make_shared<Predicate>(*this);
    }

//    std::shared_ptr<int> Predicate::make_shared() {
//        return std::make_shared<int>(4);
//    }


    BiomodelsQualifier::BiomodelsQualifier(const std::string &qualifier)
            : Predicate(qualifier) {
        setValidTerms();
        setRoot("http://biomodels.net/biology-qualifiers/"); //namespace;
        setCvNamespace("bqb"); //prefix
        verify();
    }

    void BiomodelsQualifier::setValidTerms() { //term
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