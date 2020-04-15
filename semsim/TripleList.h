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

        explicit TripleList(std::vector<Triple> triple_list);

        bool operator==(const TripleList &rhs) const;

        bool operator!=(const TripleList &rhs) const;

        semsim::Triple &operator[](unsigned long n);

        void push_back(const Triple& triple);



    };
}

#endif //LIBSEMGEN_TRIPLELIST_H
