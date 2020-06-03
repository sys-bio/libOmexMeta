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

    protected:

        librdf_node *subject_ = nullptr; // LibrdfStatement does not own
        librdf_node *predicate_ = nullptr; // LibrdfStatement does not own
        librdf_node *resource_ = nullptr; // LibrdfStatement does not own

        // starts as empty statement
        std::shared_ptr<librdf_statement> statement_ = std::shared_ptr<librdf_statement>(
                librdf_new_statement(World::getWorld()),
                librdf_free_statement
        );

        /*
         * @brief update the contained statement with current
         * values of subject, predicate and resource.
         *
         */
        void refreshStatement();

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

        void setSubject(librdf_node *node);

        void setResource(librdf_node *node);

        void setPredicate(librdf_node *node);
    };


}

#endif //LIBSEMSIM_LIBRDFSTATEMENT_H
