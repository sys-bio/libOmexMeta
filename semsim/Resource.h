//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBSEMGEN_RESOURCE_H
#define LIBSEMGEN_RESOURCE_H

#include <iostream>
#include "semsim/Resource.h"
#include "semsim/uri.h"

namespace semsim {
    class Resource {
    private:
        std::string metaId;
        Uri uri;

    public:
        Resource(std::string metaId, Uri uri) : metaId(std::move(metaId)), uri(std::move(uri)) {};

        Resource(std::string metaId, std::string uri) : metaId(std::move(metaId)), uri(Uri(std::move(uri))) {};

        std::string &getMetaId();

        Uri &getUri();

        bool operator==(const Resource &rhs) const;

        bool operator!=(const Resource &rhs) const;

        friend std::ostream &operator<<(std::ostream &os, Resource &resource);
    };


}

#endif //LIBSEMGEN_RESOURCE_H

