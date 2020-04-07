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

    public:

        Resource() = default;

        Resource(std::string resourceNamespace,
                 std::string identifier);

        Resource(std::string resource);

        const std::string &getIdentifiersBase() const;

        const std::string &getResourceNamespace() const;

        const std::string &getIdentifier() const;

        bool operator==(const Resource &rhs) const;

        bool operator!=(const Resource &rhs) const;

        friend std::ostream &operator<<(std::ostream &os, const Resource &resource);

        std::string build() const;

        static std::vector<std::string> splitStringBy(std::string str, char delimiter) {
            std::vector<std::string> tokens;
            if (str.find(delimiter) == std::string::npos) {
                // return the string in the vector
                tokens.push_back(str);
                return tokens;
            }
            std::string token;
            std::istringstream is(str);
            while (std::getline(is, token, delimiter)) {
                if (!token.empty())
                    tokens.push_back(token);
            }
            return tokens;
        }
    };


}

#endif //LIBSEMGEN_RESOURCE_H

