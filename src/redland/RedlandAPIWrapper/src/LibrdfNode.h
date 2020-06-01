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
 * Do I need to mirror the underlying structure of
 * the librdf_node* object?
 */

namespace redland {

    typedef std::unique_ptr<librdf_node> librdf_node_ptr;

    class LibrdfNode {

//        raptor_term_value value;

        struct deleter {
            void operator()(librdf_node *node);
        };

    private:
        std::shared_ptr<librdf_node> node_;
        LibrdfUri uri_;


    public:
        LibrdfNode() = default;

        static void freeNode(librdf_node* node);

        explicit LibrdfNode(librdf_node *node);

        [[nodiscard]] librdf_node *get() const;

        static librdf_node* fromUriString(const std::string &uri_string);

        static librdf_node* fromBlank(const std::string &blank);

        static librdf_node* fromLiteral(const std::string &literal, const std::string &xml_language = std::string(),
                                      const std::string &literal_datatype_uri = "string");

        raptor_term_type getRaptorTermType();

        static std::string str(librdf_node* node);

        librdf_uri* getLiteralDatatype();

        std::string getLiteralLanguage();

        std::string getBlankIdentifier();

        LibrdfUri getUri();

        void setUri(const std::string &uri);

        void setLiteralDatatype(const std::string& datatype);

        static std::string validateLiteralDatatype(const std::string &literal_datatype_uri);

        void setBlankIdentifier(const std::string &identifier);
    };
}


#endif //LIBSEMSIM_LIBRDFNODE_H
