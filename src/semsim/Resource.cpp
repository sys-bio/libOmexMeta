//
// Created by Ciaran on 4/4/2020.
//

#include "Resource.h"

namespace semsim {

    Resource::Resource(librdf_node* node)
            : node_(LibrdfNode(node)) {
    }

    std::string Resource::str() const {
        return node_.str();
    }

    bool Resource::isSet() const {
        return node_.get() != nullptr;
    }

    librdf_node* Resource::getNode() const {
        return node_.get();
    }

    Resource Resource::fromRawPtr(librdf_node *node) {
        return Resource(node);
    }

}






