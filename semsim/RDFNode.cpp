//
// Created by Ciaran on 4/17/2020.
//


#include "RDFNode.h"
#include "librdf.h"

namespace semsim {


/***************************************************
 * RDFNode implementation
 */
    RDFNode::RDFNode(librdf_world *world, std::string value, const char *xml_language, bool is_wf_xml)
            : world_(world),
              value_(value),
              xml_language_(xml_language),
              is_wf_xml_(is_wf_xml) {}


/***************************************************
 * RDFLiteralNode implementation
 */

    RDFLiteralNode::RDFLiteralNode(
            librdf_world *world, std::string value, std::string data_type_uri, const char *xml_language, bool is_wf_xml)
            : RDFNode(world, value, xml_language, is_wf_xml),
              data_type_uri(std::move(data_type_uri)) {
        is_typed_literal = true;
    }

    std::string RDFLiteralNode::str() {
        return value_;
    }

    librdf_node *RDFLiteralNode::toRdfNode() {
        return librdf_new_node_from_typed_literal(
                world_, (const unsigned char *) value_.c_str(), xml_language_,
                librdf_new_uri(world_, (const unsigned char *) data_type_uri.c_str()));
    }

/***************************************************
 * RDFUriNode implementation
 */
    RDFURINode::RDFURINode(librdf_world *world, std::string value, const char *xmlLanguage, bool isWfXml) :
            RDFNode(world, std::move(value), xmlLanguage, isWfXml) {

    }

    std::string RDFURINode::str() {
        return "not yet implemented";
    }

    librdf_node *RDFURINode::toRdfNode() {
        return librdf_new_node_from_uri_string(world_, (const unsigned char *) value_.c_str());
    }


/***************************************************
 * RDFBlankNode implementation
 */
    RDFBlankNode::RDFBlankNode(librdf_world *world, std::string value, const char *xml_language, bool is_wf_xml) :
            RDFNode(world, value, xml_language, is_wf_xml) {

    }

    std::string RDFBlankNode::str() {
        return "note yet imple";
    }

    librdf_node *RDFBlankNode::toRdfNode() {
        return librdf_new_node_from_blank_identifier(
                world_, (const unsigned char *) value_.c_str());
    }
}




















