//
// Created by Ciaran on 4/17/2020.
//


#include "RDFNode.h"
#include "librdf.h"
#include <regex>
#include <utility>
#include "SemSim.h"


namespace semsim {


/***************************************************
 * RDFNode implementation
 */
    RDFNode::RDFNode(LibrdfNode node)
            : node_(std::move(node)) {
    }

    std::string RDFNode::str() {
        return node_.str();
    }

    const LibrdfNode &RDFNode::getNode() const {
        return node_;
    }

    RDFNode::~RDFNode() = default;

//    /*
//     * Retrive a value from a librdf_node object,
//     * regardless of its type.
//     */
//    std::string RDFNode::getValue(LibrdfNode node) {
//        std::string value;
//        switch ((*node.getNode())->type) {
//            case RAPTOR_TERM_TYPE_URI: {
//                value = (const char *) librdf_uri_as_string(librdf_node_get_uri(*node.getNode()));
//                break;
//            }
//            case RAPTOR_TERM_TYPE_LITERAL: {
//                value = (const char *) librdf_node_get_literal_value(*node.getNode());
//                break;
//            }
//            case RAPTOR_TERM_TYPE_BLANK: {
//                value = (const char *) librdf_node_get_blank_identifier(*node.getNode());
//                break;
//            }
//            default:
//                throw LibRDFException("Unrecognized term type");
//        }
//        return value;
//    }

//    /*
//     * Creates a shared pointer to an RDFNode object given a librdf_world and
//     * a librdf_node.
//     */
//    std::shared_ptr<RDFNode> RDFNode::fromRDFNode(LibrdfWorld world, LibrdfNode node) {
//        switch ((*node.getNode())->type) {
//            case RAPTOR_TERM_TYPE_URI  : {
//                return std::make_shared<RDFURINode>(RDFURINode(world, node));
//            }
//            case RAPTOR_TERM_TYPE_LITERAL: {
//                return std::make_shared<RDFLiteralNode>(RDFLiteralNode(world, node));
//            }
//            case RAPTOR_TERM_TYPE_BLANK: {
//                return std::make_shared<RDFBlankNode>(RDFBlankNode(world, node));
//            }
//            default:
//                throw ValueException("Node not recognised");
//        }
//    }

/***************************************************
 * RDFLiteralNode implementation
 */

    RDFLiteralNode::RDFLiteralNode(const LibrdfNode &node)
            : RDFNode(node) {

    }

//    std::string RDFLiteralNode::str() {
//        return value_;
//    }

//    LibrdfNode RDFLiteralNode::getNode() {
//        return librdf_new_node_from_typed_literal(
//                world_, (const unsigned char *) value_.c_str(), xml_language_,
//                librdf_new_uri(world_, (const unsigned char *) data_type_uri.c_str()));
//    }

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

/***************************************************
 * RDFUriNode implementation
 */

    RDFURINode::RDFURINode(LibrdfNode node)
            : RDFNode(std::move(node)) {
    }

//    std::string RDFURINode::str() {
//        std::string identifier_dot_org = "https://identifiers.org/";
//        std::regex identifiers_regex(identifier_dot_org);
//        std::regex http_regex("^https://");
//        std::regex identifiers_org_form1("^(?!file://)(?!https://)(?!http://)([A-Za-z0-9]+)[/:]{1}(\\S*)");
////        std::regex identifiers_org_form2("^(?!file://)(?!https://)(?!http://)([A-Za-z0-9]+):(\\S*)");
//        std::regex file_regex("^file://");
//
//        std::smatch m;
//        std::string x;
//        // if we find identifiers.org form 1
//        if (std::regex_search(value_, m, identifiers_org_form1)) {
//            return identifier_dot_org + std::string(m[1]) + "/" + std::string(m[2]);
//        } else {
//            return value_;
//        }
//
//    }

//    LibrdfNode RDFURINode::getNode() {
//        return librdf_new_node_from_uri_string(world_, (const unsigned char *) str().c_str());
//    }


//    std::string RDFURINode::str() {
//        raptor_uri *uri = librdf_node_get_uri(*getNode().getNode());
//        unsigned char *s = raptor_uri_to_string(uri);
//        std::string value = (const char*)s;
//        free(s);
//        return value;
//    }

//    RDFURINode::RDFURINode(LibrdfWorld world, LibrdfNode node,
//                           const char *xml_language,
//                           bool is_wf_xml)
//            : RDFNode(world, RDFNode::getValue(node), xml_language, is_wf_xml) {
//    }


/***************************************************
 * RDFBlankNode implementation
 */
    RDFBlankNode::RDFBlankNode(LibrdfNode node)
            : RDFNode(std::move(node)) {
    }

//    std::string RDFBlankNode::str() {
//        return value_;
//    }

//    LibrdfNode RDFBlankNode::getNode() {
//        return librdf_new_node_from_blank_identifier(
//                world_, (const unsigned char *) value_.c_str());
//    }

//    RDFBlankNode::RDFBlankNode(LibrdfWorld world, LibrdfNode node,
//                               const char *xml_language,
//                               bool is_wf_xml)
//            : RDFNode(world, RDFNode::getValue(node), xml_language, is_wf_xml) {
//    }

}




















