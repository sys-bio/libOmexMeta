//
// Created by Ciaran on 5/19/2020.
//

#include "redland/LibrdfStatement.h"
#include "redland/World.h"


namespace redland {

    LibrdfStatement::~LibrdfStatement(){
        freeStatement();
    }

    LibrdfStatement::LibrdfStatement(librdf_statement *statement)
        : statement_(statement) {
        checkForNull();
    }

    LibrdfStatement::LibrdfStatement(librdf_node *subject, librdf_node *predicate, librdf_node *resource)
        : statement_(librdf_new_statement_from_nodes(
                  World::getWorld(), subject, predicate, resource)) {
        checkForNull();
    }

    LibrdfStatement::LibrdfStatement(const LibrdfNode &subject, const LibrdfNode &predicate, const LibrdfNode &resource)
        : statement_(librdf_new_statement_from_nodes(
                  World::getWorld(), subject.get(), predicate.get(), resource.get())) {
        checkForNull();
    }


    void LibrdfStatement::checkForNull() {
        if (!getSubject())
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: LibrdfStatement::checkForNull(): subject_ node is null");

        if (!getPredicate())//todo another check on underlying pointer if possible (so far checking for null causes seg fault)
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

    librdf_statement *LibrdfStatement::getWithoutIncrement() const {
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
                    "RedlandNullPointerException: LibrdfStatement::getIsVersionOfValue(): resource_ is nullptr");
        return LibrdfNode::str(getResource());
    }

    std::string LibrdfStatement::getSubjectStr() const {
        if (getSubject() == nullptr)
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: LibrdfStatement::getAbout(): subject_ is nullptr");
        return LibrdfNode::str(getSubject());
    }

    std::string LibrdfStatement::getPredicateStr() const {
        if (!getPredicate())
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: LibrdfStatement::getPredicate(): predicate_ is nullptr");
        return LibrdfNode::str(getPredicate());
    }

    std::string LibrdfStatement::getPredicateNamespaceStr() const {
        if (!getPredicate())
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: LibrdfStatement::getPredicate(): predicate_ is nullptr");
        return LibrdfNode(getPredicate()).getNamespace();
    }

    LibrdfStatement LibrdfStatement::fromRawStatementPtr(librdf_statement *statement) {
        return LibrdfStatement(statement);
    }

    LibrdfStatement
    LibrdfStatement::fromRawNodePtrs(librdf_node *subject, librdf_node *predicate, librdf_node *resource) {
        return {subject, predicate, resource};
    }

    void LibrdfStatement::refreshStatement() {
        if (getSubject() != nullptr &&
            getPredicate() != nullptr &&
            getResource() != nullptr) {
            statement_ = librdf_new_statement_from_nodes(
                    World::getWorld(), getSubject(), getPredicate(), getResource());
        }
    }

    LibrdfStatement::LibrdfStatement(LibrdfStatement &&statement) noexcept {
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
        if (!statement_)
            return;
        int usageCount = getUsage();
        librdf_free_statement(statement_);
        if (usageCount == 0){
            statement_ = nullptr;
        }
    }

    void LibrdfStatement::freeStatementAndUris() {
        /*
         * It looks like URIs do not get freed with librdf_statement.
         * So we do it here
         */
        if (statement_ != nullptr) {
            librdf_node *subject = getSubject();
            if (subject != nullptr) {
                if (subject->type == RAPTOR_TERM_TYPE_URI && subject->value.uri != nullptr) {
                    librdf_free_uri(subject->value.uri);
                } else if (subject->type == RAPTOR_TERM_TYPE_LITERAL && subject->value.literal.datatype != nullptr) {
                    librdf_free_uri(subject->value.literal.datatype);
                }
            }
            librdf_node *predicate = getPredicate();
            if (predicate != nullptr) {
                if (predicate->type == RAPTOR_TERM_TYPE_URI && predicate->value.uri != nullptr) {
                    librdf_free_uri(predicate->value.uri);
                } else if (predicate->type == RAPTOR_TERM_TYPE_LITERAL && predicate->value.literal.datatype != nullptr) {
                    librdf_free_uri(predicate->value.literal.datatype);
                }
            }
            librdf_node *resource = getResource();
            if (resource != nullptr) {
                if (resource->type == RAPTOR_TERM_TYPE_URI && resource->value.uri != nullptr) {
                    librdf_free_uri(resource->value.uri);
                } else if (resource->type == RAPTOR_TERM_TYPE_LITERAL && resource->value.literal.datatype != nullptr) {
                    librdf_free_uri(resource->value.literal.datatype);
                }
            }
            librdf_free_statement(statement_);
            statement_ = nullptr;
        }
    }

    bool LibrdfStatement::isComplete() {
        return librdf_statement_is_complete(statement_);
    }

    bool LibrdfStatement::equals(librdf_statement *first, librdf_statement *second) {
        if (!first) {
            throw std::logic_error("LibrdfStatement::equals:: first statement is null");
        }
        if (!second) {
            throw std::logic_error("LibrdfStatement::equals:: second statement is null");
        }
        librdf_node *this_subject = librdf_statement_get_subject(first);
        if (!this_subject) {
            throw std::logic_error("LibrdfStatement::equals:: this_subject is null");
        }
        librdf_node *this_predicate = librdf_statement_get_predicate(first);
        if (!this_predicate) {
            throw std::logic_error("LibrdfStatement::equals:: this_predicate is null");
        }
        librdf_node *this_resource = librdf_statement_get_object(first);
        if (!this_resource) {
            throw std::logic_error("LibrdfStatement::equals:: this_resource is null");
        }

        librdf_node *that_subject = librdf_statement_get_subject(second);
        if (!that_subject) {
            throw std::logic_error("LibrdfStatement::equals:: that_subject is null");
        }
        librdf_node *that_predicate = librdf_statement_get_predicate(second);
        if (!that_predicate) {
            throw std::logic_error("LibrdfStatement::equals:: that_predicate is null");
        }
        librdf_node *that_resource = librdf_statement_get_object(second);
        if (!that_resource) {
            throw std::logic_error("LibrdfStatement::equals:: that_resource is null");
        }
        bool subjects_equal = true;
        bool resources_equal = true;
        // we bypass comparing blank nodes.
        if (!librdf_node_is_blank(this_subject) || !librdf_node_is_blank(that_subject)) {
            subjects_equal = librdf_node_equals(this_subject, that_subject);
        }
        if (!librdf_node_is_blank(this_resource) || !librdf_node_is_blank(that_resource)) {
            resources_equal = librdf_node_equals(this_resource, that_resource);
        }
        bool predicates_equal = librdf_node_equals(this_predicate, that_predicate);
        return subjects_equal && predicates_equal && resources_equal;
    }

    bool LibrdfStatement::operator==(const LibrdfStatement &rhs) const {
        return equals(statement_, rhs.get());
    }

    bool LibrdfStatement::operator!=(const LibrdfStatement &rhs) const {
        return !(rhs == *this);
    }

    int LibrdfStatement::getUsage() const {
        return statement_->usage;
    }

}// namespace redland