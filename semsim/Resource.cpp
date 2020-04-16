//
// Created by Ciaran on 4/4/2020.
//

#include "semsim/Resource.h"

#include <utility>
#include "uri.h"
#include "sstream"
#include "iterator"

namespace semsim {


    Resource::Resource(std::string resourceNamespace, std::string identifier) :
            resource_namespace(std::move(resourceNamespace)),
            identifier(std::move(identifier)) {}

    const std::string &Resource::getIdentifiersBase() const {
        return identifiers_base;
    }

    const std::string &Resource::getResourceNamespace() const {
        return resource_namespace;
    }

    const std::string &Resource::getIdentifier() const {
        return identifier;
    }

    bool Resource::operator==(const Resource &rhs) const {
        return identifiers_base == rhs.identifiers_base &&
               resource_namespace == rhs.resource_namespace &&
               identifier == rhs.identifier;
    }

    bool Resource::operator!=(const Resource &rhs) const {
        return !(rhs == *this);
    }

    std::ostream &operator<<(std::ostream &os, const Resource &resource) {
        os << "Resource(" << resource.build() << ")";
        return os;
    }

    std::string Resource::build() const {
        std::ostringstream os;
        os << identifiers_base << "/"
           << resource_namespace << "/"
           << identifier;
        return os.str();
    }

    static std::vector<std::string> splitStringBy(std::string delimiter);

    Resource::Resource(const std::string &identifier) {
        std::vector<std::string> vec;
        if (identifier.find('/') != std::string::npos) {
            // process identifier of form namespace/identifier
            vec = splitStringBy(identifier, '/');
            if (vec.size() != 2)
                throw std::logic_error("Was expecting a vector of size 2");
        } else if (identifier.find(':') != std::string::npos) {
            // process identifier of form namespace:identifier
            vec = splitStringBy(identifier, ':');
            if (vec.size() != 2)
                throw std::logic_error("Was expecting a vector of size 2");
        } else {
            throw std::logic_error("input string ("+ identifier +") does not contain "
                                   "either one of the accepted delimiters (\"/\" or \":\")");
        }
        this->resource_namespace = vec[0];
        this->identifier = vec[1];
    }

}
