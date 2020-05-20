//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_LIBRDFNODE_H
#define LIBSEMSIM_LIBRDFNODE_H

#include "semsim/Error.h"
#include <librdf.h>
#include <raptor2.h>
#include <memory>
#include <sstream>
#include "semsim/HERE.h"

namespace semsim {
    class LibrdfNode {
        std::shared_ptr<librdf_node *> node_;
    public:
        const std::shared_ptr<librdf_node *> &getNode() const;

    public:
        LibrdfNode() = default;

        explicit LibrdfNode(librdf_node *node);

        ~LibrdfNode();

        LibrdfNode(const LibrdfNode &librdfNode);

        LibrdfNode(LibrdfNode &&librdfNode) noexcept;

        LibrdfNode &operator=(const LibrdfNode &librdfNode);

        LibrdfNode &operator=(LibrdfNode &&librdfNode) noexcept;

        bool operator!() const;

        std::string str();

        raptor_term_type getType();

        bool operator==(const LibrdfNode &rhs) const;

        bool operator!=(const LibrdfNode &rhs) const;

    };
}


#endif //LIBSEMSIM_LIBRDFNODE_H
