//
// Created by Ciaran on 5/19/2020.
//

#include "LibrdfStatement.h"
#include "World.h"


namespace redland {


    void LibrdfStatement::deleter::operator()(librdf_statement *statement) {
        if (statement)
            raptor_free_statement(statement);
    }


    LibrdfStatement::LibrdfStatement(librdf_statement *statement)
            : statement_(std::shared_ptr<librdf_statement>(statement, raptor_free_statement)) {
        subject_ = librdf_statement_get_subject(statement_.get());
        predicate_ = librdf_statement_get_predicate(statement_.get());
        resource_ = librdf_statement_get_object(statement_.get());
        checkForNull();
    }

    LibrdfStatement::LibrdfStatement(librdf_node *subject, librdf_node *predicate, librdf_node *resource)
            : subject_(subject),
              predicate_(predicate),
              resource_(resource) {
        statement_ = std::shared_ptr<librdf_statement>(
                librdf_new_statement_from_nodes(
                        World::getWorld(), subject_, predicate_, resource_
                ), raptor_free_statement
        );
        checkForNull();
    }

//    LibrdfStatement::LibrdfStatement(
//            librdf_node* subject, librdf_node* predicate, librdf_node* resource)
//            : subject_(subject), predicate_(predicate), resource_(resource) {
//        statement_ = std::shared_ptr<librdf_statement>(
//                librdf_new_statement_from_nodes(
//                        World::getWorld(), subject_, predicate_, resource_),
//                        raptor_free_statement
//        );
//        checkForNull();
//    }


    void LibrdfStatement::checkForNull() {
        if (!subject_)
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: LibrdfStatement::checkForNull(): subject_ node is null");

        if (!predicate_) //todo another check on underlying pointer if possible (so far checking for null causes seg fault)
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: LibrdfStatement::checkForNull(): predicate_ node is null");

        if (!resource_)
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
        return subject_;
    }

    librdf_node *LibrdfStatement::getPredicate() const {
        return predicate_;
    }

    librdf_node *LibrdfStatement::getResource() const {
        return resource_;
    }

    std::string LibrdfStatement::getResourceStr() const {
        if (!getResource())
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: LibrdfStatement::getResourceStr(): resource_ is nullptr");
        return LibrdfNode::str(getResource());
    }

    std::string LibrdfStatement::getSubjectStr() const {
        if (!getSubject())
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
        if (subject_ && predicate_ && resource_) {
            statement_ = std::shared_ptr<librdf_statement>(
                    librdf_new_statement_from_nodes(
                            World::getWorld(), subject_, predicate_, resource_
                    ), librdf_free_statement
            );
        }
    }
}