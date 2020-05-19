//
// Created by Ciaran on 5/17/2020.
//

#include "LibrdfNode.h"
#include "semsim/Error.h"

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

    /*
     * Retrive a value from a librdf_node object,
     * regardless of its type.
     */
    std::string LibrdfNode::str() {
        if (!*node_) {
            throw NullPointerException("LibrdfNode::str(): NullPointerException: node_");
        }
        std::string value;
        switch ((*node_)->type) {
            case RAPTOR_TERM_TYPE_URI: {
                value = (const char *) librdf_uri_as_string(librdf_node_get_uri(*node_));
                break;
            }
            case RAPTOR_TERM_TYPE_LITERAL: {
                value = (const char *) librdf_node_get_literal_value(*node_);
                break;
            }
            case RAPTOR_TERM_TYPE_BLANK: {
                value = (const char *) librdf_node_get_blank_identifier(*node_);
                break;
            }
            default:
                throw LibRDFException("Unrecognized term type");
        }
        return value;
    }

    const std::shared_ptr<LibrdfNode> &LibrdfNode::getNode() const {
        return node_;
    }

}
