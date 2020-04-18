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
        RDFURINode uri_node; // predicates can only have type RDFUriNode

        std::vector<std::string> valid_terms_{"All"};

    public:
        Predicate2() = default;

        explicit Predicate2(librdf_world *world, const std::string &namespace_,
                            std::string term, std::string prefix);

        librdf_node *toRdfNode();

        std::string str();

        static int verify(std::vector<std::string> valid_terms, std::string term);
    };

    class BiomodelsQualifiers {
    public:
        // eg http://biomodels.net/biology-qualifiers/is => bqbiol:is
        librdf_world *world_;
        std::string term_;
        std::string namespace_ = "http://biomodels.net/biology-qualifiers/";
        std::string prefix_ = "bqbiol"; // eg bqbiol
        std::vector<std::string> valid_terms_{
                "is"
        };

        Predicate2 predicate;

        BiomodelsQualifiers(librdf_world *world,
                            const std::string &term);

        std::string str();

        librdf_node *toRdfNode();

    };


}

#endif //LIBSEMGEN_PREDICATE2_H
