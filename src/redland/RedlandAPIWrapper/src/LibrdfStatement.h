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

        librdf_node *subject_; // LibrdfStatement does not own
        librdf_node *predicate_; // LibrdfStatement does not own
        librdf_node *resource_; // LibrdfStatement does not own

        std::shared_ptr<librdf_statement> statement_;

    protected:
        explicit LibrdfStatement(librdf_statement *statement);

        LibrdfStatement(librdf_node *subject, librdf_node *predicate, librdf_node *resource);

    public:

        LibrdfStatement() = default;

        static LibrdfStatement fromRawStatementPtr(librdf_statement *statement);

        static LibrdfStatement fromRawNodePtrs(librdf_node *subject, librdf_node *predicate, librdf_node *resource);

        [[nodiscard]] librdf_statement *get() const;

        [[nodiscard]] librdf_node *getSubject() const;

        [[nodiscard]] librdf_node *getPredicate() const;

        [[nodiscard]] librdf_node *getResource() const;

        [[nodiscard]] std::string getSubjectStr() const;

        [[nodiscard]] std::string getPredicateStr() const;

        [[nodiscard]] std::string getResourceStr() const;

        void checkForNull();
    };


}

#endif //LIBSEMSIM_LIBRDFSTATEMENT_H
