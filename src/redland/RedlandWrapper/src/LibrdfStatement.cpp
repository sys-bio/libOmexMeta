//
// Created by Ciaran on 5/19/2020.
//

#include "redland/LibrdfStatement.h"
#include "redland/LibrdfWorld.h"


namespace redland {

    LibrdfStatement::LibrdfStatement()
        : RefCounted_librdf_statement(librdf_new_statement(LibrdfWorld::getWorld()), librdf_free_statement) {}

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

    void LibrdfStatement::setSubject(const LibrdfNode &node) {
        // valgrind validated - we need to increment the ref counter ourselves
        // which is handled by the .get() method
        librdf_statement_set_subject(obj_, node.get());
    }

    void LibrdfStatement::setResource(const LibrdfNode &node) {
        // valgrind validated - we need to increment the ref counter ourselves
        // which is handled by the .get() method
        librdf_statement_set_object(obj_, node.get());
    }

    void LibrdfStatement::setPredicate(const LibrdfNode &node) {
        // valgrind validated - we need to increment the ref counter ourselves
        // which is handled by the .get() method
        librdf_statement_set_predicate(obj_, node.get());
    }

    bool LibrdfStatement::isComplete() {
        return librdf_statement_is_complete(obj_);
    }

    bool LibrdfStatement::operator==(const LibrdfStatement &rhs) const {
        return equals(*this, rhs);
    }

    bool LibrdfStatement::operator!=(const LibrdfStatement &rhs) const {
        return !(*this == rhs);
    }

    bool LibrdfStatement::equals(const LibrdfStatement &first, const LibrdfStatement &second) {
        // note: The reason we do not use librdf_statement_equals
        // is because librdf_statement_equals does not get eq`uality
        // correct when comparing blank nodes. We therefore roll our own equality
        // operator.
        // in the case of nullptr's, we just return false
        if (first.isNull()) {
            return false;
        }
        if (second.isNull()) {
            return false;
        }
        LibrdfNode this_subject = first.getSubjectNode();
        if (this_subject.isNull()) {
            return false;
        }
        LibrdfNode this_predicate = first.getPredicateNode();
        if (this_predicate.isNull()) {
            return false;
        }
        LibrdfNode this_resource = first.getResourceNode();
        if (this_resource.isNull()) {
            return false;
        }

        LibrdfNode that_subject = second.getSubjectNode();
        if (that_subject.isNull()) {
            return false;
        }
        LibrdfNode that_predicate = second.getPredicateNode();
        if (that_predicate.isNull()) {
            return false;
        }
        LibrdfNode that_resource = second.getResourceNode();
        if (that_resource.isNull()) {
            return false;
        }
        bool subjects_equal = true;
        bool resources_equal = true;
        // we bypass comparing blank nodes.
        if (!this_subject.isBlank() || !that_subject.isBlank()) {
            subjects_equal = this_subject == that_subject;
        }
        if (this_resource.isBlank() || !that_resource.isBlank()) {
            resources_equal = this_resource == that_resource;
        }
        bool predicates_equal = this_predicate == that_predicate;// cannot be blank
        return subjects_equal && predicates_equal && resources_equal;
    }


}// namespace redland