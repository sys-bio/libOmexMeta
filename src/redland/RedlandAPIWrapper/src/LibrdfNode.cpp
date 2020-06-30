//
// Created by Ciaran on 5/17/2020.
//

#include "LibrdfNode.h"


/*
 * todo put name of exception in all error messages.
 */
#include "World.h"

namespace redland {

    LibrdfNode::LibrdfNode(librdf_node *node)
            : node_(node) {}

    LibrdfNode LibrdfNode::fromUriString(const std::string &uri_string) {
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
        return LibrdfNode(n);
    }

    LibrdfNode LibrdfNode::fromRelativeUri(const std::string &uri_string, const std::string& base_uri) {
        LibrdfUri uri(base_uri);
        librdf_uri* u = librdf_new_uri_relative_to_base(uri.get(), (const unsigned char*) uri_string.c_str());
        uri.freeUri();
        librdf_node *n = librdf_new_node_from_uri(World::getWorld(), u);
        return LibrdfNode(n);
    }

    LibrdfNode LibrdfNode::fromBlank(const std::string &blank) {
        return LibrdfNode(librdf_new_node_from_blank_identifier(
                World::getWorld(), (const unsigned char *) blank.c_str()
        ));
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

    LibrdfNode LibrdfNode::fromLiteral(
            const std::string &literal, const std::string &literal_datatype_uri,
            const std::string &xml_language) {
        std::string literal_datatype_ = validateLiteralDatatype(literal_datatype_uri);
        const char *xml_language_;
        if (xml_language.empty()) {
            xml_language_ = nullptr;
        } else {
            xml_language_ = xml_language.c_str();
        }
        librdf_uri *literal_datatype_uri_ = librdf_new_uri(World::getWorld(),
                                                           (const unsigned char *) literal_datatype_.c_str());
        librdf_node *n = librdf_new_node_from_typed_literal(
                World::getWorld(),
                (const unsigned char *) literal.c_str(),
                xml_language_,
                literal_datatype_uri_);
        librdf_free_uri(literal_datatype_uri_);
        return LibrdfNode(n);
    }

    LibrdfNode LibrdfNode::newEmptyNode() {
        return LibrdfNode(librdf_new_node(World::getWorld()));
    }

    /*
     * Retrive a value from a librdf_node object,
     * regardless of its type.
     */
    std::string LibrdfNode::str(librdf_node *node) {
        if (!node) {
            throw RedlandNullPointerException("LibrdfNode::str(): NullPointerException: node");
        }
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
                throw RedlandLibrdfException("RedlandLibrdfException: Librdf::Str() : Unrecognized term type");
        }
        return value;
    }

    raptor_term_type LibrdfNode::getRaptorTermType() {
        return node_->type;
    }

    librdf_node *LibrdfNode::get() const {
        return node_;
    }


    LibrdfUri LibrdfNode::getLiteralDatatype() {
        return LibrdfUri::fromRawPtr(librdf_node_get_literal_value_datatype_uri(node_));
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
        return LibrdfUri::fromRawPtr(librdf_node_get_uri(node_));
    }

    void LibrdfNode::setUri(const std::string &uri) {
        if (node_->type != RAPTOR_TERM_TYPE_URI)
            throw RedlandLibrdfException(
                    "RedlandLibrdfException: LibrdfNode::setUri(): trying to set a uri on a non-uri node");
        if (node_ != nullptr) {
            freeNode();
            node_ = nullptr;
        }

        /*
         * So setters exist for librdf_node so we must create a
         * new one with the new uri.
         */
        node_ = librdf_new_node_from_uri_string(
                World::getWorld(), (const unsigned char *) uri.c_str());

    }

    void LibrdfNode::setLiteralDatatype(const std::string &datatype) {
        if (node_->type != RAPTOR_TERM_TYPE_LITERAL)
            throw RedlandLibrdfException(
                    "RedlandLibrdfException: LibrdfNode::setLiteralDatatype(): trying to set a literal datatype on a non-literal node");
        std::string literal_datatype_ = validateLiteralDatatype(datatype);

        // collect data fields that we wont change before free existing node
        bool language_is_null = false;
        if (node_->value.literal.language == nullptr) {
            language_is_null = true;
        }
        unsigned char *language_used = nullptr;
        if (!language_is_null) {
            // use std::string to make a copy
            std::string language = (const char *) node_->value.literal.language;
            language_used = (unsigned char *) language.c_str();
        }
        std::string value = (const char *) node_->value.literal.string;

        // free existing node
        if (node_ != nullptr) {
            freeNode();
            node_ = nullptr;
        }

        // reset node with node information
        node_ = librdf_new_node_from_typed_literal(
                World::getWorld(),
                (const unsigned char *) value.c_str(),
                (const char *) language_used,
                librdf_new_uri(World::getWorld(), (unsigned char *) literal_datatype_.c_str()));
    }

    void LibrdfNode::setBlankIdentifier(const std::string &identifier) {
        if (node_->type != RAPTOR_TERM_TYPE_BLANK)
            throw RedlandLibrdfException(
                    "RedlandLibrdfException: LibrdfNode::setBlankIdentifier(): trying to set a blank identifer on a non-blank node");
        if (node_ != nullptr) {
            freeNode();
            node_ = nullptr;
        }
        node_ = librdf_new_node_from_blank_identifier(
                World::getWorld(),
                (const unsigned char *) identifier.c_str());
    }

    void LibrdfNode::freeNode(librdf_node *node) {
        if (!node) {
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: LibrdfNode::free: trying to free null node");
        }
        librdf_free_node(node);
    }

    void LibrdfNode::freeNode() {
        LibrdfNode::freeNode(node_);
    }

    std::string LibrdfNode::str() const{
        return LibrdfNode::str(node_);
    }

    LibrdfNode::LibrdfNode(LibrdfNode &&node) noexcept {
        if (node.node_ != nullptr) {
            if (node_ != nullptr) {
                librdf_free_node(node_);
                node_ = nullptr;
            }
            node_ = node.node_;
            node.node_ = nullptr;
        }
    }

    LibrdfNode &LibrdfNode::operator=(LibrdfNode &&node) noexcept {
        if (this != &node) {
            if (node.node_ != nullptr) {
                if (node_ != nullptr) {
                    librdf_free_node(node_);
                    node_ = nullptr;
                }
                node_ = node.node_;
                node.node_ = nullptr;
            }
        }
        return *this;
    }

    bool LibrdfNode::operator==(const LibrdfNode &rhs) const {
        return librdf_node_equals(node_, rhs.node_);
    }

    bool LibrdfNode::operator!=(const LibrdfNode &rhs) const {
        return !(rhs == *this);
    }

    LibrdfNode LibrdfNode::copyNode(const LibrdfNode& node) {
        return LibrdfNode(librdf_new_node_from_node(node.node_));
    }

}
