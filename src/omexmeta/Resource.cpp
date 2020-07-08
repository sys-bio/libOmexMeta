//
// Created by Ciaran on 4/4/2020.
//

#include "Resource.h"
#include "Error.h"

namespace omexmeta {

    Resource::Resource(librdf_node *node)
            : node_(node) {
    }

    Resource::Resource(LibrdfNode node)
            : node_(node.get()) {

    }

    std::string Resource::str() const {
        if (!node_) {
            throw NullPointerException("NullPointerException: Resource::str(): node_ is null");
        }
        return LibrdfNode::str(node_);
    }

    bool Resource::isSet() const {
        return node_ != nullptr;
    }

    librdf_node *Resource::getNode() const {
        return node_;
    }

    Resource Resource::fromRawPtr(librdf_node *node) {
        return Resource(node);
    }

    void Resource::free() {
        if (node_) {
            LibrdfNode::freeNode(node_);
            setNode(nullptr);
        }
    }

    void Resource::setNode(librdf_node *node) {
        node_ = node;
    }

    bool Resource::operator==(const Resource &rhs) const {
        return librdf_node_equals(node_, rhs.node_);
    }

    bool Resource::operator!=(const Resource &rhs) const {
        return !(rhs == *this);
    }


}






