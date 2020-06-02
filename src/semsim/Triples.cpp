//
// Created by Ciaran on 4/29/2020.
//
#include "Triples.h"

namespace semsim {


    Triples::Triples() = default;

    Triples::Triples(Triple triple) {
        triples_.push_back(std::make_shared<Triple>(std::move(triple)));
    }

    Triples::Triples(std::vector<Triple> triples) {
        for (auto &triple: triples) {
            triples_.push_back(std::make_shared<Triple>(std::move(triple)));
        }
    }

    void Triples::push_back(Triple triple) {
        triples_.push_back(std::make_shared<Triple>(std::move(triple)));
    }

    void Triples::push_back(const std::shared_ptr<Triple>& triple) {
        triples_.push_back(triple);
    }

    void Triples::emplace_back(Subject subject, const PredicatePtr& predicatePtr, const Resource& resource) {
        Triple triple(subject, predicatePtr, resource);
        triples_.push_back(std::make_shared<Triple>(std::move(triple)));
    }

    void Triples::emplace_back(Subject subject, const Predicate& predicate, const Resource& resource) {
        Triple triple(subject.getNode(), predicate.getNode(), resource.getNode());
        triples_.push_back(std::make_shared<Triple>(std::move(triple)));
    }

    void Triples::emplace_back(Subject subject, BiomodelsBiologyQualifier predicate, const Resource& resource) {
        Triple triple(subject, std::make_shared<BiomodelsBiologyQualifier>(std::move(predicate)),
                      resource);
        triples_.push_back(std::make_shared<Triple>(std::move(triple)));
    }

    void Triples::emplace_back(Subject subject, BiomodelsModelQualifier predicate, const Resource& resource) {
        Triple triple(subject, std::make_shared<BiomodelsModelQualifier>(std::move(predicate)),
                      resource);
        triples_.push_back(std::make_shared<Triple>(std::move(triple)));
    }

    void Triples::emplace_back(Subject subject, DCTerm predicate, const Resource& resource) {
        Triple triple(subject, std::make_shared<DCTerm>(std::move(predicate)), resource);
        triples_.push_back(std::make_shared<Triple>(std::move(triple)));
    }

    void Triples::emplace_back(Subject subject, SemSim predicate, const Resource& resource) {
        Triple triple(subject, std::make_shared<SemSim>(std::move(predicate)), resource);
        triples_.push_back(std::make_shared<Triple>(std::move(triple)));
    }

//    void Triples::emplace_back(LibrdfStatement statement) {
//        triples_.push_back(std::make_shared<Triple>(statement));
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

    SharedTripleVector::iterator Triples::begin() {
        return triples_.begin();
    }

    SharedTripleVector::iterator Triples::end() {
        return triples_.end();
    }

    std::string Triples::str(const std::string& format, const std::string& base) {

        // Here we create temporary set of tools for serializing a simple
        // triple.
        librdf_world *world = librdf_new_world();
        librdf_storage *storage = librdf_new_storage(world, "memory", "SemsimMemoryStore", nullptr);
        librdf_model *model = librdf_new_model(world, storage, nullptr);

        librdf_serializer *serializer = librdf_new_serializer(world, format.c_str(), nullptr, nullptr);
        for (auto &it : triples_) {
            // ensure we have three nodes and a statement
            if (!it->getSubject()) {
                throw RedlandNullPointerException("RedlandNullPointerException: Triples::str: subject is null");
            }
            if (!it->getPredicate()) {
                throw RedlandNullPointerException("RedlandNullPointerException: Triples::str: predicate is null");
            }
            if (!it->getResource()) {
                throw RedlandNullPointerException("RedlandNullPointerException: Triples::str: resource is null");
            }
            if (!it->getStatement()) {
                throw RedlandNullPointerException("RedlandNullPointerException: Triples::str: statement is null");
            }

            librdf_model_add_statement(model, it->getStatement().get());
            Predicate::addSeenNamespaceToSerializer(world, serializer, it->getPredicate());
        }

        // do the serializing
        librdf_uri *base_uri = librdf_new_uri(world, (const unsigned char *) base.c_str());
        unsigned char *string = librdf_serializer_serialize_model_to_string(serializer, base_uri, model);
        std::string str = (const char *) string;

        // free up resources
        free(string);
        librdf_free_serializer(serializer);
        librdf_free_uri(base_uri);
        librdf_free_model(model);
        librdf_free_storage(storage);
        librdf_free_world(world);
        return str;


    }

    void Triples::emplace_back(librdf_node* subject, librdf_node* predicate, librdf_node*resource) {
        Triple triple(subject, predicate, resource);
        std::shared_ptr<Triple> ptr = std::make_shared<Triple>(triple);
        triples_.push_back(ptr);
    }

}