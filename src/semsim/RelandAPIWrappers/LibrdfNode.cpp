//
// Created by Ciaran on 5/17/2020.
//

#include "LibrdfNode.h"

namespace semsim {

    LibrdfNode::LibrdfNode(librdf_node *node) :
            node_(std::make_shared<librdf_node *>(node)) {

    }

    LibrdfNode::~LibrdfNode() {
        if (node_.use_count() == 1){
            librdf_free_node(*node_);
        }
    }

    LibrdfNode::LibrdfNode(const LibrdfNode &librdfNode) {
        if (node_)
            librdf_free_node(*node_); // Remove prexisting node before copy
        node_ = librdfNode.node_;
    }

    LibrdfNode::LibrdfNode(LibrdfNode &&librdfNode) noexcept {

    }

    LibrdfNode &LibrdfNode::operator=(const LibrdfNode &librdfNode) {
    }

    LibrdfNode &LibrdfNode::operator=(LibrdfNode &&librdfNode) noexcept {
    }
}