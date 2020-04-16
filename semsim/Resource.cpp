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
        // check whether user has given full html
        if (identifier.rfind("https://", 0) == 0) {
            // if yes, and it isn't an identifiers.org link, throw an error
            if (identifier.rfind("https://identifiers.org", 0) != 0) {
                std::ostringstream err;
                err << __FILE__ << ":" << __LINE__ << ": url detected but it doesn't "
                                                      "start with \"https://identifiers.org\". All "
                                                      "resources must be resolvable with "
                                                      "\"https://identifiers.org\". For example:"
                                                      "\"https://identifiers.org/uniprot/P0DP23\"" << std::endl;
                throw std::invalid_argument(err.str());
            }
            // otherwise, extract the needed bits from the url
            std::vector<std::string> html_vec = splitStringBy(identifier, '/');
            int html_vec_size = html_vec.size();
            // we want the second to last and last elements in the split url
            this->resource_namespace = html_vec[html_vec_size - 2];
            this->identifier = html_vec[html_vec_size - 1];
        }

        // if the string isn't a url
        else {
            // check to see whether "/" is in the string
            if (identifier.find('/') != std::string::npos) {
                // if so, process identifier of form namespace/identifier
                vec = splitStringBy(identifier, '/');
                if (vec.size() != 2)
                    throw std::logic_error("Was expecting a vector of size 2");
            } else if (identifier.find(':') != std::string::npos) {
                // otherwise process identifier of form namespace:identifier
                vec = splitStringBy(identifier, ':');
                if (vec.size() != 2)
                    throw std::logic_error("Was expecting a vector of size 2");
            } else {
                // anything else is an error
                throw std::logic_error("input string (" + identifier + ") does not contain "
                                                                       "either one of the accepted delimiters (\"/\" or \":\")");
            }
            this->resource_namespace = vec[0];
            this->identifier = vec[1];
        }
    }

}
