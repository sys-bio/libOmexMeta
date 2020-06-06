//
// Created by Ciaran on 5/19/2020.
//

#include "LibrdfStatement.h"
#include "World.h"


namespace redland {

    LibrdfStatement::LibrdfStatement(librdf_statement *statement)
            : statement_(std::shared_ptr<librdf_statement>(statement, raptor_free_statement)) {
        checkForNull();
    }

    LibrdfStatement::LibrdfStatement(librdf_node *subject, librdf_node *predicate, librdf_node *resource)
            : statement_(std::shared_ptr<librdf_statement>(
            librdf_new_statement_from_nodes(
                    World::getWorld(), subject, predicate, resource
            ), raptor_free_statement)) {
        checkForNull();
    }

    LibrdfStatement::LibrdfStatement(const LibrdfNode &subject, const LibrdfNode &predicate, const LibrdfNode &resource)
            : statement_(std::shared_ptr<librdf_statement>(
            librdf_new_statement_from_nodes(
                    World::getWorld(), subject.get(), predicate.get(), resource.get()
            ), raptor_free_statement)) {
        checkForNull();
    }


    void LibrdfStatement::checkForNull() {
        if (!getSubject())
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: LibrdfStatement::checkForNull(): subject_ node is null");

        if (!getPredicate()) //todo another check on underlying pointer if possible (so far checking for null causes seg fault)
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: LibrdfStatement::checkForNull(): predicate_ node is null");

        if (!getResource())
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: LibrdfStatement::checkForNull(): resource_ node is null");

        if (!statement_.get())
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: LibrdfStatement::checkForNull(): statement_ is null");
    }

    librdf_statement *LibrdfStatement::get() const {
        return statement_.get();
    }

    librdf_node *LibrdfStatement::getSubject() const {
        return librdf_statement_get_subject(statement_.get());
    }

    librdf_node *LibrdfStatement::getPredicate() const {
        return librdf_statement_get_predicate(statement_.get());
    }

    void LibrdfStatement::setSubject(librdf_node *node) {
        librdf_statement_set_subject(statement_.get(), node);
    }

    void LibrdfStatement::setResource(librdf_node *node) {
        librdf_statement_set_object(statement_.get(), node);
    }

    void LibrdfStatement::setPredicate(librdf_node *node) {
        librdf_statement_set_predicate(statement_.get(), node);
    }

    librdf_node *LibrdfStatement::getResource() const {
        return librdf_statement_get_object(statement_.get());
    }

    std::string LibrdfStatement::getResourceStr() const {
        if (!getResource())
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: LibrdfStatement::getResourceStr(): resource_ is nullptr");
        return LibrdfNode::str(getResource());
    }

    std::string LibrdfStatement::getSubjectStr() const {
        if (getSubject() == nullptr)
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: LibrdfStatement::getSubjectStr(): subject_ is nullptr");
        return LibrdfNode::str(getSubject());
    }

    std::string LibrdfStatement::getPredicateStr() const {
        if (!getPredicate())
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: LibrdfStatement::getPredicate(): predicate_ is nullptr");
        return LibrdfNode::str(getPredicate());
    }

    LibrdfStatement LibrdfStatement::fromRawStatementPtr(librdf_statement *statement) {
        return LibrdfStatement(statement);
    }

    LibrdfStatement
    LibrdfStatement::fromRawNodePtrs(librdf_node *subject, librdf_node *predicate, librdf_node *resource) {
        return LibrdfStatement(subject, predicate, resource);
    }

    void LibrdfStatement::refreshStatement() {
        if (getSubject() != nullptr &&
            getPredicate() != nullptr &&
            getResource() != nullptr) {
            statement_ = std::shared_ptr<librdf_statement>(
                    librdf_new_statement_from_nodes(
                            World::getWorld(), getSubject(), getPredicate(), getResource()
                    ), librdf_free_statement
            );
        }
    }

}