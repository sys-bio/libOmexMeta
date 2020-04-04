//
// Created by Ciaran on 4/4/2020.
//

#include "Triple.h"

#include <utility>

namespace semsim {

    Triple::Triple(Subject subject, Predicate predicate, Resource resource) : subject(std::move(subject)),
                                                                              predicate(std::move(predicate)),
                                                                              resource(std::move(resource)) {}

    const Subject &Triple::getSubject() const {
        return subject;
    }

    const Predicate &Triple::getPredicate() const {
        return predicate;
    }

    const Resource &Triple::getResource() const {
        return resource;
    }

    bool Triple::operator==(const Triple &rhs) const {
        return subject == rhs.subject &&
               predicate == rhs.predicate &&
               resource == rhs.resource;
    }

    bool Triple::operator!=(const Triple &rhs) const {
        return !(rhs == *this);
    }

    std::ostream &operator<<(std::ostream &os, const Triple &triple) {
        os << "Triple(subject="
           << triple.getSubject()
           << ", predicate="
           << triple.predicate
           << ", resource="
           << triple.resource;
        return os;
    }
}