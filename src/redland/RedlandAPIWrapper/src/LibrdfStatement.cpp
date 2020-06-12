//
// Created by Ciaran on 5/19/2020.
//

#include "LibrdfStatement.h"
#include "World.h"


namespace redland {

    LibrdfStatement::LibrdfStatement(librdf_statement *statement)
            : statement_(statement) {
        checkForNull();
    }

    LibrdfStatement::LibrdfStatement(librdf_node *subject, librdf_node *predicate, librdf_node *resource)
            : statement_(librdf_new_statement_from_nodes(
            World::getWorld(), subject, predicate, resource
    )) {
        checkForNull();
    }

    LibrdfStatement::LibrdfStatement(const LibrdfNode &subject, const LibrdfNode &predicate, const LibrdfNode &resource)
            : statement_(librdf_new_statement_from_nodes(
            World::getWorld(), subject.get(), predicate.get(), resource.get()
    )) {
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

        if (!statement_)
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: LibrdfStatement::checkForNull(): statement_ is null");
    }

    librdf_statement *LibrdfStatement::get() const {
        return statement_;
    }

    librdf_node *LibrdfStatement::getSubject() const {
        return librdf_statement_get_subject(statement_);
    }

    librdf_node *LibrdfStatement::getPredicate() const {
        return librdf_statement_get_predicate(statement_);
    }

    void LibrdfStatement::setSubject(librdf_node *node) {
        librdf_statement_set_subject(statement_, node);
    }

    void LibrdfStatement::setResource(librdf_node *node) {
        librdf_statement_set_object(statement_, node);
    }

    void LibrdfStatement::setPredicate(librdf_node *node) {
        librdf_statement_set_predicate(statement_, node);
    }

    librdf_node *LibrdfStatement::getResource() const {
        return librdf_statement_get_object(statement_);
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
            statement_ = librdf_new_statement_from_nodes(
                    World::getWorld(), getSubject(), getPredicate(), getResource()
            );
        }
    }

    /*
     *
     *
     * If I support a copy constructor, it might work
     * if add to the underlying reference counter myself?
     * Bad idea. but loads of allocation bugs when you delete
     * these constructors. So instead, finish making everything move
     * not copy then delete them!
     */
    LibrdfStatement::LibrdfStatement(const LibrdfStatement &statement) {
        std::cout << "calling LibrdfStatement copy constructor" << std::endl;
        if (this != &statement) {
            if (statement.statement_ != nullptr) {
                if (statement_ != nullptr) {
                    librdf_free_statement(statement_);
                    statement_ = nullptr;
                }
                statement_ = statement.statement_;
                statement.statement_->usage++;
            }
        }
    }

    LibrdfStatement &LibrdfStatement::operator=(const LibrdfStatement &statement) {
        std::cout << "calling LibrdfStatement copy assignment operator" << std::endl;
        if (this != &statement) {
            if (statement.statement_ != nullptr) {
                if (statement_ != nullptr) {
                    librdf_free_statement(statement_);
                    statement_ = nullptr;
                }
                statement_ = statement.statement_;
                statement.statement_->usage++;
            }
        }
        return *this;
    }


    LibrdfStatement::LibrdfStatement(LibrdfStatement &&statement) noexcept {
        std::cout << "calling LibrdfStatement move constructor" << std::endl;
        if (statement.statement_ != nullptr) {
            if (statement_ != nullptr) {
                librdf_free_statement(statement_);
                statement_ = nullptr;
            }
            statement_ = statement.statement_;
            statement.statement_ = nullptr;
        }
    }

    LibrdfStatement &LibrdfStatement::operator=(LibrdfStatement &&statement) noexcept {
        std::cout << "calling LibrdfStatement move assignment operator" << std::endl;
        if (this != &statement) {
            if (statement.statement_ != nullptr) {
                if (statement_ != nullptr) {
                    librdf_free_statement(statement_);
                    statement_ = nullptr;
                }
                statement_ = statement.statement_;
                statement.statement_ = nullptr;
            }
        }
        return *this;
    }

    void LibrdfStatement::freeStatement() {
        if (statement_) {
            librdf_free_statement(statement_);
            statement_ = nullptr;
        }

    }

    bool LibrdfStatement::isComplete() {
        return librdf_statement_is_complete(statement_);
    }

    bool LibrdfStatement::operator==(const LibrdfStatement &rhs) const {
        return librdf_statement_equals(statement_, rhs.statement_);
    }

    bool LibrdfStatement::operator!=(const LibrdfStatement &rhs) const {
        return !(rhs == *this);
    }
}