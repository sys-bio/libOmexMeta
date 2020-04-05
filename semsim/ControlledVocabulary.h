//
// Created by Ciaran on 4/5/2020.
//

#ifndef LIBSEMGEN_CONTROLLEDVOCABULARY_H
#define LIBSEMGEN_CONTROLLEDVOCABULARY_H

#include "iostream"
#include "sstream"
#include <algorithm>
#include "uri.h"

namespace semsim {
    class ControlledVocabulary {
        std::string root;
        std::string cv_namespace;
        std::string qualifier;
    protected:
        std::vector<std::string> valid_terms;

        virtual void setValidTerms() = 0;

        void verify() ;

    public:
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

    };

    class BiomodelsQualifier : public ControlledVocabulary {
    public:
        explicit BiomodelsQualifier(const std::string &qualifier);

    protected:
        void setValidTerms() override;
    };


}

#endif //LIBSEMGEN_CONTROLLEDVOCABULARY_H
