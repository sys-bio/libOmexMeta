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


        struct deleter {
            void operator()(librdf_statement *statement);
        };

    protected:
        LibrdfNode subject_;
        LibrdfNode predicate_;
        LibrdfNode resource_;

        std::shared_ptr<librdf_statement> statement_;

    public:
        LibrdfStatement() = default;

        explicit LibrdfStatement(librdf_statement *statement);

        explicit LibrdfStatement(LibrdfNode subject, LibrdfNode predicate, LibrdfNode resource);

//        explicit LibrdfStatement(const LibrdfNode& subject, const LibrdfNode& predicate, const  LibrdfNode& resource);

        librdf_statement *get() const;

        const LibrdfNode &getSubject() const;

        const LibrdfNode &getPredicate() const;

        const LibrdfNode &getResource() const;


        void checkForNull();
    };


}

#endif //LIBSEMSIM_LIBRDFSTATEMENT_H
