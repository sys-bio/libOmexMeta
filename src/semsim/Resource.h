//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBSEMSIM_RESOURCE_H
#define LIBSEMSIM_RESOURCE_H

#include "librdf.h"
#include "LibrdfNode.h"

#include <iostream>
#include "sstream"
#include <vector>

using namespace redland;

namespace semsim {
    class Resource {

        explicit Resource(librdf_node *node);

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

#endif //LIBSEMSIM_RESOURCE_H

