//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_LIBRDFNODE_H
#define LIBSEMSIM_LIBRDFNODE_H

#include <librdf.h>
#include "CWrapper.h"

namespace semsim {
    class LibrdfNode : private CWrapper {
        librdf_model *model_;

    public:
        LibrdfNode(librdf_model *model);

        ~LibrdfNode();

        LibrdfNode(LibrdfNode &LibrdfNode);

        LibrdfNode(LibrdfNode &&LibrdfNode) noexcept;

        LibrdfNode &operator=(LibrdfNode &LibrdfNode);

        LibrdfNode &operator=(LibrdfNode &&LibrdfNode) noexcept;

        bool operator==(const LibrdfNode &rhs) const;

        bool operator!=(const LibrdfNode &rhs) const;

        librdf_model *getModel() const;
    };
}


#endif //LIBSEMSIM_LIBRDFNODE_H
