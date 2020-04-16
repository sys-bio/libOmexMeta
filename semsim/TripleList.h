//
// Created by Ciaran on 4/15/2020.
//

#ifndef LIBSEMGEN_TRIPLELIST_H
#define LIBSEMGEN_TRIPLELIST_H

#include <vector>
#include "semsim/Triple.h"

namespace semsim {
    class TripleList {
    private:
        std::vector<Triple> triple_list_;

    public:

        TripleList() = default;

        explicit TripleList(const std::vector<Triple> &triples);

        bool operator==(const TripleList &rhs) const;

        bool operator!=(const TripleList &rhs) const;

        semsim::Triple &operator[](unsigned long n);

        void push_back(const Triple& triple);

        void emplace_back(const Subject &subject, const Predicate &predicate, const Resource &resource);

    };
}

#endif //LIBSEMGEN_TRIPLELIST_H
