//
// Created by Ciaran on 4/17/2020.
//

#ifndef LIBSEMSIM_PREDICATE_H
#define LIBSEMSIM_PREDICATE_H

#include "semsim/RedlandAPIWrapper/World.h"
#include "semsim/SemsimUtils.h"

#include <librdf.h>

#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <iostream>
#include <utility>


namespace semsim {

    class Predicate {
    protected:

        std::string namespace_, term_, prefix_;
        std::string uri_;
        std::unique_ptr<LibrdfNode> uri_node_; //! predicates can only have type RDFUriNode
        std::vector<std::string> valid_terms_{"All"};

    public:
        Predicate() = default;

        static std::unordered_map<std::string, std::string> prefix_map();

        Predicate(const std::string &namespace_,
                  std::string term, std::string prefix);

        explicit Predicate(LibrdfNode node);

        std::string str();

        static int verify(std::vector<std::string> valid_terms, const std::string &term);

        static bool namespaceKnown(const std::string &ns);

        const std::unique_ptr<LibrdfNode> &getNode() const;

        const std::vector<std::string> &getValidTerms() const;

        const std::string &getNamespace() const;

        const std::string &getTerm() const;

        const std::string &getPrefix() const;

        const std::string &getUri() const;
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

        BiomodelsBiologyQualifier(const std::string &term);

    };

    class BiomodelsModelQualifier : public Predicate {
    public:
        std::vector<std::string> valid_terms_{
                "is",
                "isDerivedFrom",
                "isDescribedBy",
                "isInstanceOf",
                "hasInstance",
        };

        BiomodelsModelQualifier() = default;

        BiomodelsModelQualifier(const std::string &term);

    };

    class DCTerm : public Predicate {
    public:
        std::vector<std::string> valid_terms_{
                "Description"
        };

        DCTerm() = default;

        DCTerm(const std::string &term);

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

        SemSim(const std::string &term);

    };

    typedef std::shared_ptr<Predicate> PredicatePtr;
    typedef std::vector<Predicate> Predicates;
    typedef std::vector<PredicatePtr> PredicatePtrs;

    PredicatePtr PredicateFactory(std::string namespace_, const std::string &term);

}


#endif //LIBSEMSIM_PREDICATE_H