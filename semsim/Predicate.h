//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBSEMGEN_PREDICATE_H
#define LIBSEMGEN_PREDICATE_H

#include <utility>
#include <ostream>

#include "semsim/uri.h"

namespace semsim {
    class Predicate {
    private:
        Uri uri;

    public:

        explicit Predicate(Uri uri);
        explicit Predicate(std::string uri);

        const Uri &getUri() const;

        friend std::ostream &operator<<(std::ostream &os, const Predicate &predicate);

        bool operator==(const Predicate &rhs) const;

        bool operator!=(const Predicate &rhs) const;
    };
}

#endif //LIBSEMGEN_PREDICATE_H
