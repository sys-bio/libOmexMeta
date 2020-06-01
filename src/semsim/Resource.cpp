//
// Created by Ciaran on 4/4/2020.
//

#include "Resource.h"

namespace semsim {

    Resource::Resource(librdf_node* node)
            : node_(node) {
    }

    std::string Resource::str() const {
        return LibrdfNode::str(node_);
    }

    bool Resource::isSet() const {
        return node_ != nullptr;
    }

    librdf_node* Resource::getNode() const {
        return node_;
    }

    Resource Resource::fromRawPtr(librdf_node *node) {
        return Resource(node);
    }

    void Resource::freeNode() {
        LibrdfNode::freeNode(node_);
    }

}






