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

    std::string Triple::str(const std::string &format, const std::string &base) const {
        // ensure we have three nodes and a statement
        if (!getSubject()) {
            throw RedlandNullPointerException("RedlandNullPointerException: Triple::str: subject is null");
        }
        if (!getPredicate()) {
            throw RedlandNullPointerException("RedlandNullPointerException: Triple::str: predicate is null");
        }
        if (!getResource()) {
            throw RedlandNullPointerException("RedlandNullPointerException: Triple::str: resource is null");
        }
        if (!statement_) {
            throw RedlandNullPointerException("RedlandNullPointerException: Triple::str: statement is null");
        }

        // Here we create temporary set of tools for serializing a simple
        // triple.
        librdf_world *world = librdf_new_world();
        librdf_storage *storage = librdf_new_storage(world, "memory", "SemsimMemoryStore", nullptr);
        librdf_model *model = librdf_new_model(world, storage, nullptr);

        librdf_model_add_statement(model, statement_);
        librdf_serializer *serializer = librdf_new_serializer(world, format.c_str(), nullptr, nullptr);

        // deal with namespaces
        Predicate::addSeenNamespaceToSerializer(world, serializer, getPredicate());

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

    semsim::Triple &semsim::Triple::setAbout(const std::string &about) {
        if (getSubject() != nullptr)
            LibrdfNode::freeNode(getSubject());
        setSubject(LibrdfNode::fromUriString(about).get());
        return *this;
    }

    semsim::Triple &
    semsim::Triple::setPredicate(const std::string &namespace_, const std::string &term) {
        if (getPredicate() != nullptr)
            LibrdfNode::freeNode(getPredicate());
        // ive implemented the logic here rather then using LibrdfStatement::setPredicate
        //  because I want them both to be called setPredicate.
        librdf_node* node = PredicateFactory(namespace_, term)->getNode();
        librdf_statement_set_predicate(statement_, node);
        return *this;
    }

    semsim::Triple &
    semsim::Triple::setPredicate(const std::string &uri) {
        if (getPredicate() != nullptr)
            LibrdfNode::freeNode(getPredicate());
        LibrdfNode node = LibrdfNode::fromUriString(uri);
        // we pass ownership of node to the statement.
        librdf_statement_set_predicate(statement_, node.get());
        return *this;
    }


    semsim::Triple &semsim::Triple::setResourceLiteral(const std::string &literal) {
        // if getResource() node alredy exists, free before resetting
        if (getResource() != nullptr)
            LibrdfNode::freeNode(getResource());
        setResource(LibrdfNode::fromLiteral(literal).get());
        return *this;
    }

    semsim::Triple &semsim::Triple::setResourceUri(const std::string &identifiers_uri) {
        if (getResource() != nullptr)
            LibrdfNode::freeNode(getResource());
        setResource(LibrdfNode::fromUriString(identifiers_uri).get());
        return *this;
    }

    semsim::Triple &semsim::Triple::setResourceBlank(const std::string &blank_id) {
        if (getResource() != nullptr)
            LibrdfNode::freeNode(getResource());
        setResource(LibrdfNode::fromBlank(blank_id).get());
        return *this;
    }

    std::string semsim::Triple::getAbout() const {
        return LibrdfNode::str(getSubject());
    }

    bool Triple::isEmpty() {
        return !getSubject() && !getPredicate() && !getResource();
    }

    librdf_statement* Triple::getStatement() const {
        return statement_;
    }

}

