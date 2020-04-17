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

        //todo figure out correct nomenclecture
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

        Uri getUri() const; // deprecated. Use str instead

        std::string str();

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


}

#endif //LIBSEMGEN_PREDICATE_H
