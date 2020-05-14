//
// Created by Ciaran on 4/17/2020.
//

#ifndef LIBSEMGEN_PREDICATE_H
#define LIBSEMGEN_PREDICATE_H

#include <librdf.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include "RDFNode.h"
#include "unordered_map"

namespace semsim {
    class Predicate {
    protected:

        librdf_world *world_;
        std::string namespace_, term_, prefix_;
        std::string uri_;
        std::shared_ptr<RDFURINode> uri_node_; // predicates can only have type RDFUriNode

        std::vector<std::string> valid_terms_{"All"};

    public:
        static std::unordered_map<std::string, std::string> prefix_map();

        Predicate() = default;

        void setPrefix(const std::string &prefix);

        void setNamespace(const std::string &ns);

        Predicate(librdf_world *world, const std::string &namespace_,
                  std::string term, std::string prefix);

        Predicate(librdf_world *world, librdf_node *node);

        librdf_node *toRdfNode();

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

        BiomodelsBiologyQualifier(librdf_world *world, const std::string &term);

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

        BiomodelsModelQualifier(librdf_world *world, const std::string &term);

    };

    class DCTerm : public Predicate {
    public:
        std::vector<std::string> valid_terms_{
                "Description"
        };

        DCTerm() = default;

        DCTerm(librdf_world *world, const std::string &term);

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

        SemSim(librdf_world *world, const std::string &term);

    };

    typedef std::shared_ptr<Predicate> PredicatePtr;
    typedef std::vector<Predicate> Predicates;
    typedef std::vector<PredicatePtr> PredicatePtrs;

    PredicatePtr PredicateFactory(librdf_world *world, std::string namespace_, const std::string &term);

}


#endif //LIBSEMGEN_PREDICATE_H