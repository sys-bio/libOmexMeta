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
        std::string root;
        std::string cv_namespace;
        std::string qualifier;
    protected:
        std::vector<std::string> valid_terms;

        virtual void setValidTerms();

        void verify();

    public:
        Predicate() = default;

        explicit Predicate(std::string qualifier);

        const std::string &getCvNamespace() const;

        void setRoot(const std::string &root);

        void setCvNamespace(const std::string &cvNamespace);

        const std::string &getRoot() const;

        const std::string &getQualifier() const;

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

        explicit BiomodelsQualifier(const std::string &qualifier);

    protected:
        void setValidTerms() override;
    };

    /*
     * A mapping between commonly used namespaces and
     * their links
     */
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
