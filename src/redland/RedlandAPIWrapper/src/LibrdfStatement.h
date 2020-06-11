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

        // starts as empty statement
        librdf_statement *statement_ = librdf_new_statement(World::getWorld());

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

        LibrdfStatement(const LibrdfNode &subject, const LibrdfNode &predicate, const LibrdfNode &resource);

        static LibrdfStatement fromRawStatementPtr(librdf_statement *statement);

        static LibrdfStatement fromRawNodePtrs(librdf_node *subject, librdf_node *predicate, librdf_node *resource);

        LibrdfStatement(const LibrdfStatement &statement);

        LibrdfStatement(LibrdfStatement &&statement) noexcept;

        LibrdfStatement &operator=(const LibrdfStatement &statement) ;

        LibrdfStatement &operator=(LibrdfStatement &&statement) noexcept;

        ~LibrdfStatement();

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
