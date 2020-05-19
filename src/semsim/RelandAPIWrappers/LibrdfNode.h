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
        const std::shared_ptr<librdf_node *> &getNode() const;

    public:
        explicit LibrdfNode(librdf_node *node);

        ~LibrdfNode();

        LibrdfNode(const LibrdfNode &librdfNode);

        LibrdfNode(LibrdfNode &&librdfNode) noexcept;

        LibrdfNode &operator=(const LibrdfNode &librdfNode);

        LibrdfNode &operator=(LibrdfNode &&librdfNode) noexcept;

        std::string str();

    };
}


#endif //LIBSEMSIM_LIBRDFNODE_H
