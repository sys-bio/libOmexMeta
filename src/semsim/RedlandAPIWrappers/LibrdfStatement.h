//
// Created by Ciaran on 5/19/2020.
//

#ifndef LIBSEMSIM_LIBRDFSTATEMENT_H
#define LIBSEMSIM_LIBRDFSTATEMENT_H


#include <librdf.h>
#include <memory>
#include <iostream>
#include "semsim/RedlandAPIWrappers/LibrdfNode.h"

namespace semsim {
    class LibrdfStatement {
        std::shared_ptr<librdf_statement *> statement_;

    public:
        LibrdfStatement() = default;

        explicit LibrdfStatement(librdf_statement *statement);

        ~LibrdfStatement();

        LibrdfStatement(const LibrdfStatement &LibrdfStatement);

        LibrdfStatement(LibrdfStatement &&LibrdfStatement) noexcept;

        LibrdfStatement &operator=(const LibrdfStatement &LibrdfStatement);

        LibrdfStatement &operator=(LibrdfStatement &&LibrdfStatement) noexcept;

        bool operator==(const LibrdfStatement &rhs) const;

        bool operator!=(const LibrdfStatement &rhs) const;

        const std::shared_ptr<librdf_statement *> &getStatement() const;

        bool operator!() const;

        LibrdfNode getSubjectNode();

        LibrdfNode getPredicateNode();

        LibrdfNode getObjectNode();
    };


}

#endif //LIBSEMSIM_LIBRDFSTATEMENT_H
