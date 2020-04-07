//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBSEMGEN_PREDICATE_H
#define LIBSEMGEN_PREDICATE_H

#include <utility>
#include <ostream>
#include <memory>

#include "semsim/uri.h"
#include "semsim/ControlledVocabulary.h"

namespace semsim {
    class Predicate {
    private:
        std::shared_ptr<ControlledVocabulary> term;

    public:

        Predicate() = default;

        explicit Predicate(const std::shared_ptr<ControlledVocabulary> &term);

        bool operator==(const Predicate &rhs) const;

        bool operator!=(const Predicate &rhs) const;

        friend std::ostream &operator<<(std::ostream &os, const Predicate &predicate);

        Uri getUri() const;

        const std::shared_ptr<ControlledVocabulary> &getTerm() const;
    };

}

#endif //LIBSEMGEN_PREDICATE_H
