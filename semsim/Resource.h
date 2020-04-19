//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBSEMGEN_RESOURCE_H
#define LIBSEMGEN_RESOURCE_H

#include "librdf.h"
#include <iostream>
#include "semsim/Resource.h"
#include "semsim/uri.h"
#include "sstream"
#include "semsim/RDFNode.h"

namespace semsim {
    class Resource {
        librdf_world* world_;
        RDFNodePtr rdf_node_ptr_;

    public:
        Resource() = default;

        Resource(librdf_world *world, const RDFLiteralNode &node);

        Resource(librdf_world *world, const RDFURINode &node);

        Resource(librdf_world *world, const RDFBlankNode &node);

        std::string str();

        librdf_node *toRdfNode();


    };

}

#endif //LIBSEMGEN_RESOURCE_H

