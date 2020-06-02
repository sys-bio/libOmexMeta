//
// Created by Ciaran on 4/4/2020.
//

#include "Triple.h"


namespace semsim {

    Triple::Triple(const Subject &subject, const PredicatePtr &predicate_ptr, const Resource &resource)
            : LibrdfStatement(subject.getNode(),
                              predicate_ptr->getNode(),
                              resource.getNode()) {
    }

    Triple::Triple(librdf_node *subject, librdf_node *predicate, librdf_node *resource) :
            LibrdfStatement(subject, predicate, resource) {}

    Triple Triple::fromRawStatementPtr(librdf_statement *statement) {
        return Triple(statement);
    }

    Triple::Triple(librdf_statement *statement) : LibrdfStatement(statement) {}

    std::string Triple::str(const std::string &format, const std::string &base) {
        // ensure we have three nodes and a statement
        if (!subject_){
            throw RedlandNullPointerException("RedlandNullPointerException: Triple::str: subject is null");
        }
        if (!predicate_){
            throw RedlandNullPointerException("RedlandNullPointerException: Triple::str: predicate is null");
        }
        if (!resource_){
            throw RedlandNullPointerException("RedlandNullPointerException: Triple::str: resource is null");
        }
        if (!statement_){
            throw RedlandNullPointerException("RedlandNullPointerException: Triple::str: statement is null");
        }

        // Here we create temporary set of tools for serializing a simple
        // triple.
        librdf_world *world = librdf_new_world();
        librdf_storage *storage = librdf_new_storage(world, "memory", "SemsimMemoryStore", nullptr);
        librdf_model *model = librdf_new_model(world, storage, nullptr);

        librdf_model_add_statement(model, statement_.get());
        librdf_serializer *serializer = librdf_new_serializer(world, format.c_str(), nullptr, nullptr);

        // deal with namespaces
        Predicate::addSeenNamespaceToSerializer(world,serializer, predicate_);

        // do the serializing
        librdf_uri *base_uri = librdf_new_uri(world, (const unsigned char *) base.c_str());
        unsigned char* string = librdf_serializer_serialize_model_to_string(serializer, base_uri, model);
        std::string str = (const char*)string;

        // free up resources
        free(string);
        librdf_free_serializer(serializer);
        librdf_free_uri(base_uri);
        librdf_free_model(model);
        librdf_free_storage(storage);
        librdf_free_world(world);
        return str;

    }

    semsim::Triple &semsim::Triple::setAbout(const std::string &about) {
        if (subject_)
            LibrdfNode::freeNode(subject_);
        subject_ = LibrdfNode::fromUriString(about);
        refreshStatement();
        return (*this);
    }

    std::string semsim::Triple::getAbout() const {
        return LibrdfNode::str(subject_);
    }

    semsim::Triple &
    semsim::Triple::setPredicate(const std::string &namespace_, const std::string &term) {
        if (predicate_)
            LibrdfNode::freeNode(predicate_);
        predicate_ = semsim::PredicateFactory(namespace_, term)->getNode();
        refreshStatement();
        return *this;
    }


    semsim::Triple &semsim::Triple::setResourceLiteral(const std::string &literal) {
        // if resource_ node alredy exists, free before resetting
        if (resource_)
            LibrdfNode::freeNode(resource_);
        resource_ = LibrdfNode::fromLiteral(literal);
        refreshStatement();
        return *this;
    }

    semsim::Triple &semsim::Triple::setResourceUri(const std::string &identifiers_uri) {
        if (resource_)
            LibrdfNode::freeNode(resource_);
        resource_ = LibrdfNode::fromUriString(identifiers_uri);
        refreshStatement();
        return *this;
    }

    semsim::Triple &semsim::Triple::setResourceBlank(const std::string &blank_id) {
        if (resource_)
            LibrdfNode::freeNode(resource_);
        resource_ = LibrdfNode::fromBlank(blank_id);
        refreshStatement();
        return *this;
    }

    bool Triple::isEmpty() {
        return !subject_ && !predicate_ && !resource_;
    }

    std::shared_ptr<librdf_statement> Triple::getStatement() const {
        return statement_;
    }

}

