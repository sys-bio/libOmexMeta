//
// Created by Ciaran on 4/15/2020.
//

#include "TripleList.h"

#include <utility>

bool semsim::TripleList::operator==(const semsim::TripleList &rhs) const {
    return triple_list_ == rhs.triple_list_;
}

bool semsim::TripleList::operator!=(const semsim::TripleList &rhs) const {
    return !(rhs == *this);
}

semsim::TripleList::TripleList(std::vector<Triple> triple_list)
        : triple_list_(std::move(triple_list)) {
}

semsim::Triple &semsim::TripleList::operator[](unsigned long n) {
    return triple_list_.operator[](n);
}

void semsim::TripleList::push_back(const Triple& triple) {
    triple_list_.push_back(triple);
}
