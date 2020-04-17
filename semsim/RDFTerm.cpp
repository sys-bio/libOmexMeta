//
// Created by Ciaran on 4/17/2020.
//

#include "RDFTerm.h"
#include <regex>
#include <utility>


/************************************************
 * RDFTerm methods
 */


std::string semsim::RDFTerm::str() const {
    return "None";
}

semsim::RDFTerm *semsim::RDFTerm::clone() const {
    return const_cast<RDFTerm *>(this);
}


/************************************************
 * URITerm methods
 */

semsim::URITerm::URITerm(std::string uri)
        : uri_(std::move(uri)) {
}

std::string semsim::URITerm::str() const {
    return uri_;
}

semsim::URITerm::URITerm(std::string uri, std::string fragment) :
        uri_(std::move(uri)),
        fragment_(std::move(fragment)) {
}

const std::string &semsim::URITerm::getUri() const {
    return uri_;
}


semsim::URITerm *semsim::URITerm::clone() const {
    return new URITerm(*this);
}


/************************************************
 * IdentifiersURITerm methods
 */

std::string semsim::IdentifiersURITerm::str() const {
    std::regex http_regex("https://");
    std::regex identifiers_org_form1("^(?![https://])([A-Za-z0-9]*):{1}(\\S*)");
    std::regex identifiers_org_form2("^(?![https://])([A-Za-z0-9]*)/{1}(\\S*)");

    std::smatch m;

    if (std::regex_search(getUri(), m, identifiers_org_form1)) {
        // if its not html string check for form uniprot:identifier
        return identifiers_uri_ + std::string(m[1]) + "/" + std::string(m[2]);
    } else if (std::regex_search(getUri(), m, identifiers_org_form2)) {
        // if its not html string check for form uniprot/identifier
        return identifiers_uri_ + std::string(m[1]) + "/" + std::string(m[2]);
    } else {
        return getUri();
    }
}

semsim::IdentifiersURITerm *semsim::IdentifiersURITerm::clone() const {
    return new IdentifiersURITerm(*this);
}

semsim::IdentifiersURITerm::IdentifiersURITerm(std::string resource) : URITerm(resource) {}



/************************************************
 * RelativeURITerm methods
 */

std::string semsim::RelativeURITerm::str() const {

}

semsim::RelativeURITerm *semsim::RelativeURITerm::clone() const {
    return new RelativeURITerm(*this);
}

semsim::RelativeURITerm::RelativeURITerm(std::string resource) : URITerm(resource) {}


/************************************************
 * LiteralTerm methods
 */

semsim::LiteralTerm::LiteralTerm(std::string
                                 literal) : literal_(literal) {

}

semsim::LiteralTerm::LiteralTerm(std::string
                                 literal, std::string
                                 language_tag)
        : literal_(literal), language_tag_(language_tag) {
    datatype_ = language_datatype_str_;
}

std::string semsim::LiteralTerm::str() const {
    return literal_;
}

semsim::LiteralTerm *semsim::LiteralTerm::clone() const {
    return new LiteralTerm(*this);
}


/************************************************
 * BlankTerm methods
 */

std::string semsim::BlankTerm::str() const {
    return term_;
}

semsim::BlankTerm::BlankTerm(std::string
                             term) : term_(std::move(term)) {

}

semsim::BlankTerm *semsim::BlankTerm::clone() const {
    return new BlankTerm(*this);
}

