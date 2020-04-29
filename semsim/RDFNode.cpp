//
// Created by Ciaran on 4/17/2020.
//


#include "RDFNode.h"
#include "librdf.h"
#include <regex>
#include <utility>
#include "semsim/SemSim.h"


namespace semsim {


/***************************************************
 * RDFNode implementation
 */
    RDFNode::RDFNode(librdf_world *world, std::string value, const char *xml_language, bool is_wf_xml)
            : world_(world),
              value_(std::move(value)),
              xml_language_(xml_language),
              is_wf_xml_(is_wf_xml) {

    }

    /*
     * Retrive a value from a librdf_node object,
     * regardless of its type.
     */
    std::string RDFNode::getValue(librdf_node *node) {
        std::string value;
        switch (node->type) {
            case RAPTOR_TERM_TYPE_URI: {
                value = (const char *) librdf_uri_as_string(librdf_node_get_uri(node));
                break;
            }
            case RAPTOR_TERM_TYPE_LITERAL: {
                value = (const char *) librdf_node_get_literal_value(node);
                break;
            }
            case RAPTOR_TERM_TYPE_BLANK: {
                value = (const char *) librdf_node_get_blank_identifier(node);
                break;
            }
            default:
                throw LibRDFException("Unrecognized term type");
        }
        return value;
    }

    /*
     * Creates a shared pointer to an RDFNode object given a librdf_world and
     * a librdf_node.
     */
    std::shared_ptr<RDFNode> RDFNode::fromRDFNode(librdf_world *world, librdf_node *node) {
        switch (node->type) {
            case RAPTOR_TERM_TYPE_URI  : {
                return std::make_shared<RDFURINode>(RDFURINode(world, node));
            }
            case RAPTOR_TERM_TYPE_LITERAL: {
                return  std::make_shared<RDFLiteralNode>(RDFLiteralNode(world, node));
            }
            case RAPTOR_TERM_TYPE_BLANK: {
                return  std::make_shared<RDFBlankNode>(RDFBlankNode(world, node));
            }
            default:
                throw ValueException("Node not recognised");
        }
    }

/***************************************************
 * RDFLiteralNode implementation
 */

        RDFLiteralNode::RDFLiteralNode(
                librdf_world * world, std::string
        value, std::string
        data_type_uri,
        const char *xml_language,
        bool is_wf_xml)
        : RDFNode(world, std::move(value), xml_language, is_wf_xml),
                data_type_uri(std::move(data_type_uri))
        {
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


        RDFLiteralNode::RDFLiteralNode(librdf_world * world, librdf_node * node, std::string
        data_type,
        const char *xml_language,
        bool is_wf_xml)
        : RDFNode(world, RDFNode::getValue(node), xml_language, is_wf_xml), data_type_uri(std::move(data_type))
        {
        }

/***************************************************
 * RDFUriNode implementation
 */
        RDFURINode::RDFURINode(librdf_world * world, std::string
        value,
        const char *xmlLanguage,
        bool isWfXml) :
        RDFNode(world, std::move(value), xmlLanguage, isWfXml)
        {

        }

        std::string RDFURINode::str() {
            std::string identifier_dot_org = "https://identifiers.org/";
            std::regex identifiers_regex(identifier_dot_org);
            std::regex http_regex("^https://");
            std::regex identifiers_org_form1("^(?!file://)(?!https://)(?!http://)([A-Za-z0-9]+)[/:]{1}(\\S*)");
//        std::regex identifiers_org_form2("^(?!file://)(?!https://)(?!http://)([A-Za-z0-9]+):(\\S*)");
            std::regex file_regex("^file://");

            std::smatch m;
            std::string x;
            // if we find identifiers.org form 1
            if (std::regex_search(value_, m, identifiers_org_form1)) {
                return identifier_dot_org + std::string(m[1]) + "/" + std::string(m[2]);
            } else {
                return value_;
            }

        }

        librdf_node *RDFURINode::toRdfNode() {
            return librdf_new_node_from_uri_string(world_, (const unsigned char *) str().c_str());
        }


        RDFURINode::RDFURINode(librdf_world * world, librdf_node * node,
        const char *xml_language,
        bool is_wf_xml)
        : RDFNode(world, RDFNode::getValue(node), xml_language, is_wf_xml)
        {
        }


/***************************************************
 * RDFBlankNode implementation
 */
        RDFBlankNode::RDFBlankNode(librdf_world * world, std::string
        value,
        const char *xml_language,
        bool is_wf_xml) :
        RDFNode(world, std::move(value), xml_language, is_wf_xml)
        {

        }

        std::string RDFBlankNode::str() {
            return "note yet imple";
        }

        librdf_node *RDFBlankNode::toRdfNode() {
            return librdf_new_node_from_blank_identifier(
                    world_, (const unsigned char *) value_.c_str());
        }

        RDFBlankNode::RDFBlankNode(librdf_world * world, librdf_node * node,
        const char *xml_language,
        bool is_wf_xml)
        : RDFNode(world, RDFNode::getValue(node), xml_language, is_wf_xml)
        {
        }
    }




















