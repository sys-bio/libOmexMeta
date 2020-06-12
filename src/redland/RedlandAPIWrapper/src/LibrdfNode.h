//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_LIBRDFNODE_H
#define LIBSEMSIM_LIBRDFNODE_H

//
#include <librdf.h>
#include <raptor2.h>
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
namespace redland {

    class LibrdfNode {


    private:
        librdf_node *node_ = nullptr;


    public:
        LibrdfNode() = default;

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

        raptor_term_type getRaptorTermType();

        static std::string str(librdf_node *node);

        std::string str();

        LibrdfUri getLiteralDatatype();

        std::string getLiteralLanguage();

        std::string getBlankIdentifier();

        LibrdfUri getUri();

        void setUri(const std::string &uri);

        void setLiteralDatatype(const std::string &datatype);

        static std::string validateLiteralDatatype(const std::string &literal_datatype_uri);

        void setBlankIdentifier(const std::string &identifier);
    };
}


#endif //LIBSEMSIM_LIBRDFNODE_H
