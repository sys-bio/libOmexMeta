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
#include "SemsimUtils.h"

namespace semsim {
    class Resource {

    protected:
        LibrdfWorld world_;
        RDFNodePtr rdf_node_ptr_;
    public:
        Resource() = default;

        Resource(LibrdfWorld world, const RDFLiteralNode &node);

        Resource(LibrdfWorld world, const RDFURINode &node);

        Resource(LibrdfWorld world, const RDFBlankNode &node);

        Resource(LibrdfWorld world, LibrdfNode node);

        LibrdfNode toRdfNode() const;

        std::string str() const;

        virtual bool isSet() const;
    };

    typedef std::vector<Resource> Resources;

}

#endif //LIBSEMGEN_RESOURCE_H

