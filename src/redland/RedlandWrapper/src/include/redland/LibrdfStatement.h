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

        bool operator==(const LibrdfStatement &rhs) const;

        bool operator!=(const LibrdfStatement &rhs) const;

        static bool equals(librdf_statement *first, librdf_statement *second);


        LibrdfStatement(const LibrdfNode &subject, const LibrdfNode &predicate, const LibrdfNode &resource);

//        static LibrdfStatement fromRawStatementPtr(librdf_statement *statement);
//
//        static LibrdfStatement fromRawNodePtrs(librdf_node *subject, librdf_node *predicate, librdf_node *resource);
//
//        void freeStatement();

        [[nodiscard]] librdf_node *getSubjectAsRawNode() const;

        [[nodiscard]] librdf_node *getPredicateAsRawNode() const;

        [[nodiscard]] librdf_node *getResourceAsRawNode() const;

        [[nodiscard]] LibrdfNode getSubjectNode() const;

        [[nodiscard]] LibrdfNode getPredicateNode() const;

        [[nodiscard]] LibrdfNode getResourceNode() const;

//        [[nodiscard]] std::string getSubjectStr() const;
//
//        [[nodiscard]] std::string getPredicateStr() const;
//
//        [[nodiscard]] std::string getResourceStr() const;

        void checkForNull() override;

        void setSubject(librdf_node *node);

        void setResource(librdf_node *node);

        void setPredicate(librdf_node *node);

        bool isComplete();

        [[maybe_unused]] [[nodiscard]] std::string getPredicateNamespaceStr() const;

    };
}// namespace redland

#endif//LIBOMEXMETA_LIBRDFSTATEMENT_H
