//
// Created by Ciaran on 5/19/2020.
//

#ifndef LIBOMEXMETA_LIBRDFSTATEMENT_H
#define LIBOMEXMETA_LIBRDFSTATEMENT_H


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

    public:
        bool operator==(const LibrdfStatement &rhs) const;

        bool operator!=(const LibrdfStatement &rhs) const;

    protected:
        explicit LibrdfStatement(librdf_statement *statement);

        LibrdfStatement(librdf_node *subject, librdf_node *predicate, librdf_node *resource);

    public:

        LibrdfStatement() = default;

        LibrdfStatement(const LibrdfNode &subject, const LibrdfNode &predicate, const LibrdfNode &resource);

        static LibrdfStatement fromRawStatementPtr(librdf_statement *statement);

        static LibrdfStatement fromRawNodePtrs(librdf_node *subject, librdf_node *predicate, librdf_node *resource);

        LibrdfStatement(const LibrdfStatement &statement) = delete;

        LibrdfStatement(LibrdfStatement &&statement) noexcept;

        LibrdfStatement &operator=(const LibrdfStatement &statement) = delete;

        LibrdfStatement &operator=(LibrdfStatement &&statement) noexcept;

        ~LibrdfStatement() = default;

        void freeStatement();

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

        bool isComplete();
    };


}

#endif //LIBOMEXMETA_LIBRDFSTATEMENT_H
