//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBSEMGEN_SUBJECT_H
#define LIBSEMGEN_SUBJECT_H

#include "iostream"
#include "semsim/RDFNode.h"

namespace semsim {
    class Subject {
    private:
        librdf_world *world_;

        RDFNodePtr rdfNodePtr_;

    public:
        Subject() = default;

        Subject(librdf_world *world, const RDFBlankNode &node);

        explicit Subject(librdf_world *world, const RDFURINode &node);

        librdf_node *toRdfNode();

        std::string str();

    };

}

#endif //LIBSEMGEN_SUBJECT_H
