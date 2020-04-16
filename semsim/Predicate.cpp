//
// Created by Ciaran on 4/5/2020.
//

#include "Predicate.h"

#include <iostream>
#include <memory>


//todo should I relabel Predicate to Term???
namespace semsim {
    Predicate::Predicate(std::string term) : term_(std::move(term)) {}

    const std::string &Predicate::getPrefix() const {
        return prefix_;
    }

    bool Predicate::operator==(const Predicate &rhs) const {
        return prefix_ == rhs.prefix_ &&
               namespace_ == rhs.namespace_ &&
               term_ == rhs.term_;
    }

    std::ostream &operator<<(std::ostream &os, const Predicate &vocabulary) {
        os << vocabulary.getUri().str();
        return os;
    }

    bool Predicate::operator!=(const Predicate &rhs) const {
        return !(rhs == *this);
    }

    const std::string &Predicate::getNamespace() const {
        return namespace_;
    }

    const std::string &Predicate::getTerm() const {
        return term_;
    }

    const std::vector<std::string> &Predicate::getValidTerms() const {
        return valid_terms;
    }

    void Predicate::setNamespace(const std::string &namespace_) {
        this->namespace_ = namespace_;
    }

    Uri Predicate::getUri() const {
        return Uri(namespace_ + term_);
    }

    void Predicate::setPrefix(const std::string &prefix) {
        prefix_ = prefix;
    }

    void Predicate::verify() {
        if (!(std::find(valid_terms.begin(), valid_terms.end(), term_) != valid_terms.end())) {
            std::ostringstream os;
            os << "Invalid term given. Terms available for " << prefix_
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
        setNamespace("http://biomodels.net/biology-qualifiers/"); //namespace;
        setPrefix("bqb"); //prefix
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

    DCTerms::DCTerms(const std::string &qualifier) {
        setValidTerms();
        setNamespace("http://purl.org/dc/terms/"); //namespace;
        setPrefix("dc"); //prefix
        verify();
    }

    void DCTerms::setValidTerms() {
        this->valid_terms = {
                "description"
        };
    }
}