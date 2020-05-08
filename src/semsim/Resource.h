//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBSEMGEN_RESOURCE_H
#define LIBSEMGEN_RESOURCE_H

#include "librdf.h"
#include <iostream>
#include "Resource.h"
#include "sstream"
#include "RDFNode.h"
#include <vector>

namespace semsim {
    class Resource {

    protected:
        librdf_world *world_;
        RDFNodePtr rdf_node_ptr_;
    public:
        Resource() = default;

        Resource(librdf_world *world, const RDFLiteralNode &node);

        Resource(librdf_world *world, const RDFURINode &node);

        Resource(librdf_world *world, const RDFBlankNode &node);

        Resource(librdf_world* world, librdf_node* node);

        librdf_node *toRdfNode() const;

        std::string str() const;

        virtual bool isSet() const;
    };

    typedef std::vector<Resource> Resources;

}

#endif //LIBSEMGEN_RESOURCE_H

