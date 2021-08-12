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

    std::string
    Triples::str(const std::string &format, std::string base, std::string omex_name, std::string model_name) {
        base = OmexMetaUtils::prepareBaseUri(base);
        // Here we create temporary set of tools for serializing a simple
        // triple.
        librdf_world *world = librdf_new_world();
        librdf_storage *storage = librdf_new_storage(world, "memory", "SemsimMemoryStore", nullptr);
        librdf_model *model = librdf_new_model(world, storage, nullptr);

        librdf_serializer *serializer = librdf_new_serializer(world, format.c_str(), nullptr, nullptr);
        for (auto &it : triples_) {
            // ensure we have three nodes and a statement
            if (it.getSubjectNode().isNull()) {
                throw RedlandNullPointerException("RedlandNullPointerException: Triples::str: subject is null");
            }
            if (it.getPredicateNode().isNull()) {
                throw RedlandNullPointerException("RedlandNullPointerException: Triples::str: predicate is null");
            }
            if (it.getResourceNode().isNull()) {
                throw RedlandNullPointerException("RedlandNullPointerException: Triples::str: resource is null");
            }
            if (!it.getStatement()) {
                throw RedlandNullPointerException("RedlandNullPointerException: Triples::str: statement is null");
            }
            librdf_model_add_statement(model, it.getStatement());
            Predicate::addSeenNamespaceToSerializer(world, serializer, it.getPredicateNode().obj_);
        }

        // turn off base uri
        LibrdfUri write_base_uri_uri = LibrdfUri("http://feature.librdf.org/raptor-writeBaseURI");
        LibrdfNode write_base_uri_node = LibrdfNode::fromLiteral("0");
        librdf_serializer_set_feature(serializer, write_base_uri_uri.get(), write_base_uri_node.get());

        std::vector<std::string> nsvec = OmexMetaUtils::configurePrefixStrings("http://omex-library.org/",
                                                                               std::move(omex_name),
                                                                               std::move(model_name));

        // make uri's for the namespaces
        librdf_uri *OMEXlib = librdf_new_uri(LibrdfWorld::getWorld(), (const unsigned char *) nsvec[0].c_str());
        librdf_uri *myomex = librdf_new_uri(LibrdfWorld::getWorld(), (const unsigned char *) nsvec[1].c_str());
        librdf_uri *local = librdf_new_uri(LibrdfWorld::getWorld(), (const unsigned char *) nsvec[2].c_str());
        librdf_serializer_set_namespace(serializer, OMEXlib, "OMEXlib");
        librdf_serializer_set_namespace(serializer, myomex, "myOMEX");
        librdf_serializer_set_namespace(serializer, local, "local");

        // free the uri's now that we're done with them.
        librdf_free_uri(OMEXlib);
        librdf_free_uri(myomex);
        librdf_free_uri(local);

        librdf_uri *base_uri = librdf_new_uri(world, (const unsigned char *) OmexMetaUtils::prepareBaseUri(base).c_str());
        // do the serializing
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