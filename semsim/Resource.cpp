//
// Created by Ciaran on 4/4/2020.
//

#include "semsim/Resource.h"

#include <utility>
#include <regex>
#include "uri.h"
#include "sstream"
#include "iterator"
#include "SemsimUtils.h"

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
        os << "Resource(" << resource.str() << ")";
        return os;
    }

    std::string Resource::str() const {
        if (is_literal_) {
            return this->literal;
        }

        std::ostringstream os;
        os << identifiers_base << "/"
           << resource_namespace << "/"
           << identifier;
        return os.str();
    }

    static std::vector<std::string> splitStringBy(std::string delimiter);

    Resource::Resource(const std::string &identifier) {
        std::regex http_regex("https://");
        std::regex identifiers_org_form1("^(?![https://])([A-Za-z0-9]*):{1}(\\S*)");
        std::regex identifiers_org_form2("^(?![https://])([A-Za-z0-9]*)/{1}(\\S*)");

        std::smatch m;

        // check whether user has given full url
        if (std::regex_search(identifier, http_regex)) {
            // if yes, and it isn't an identifiers.org link, throw an error
            if (identifier.rfind("https://identifiers.org/", 0) != 0) {
                std::ostringstream err;
                err << __FILE__ << ":" << __LINE__ << ": Url \"" << identifier << "\" detected but it doesn't "
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

            // if its not html string check for form uniprot:identifier
        else if (std::regex_search(identifier, m, identifiers_org_form1)) {
            this->resource_namespace = m[1];
            this->identifier = m[2];
        }

            // if its not html string check for form uniprot/identifier
        else if (std::regex_search(identifier, m, identifiers_org_form2)) {
            this->resource_namespace = m[1];
            this->identifier = m[2];
        } else {
            // its a literal
            is_literal_ = true;
            literal = identifier;
        }
    }


    std::vector<std::string> Resource::splitStringBy(const std::string &str, char delimiter) {
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

    bool Resource::isLiteral() const {
        return is_literal_;
    }


}


