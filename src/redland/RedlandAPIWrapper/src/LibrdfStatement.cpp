//
// Created by Ciaran on 5/19/2020.
//

#include "LibrdfStatement.h"
#include "World.h"


namespace redland {


    void LibrdfStatement::deleter::operator()(librdf_statement *statement) {
        if (statement)
            raptor_free_statement_wrapper(statement);
    }


    LibrdfStatement::LibrdfStatement(librdf_statement *statement)
    /*
     * todo keep an eye on this constructor - could it be the cause of some memory related issues.
     */
            : statement_(std::shared_ptr<librdf_statement>(statement, raptor_free_statement_wrapper)) {
        subject_ = LibrdfNode(librdf_statement_get_subject(statement_.get()));
        predicate_ = LibrdfNode(librdf_statement_get_subject(statement_.get()));
        resource_ = LibrdfNode(librdf_statement_get_subject(statement_.get()));
    }

    LibrdfStatement::LibrdfStatement(LibrdfNode subject, LibrdfNode predicate, LibrdfNode resource)
            : subject_(std::move(subject)),
              predicate_(std::move(predicate)),
              resource_(std::move(resource)) {
        statement_ = std::shared_ptr<librdf_statement>(
                librdf_new_statement_from_nodes(
                        World::getWorld(), subject_.get(), predicate_.get(), resource_.get()
                ), raptor_free_statement_wrapper
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