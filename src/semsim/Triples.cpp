//
// Created by Ciaran on 4/29/2020.
//
#include "Triples.h"

namespace semsim {


    Triples::Triples() = default;

    Triples::Triples(Triple triple) {
        triples_.push_back(std::make_unique<Triple>(std::move(triple)));
    }

    Triples::Triples(std::vector<Triple> triples) {
        for (auto &triple: triples) {
            triples_.push_back(std::make_unique<Triple>(std::move(triple)));
        }
    }

    void Triples::push_back(Triple triple) {
        triples_.push_back(std::make_unique<Triple>(std::move(triple)));
    }

    void Triples::emplace_back(Subject subject, PredicatePtr predicatePtr, Resource resource) {
        Triple triple(std::move(subject), std::move(predicatePtr), std::move(resource));
        triples_.push_back(std::make_unique<Triple>(std::move(triple)));
    }

    void Triples::emplace_back(Subject subject, Predicate predicate, Resource resource) {
        Triple triple(std::move(subject), std::move(predicate), std::move(resource));
        triples_.push_back(std::make_unique<Triple>(std::move(triple)));
    }

    void Triples::emplace_back(Subject subject, BiomodelsBiologyQualifier predicate, Resource resource) {
        Triple triple(std::move(subject), std::make_unique<BiomodelsBiologyQualifier>(std::move(predicate)),
                       std::move(resource));
        triples_.push_back(std::make_unique<Triple>(std::move(triple)));
    }

    void Triples::emplace_back(Subject subject, BiomodelsModelQualifier predicate, Resource resource) {
        Triple triple(std::move(subject), std::make_unique<BiomodelsModelQualifier>(std::move(predicate)),
                       std::move(resource));
        triples_.push_back(std::make_unique<Triple>(std::move(triple)));
    }

    void Triples::emplace_back(Subject subject, DCTerm predicate, Resource resource) {
        Triple triple(std::move(subject), std::make_unique<DCTerm>(std::move(predicate)), std::move(resource));
        triples_.push_back(std::make_unique<Triple>(std::move(triple)));
    }

    void Triples::emplace_back(Subject subject, SemSim predicate, Resource resource) {
        Triple triple(std::move(subject), std::make_unique<SemSim>(std::move(predicate)), std::move(resource));
        triples_.push_back(std::make_unique<Triple>(std::move(triple)));
    }

//    void Triples::emplace_back(LibrdfStatement statement) {
//        triples_.push_back(std::make_unique<Triple>(statement));
//    }


    std::vector<std::string> Triples::getSubjectsStr() {
        std::vector<std::string> vec;
        for (auto &triple : triples_) {
            vec.push_back(triple->getSubjectStr());
        }
        return vec;
    }

    std::vector<std::string> Triples::getPredicates() {
        std::vector<std::string> vec;
        for (auto &triple: triples_) {
            vec.push_back(triple->getPredicateStr());
        }
        return vec;
    }

    std::vector<std::string> Triples::getResources() {
        std::vector<std::string> vec;
        for (auto &triple: triples_) {
            vec.push_back(triple->getResourceStr());
        }
        return vec;
    }

    int Triples::size() {
        return triples_.size();
    }

    UniqueTripleVector::iterator Triples::begin() {
        return triples_.begin();
    }

    UniqueTripleVector::iterator Triples::end() {
        return triples_.end();
    }

//    std::string Triples::str(std::string format, std::string base) {
//        LibrdfWorld world;
////
////        LibrdfStorage storage = world.newStorage("memory", "temp_storage");
////        LibrdfModel model = world.newModel(storage);
////        LibrdfSerializer serializer(librdf_new_serializer())
//        return TripleWriter(*this, base, format).toString();
//    }

}