//
// Created by Ciaran on 5/19/2020.
//

#include "LibrdfStatement.h"


namespace semsim {

    /*
     * If you use librdf_free_statement(statement)
     * you will be trying to free the statement
     * AND the nodes associated with it. This
     * conflicts the concept in Redland C++ API that
     * each object is responsible for its own construction
     * and destruction. The LibrdfNode class will free itself
     * and therefore here we only free the statement.
     */
//    void free_statement(librdf_statement* statement){
//        free(statement);
//    }
    void free_statement(librdf_statement *statement) {
        /* dynamically or statically allocated? */
        int is_dynamic;

        if (!statement)
            return;

        is_dynamic = (statement->usage >= 0);

        /* dynamically allocated and still in use? */
        if (is_dynamic && --statement->usage)
            return;

        raptor_statement_clear(statement);

        if (is_dynamic)
            free(statement);
    }


    LibrdfStatement::LibrdfStatement(librdf_statement *statement)
            : statement_(statement_ptr(statement, free_statement)) {
    }

    bool LibrdfStatement::operator==(const LibrdfStatement &rhs) const {
        return statement_.get() == rhs.statement_.get();
    }

    bool LibrdfStatement::operator!=(const LibrdfStatement &rhs) const {
        return !(rhs == *this);
    }

    const statement_ptr &LibrdfStatement::getStatement() const {
        return statement_;
    }

    bool LibrdfStatement::operator!() const {
        return !statement_.get();
    }

    LibrdfNode LibrdfStatement::getSubjectNode() {
        return LibrdfNode(librdf_statement_get_subject(statement_.get()));
    }

    LibrdfNode LibrdfStatement::getPredicateNode() {
        return LibrdfNode(librdf_statement_get_predicate(statement_.get()));
    }

    LibrdfNode LibrdfStatement::getObjectNode() {
        return LibrdfNode(librdf_statement_get_object(statement_.get()));
    }

    librdf_statement *LibrdfStatement::get() {
        return statement_.get();
    }

    void LibrdfStatement::setSubject(LibrdfNode node) {
        librdf_statement_set_subject(get(), node.get());
    }

    void LibrdfStatement::setPredicate(LibrdfNode node) {
        librdf_statement_set_predicate(get(), node.get());

    }

    void LibrdfStatement::setResource(LibrdfNode node) {
        librdf_statement_set_object(get(), node.get());

    }


}