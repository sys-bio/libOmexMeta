//
// Created by Ciaran on 4/17/2020.
//


#include "semsim/RDFNode.h"


namespace semsim {


/***************************************************
 * RDFNode implementation
 */
    RDFNode::RDFNode(LibrdfNode node)
            : node_(std::move(node)) {
    }

    const LibrdfNode &RDFNode::getNode() const {
        return node_;
    }

    std::string RDFNode::str() {
        throw std::logic_error("Base class of RDFNode should not be used. "
                               "The fact you are seeing this error means "
                               "there is a bug. Plase submit a github issue.");
        return std::__cxx11::string();
    }

    RDFNode::~RDFNode() = default;

    /*
     * Creates a shared pointer to an RDFNode object given a librdf_world and
     * a librdf_node.
     */
    std::shared_ptr<RDFNode> RDFNode::fromRDFNode(LibrdfWorld world, LibrdfNode node) {
        switch (node.getType()) {
            case RAPTOR_TERM_TYPE_URI  : {
                return std::make_shared<RDFURINode>(node);
            }

            case RAPTOR_TERM_TYPE_LITERAL: {
                return std::make_shared<RDFLiteralNode>(node);
            }

            case RAPTOR_TERM_TYPE_BLANK: {
                return std::make_shared<RDFBlankNode>(node);
            }

            default:
                throw ValueException("Node not recognised");
        }
    }


/***************************************************
 * RDFLiteralNode implementation
 */

    RDFLiteralNode::RDFLiteralNode(const LibrdfNode &node)
            : RDFNode(node) {

    }

    std::string RDFLiteralNode::str() {
        unsigned char *val = librdf_node_get_literal_value(*node_.getNode());
        std::string str = (const char *) val;
        free(val);
        return str;
    }


/***************************************************
 * RDFLiteralNode implementation
 */

    RDFTypedLiteralNode::RDFTypedLiteralNode(LibrdfNode node) : RDFNode(node) {

    }

    std::string RDFTypedLiteralNode::getType() {
        raptor_uri *uri = librdf_node_get_literal_value_datatype_uri(*getNode().getNode());
        unsigned char *s = raptor_uri_to_string(uri);
        std::string string = (const char *) s;
        free(s);
        return string;
    }

    std::string RDFTypedLiteralNode::str() {
        unsigned char *val = librdf_node_get_literal_value(*node_.getNode());
        std::string str = (const char *) val;
        free(val);
        return str;
    }

/***************************************************
 * RDFUriNode implementation
 */

    RDFURINode::RDFURINode(LibrdfNode node)
            : RDFNode(std::move(node)) {
    }

    std::string RDFURINode::str() {
        librdf_uri *uri = librdf_node_get_uri(*node_.getNode());
        unsigned char *cstr = librdf_uri_to_string(uri);
        std::string str = (const char *) cstr;
        free(cstr);
        return str;
    }


/***************************************************
 * RDFBlankNode implementation
 */
    RDFBlankNode::RDFBlankNode(LibrdfNode node)
            : RDFNode(std::move(node)) {
    }

    std::string RDFBlankNode::str() {
        unsigned char *val = librdf_node_get_blank_identifier(*node_.getNode());
        std::string str = (const char *) val;
        free(val);
        return str;
    }

}




















