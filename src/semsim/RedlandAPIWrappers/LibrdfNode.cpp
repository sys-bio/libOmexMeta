//
// Created by Ciaran on 5/17/2020.
//

#include "LibrdfNode.h"


/*
 * todo put name of exception in all error messages.
 */

namespace semsim {

    LibrdfNode::LibrdfNode(librdf_node *node) :
            node_(node_ptr(node, librdf_free_node)) {

    }

    const node_ptr &LibrdfNode::getNode() const {
        return node_;
    }

    bool LibrdfNode::operator==(const LibrdfNode &rhs) const {
        return node_.get() == rhs.node_.get();
    }

    bool LibrdfNode::operator!=(const LibrdfNode &rhs) const {
        return !(rhs == *this);
    }

    bool LibrdfNode::operator!() const {
        return !getNode();
    }

    /*
     * Retrive a value from a librdf_node object,
     * regardless of its type.
     */
    std::string LibrdfNode::str() {
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

    librdf_node *LibrdfNode::get() {
        return node_.get();
    }


}
