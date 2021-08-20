//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBOMEXMETA_LIBRDFNODE_H
#define LIBOMEXMETA_LIBRDFNODE_H

#include "LibrdfException.h"
#include "LibrdfUri.h"
#include "LibrdfWorld.h"
#include "RefCountedRedlandType.h"
#include "librdf.h"
#include "raptor2.h"
#include <memory>
#include <sstream>


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

    /**
     * @brief std::function signature of librdf_free_node
     */
    using node_free_func = std::function<void(librdf_node *)>;

    /**
     * @brief instantiation of superclass
     */
    using RefCounted_librdf_node = RefCountedRedlandType<librdf_node, node_free_func>;


    /**
      * @brief C++ wrapper around librdf_node that uses RAII for memory management
      */
    class LibrdfNode : public RefCounted_librdf_node {

    public:
        /**
         * @brief use superclass constructors and rule of 5
         */
        LibrdfNode() = default;

        bool operator==(const LibrdfNode &rhs) const;

        bool operator!=(const LibrdfNode &rhs) const;

        void freeNode();

        explicit LibrdfNode(librdf_node *node);

        explicit LibrdfNode(const LibrdfUri &uri);

        static LibrdfNode fromUriString(const std::string &uri_string);

        static LibrdfNode fromBlank(const std::string &blank);

        /**
         * @brief construct a literal node
         * @param literal the value to use for literal node
         * @param literal_datatype_uri defaults to "", i.e. no defined datatype. Users can use any datatype from the
         * RDF specification and users do not need to pass the full URI. For example, to specify a datatype was a string
         * you only need to use "string" for this argument.
         * @param xml_language The language for this literal. See RDF specification for more details.
         */
        static LibrdfNode fromLiteral(const std::string &literal, const std::string &literal_datatype_uri = "",
                                      const std::string &xml_language = std::string());

        static LibrdfNode newEmptyNode();

        raptor_term_type getRaptorTermType() const;

        std::string str() const;

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
         * @brief indicator for whether this is a blank node
         */
        bool isBlank();

        /**
         * @brief indicator for whether this is a uri node
         */
        bool isUri();

        /**
         * @brief indicator for whether this is a literal node
         */
        bool isLiteral();
    };
}// namespace redland


#endif//LIBOMEXMETA_LIBRDFNODE_H
