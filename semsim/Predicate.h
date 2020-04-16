//
// Created by Ciaran on 4/5/2020.
//

#ifndef LIBSEMGEN_PREDICATE_H
#define LIBSEMGEN_PREDICATE_H

#include <algorithm>
#include <memory>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include "uri.h"

namespace semsim {
    class Predicate {
        std::string namespace_;
        std::string prefix_;
        std::string term_;
    protected:
        std::vector<std::string> valid_terms;

        virtual void setValidTerms();

        void verify();

    public:
        Predicate() = default;

        explicit Predicate(std::string term_);

        const std::string &getPrefix() const;

        void setNamespace(const std::string &namespace_);

        void setPrefix(const std::string &prefix);

        const std::string &getNamespace() const;

        const std::string &getTerm() const;

        const std::vector<std::string> &getValidTerms() const;

        bool operator==(const Predicate &rhs) const;

        bool operator!=(const Predicate &rhs) const;

        friend std::ostream &operator<<(std::ostream &os, const Predicate &vocabulary);

        Uri getUri() const;

        std::shared_ptr<Predicate> make_shared();

    };

    typedef std::unique_ptr<Predicate> PredicatePtr;

    class BiomodelsQualifier : public Predicate {
    public:
        BiomodelsQualifier() = default;

        explicit BiomodelsQualifier(const std::string &term_);

    protected:
        void setValidTerms() override;
    };


    class DCTerms : public Predicate {
    public:
        DCTerms() = default;

        explicit DCTerms(const std::string &term_);

    protected:
        void setValidTerms() override;
    };


    // todo do i need to delete this class??
    class PredicateNamespaces {
    public:

        PredicateNamespaces() = default;

        static std::unordered_map<std::string, std::string> getNamespaces() {
            std::unordered_map<std::string, std::string> namespaces;
            namespaces["bqb"] = "http://biomodels.net/biology-qualifiers";
            return namespaces;
        }

        //todo idea: implement a register namespace method so users
        // can register their own namespaces. Practically, this would mean
        // just adding a new key value pair into the ns dict.


    };


}

#endif //LIBSEMGEN_PREDICATE_H
