//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBSEMGEN_RESOURCE_H
#define LIBSEMGEN_RESOURCE_H

#include <iostream>
#include "semsim/Resource.h"
#include "semsim/uri.h"
#include "sstream"

namespace semsim {
    class Resource {
    private:

        std::string identifiers_base = "https://identifiers.org";
        std::string resource_namespace;
        std::string identifier;
        std::string literal;
        bool is_literal_{};

    public:
        Resource(const std::string &identifier);

        Resource() = default;

        Resource(std::string resourceNamespace,
                 std::string identifier);

        const std::string &getIdentifiersBase() const;

        const std::string &getResourceNamespace() const;

        const std::string &getIdentifier() const;

        bool operator==(const Resource &rhs) const;

        bool operator!=(const Resource &rhs) const;

        friend std::ostream &operator<<(std::ostream &os, const Resource &resource);

        std::string str() const;

        static std::vector<std::string> splitStringBy(const std::string& str, char delimiter);
    };


}

#endif //LIBSEMGEN_RESOURCE_H

