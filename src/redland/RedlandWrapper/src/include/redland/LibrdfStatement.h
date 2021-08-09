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

    /**
     * @brief std::function signature of librdf_free_node
     */
    using statement_free_func = std::function<void(librdf_statement *)>;

    /**
     * Instantiation of templated superclass
     */
    using RefCounted_librdf_statement = RefCounted<librdf_statement, statement_free_func>;


    /**
     * @brief C++ wrapper around librdf_statement using RAII for memory management
     */
    class LibrdfStatement : public RefCounted_librdf_statement {
    public:

        /**
         * @brief use superclass ctr and rule of 5
         */
        using RefCounted_librdf_statement::RefCounted_librdf_statement;

        /**
         * @brief construct a LibrdfStatement from an existing librdf_statement* pointer.
         * @brief The reference is stolen, and subsequently managed by LibrdfStatement
         */
        explicit LibrdfStatement(librdf_statement *statement);

        /**
         * @brief default construct an instance of librdf_statement*.
         * @details Memory is owned by LibrdfStatement and automatically
         * destructed via RAII.
         */
        LibrdfStatement();

        /**
         * @brief equality operator.
         * @detials equal if the three nodes contained by this statement are equal
         */
        bool operator==(const LibrdfStatement &rhs) const;

        /**
         * @brief inequality operator. Inverse of equality operator
         */
        bool operator!=(const LibrdfStatement &rhs) const;

        /**
         * @brief returns true if first equals second.
         * @details All three of subject, predicate and resource nodes need to be equal
         * before LibrdfStatement::equals returns true.
         */
        static bool equals(librdf_statement *first, librdf_statement *second);

        /**
         * @brief construct a LibrdfStatement from LibrdfNode objects.
         * @details The memory associated with the constructed librdf_statement* is managed by RAII
         * while the LibrdfNode types handled themselves, also by RAII. The reference count of
         * the LibrdfNode types is incremented by 1 on instantiation
         */
        LibrdfStatement(const LibrdfNode &subject, const LibrdfNode &predicate, const LibrdfNode &resource);

        /**
         * @brief get the subject of this statement as a LibrdfNode.
         * @details Ref count is incremented by 1
         */
        [[nodiscard]] LibrdfNode getSubjectNode() const;

        /**
         * @brief get the predicate of this statement as a LibrdfNode.
         * @details Ref count is incremented by 1
         */
        [[nodiscard]] LibrdfNode getPredicateNode() const;

        /**
         * @brief get the resource of this statement as a LibrdfNode.
         * @details Ref count is incremented by 1
         */
        [[nodiscard]] LibrdfNode getResourceNode() const;

        /**
         * @brief throws an error if any of the subject, predicate, resource or librdf_statement are
         * nullptr.
         */
        void checkForNull() override;

        /**
         * @brief set the subject of this LibrdfStatement
         * to node.
         * @details reference count of node is incremented
         */
        void setSubject(const LibrdfNode& node);

        /**
         * @brief set the resource of this LibrdfStatement
         * to node.
         * @details reference count of node is incremented
         */
        void setResource(const LibrdfNode& node);

        /**
         * @brief set the predicate of this LibrdfStatement
         * to node.
         * @details reference count of node is incremented
         */
        void setPredicate(const LibrdfNode& node);

        /**
         * @brief returns true when all of subject, predicate and resource
         * nodes are not empty.
         */
        bool isComplete();

    };
}// namespace redland

#endif//LIBOMEXMETA_LIBRDFSTATEMENT_H
