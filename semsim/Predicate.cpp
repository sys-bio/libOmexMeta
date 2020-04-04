//
// Created by Ciaran on 4/4/2020.
//

#include "Predicate.h"

#include <utility>


namespace semsim {


    Predicate::Predicate(Uri uri) : uri(std::move(uri)) {}

    Predicate::Predicate(std::string uri) : uri(Uri(std::move(uri))) {}

    const Uri &Predicate::getUri() const {
        return uri;
    }

    bool Predicate::operator==(const Predicate &rhs) const {
        return uri == rhs.uri;
    }

    bool Predicate::operator!=(const Predicate &rhs) const {
        return !(rhs == *this);
    }

    std::ostream &operator<<(std::ostream &os, const Predicate &predicate) {
        os << "Predicate(uri=" << predicate.getUri().str() << ")";
        return os;
    }
}
