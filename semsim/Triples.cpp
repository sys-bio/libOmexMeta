//
// Created by Ciaran on 4/29/2020.
//
#include "semsim/Error.h"
#include "semsim/Triples.h"

namespace semsim {


    Triples::Triples() = default;

    Triples::Triples(std::vector<Triple> triples) {
        triples_ = triples;
    }

    Triples::Triples(std::initializer_list <Triple> l){
        triples_ = l;
    }

    void Triples::push_back(Triple triple) {
        triples_.push_back(triple);
    }

    void Triples::emplace_back(librdf_world *world, Subject subject, PredicatePtr predicatePtr, Resource resource) {
        triples_.emplace_back(world, subject, predicatePtr, resource);

    }

    void Triples::emplace_back(librdf_world *world, librdf_statement *statement) {
        triples_.push_back(Triple::fromStatement(world, statement));
    }

    Subjects Triples::getSubjects() {
        Subjects subjects;
        for (auto &triple : triples_) {
            subjects.push_back(triple.getSubject());
        }
        return subjects;
    }

    PredicatePtrs Triples::getPredicates() {
        PredicatePtrs predicatePtrs;
        for (auto &triple: triples_) {
            predicatePtrs.push_back(triple.getPredicatePtr());
        }
        return predicatePtrs;
    }

    Resources Triples::getResources() {
        Resources resources;
        for (auto &triple: triples_) {
            resources.push_back(triple.getResource());
        }
        return resources;
    }

    int Triples::size() {
        return triples_.size();
    }

    std::vector<Triple>::iterator Triples::begin() {
        return triples_.begin();
    }

    std::vector<Triple>::iterator Triples::end() {
        return triples_.end();
    }

    std::string Triples::str(std::string format) {
        return "empty";
        //todo implement a writeTriples function in Writer
//        throw NotImplementedException("Not yet impemented");
    }


}