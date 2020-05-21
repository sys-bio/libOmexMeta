//
// Created by Ciaran on 5/19/2020.
//

#include "LibrdfStatement.h"


namespace semsim {

    LibrdfStatement::LibrdfStatement(librdf_statement *statement)
            : statement_(statement_ptr(statement, librdf_free_statement)) {
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


}