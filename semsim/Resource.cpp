//
// Created by Ciaran on 4/4/2020.
//

#include "semsim/Resource.h"
#include "uri.h"

namespace semsim {
    std::string &Resource::getMetaId() {
        return metaId;
    }

    Uri &Resource::getUri() {
        return uri;
    }

    bool Resource::operator==(const Resource &rhs) const {
        return metaId == rhs.metaId &&
               uri == rhs.uri;
    }

    bool Resource::operator!=(const Resource &rhs) const {
        return !(rhs == *this);
    }

    std::ostream &operator<<(std::ostream &os, Resource &resource) {
        os << "Resource(metaId=" << resource.getMetaId() << ", uri=" << resource.getUri().str() << ")";
        return os;
    }


}
