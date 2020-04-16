//
// Created by Ciaran on 4/15/2020.
//

#include "TripleList.h"

#include <utility>
#include <cstdarg>

bool semsim::TripleList::operator==(const semsim::TripleList &rhs) const {
    return triple_list_ == rhs.triple_list_;
}

bool semsim::TripleList::operator!=(const semsim::TripleList &rhs) const {
    return !(rhs == *this);
}

//semsim::TripleList::TripleList(std::vector<Triple> triple_list)
//        : triple_list_(std::move(triple_list)) {
//}

semsim::Triple &semsim::TripleList::operator[](unsigned long n) {
    return triple_list_.operator[](n);
}

semsim::TripleList::TripleList(const std::vector<Triple> &triples) {
    this->triple_list_ = triples;
}

void semsim::TripleList::push_back(const Triple &triple) {
    triple_list_.push_back(triple);
}

void semsim::TripleList::emplace_back(const Subject &subject, const Predicate &predicate, const Resource &resource) {
    triple_list_.emplace_back(subject, predicate, resource);
}

