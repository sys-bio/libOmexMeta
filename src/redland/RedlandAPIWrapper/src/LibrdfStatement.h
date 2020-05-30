//
// Created by Ciaran on 5/19/2020.
//

#ifndef LIBSEMSIM_LIBRDFSTATEMENT_H
#define LIBSEMSIM_LIBRDFSTATEMENT_H


#include <librdf.h>
#include <memory>
#include <iostream>
#include "LibrdfNode.h"

namespace redland {

    class LibrdfStatement {

        LibrdfNode subject_;
        LibrdfNode predicate_;
        LibrdfNode resource_;

        struct deleter {
            void operator()(librdf_statement *statement);
        };

        std::unique_ptr<librdf_statement, deleter> statement_;

    public:
        LibrdfStatement() = default;

        explicit LibrdfStatement(librdf_statement *statement);

        explicit LibrdfStatement(LibrdfNode subject, LibrdfNode predicate, LibrdfNode resource);

        librdf_statement *get() const;

        const LibrdfNode &getSubject() const;

        const LibrdfNode &getPredicate() const;

        const LibrdfNode &getResource() const;


    };


}

#endif //LIBSEMSIM_LIBRDFSTATEMENT_H
