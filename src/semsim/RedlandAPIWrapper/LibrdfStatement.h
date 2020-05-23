//
// Created by Ciaran on 5/19/2020.
//

#ifndef LIBSEMSIM_LIBRDFSTATEMENT_H
#define LIBSEMSIM_LIBRDFSTATEMENT_H


#include <librdf.h>
#include <memory>
#include <iostream>
#include "semsim/RedlandAPIWrapper/LibrdfNode.h"

namespace semsim {
    typedef std::shared_ptr<librdf_statement> statement_ptr;

    class LibrdfStatement {
        statement_ptr statement_;

    public:
        LibrdfStatement() = default;

        explicit LibrdfStatement(librdf_statement *statement);

        bool operator==(const LibrdfStatement &rhs) const;

        bool operator!=(const LibrdfStatement &rhs) const;

        bool operator!() const;

        LibrdfNode getSubjectNode();

        LibrdfNode getPredicateNode();

        LibrdfNode getObjectNode();

        const statement_ptr &getStatement() const;

        librdf_statement *get();

        void setSubject(LibrdfNode node);

        void setPredicate(LibrdfNode node);

        void setResource(LibrdfNode node);

    };


}

#endif //LIBSEMSIM_LIBRDFSTATEMENT_H
