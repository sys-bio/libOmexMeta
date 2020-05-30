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

    protected:
        LibrdfNode node_;
    public:
        Resource() = default;

        [[nodiscard]] const LibrdfNode &getNode() const;

        explicit Resource(LibrdfNode node);

        [[nodiscard]] std::string str() const;

        [[nodiscard]] virtual bool isSet() const;
    };

    typedef std::vector<Resource> Resources;

}

#endif //LIBSEMSIM_RESOURCE_H

