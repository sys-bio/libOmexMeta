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
        std::string identifiers_base = "https://identifiers.org";
        std::string resource_namespace;
        std::string identifier;


    public:

        Resource(std::string resourceNamespace,
                 std::string identifier);

        const std::string &getIdentifiersBase() const;

        const std::string &getResourceNamespace() const;

        const std::string &getIdentifier() const;

        bool operator==(const Resource &rhs) const;

        bool operator!=(const Resource &rhs) const;

        friend std::ostream &operator<<(std::ostream &os, const Resource &resource);

        std::string build() const;
    };


}

#endif //LIBSEMGEN_RESOURCE_H

