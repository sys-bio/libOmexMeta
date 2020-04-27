//
// Created by Ciaran on 4/17/2020.
//


#include "RDFNode.h"
#include "librdf.h"
#include <regex>
#include "semsim/SemSim.h"


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
        std::string identifier_dot_org = "https://identifiers.org/";
        std::regex identifiers_regex(identifier_dot_org);
        std::regex http_regex("https://");
        std::regex identifiers_org_form1("^(?![https://])([A-Za-z0-9]*):{1}(\\S*)");
        std::regex identifiers_org_form2("^(?![https://])([A-Za-z0-9]*)/{1}(\\S*)");

        std::smatch m;
        std::string x;
        if (std::regex_search(value_, m, identifiers_org_form1)) {
            // if its not html string check for form uniprot:identifier
            x = identifier_dot_org + std::string(m[1]) + "/" + std::string(m[2]);
            return x;
        } else if (std::regex_search(value_, m, identifiers_org_form2)) {
            // if its not html string check for form uniprot/identifier
            return identifier_dot_org + std::string(m[1]) + "/" + std::string(m[2]);
        } else {
            return value_;
        }
    }

    librdf_node *RDFURINode::toRdfNode() {
        // todo does str need to be relative to base???
        return librdf_new_node_from_uri_string(world_, (const unsigned char *) str().c_str());
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




















