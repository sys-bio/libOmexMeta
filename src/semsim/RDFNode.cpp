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
    std::unique_ptr<RDFNode> RDFNode::fromRDFNode(LibrdfNode node) {
        switch (node.getType()) {
            case RAPTOR_TERM_TYPE_URI  : {
                return std::make_unique<RDFURINode>(std::move(node));
            }

            case RAPTOR_TERM_TYPE_LITERAL: {
                return std::make_unique<RDFLiteralNode>(std::move(node));
            }

            case RAPTOR_TERM_TYPE_BLANK: {
                return std::make_unique<RDFBlankNode>(std::move(node));
            }

            default:
                throw ValueException("Node not recognised");
        }
    }


/***************************************************
 * RDFLiteralNode implementation
 */

    RDFLiteralNode::RDFLiteralNode(const LibrdfNode &node)
            : RDFNode(std::move(node)) {

    }

    std::string RDFLiteralNode::str() {
        return node_.str();
    }


/***************************************************
 * RDFLiteralNode implementation
 */

    RDFTypedLiteralNode::RDFTypedLiteralNode(LibrdfNode node) : RDFNode(node) {

    }

    std::string RDFTypedLiteralNode::getType() {
        return LibrdfUri(node_.get()->value.literal.datatype).str();
    }

    [[maybe_unused]] std::string RDFTypedLiteralNode::getLanguage() {
        return std::string((const char *) node_.get()->value.literal.language);
    }

    std::string RDFTypedLiteralNode::str() {
        return node_.str();
    }

/***************************************************
 * RDFUriNode implementation
 */

    RDFURINode::RDFURINode(LibrdfNode node)
            : RDFNode(std::move(node)) {
    }

    std::string RDFURINode::str() {
        return node_.str();
    }

    LibrdfUri RDFURINode::getUri() const {
        return LibrdfUri(node_.get()->value.uri);
    }


/***************************************************
 * RDFBlankNode implementation
 */
    RDFBlankNode::RDFBlankNode(LibrdfNode node)
            : RDFNode(std::move(node)) {
    }

    std::string RDFBlankNode::str() {
        return node_.str();
    }

    std::string RDFBlankNode::getBlankIdentifier() const {
        return std::string(
        const char*)node_.get()->value.blank.string);
    }

}




















