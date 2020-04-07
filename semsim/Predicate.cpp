//
// Created by Ciaran on 4/4/2020.
//

#include "Predicate.h"
#include "ControlledVocabulary.h"

namespace semsim {

    Predicate::Predicate(const std::shared_ptr<ControlledVocabulary> &term) {
        this->term = term;
    }

    bool Predicate::operator==(const Predicate &rhs) const {
        return *term == *rhs.term;
    }

    bool Predicate::operator!=(const Predicate &rhs) const {
        return !(rhs == *this);
    }

    std::ostream &operator<<(std::ostream &os, const Predicate &predicate) {
        os << "Predicate(" << *predicate.term << ")";
        return os;
    }

    Uri Predicate::getUri() const {
        return term->getUri();
    }

    const std::shared_ptr<ControlledVocabulary> &Predicate::getTerm() const {
        return term;
    }
}


