//
// Created by Ciaran on 4/29/2020.
//
#include "omexmeta/Triples.h"


namespace omexmeta {


    Triples::Triples() = default;

    Triples::Triples(Triple &triple) {
        moveBack(triple);
    }

    Triples::Triples(std::vector<Triple> triples) {
        for (auto &triple: triples) {
            moveBack(triple);
        }
    }

    /**
     * @brief moves a Triple object to the back of Triples
     * @param triple The Triple object to move.
     * @details The vector storing the Triples is increased
     * in size by 1 and the @param triple is moved into that
     * slot. Therefore, ownership of the triple passes to
     * the Triples object who is reposible for freeing the Triple.
     */
    void Triples::moveBack(Triple &triple) {
        // This move calls Triple destrubtor?
        triples_.push_back(std::move(triple));
    }

//    void Triples::emplace_back(UriHandler& uriHandler, librdf_node *subject, librdf_node *predicate, librdf_node *resource) {
//        Triple triple(uriHandler, subject, predicate, resource);
//        moveBack(triple);
//    }

    void Triples::emplace_back(UriHandler& uriHandler, LibrdfNode subject, const PredicatePtr &predicatePtr, const LibrdfNode &resource) {
        Triple triple(uriHandler, subject, predicatePtr->getNode(), resource);
        moveBack(triple);
    }

    void Triples::emplace_back(UriHandler& uriHandler, const LibrdfNode& subject, const LibrdfNode& predicate, const LibrdfNode &resource) {
        Triple triple(uriHandler, subject, predicate, resource);
        // creating a triple, a wrapper around a shared poitner. So we increment the usage count
        moveBack(triple);
    }

    void Triples::emplace_back(UriHandler& uriHandler, LibrdfNode subject, const Predicate &predicate, const LibrdfNode &resource) {
        LibrdfNode p = LibrdfNode::fromUriString(predicate.getNamespace());
        Triple triple(uriHandler, subject, p, resource);
        moveBack(triple);
    }

//    void Triples::emplace_back(UriHandler& uriHandler, LibrdfNode subject, BiomodelsBiologyQualifier predicate, const LibrdfNode &resource) {
//        Triple triple(uriHandler, subject, std::make_shared<BiomodelsBiologyQualifier>(std::move(predicate)).get(), resource);
//        moveBack(triple);
//    }
//
//    void Triples::emplace_back(UriHandler& uriHandler, LibrdfNode subject, BiomodelsModelQualifier predicate, const LibrdfNode &resource) {
//        Triple triple(uriHandler, subject, std::make_shared<BiomodelsModelQualifier>(std::move(predicate))->get(), resource);
//        moveBack(triple);
//    }
//
//    void Triples::emplace_back(UriHandler& uriHandler, LibrdfNode subject, DCTerm predicate, const LibrdfNode &resource) {
//        Triple triple(uriHandler, subject, std::make_shared<DCTerm>(std::move(predicate))->get(), resource);
//        moveBack(triple);
//    }
//
//    void Triples::emplace_back(UriHandler& uriHandler, LibrdfNode subject, SemSim predicate, const LibrdfNode &resource) {
//        Triple triple(uriHandler, subject, std::make_shared<SemSim>(std::move(predicate))->get(), resource);
//        moveBack(triple);
//    }

    std::vector<std::string> Triples::getSubjectsStr() {
        std::vector<std::string> vec;
        for (auto &triple : triples_) {
            vec.push_back(triple.getSubjectNode().str());
        }
        return vec;
    }

    std::vector<std::string> Triples::getPredicates() {
        std::vector<std::string> vec;
        for (auto &triple: triples_) {
            vec.push_back(triple.getPredicateNode().str());
        }
        return vec;
    }

    std::vector<std::string> Triples::getResources() {
        std::vector<std::string> vec;
        for (auto &triple: triples_) {
            vec.push_back(triple.getResourceNode().str());
        }
        return vec;
    }

    int Triples::size() const {
        return triples_.size();
    }

    TripleVector::iterator Triples::begin() {
        return triples_.begin();
    }

    TripleVector::iterator Triples::end() {
        return triples_.end();
    }

    Triple Triples::pop() {
        // get reference to back of triples_ vector
        Triple triple = triples_.back();
        // then remove it from the triples_ vector
        triples_.pop_back();
        // return by move so no copies are made.
        return std::move(triple);
    }


    void Triples::freeTriples() {
        for (auto& triple: triples_){
            triple.freeTriple();
        }
        triples_ = std::vector<Triple>();
    }

    bool Triples::isEmpty() {
        return triples_.empty();
    }

    Triple &Triples::operator[](int index) {
        return triples_[index];
    }

    const Triple &Triples::operator[](int index) const {
        return triples_[index];
    }

    bool Triples::operator==(const Triples &rhs) const {
        return triples_ == rhs.triples_;
    }

    bool Triples::operator!=(const Triples &rhs) const {
        return !(rhs == *this);
    }

    Triples::Triples(int size) {
        triples_.reserve(size);
    }

    int Triples::capacity() {
        return triples_.capacity();
    }

}