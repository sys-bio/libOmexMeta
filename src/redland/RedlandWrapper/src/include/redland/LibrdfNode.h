//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBOMEXMETA_LIBRDFNODE_H
#define LIBOMEXMETA_LIBRDFNODE_H

//
#include "LibrdfException.h"
#include "LibrdfUri.h"
#include "World.h"
#include "librdf.h"
#include "raptor2.h"
#include <memory>
#include <sstream>


/*
 * todo
 *  This objcet is a bit of a mess at the moment.
 *  Its currently not really being used as an
 *  object, but as a static librdf_node* generator.
 *  Probably the best thing to do is remove all
 *  methods except the librdf_node* generators
 *  which are actually used in the rest of the code.
 */
/*
 *valid literals
 * "UNKNOWN",
        "blank",
        "uri",
        "string",
        "xsdstring",
        "boolean",
        "integer",
        "float",
        "double",
        "decimal",
        "datetime",
        "udt",
        "pattern",
        "qname",
        "variable",
        "<integer subtype>",
        "date"
 */
namespace redland {

    class LibrdfNode {

    public:
        LibrdfNode() = default;

        ~LibrdfNode();

        bool operator==(const LibrdfNode &rhs) const;

        bool operator!=(const LibrdfNode &rhs) const;

        static void freeNode(librdf_node *node);

        void freeNode();

        LibrdfNode(const LibrdfNode &node) = delete;

        LibrdfNode(LibrdfNode &&node) noexcept;

        LibrdfNode &operator=(const LibrdfNode &node) = delete;

        LibrdfNode &operator=(LibrdfNode &&node) noexcept;

        explicit LibrdfNode(librdf_node *node);

        explicit LibrdfNode(const LibrdfUri& uri);

        /**
         * @brief return pointer to underlying librdf_node pointer
         * @details using this method increments the librdf_node* usage count
         * by 1. The caller is responsible for decrementing the usage count.
         * @see getUsage()
         * @note the librdf_statement takes shared ownership of a node when passed
         * to librdf_new_statement.
         */
        [[nodiscard]] librdf_node *get() const;

        /**
         * @brief get the underlying librdf_node*
         * @details do not increment the shared pointer reference
         * counter.
         * @warning this method assumes you know what you are doing
         * with regards to the librdf reference counting system
         * @see LibrdfNode::get()
         */
        [[nodiscard]] librdf_node *getWithoutIncrement() const;

        static LibrdfNode fromUriString(const std::string &uri_string);

        static LibrdfNode fromBlank(const std::string &blank);

        static LibrdfNode fromLiteral(const std::string &literal, const std::string &literal_datatype_uri = "string",
                                      const std::string &xml_language = std::string());

        static LibrdfNode newEmptyNode();

        raptor_term_type getRaptorTermType();

        static std::string str(librdf_node *node);

        [[nodiscard]] std::string str() const;

        LibrdfUri getLiteralDatatype();

        std::string getLiteralLanguage();

        std::string getBlankIdentifier();

        LibrdfUri getUri();

        void setUri(const std::string &uri);

        void setLiteralDatatype(const std::string &datatype);

        static std::string validateLiteralDatatype(const std::string &literal_datatype_uri);

        void setBlankIdentifier(const std::string &identifier);

        /*
         * @brief shallow copy a node. Internal ref count incremented by 1
         */
        static LibrdfNode copyNode(const LibrdfNode &node);

        static LibrdfNode fromRelativeUri(const std::string &uri_string, const std::string &base_uri);

        /**
         * @brief get namespace portion of the node. I.e. all but last section of the uri
         */
        std::string getNamespace() const;

        static std::vector<std::string> splitStringBy(const std::string &str, char delimiter);

        /**
         * @brief returns the usage of the underlying librdf_node pointer
         */
         unsigned int getUsage();

    private:
        librdf_node *node_ = nullptr;
    };
}// namespace redland


#endif//LIBOMEXMETA_LIBRDFNODE_H
