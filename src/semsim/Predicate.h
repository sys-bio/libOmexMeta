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


        /*
         * @brief utility for checking whether the uri in @parameter predicate
         * has a namespace that we already know. If found, the namespace is
         * added to @parameter serializer
         */
        static void addSeenNamespaceToSerializer(librdf_world *world, librdf_serializer *serializer, librdf_node *predicate);

        struct deleter {
            /*
             * @brief static destructor for predicate
             *
             * We do not want to let Predicate manage the lifetime of its node_
             * because Predicate is a part of Triple and Triple manages its lifetime.
             * However, sometimes its useful to have a std::unique_ptr to a predicate
             * (see Participant) and in this case we need to pass in this function
             * as a deleter.
             */
            void operator()(Predicate *predicate);
        };

        static std::unique_ptr<Predicate, deleter> makeUniquePredicate(Predicate predicate);

        /*
         * @brief get raw pointer from predicate.
         * @param Predicate predicate: The predicate to take raw pointer of
         *
         * For developers. Used in initializer list of other classes (like Participants)
         * since we cannot take a address of a temporary object
         */
        static Predicate *makeRawPtr(Predicate predicate);

        void setNode(librdf_node *node);
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