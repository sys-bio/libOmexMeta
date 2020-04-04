//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBSEMGEN_TRIPLE_H
#define LIBSEMGEN_TRIPLE_H

#include <ostream>
#include "Subject.h"
#include "Predicate.h"
#include "Resource.h"

namespace semsim {
    class Triple {
        Subject subject;
        Predicate predicate;
        Resource resource;
    public:
        Triple(Subject subject, Predicate predicate, Resource resource);

        const Subject &getSubject() const;

        const Predicate &getPredicate() const;

        const Resource &getResource() const;

        bool operator==(const Triple &rhs) const;

        bool operator!=(const Triple &rhs) const;

        friend std::ostream &operator<<(std::ostream &os, const Triple &triple);
    };
}

#endif //LIBSEMGEN_TRIPLE_H
