//
// Created by Ciaran on 5/19/2020.
//

#include "redland/LibrdfStatement.h"
#include "redland/LibrdfWorld.h"


namespace redland {

    LibrdfStatement::LibrdfStatement()
        : RefCounted_librdf_statement(librdf_new_statement(LibrdfWorld::getWorld()), librdf_free_statement) {}


    bool LibrdfStatement::operator==(const LibrdfStatement &rhs) const {
        return equals(obj_, rhs.getWithoutIncrement());
    }

    bool LibrdfStatement::operator!=(const LibrdfStatement &rhs) const {
        return !(rhs == *this);
    }


    LibrdfStatement::LibrdfStatement(librdf_statement *statement)
        : RefCounted_librdf_statement(statement, librdf_free_statement) {}

    LibrdfStatement::LibrdfStatement(const LibrdfNode &subject, const LibrdfNode &predicate, const LibrdfNode &resource)
        : RefCounted_librdf_statement(
                  librdf_new_statement_from_nodes(
                          LibrdfWorld::getWorld(), subject.get(), predicate.get(), resource.get()),
                  librdf_free_statement) {}


    void LibrdfStatement::checkForNull() {
        RefCounted_librdf_statement::checkForNull();
        if (!getSubjectNode().getWithoutIncrement())
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: LibrdfStatement::checkForNull(): subject_ node is null");

        if (!getPredicateNode().getWithoutIncrement())//todo another check on underlying pointer if possible (so far checking for null causes seg fault)
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: LibrdfStatement::checkForNull(): predicate_ node is null");

        if (!getResourceNode().getWithoutIncrement())
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: LibrdfStatement::checkForNull(): resource_ node is null");
    }


    LibrdfNode LibrdfStatement::getSubjectNode() const {
        LibrdfNode node(librdf_statement_get_subject(obj_));
        node.incrementUsage();// todo this should be handled automatically by LibrdfNode ctr
        return node;
    }

    LibrdfNode LibrdfStatement::getPredicateNode() const {
        LibrdfNode node = LibrdfNode(librdf_statement_get_predicate(obj_));
        node.incrementUsage();
        return node;
    }

    LibrdfNode LibrdfStatement::getResourceNode() const {
        LibrdfNode node = LibrdfNode(librdf_statement_get_object(obj_));
        node.incrementUsage();
        return node;
    }

    void LibrdfStatement::setSubject(librdf_node *node) {
        librdf_statement_set_subject(obj_, node);
    }

    void LibrdfStatement::setResource(librdf_node *node) {
        librdf_statement_set_object(obj_, node);
    }

    void LibrdfStatement::setPredicate(librdf_node *node) {
        librdf_statement_set_predicate(obj_, node);
    }

    std::string LibrdfStatement::getPredicateNamespaceStr() const {
        if (!getPredicateNode().getWithoutIncrement())
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: LibrdfStatement::getPredicateAsRawNode(): predicate_ is nullptr");
        return getPredicateNode().getNamespace();
    }

    bool LibrdfStatement::isComplete() {
        return librdf_statement_is_complete(obj_);
    }

    bool LibrdfStatement::equals(librdf_statement *first, librdf_statement *second) {
        // note: The reason we do not use librdf_statement_equals
        // is because librdf_statement_equals does not get equality
        // correct when comparing blank nodes. We therefore roll our own equality
        // operator.
        // in the case of nullptr's, we just return false
        if (!first) {
            return false;
        }
        if (!second) {
            return false;
        }
        librdf_node *this_subject = librdf_statement_get_subject(first);
        if (!this_subject) {
            return false;
        }
        librdf_node *this_predicate = librdf_statement_get_predicate(first);
        if (!this_predicate) {
            return false;
        }
        librdf_node *this_resource = librdf_statement_get_object(first);
        if (!this_resource) {
            return false;
        }

        librdf_node *that_subject = librdf_statement_get_subject(second);
        if (!that_subject) {
            return false;
        }
        librdf_node *that_predicate = librdf_statement_get_predicate(second);
        if (!that_predicate) {
            return false;
        }
        librdf_node *that_resource = librdf_statement_get_object(second);
        if (!that_resource) {
            return false;
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


}// namespace redland