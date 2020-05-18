//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_LIBRDFNODE_H
#define LIBSEMSIM_LIBRDFNODE_H

#include <librdf.h>
#include <memory>

namespace semsim {
    class LibrdfNode {
        std::shared_ptr<librdf_node *> node_;

    public:
        explicit LibrdfNode(librdf_node *node);

    };
}


#endif //LIBSEMSIM_LIBRDFNODE_H
