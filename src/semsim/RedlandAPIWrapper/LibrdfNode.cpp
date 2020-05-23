//
// Created by Ciaran on 5/17/2020.
//

#include "LibrdfNode.h"


/*
 * todo put name of exception in all error messages.
 */
#include "semsim/RedlandAPIWrapper/World.h"

namespace semsim {


    void LibrdfNode::deleter::operator()(librdf_node *node) {
        librdf_free_node(node);
    }

    LibrdfNode::LibrdfNode(librdf_node *node)
            : node_(node) {

    }

    LibrdfNode LibrdfNode::fromUriString(const std::string &uri_string) {
        return LibrdfNode(librdf_new_node_from_uri_string(
                World::getWorld(), (const unsigned char *) uri_string.c_str())
        );
    }

    LibrdfNode LibrdfNode::fromBlank(const std::string &blank) {
        return LibrdfNode(
                librdf_new_node_from_blank_identifier(
                        World::getWorld(), (const unsigned char *) blank.c_str()
                )
        );
    }

    LibrdfNode
    LibrdfNode::fromLiteral(const std::string &literal, std::string xml_language, std::string literal_datatype_uri) {
        std::string literal_datatype_prefix = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";
        if (literal_datatype_uri.rfind(literal_datatype_prefix, 0) != 0) {
            literal_datatype_uri = literal_datatype_prefix + literal_datatype_uri;
        }
        const char *xml_language_;
        if (xml_language.empty()) {
            xml_language_ = nullptr;
        } else {
            xml_language_ = xml_language.c_str();
        }
        return LibrdfNode(
                librdf_new_node_from_typed_literal(
                        World::getWorld(),
                        (const unsigned char *) literal.c_str(),
                        xml_language_,
                        LibrdfUri(literal_datatype_uri).get()
                )
        );
    }


    /*
     * Retrive a value from a librdf_node object,
     * regardless of its type.
     */
    std::string LibrdfNode::str() const {
        if (!node_) {
            throw NullPointerException("LibrdfNode::str(): NullPointerException: node_");
        }
        std::string value;
        std::ostringstream err;
        err << "NullPointerException: LibrdfNode::str():";
        switch (node_.get()->type) {
            case RAPTOR_TERM_TYPE_URI: {
                value = (const char *) librdf_uri_as_string(librdf_node_get_uri(node_.get()));
                err << "RAPTOR_TERM_TYPE_URI: ";
                break;
            }
            case RAPTOR_TERM_TYPE_LITERAL: {
                err << "RAPTOR_TERM_TYPE_LITERAL: ";
                value = (const char *) librdf_node_get_literal_value(node_.get());
                break;
            }
            case RAPTOR_TERM_TYPE_BLANK: {
                err << "RAPTOR_TERM_TYPE_BLANK: ";
                value = (const char *) librdf_node_get_blank_identifier(node_.get());
                break;
            }
            default:
                throw LibRDFException("LibRDFException: Librdf::Str() : Unrecognized term type");
        }
        err << "value is nullptr" << std::endl;
        std::cout << "Value is: " << value << std::endl;
        if (value.empty()) {
            throw NullPointerException(err.str());
        }
        std::string output = value;
        return output;
    }

    raptor_term_type LibrdfNode::getType() {
        return node_.get()->type;
    }

    librdf_node *LibrdfNode::get() const {
        return node_.get();
    }


}
