//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBOMEXMETA_RESOURCE_H
#define LIBOMEXMETA_RESOURCE_H

#include "redland/librdf.h"
#include "redland/LibrdfNode.h"

#include "omexmeta/Error.h"

#include <iostream>
#include "sstream"
#include <vector>


using namespace redland;

namespace omexmeta {
    class [[deprecated("Use redland::LibRDFNode directly instead. i.e. LibRDFNode::fromUriString(...).get()")]] Resource {

        explicit Resource(librdf_node *node);

    public:
        bool operator==(const Resource &rhs) const;

        bool operator!=(const Resource &rhs) const;

    protected:
        librdf_node *node_ = nullptr;
    public:
        explicit Resource(LibrdfNode node);

        Resource() = default;

        void setNode(librdf_node *node);

        static Resource fromRawPtr(librdf_node *node);

        [[nodiscard]] librdf_node *getNode() const;

        [[nodiscard]] std::string str() const;

        [[nodiscard]] virtual bool isSet() const;

        void free();
    };


    typedef std::vector<Resource> Resources;

}

#endif //LIBOMEXMETA_RESOURCE_H

