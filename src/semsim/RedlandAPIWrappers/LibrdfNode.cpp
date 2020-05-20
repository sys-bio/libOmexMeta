//
// Created by Ciaran on 5/17/2020.
//

#include "LibrdfNode.h"


/*
 * todo put name of exception in all error messages.
 */

namespace semsim {

    LibrdfNode::LibrdfNode(librdf_node *node) :
            node_(std::make_shared<librdf_node *>(node)) {

    }

    LibrdfNode::~LibrdfNode() {
        if (node_.use_count() == 1) {
            librdf_free_node(*node_);
        }
    }

    LibrdfNode::LibrdfNode(const LibrdfNode &librdfNode) {
        if (node_)
            librdf_free_node(*node_); // Remove prexisting node before copy
        node_ = librdfNode.node_;
    }

    LibrdfNode::LibrdfNode(LibrdfNode &&librdfNode) noexcept {
        if (node_) {
            librdf_free_node(*node_);
        }
        node_ = std::move(librdfNode.node_);
    }

    LibrdfNode &LibrdfNode::operator=(const LibrdfNode &librdfNode) {
        if (this != &librdfNode) {
            if (node_) {
                librdf_free_node(*node_);
            }
            node_ = librdfNode.node_;
        }
        return *this;
    }

    LibrdfNode &LibrdfNode::operator=(LibrdfNode &&librdfNode) noexcept {
        if (this != &librdfNode) {
            if (node_) {
                librdf_free_node(*node_);
            }
            node_ = std::move(librdfNode.node_);
        }
        return *this;
    }

    const std::shared_ptr<librdf_node *> &LibrdfNode::getNode() const {
        return node_;
    }

    bool LibrdfNode::operator==(const LibrdfNode &rhs) const {
        return *node_ == *rhs.node_;
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
        HERE();
        if (!*node_) {
            throw NullPointerException("LibrdfNode::str(): NullPointerException: node_");
        }
        HERE();
        std::string value;
        HERE();
        std::ostringstream err;
        HERE();
        err << "NullPointerException: LibrdfNode::str():";
        HERE();
        switch ((*node_)->type) {
            case RAPTOR_TERM_TYPE_URI: {
                HERE();
                value = (const char *) librdf_uri_as_string(librdf_node_get_uri(*node_));
                HERE();
                err << "RAPTOR_TERM_TYPE_URI: ";
                HERE();
                break;
            }
            case RAPTOR_TERM_TYPE_LITERAL: {
                err << "RAPTOR_TERM_TYPE_LITERAL: ";
                value = (const char *) librdf_node_get_literal_value(*node_);
                break;
            }
            case RAPTOR_TERM_TYPE_BLANK: {
                err << "RAPTOR_TERM_TYPE_BLANK: ";
                value = (const char *) librdf_node_get_blank_identifier(*node_);
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
        return (*node_)->type;
    }


}
