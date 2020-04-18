//
// Created by Ciaran on 4/17/2020.
//

#ifndef LIBSEMGEN_PREDICATE2_H
#define LIBSEMGEN_PREDICATE2_H

#include <librdf.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include "RDFNode.h"

namespace semsim {
    class Predicate2 {
    protected:
        librdf_world *world_;
        std::string namespace_, term_, prefix_;
        std::string uri_;
        std::unique_ptr<RDFURINode> uri_node_; // predicates can only have type RDFUriNode

        std::vector<std::string> valid_terms_{"All"};

    public:
        Predicate2() = default;

        void setPrefix(const std::string &prefix);

        Predicate2(librdf_world *world, const std::string &namespace_,
                   std::string term, std::string prefix);

        librdf_node *toRdfNode();

        std::string str();

        const std::string &getNamespace() const;

        const std::string &getTerm() const;

        const std::string &getPrefix() const;

        const std::string &getUri() const;

        static int verify(std::vector<std::string> valid_terms, const std::string &term);
    };

    class BiomodelsQualifiers : public Predicate2 {
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
                "hasTaxon"};

        BiomodelsQualifiers(librdf_world *world, const std::string &term);

    };

    class DCTerm : public Predicate2 {
    public:
        std::vector<std::string> valid_terms_{
                "Description"
        };

        DCTerm(librdf_world *world, const std::string &term);

    };


}

#endif //LIBSEMGEN_PREDICATE2_H
