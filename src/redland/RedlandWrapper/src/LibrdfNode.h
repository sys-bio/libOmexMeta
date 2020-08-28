//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBOMEXMETA_LIBRDFNODE_H
#define LIBOMEXMETA_LIBRDFNODE_H

//
#include "librdf.h"
#include "raptor2.h"
#include <memory>
#include <sstream>
#include "LibrdfUri.h"
#include "World.h"
#include "LibrdfException.h"


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


    private:
        librdf_node *node_ = nullptr;


    public:
        LibrdfNode() = default;

        bool operator==(const LibrdfNode &rhs) const;

        bool operator!=(const LibrdfNode &rhs) const;

        static void freeNode(librdf_node *node);

        void freeNode();

        LibrdfNode(const LibrdfNode &node) = delete;

        LibrdfNode(LibrdfNode &&node) noexcept;

        LibrdfNode &operator=(const LibrdfNode &node) = delete;

        LibrdfNode &operator=(LibrdfNode &&node) noexcept;

        explicit LibrdfNode(librdf_node *node);

        [[nodiscard]] librdf_node *get() const;

        static LibrdfNode fromUriString(const std::string &uri_string);

        static LibrdfNode fromBlank(const std::string &blank);

        static LibrdfNode fromLiteral(const std::string &literal, const std::string &literal_datatype_uri = "string",
                                      const std::string &xml_language = std::string());

        static LibrdfNode newEmptyNode();

        raptor_term_type getRaptorTermType();

        static std::string str(librdf_node *node);

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

        LibrdfNode fromUriString(const std::string &uri_string, const std::string &local_prefix);
    };
}


#endif //LIBOMEXMETA_LIBRDFNODE_H
