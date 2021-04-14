//
// Created by Ciaran on 5/19/2020.
//

#ifndef LIBOMEXMETA_LIBRDFSTATEMENT_H
#define LIBOMEXMETA_LIBRDFSTATEMENT_H


#include "LibrdfNode.h"
#include "librdf.h"
#include <iostream>
#include <memory>
#include <unordered_map>

namespace redland {

    class LibrdfStatement {
    public:
        ~LibrdfStatement();

        LibrdfStatement(librdf_node *subject, librdf_node *predicate, librdf_node *resource);

        LibrdfStatement(const LibrdfStatement &statement) ;

        LibrdfStatement(LibrdfStatement &&statement) noexcept;

        LibrdfStatement &operator=(const LibrdfStatement &statement) ;

        LibrdfStatement &operator=(LibrdfStatement &&statement) noexcept;

        bool operator==(const LibrdfStatement &rhs) const;

        bool operator!=(const LibrdfStatement &rhs) const;

        static bool equals(librdf_statement *first, librdf_statement *second);

        LibrdfStatement() = default;

        LibrdfStatement(const LibrdfNode &subject, const LibrdfNode &predicate, const LibrdfNode &resource);

        static LibrdfStatement fromRawStatementPtr(librdf_statement *statement);

        static LibrdfStatement fromRawNodePtrs(librdf_node *subject, librdf_node *predicate, librdf_node *resource);

        void freeStatement();

        /**
         * @brief returns a librdf_statement pointer and increments the
         * usage count. The caller is responsible for calling
         * @see freeUri to decrement the librdf_statement* again.
         * @note when @see getUsage() is 1 the destructor
         * will take care of freeing memory associated with
         * librdf_statement object.
         */
        [[nodiscard]] librdf_statement *get() const;

        /**
         * @brief get the underlying librdf_statement*
         * @details do not increment the shared pointer reference
         * counter.
         * @warning this method assumes you know what you are doing
         * with regards to the librdf reference counting system
         * @see LibrdfStatement::get()
         */
        [[nodiscard]] librdf_statement *getWithoutIncrement() const;

        [[nodiscard]] librdf_node *getSubjectAsRawNode() const;

        [[nodiscard]] librdf_node *getPredicateAsRawNode() const;

        [[nodiscard]] librdf_node *getResourceAsRawNode() const;

        [[nodiscard]] LibrdfNode getSubjectNode() const;

        [[nodiscard]] LibrdfNode getPredicateNode() const;

        [[nodiscard]] LibrdfNode getResourceNode() const;

        [[nodiscard]] std::string getSubjectStr() const;

        [[nodiscard]] std::string getPredicateStr() const;

        [[nodiscard]] std::string getResourceStr() const;

        void checkForNull();

        void setSubject(librdf_node *node);

        void setResource(librdf_node *node);

        void setPredicate(librdf_node *node);

        bool isComplete();

        void freeStatementAndUris();

        [[nodiscard]] std::string getPredicateNamespaceStr() const;

        [[nodiscard]] int getUsage() const;

        void incrementUsage() const;

    protected:
        // starts as empty statement
        librdf_statement *statement_ = librdf_new_statement(World::getWorld());

        /*
         * @brief update the contained statement with current
         * values of subject, predicate and resource.
         */
        void refreshStatement();

        explicit LibrdfStatement(librdf_statement *statement);
    };
}// namespace redland

#endif//LIBOMEXMETA_LIBRDFSTATEMENT_H
