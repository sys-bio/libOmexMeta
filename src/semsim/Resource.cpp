//
// Created by Ciaran on 4/4/2020.
//

#include "Resource.h"

namespace semsim {

    std::string Resource::str() const {
        return node_.str();
    }

    Resource::Resource(LibrdfNode node)
            : node_(std::move(node)) {
    }

    bool Resource::isSet() const {
        return node_.get() != nullptr;
    }

    const LibrdfNode &Resource::getNode() const {
        return node_;
    }

}






