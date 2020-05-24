//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBSEMSIM_RESOURCE_H
#define LIBSEMSIM_RESOURCE_H

#include "librdf.h"
#include <iostream>
#include "sstream"
#include <vector>


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

        LibrdfNode getNode() const;

        std::string str() const;

        virtual bool isSet() const;
    };

    typedef std::vector<Resource> Resources;

}

#endif //LIBSEMSIM_RESOURCE_H

