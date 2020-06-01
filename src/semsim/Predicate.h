//
// Created by Ciaran on 4/17/2020.
//

#ifndef LIBSEMSIM_PREDICATE_H
#define LIBSEMSIM_PREDICATE_H

#include "World.h"
#include "semsim/SemsimUtils.h"
#include <librdf.h>

#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <iostream>
#include <utility>

using namespace redland;

namespace semsim {

    typedef std::unordered_map<std::string, std::string> NamespaceMap;

    class Predicate {
    protected:

        std::string namespace_, term_, prefix_;
        std::string uri_;
        librdf_node *node_ = nullptr; //! predicates can only have type uri
        std::vector<std::string> valid_terms_{"All"};

        explicit Predicate(librdf_node *node);

    public:
        Predicate() = default;

        static std::unordered_map<std::string, std::string> namespaceMap();

        Predicate(const std::string &namespace_,
                  std::string term, std::string prefix);

        static Predicate fromRawPtr(librdf_node *node);

        std::string str();

        static void verify(std::vector<std::string> valid_terms, const std::string &term);

        static bool namespaceKnown(const std::string &ns);

        [[nodiscard]] librdf_node *getNode() const;

        [[nodiscard]] const std::vector<std::string> &getValidTerms() const;

        [[nodiscard]] const std::string &getNamespace() const;

        [[nodiscard]] const std::string &getTerm() const;

        [[nodiscard]] const std::string &getPrefix() const;

        [[nodiscard]] const std::string &getUri() const;

        void freeNode();
    };

    class BiomodelsBiologyQualifier : public Predicate {
    public:
        std::vector<std::string> valid_terms_{
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

        BiomodelsBiologyQualifier() = default;

        explicit BiomodelsBiologyQualifier(const std::string &term);

        void verify();
    };

    class BiomodelsModelQualifier : public Predicate {
    public:
        std::vector<std::string> valid_terms_{
                "isDerivedFrom",
                "isDescribedBy",
                "isInstanceOf",
                "hasInstance",
        };

        BiomodelsModelQualifier() = default;

        explicit BiomodelsModelQualifier(const std::string &term);

        void verify();
    };

    class DCTerm : public Predicate {
    public:
        std::vector<std::string> valid_terms_{
                "Description"
        };

        DCTerm() = default;

        explicit DCTerm(const std::string &term);

        void verify();
    };

    class SemSim : public Predicate {
    public:
        std::vector<std::string> valid_terms_{
                "hasSourceParticipant",
                "hasSinkParticipant",
                "hasMediatorParticipant",
                "hasMultiplier",
                "hasPhysicalEntityReference",
        };

        SemSim() = default;

        explicit SemSim(const std::string &term);

        void verify();
    };

    typedef std::shared_ptr<Predicate> PredicatePtr;
    typedef std::vector<Predicate> Predicates;
    typedef std::vector<PredicatePtr> PredicatePtrs;

    PredicatePtr PredicateFactory(std::string namespace_, const std::string &term);

}


#endif //LIBSEMSIM_PREDICATE_H