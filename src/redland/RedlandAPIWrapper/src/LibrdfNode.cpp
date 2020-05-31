//
// Created by Ciaran on 5/17/2020.
//

#include "LibrdfNode.h"


/*
 * todo put name of exception in all error messages.
 */
#include "World.h"

namespace redland {

    void LibrdfNode::deleter::operator()(librdf_node *node) {
        if (node)
            raptor_free_term(node);
    }

    LibrdfNode::LibrdfNode(librdf_node *node)
            : node_(std::shared_ptr<librdf_node>(node, raptor_free_term)) {
        uri_ = LibrdfUri::fromRawPtr(node_->value.uri);
    }

    librdf_node *LibrdfNode::fromUriString(const std::string &uri_string) {
        std::string identifier_dot_org = "https://identifiers.org/";
        std::regex identifiers_regex(identifier_dot_org);
        std::regex http_regex("^https://");
        std::regex identifiers_org_form1("^(?!file://)(?!https://)(?!http://)([A-Za-z0-9]+)[/:]{1}(\\S*)");
        std::regex file_regex("^file://");

        std::smatch m;
        std::string uri_string_;
        // if we find identifiers.org form 1
        if (std::regex_search(uri_string, m, identifiers_org_form1)) {
            uri_string_ = identifier_dot_org + std::string(m[1]) + "/" + std::string(m[2]);
        } else {
            uri_string_ = uri_string;
        }
        librdf_node *n = librdf_new_node_from_uri_string(
                World::getWorld(), (const unsigned char *) uri_string_.c_str());
        return n;
    }

    librdf_node *LibrdfNode::fromBlank(const std::string &blank) {
        return librdf_new_node_from_blank_identifier(
                World::getWorld(), (const unsigned char *) blank.c_str()
        );
    }

    std::string LibrdfNode::validateLiteralDatatype(const std::string &literal_datatype_uri) {
        std::string literal_datatype_prefix_ = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";
        std::string literal_datatype_;
        if (literal_datatype_uri.rfind(literal_datatype_prefix_, 0) != 0) {
            literal_datatype_ = literal_datatype_prefix_ + literal_datatype_uri;
        } else {
            literal_datatype_ = literal_datatype_uri;
        }
        return literal_datatype_;
    }

    librdf_node *
    LibrdfNode::fromLiteral(const std::string &literal, const std::string &xml_language,
                            const std::string &literal_datatype_uri) {
        std::string literal_datatype_ = validateLiteralDatatype(literal_datatype_uri);
        const char *xml_language_;
        if (xml_language.empty()) {
            xml_language_ = nullptr;
        } else {
            xml_language_ = xml_language.c_str();
        }
        return librdf_new_node_from_typed_literal(
                World::getWorld(),
                (const unsigned char *) literal.c_str(),
                xml_language_,
                librdf_new_uri(World::getWorld(), (const unsigned char *) literal_datatype_.c_str())
        );
    }


    /*
     * Retrive a value from a librdf_node object,
     * regardless of its type.
     */
    std::string LibrdfNode::str() const {
        if (!node_) {
            throw RedlandNullPointerException("LibrdfNode::str(): NullPointerException: node_");
        }
        std::string value;
        switch (node_->type) {
            case RAPTOR_TERM_TYPE_URI: {
                value = (const char *) librdf_uri_as_string(librdf_node_get_uri(node_.get()));
                break;
            }
            case RAPTOR_TERM_TYPE_LITERAL: {
                value = (const char *) librdf_node_get_literal_value(node_.get());
                break;
            }
            case RAPTOR_TERM_TYPE_BLANK: {
                value = (const char *) librdf_node_get_blank_identifier(node_.get());
                break;
            }
            default:
                throw RedlandLibrdfException("RedlandLibrdfException: Librdf::Str() : Unrecognized term type");
        }
        return value;
    }

    raptor_term_type LibrdfNode::getRaptorTermType() {
        return node_->type;
    }

    librdf_node *LibrdfNode::get() const {
        return node_.get();
    }

    /*
     * Todo consider putting error messages on the following methods
     * if they are empty
     */

    librdf_uri *LibrdfNode::getLiteralDatatype() {
        return librdf_node_get_literal_value_datatype_uri(node_.get());
    }

    std::string LibrdfNode::getLiteralLanguage() {
        const char *language = (const char *) node_->value.literal.language;
        if (!language)
            return std::string();
        return std::string(language);
    }

    std::string LibrdfNode::getBlankIdentifier() {
        return std::string((const char *) node_->value.blank.string);
    }

    LibrdfUri LibrdfNode::getUri() {
        if (uri_.isNull())
            throw RedlandNullPointerException("RedlandNullPointerException: LibrdfNode::getUri(): uri_ is not set. ");
        return uri_;
    }

    void LibrdfNode::setUri(const std::string &uri) {
        if (node_->type != RAPTOR_TERM_TYPE_URI)
            throw RedlandLibrdfException(
                    "RedlandLibrdfException: LibrdfNode::setUri(): trying to set a uri on a non-uri node");

        /*
         * So setters exist for librdf_node so we must create a
         * new one with the new uri.
         */
        node_ = std::shared_ptr<librdf_node>(librdf_new_node_from_uri_string(
                World::getWorld(), (const unsigned char *) uri.c_str()),
                                             raptor_free_term
        );
        uri_ = LibrdfUri::fromRawPtr(librdf_node_get_uri(node_.get()));

    }

    void LibrdfNode::setLiteralDatatype(const std::string &datatype) {
        if (node_->type != RAPTOR_TERM_TYPE_LITERAL)
            throw RedlandLibrdfException(
                    "RedlandLibrdfException: LibrdfNode::setLiteralDatatype(): trying to set a literal datatype on a non-literal node");
        std::string literal_datatype_ = validateLiteralDatatype(datatype);

        node_ = std::shared_ptr<librdf_node>(
                librdf_new_node_from_typed_literal(
                        World::getWorld(),
                        node_->value.literal.string,
                        (const char *) node_->value.literal.language,
                        librdf_new_uri(World::getWorld(),
                                       (unsigned char *) literal_datatype_.c_str())
                ), raptor_free_term);
    }

    void LibrdfNode::setBlankIdentifier(const std::string &identifier) {
        if (node_->type != RAPTOR_TERM_TYPE_BLANK)
            throw RedlandLibrdfException(
                    "RedlandLibrdfException: LibrdfNode::setBlankIdentifier(): trying to set a blank identifer on a non-blank node");
        node_ = std::shared_ptr<librdf_node>(
                librdf_new_node_from_blank_identifier(
                        World::getWorld(),
                        (const unsigned char *) identifier.c_str()
                ), raptor_free_term);
    }


}
