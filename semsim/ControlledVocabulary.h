//
// Created by Ciaran on 4/5/2020.
//

#ifndef LIBSEMGEN_CONTROLLEDVOCABULARY_H
#define LIBSEMGEN_CONTROLLEDVOCABULARY_H

#include <algorithm>
#include <memory>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include "uri.h"

namespace semsim {
    class ControlledVocabulary {
        std::string root;
        std::string cv_namespace;
        std::string qualifier;
    protected:
        std::vector<std::string> valid_terms;

        virtual void setValidTerms();

        void verify() ;

    public:
        ControlledVocabulary() = default;

        explicit ControlledVocabulary(std::string qualifier);

        const std::string &getCvNamespace() const;

        void setRoot(const std::string &root);

        void setCvNamespace(const std::string &cvNamespace);

        const std::string &getRoot() const;

        const std::string &getQualifier() const;

        const std::vector<std::string> &getValidTerms() const;

        bool operator==(const ControlledVocabulary &rhs) const;

        bool operator!=(const ControlledVocabulary &rhs) const;

        friend std::ostream &operator<<(std::ostream &os, const ControlledVocabulary &vocabulary);

        Uri getUri() const;

        std::shared_ptr<ControlledVocabulary> make_shared();

    };

    class BiomodelsQualifier : public ControlledVocabulary {
    public:
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

        static std::unordered_map<std::string, std::string> getNamespaces()  {
           std::unordered_map<std::string, std::string> namespaces;
           namespaces["bqb"] = "http://biomodels.net/biology-qualifiers";
           return namespaces;
        }

        //todo idea: implement a register namespace method so users
        // can register their own namespaces. Practically, this would mean
        // just adding a new key value pair into the ns dict.


    };


}

#endif //LIBSEMGEN_CONTROLLEDVOCABULARY_H
