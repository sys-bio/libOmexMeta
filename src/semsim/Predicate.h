//
// Created by Ciaran on 4/17/2020.
//

#ifndef LIBSEMSIM_PREDICATE_H
#define LIBSEMSIM_PREDICATE_H

#include <librdf.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <iostream>
#include <utility>
#include "semsim/RDFNode.h"

#include "semsim/RedlandAPIWrappers/LibrdfWorld.h"


#include "semsim/SemsimUtils.h"


namespace semsim {

    class Predicate {
    protected:

        Predicate(semsim::LibrdfWorld world, const RDFURINode &node);

        LibrdfWorld world_;
        std::string namespace_, term_, prefix_;
        std::string uri_;
        std::shared_ptr<RDFURINode> uri_node_; // predicates can only have type RDFUriNode

        std::vector<std::string> valid_terms_{"All"};

    public:
        static std::unordered_map<std::string, std::string> prefix_map();

        Predicate() = default;

        void setPrefix(const std::string &prefix);

        void setNamespace(const std::string &ns);

        Predicate(LibrdfWorld world, const std::string &namespace_,
                  std::string term, std::string prefix);

        Predicate(LibrdfWorld world, LibrdfNode node);

        LibrdfNode getNode();

        std::string str();

        const std::string &getNamespace() const;

        const std::string &getTerm() const;

        const std::string &getPrefix() const;

        const std::string &getUri() const;

        static int verify(std::vector<std::string> valid_terms, const std::string &term);

        static bool namespaceKnown(std::string ns);

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

        BiomodelsBiologyQualifier(LibrdfWorld world, const std::string &term);

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

        BiomodelsModelQualifier(LibrdfWorld world, const std::string &term);

    };

    class DCTerm : public Predicate {
    public:
        std::vector<std::string> valid_terms_{
                "Description"
        };

        DCTerm() = default;

        DCTerm(LibrdfWorld world, const std::string &term);

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

        SemSim(LibrdfWorld world, const std::string &term);

    };

    typedef std::shared_ptr<Predicate> PredicatePtr;
    typedef std::vector<Predicate> Predicates;
    typedef std::vector<PredicatePtr> PredicatePtrs;

    PredicatePtr PredicateFactory(LibrdfWorld world, std::string namespace_, const std::string &term);

}


#endif //LIBSEMSIM_PREDICATE_H