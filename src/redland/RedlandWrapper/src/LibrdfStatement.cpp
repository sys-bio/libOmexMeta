//
// Created by Ciaran on 5/19/2020.
//

#include "redland/LibrdfStatement.h"
#include "redland/LibrdfWorld.h"
#include "redland/Logger.h"

namespace redland {

    LibrdfStatement::LibrdfStatement()
        : RefCounted_librdf_statement(librdf_new_statement(LibrdfWorld::getWorld()), librdf_free_statement) {
        REDLAND_DEBUG("Instantiated a LibrdfStatement instance");
    }

    LibrdfStatement::LibrdfStatement(librdf_statement *statement)
        : RefCounted_librdf_statement(statement, librdf_free_statement) {
        REDLAND_DEBUG("Instantiated a LibrdfStatement instance");
    }

    LibrdfStatement::LibrdfStatement(const LibrdfNode &subject, const LibrdfNode &predicate, const LibrdfNode &resource)
        : RefCounted_librdf_statement(
                  librdf_new_statement_from_nodes(
                          LibrdfWorld::getWorld(), subject.get(), predicate.get(), resource.get()),
                  librdf_free_statement) {
    }


    void LibrdfStatement::checkForNull() {
        RefCounted_librdf_statement::checkForNull();
        if (getSubjectNode().isNull()) {
            std::string err = "Subject node is null";
            REDLAND_ERROR(err);
            throw RedlandNullPointerException(err);
        }

        if (getPredicateNode().isNull()) {
            std::string err = "Predicate node is null";
            REDLAND_ERROR(err);
            throw RedlandNullPointerException(err);
        }
        if (getResourceNode().isNull()) {
            std::string err = "Resource node is null";
            REDLAND_ERROR(err);
            throw RedlandNullPointerException(err);
        }
    }


    LibrdfNode LibrdfStatement::getSubjectNode() const {
        // we need to be able to create LibrdfNode that contains a nullptr
        // so that we can build a LibrdfStatement/Triple from components (aka it starts empty)
        librdf_node* nodePtr = librdf_statement_get_subject(obj_);
        LibrdfNode node;
        if (nodePtr){
            node = LibrdfNode(nodePtr);
            node.incrementUsage();// todo this should be handled automatically by LibrdfNode ctr
        }
        return node;
    }

    LibrdfNode LibrdfStatement::getPredicateNode() const {
        // we need to be able to create LibrdfNode that contains a nullptr
        // so that we can build a LibrdfStatement/Triple from components (aka it starts empty)
        librdf_node* nodePtr = librdf_statement_get_predicate(obj_);
        LibrdfNode node;
        if (nodePtr){
            node = LibrdfNode(nodePtr);
            node.incrementUsage();
        }
        return node;
    }

    LibrdfNode LibrdfStatement::getResourceNode() const {
        // we need to be able to create LibrdfNode that contains a nullptr
        // so that we can build a LibrdfStatement/Triple from components (aka it starts empty)
        librdf_node* nodePtr = librdf_statement_get_object(obj_);
        LibrdfNode node;
        if (nodePtr){
            node = LibrdfNode(nodePtr);
            node.incrementUsage();// todo this should be handled automatically by LibrdfNode ctr
        }
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
        if (node.isNull()) {
            REDLAND_ERROR("LibrdfNode node contains null librdf_node*");
            spdlog::dump_backtrace();
        }
        if (isNull()) {
            REDLAND_ERROR("LibrdfStatement node contains null librdf_node*");
            spdlog::dump_backtrace();
        }
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

        // in the case of LibrdfStatement nullptr's, we just return false
        if (first.isNull()) {
            return false;
        }
        if (second.isNull()) {
            return false;
        }

        // if any of this LibrdfStatement nodes are null, return
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

        // if any of that LibrdfStatement nodes are null, return
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

        // assess equality, ignoring blank nodes
        bool subjects_equal = true;
        bool resources_equal = true;
        // we bypass comparing blank nodes.
        if (!this_subject.isBlank() || !that_subject.isBlank()) {
            subjects_equal = this_subject == that_subject;
        }
        if (!this_resource.isBlank() || !that_resource.isBlank()) {
            resources_equal = this_resource == that_resource;
        }
        // predicates cannot be blank
        bool predicates_equal = this_predicate == that_predicate;
        return subjects_equal && predicates_equal && resources_equal;
    }


}// namespace redland