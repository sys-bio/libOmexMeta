//
// Created by Ciaran on 5/19/2020.
//

#include "LibrdfStatement.h"


namespace semsim {

    LibrdfStatement::LibrdfStatement(librdf_statement *statement)
            : statement_(std::make_shared<librdf_statement *>(statement)) {
    }

    LibrdfStatement::~LibrdfStatement() {
        if (statement_.use_count() == 1) {
            librdf_free_statement(*statement_);
        }
    }

    LibrdfStatement::LibrdfStatement(const LibrdfStatement &LibrdfStatement) {
        // If we already have a statement in this object, get rid
        // before we take LibrdfStatement.statement_ copy
        std::cout << statement_ << std::endl;
        if (statement_ != nullptr) {
            librdf_free_statement(*statement_);
        }
        statement_ = LibrdfStatement.statement_;
    }

    LibrdfStatement &LibrdfStatement::operator=(const LibrdfStatement &LibrdfStatement) {
        if (this != &LibrdfStatement) {
            librdf_free_statement(*this->statement_);
            statement_ = LibrdfStatement.statement_;
        }
        return *this;
    }

    LibrdfStatement &LibrdfStatement::operator=(LibrdfStatement &&LibrdfStatement) noexcept {
        if (this != &LibrdfStatement) {
            std::cout << "move assignment" << std::endl;
            librdf_free_statement(*this->statement_); // free current statement before taking theirs
            statement_ = std::move(LibrdfStatement.statement_);
        }
        return *this;
    }

    LibrdfStatement::LibrdfStatement(LibrdfStatement &&LibrdfStatement) noexcept {
        statement_ = std::move(LibrdfStatement.statement_);
    }


    bool LibrdfStatement::operator==(const LibrdfStatement &rhs) const {
        return statement_ == rhs.statement_;
    }

    bool LibrdfStatement::operator!=(const LibrdfStatement &rhs) const {
        return !(rhs == *this);
    }

    const std::shared_ptr<librdf_statement *> &LibrdfStatement::getStatement() const {
        return statement_;
    }

    bool LibrdfStatement::operator!() const {
        return !statement_;
    }

}