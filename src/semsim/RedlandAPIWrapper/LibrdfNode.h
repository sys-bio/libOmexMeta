//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_LIBRDFNODE_H
#define LIBSEMSIM_LIBRDFNODE_H

#include "semsim/Error.h"
#include <librdf.h>
#include <raptor2.h>
#include <memory>
#include <sstream>
#include "semsim/HERE.h"
#include "semsim/RedlandAPIWrapper/LibrdfUri.h"
/*
 * Do I need to mirror the underlying structure of
 * the librdf_node* object?
 */

namespace semsim {

    typedef std::unique_ptr<librdf_node> librdf_node_ptr;

    class LibrdfNode {

//        raptor_term_value value;

        struct deleter {
            void operator()(librdf_node *node);
        };

        std::unique_ptr<librdf_node, deleter> node_;

    public:
        LibrdfNode() = default;

        explicit LibrdfNode(librdf_node *node);

        static LibrdfNode fromUriString(const std::string &uri_string);

        static LibrdfNode fromBlank(const std::string &blank);

        static LibrdfNode fromLiteral(const std::string &literal, std::string xml_language = std::string(),
                                      std::string literal_datatype_uri = "string");


//        std::string str();
//
//        raptor_term_type getType();
//
//        librdf_node *get();

        raptor_term_type getType();

        librdf_node *get() const;

        std::string str() const;
    };
}


#endif //LIBSEMSIM_LIBRDFNODE_H
