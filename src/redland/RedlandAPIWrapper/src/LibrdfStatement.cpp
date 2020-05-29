//
// Created by Ciaran on 5/19/2020.
//

#include "LibrdfStatement.h"
#include "World.h"


namespace semsim {


    void LibrdfStatement::deleter::operator()(librdf_statement *statement) {
        if (statement)
            librdf_free_statement(statement);
    }

    LibrdfStatement::LibrdfStatement(librdf_statement *statement)
            : statement_(std::unique_ptr<librdf_statement, deleter>(statement)),
              subject_(LibrdfNode(librdf_statement_get_subject(statement))),
              predicate_(LibrdfNode(librdf_statement_get_subject(statement))),
              resource_(LibrdfNode(librdf_statement_get_subject(statement))) {}

    LibrdfStatement::LibrdfStatement(LibrdfNode subject, LibrdfNode predicate, LibrdfNode resource)
            : subject_(std::move(subject)),
              predicate_(std::move(predicate)),
              resource_(std::move(resource)) {
        statement_ = std::unique_ptr<librdf_statement, deleter>(
                librdf_new_statement_from_nodes(
                        World::getWorld(), subject_.get(), predicate_.get(), resource_.get()
                )
        );
    }

    librdf_statement *LibrdfStatement::get() const {
        return statement_.get();
    }

    const LibrdfNode &LibrdfStatement::getSubject() const {
        return subject_;
    }

    const LibrdfNode &LibrdfStatement::getPredicate() const {
        return predicate_;
    }

    const LibrdfNode &LibrdfStatement::getResource() const {
        return resource_;
    }

}