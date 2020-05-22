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

/*
 * Do I need to mirror the underlying structure of
 * the librdf_node* object?
 */

namespace semsim {

    typedef std::shared_ptr<librdf_node> node_ptr;

    class LibrdfNode {
        node_ptr node_;

    public:
        const node_ptr &getNode() const;

        LibrdfNode() = default;

        explicit LibrdfNode(librdf_node *node);

        bool operator!() const;

        std::string str();

        raptor_term_type getType();

        bool operator==(const LibrdfNode &rhs) const;

        bool operator!=(const LibrdfNode &rhs) const;

        librdf_node *get();

    };
}


#endif //LIBSEMSIM_LIBRDFNODE_H
