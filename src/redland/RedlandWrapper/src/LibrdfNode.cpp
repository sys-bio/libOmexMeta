//
// Created by Ciaran on 5/17/2020.
//

#include "redland/LibrdfNode.h"
#include "redland/Logger.h"

/*
 * todo put name of exception in all error messages.
 */
#include "redland/LibrdfWorld.h"

namespace redland {


    LibrdfNode::LibrdfNode(librdf_node *node)
        : RefCounted_librdf_node(node, librdf_free_node) {
//        REDLAND_DEBUG("Instantiated a LibrdfNode instance");
    }

    LibrdfNode::LibrdfNode(const LibrdfUri &uri)
        : RefCounted_librdf_node(LibrdfNode::fromUriString(uri.str()).get(), librdf_free_node) {
//        REDLAND_DEBUG("Instantiated a LibrdfNode instance");
    };

    //todo the content of thos method really belongs somewhere else
    LibrdfNode LibrdfNode::fromUriString(const std::string &uri_string) {
        std::string identifier_dot_org = "https://identifiers.org/";
        std::regex identifiers_regex(identifier_dot_org);
        std::regex http_regex("^https://");
        std::regex identifiers_org_form1("^(?!file://)(?!https://)(?!http://)([A-Za-z0-9]+)[/:]{1}(\\S*)");
        std::regex file_regex("^file://");
        std::regex go_regex("^GO:\d*");
        std::regex pubmed_regex("^[Pp][Uu][Bb][Mm][Ee][Dd]:\d*");
        std::regex taxon_regex("^[Tt][Aa][Xx][Oo][Nn][Oo][Mm][Yy]:\d*");
        std::regex biomodels_db_regex("^[Bb][Ii][Oo][Mm][Oo][Dd][Ee][Ll][Ss]\.[Dd][Bb]:\d*");
        std::regex uniprot_regex("^[Uu][Nn][Ii][Pp][Rr][Oo][Tt]:\d*");
        std::regex opb_regex("^[Oo][Pp][Bb]:\d*");
        std::regex fma_regex("^[Ff][Mm][Aa]:\d*");
        std::regex chebi_regex("^[Cc][Hh][Ee][Bb][Ii]:\d*");
        std::regex urn_miriam_regex("^urn:miriam:.*");

        std::smatch m;
        std::string uri_string_;
        // if we find identifiers.org form 1
        if (std::regex_search(uri_string, m, go_regex)) {
            uri_string_ = identifier_dot_org + uri_string;
        }

        else if (std::regex_search(uri_string, m, pubmed_regex)) {
            uri_string_ = identifier_dot_org + uri_string;
        }

        else if (std::regex_search(uri_string, m, chebi_regex)) {
            uri_string_ = identifier_dot_org + uri_string;
        }

        else if (std::regex_search(uri_string, m, opb_regex)) {
            uri_string_ = identifier_dot_org + uri_string;
        }

        else if (std::regex_search(uri_string, m, taxon_regex)) {
            uri_string_ = identifier_dot_org + uri_string;
        }

        else if (std::regex_search(uri_string, m, biomodels_db_regex)) {
            uri_string_ = identifier_dot_org + uri_string;
        }

        else if (std::regex_search(uri_string, m, uniprot_regex)) {
            uri_string_ = identifier_dot_org + uri_string;
        }

        else if (std::regex_search(uri_string, m, opb_regex)) {
            uri_string_ = identifier_dot_org + uri_string;
        }

        else if (std::regex_search(uri_string, m, fma_regex)) {
            uri_string_ = identifier_dot_org + uri_string;
        }

        // urn:miriam: resources stay the same
        else if (std::regex_search(uri_string, m, urn_miriam_regex)) {
            uri_string_ = uri_string;
        }

        else if (std::regex_search(uri_string, m, identifiers_org_form1)) {
            uri_string_ = identifier_dot_org + std::string(m[1]) + "/" + std::string(m[2]);
        }

        else {
            uri_string_ = uri_string;
        }

//        LibrdfUri uri(uri_string);
//        librdf_node* n = librdf_new_node_from_uri(LibrdfWorld::getWorld(), uri.getWithoutIncrement());
        librdf_node *n = librdf_new_node_from_uri_string(
                LibrdfWorld::getWorld(), (const unsigned char *) uri_string_.c_str());
        return LibrdfNode(n);
    }

    LibrdfNode LibrdfNode::fromRelativeUri(const std::string &uri_string, const std::string &base_uri) {
        LibrdfUri uri(base_uri);
        librdf_uri *u  = librdf_new_uri_relative_to_base(uri.get(), (const unsigned char *) uri_string.c_str());
        librdf_node *n = librdf_new_node_from_uri(LibrdfWorld::getWorld(), u);
        return LibrdfNode(n);
    }

    LibrdfNode LibrdfNode::fromBlank(const std::string &blank) {
        return LibrdfNode(librdf_new_node_from_blank_identifier(
                LibrdfWorld::getWorld(), (const unsigned char *) blank.c_str()));
    }

    std::string LibrdfNode::validateLiteralDatatype(const std::string &literal_datatype_uri) {
        // when the user provides a full uri, we just return it as we assume
        // it is valid
        if (literal_datatype_uri.rfind("http", 0) == 0) {
            return literal_datatype_uri;
        }
        // otherwise we assume standard w3 uri and prepend for the user
        std::string literal_datatype_prefix_ = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";
        std::string literal_datatype_;

        literal_datatype_ = literal_datatype_prefix_ + literal_datatype_uri;

        return literal_datatype_;
    }

    LibrdfNode LibrdfNode::fromLiteral(
            const std::string &literal, const std::string &literal_datatype_uri,
            const std::string &xml_language) {
        std::string literal_datatype_;
        if (!literal_datatype_uri.empty()) {
            literal_datatype_ = validateLiteralDatatype(literal_datatype_uri);
        }
        const char *xml_language_;
        if (xml_language.empty()) {
            xml_language_ = nullptr;
        } else {
            xml_language_ = xml_language.c_str();
        }
        librdf_uri *literal_datatype_uri_ = nullptr;
        if (!literal_datatype_.empty()) {
            literal_datatype_uri_ = librdf_new_uri(
                    LibrdfWorld::getWorld(),
                    (const unsigned char *) literal_datatype_.c_str());
        }
        librdf_node *n = librdf_new_node_from_typed_literal(
                LibrdfWorld::getWorld(),
                (const unsigned char *) literal.c_str(),
                xml_language_,
                literal_datatype_uri_);
        librdf_free_uri(literal_datatype_uri_);
        LibrdfNode node(n);
        return node;
    }

    LibrdfNode LibrdfNode::newEmptyNode() {
        return LibrdfNode(librdf_new_node(LibrdfWorld::getWorld()));
    }

    /*
     * Retrive a value from a librdf_node object,
     * regardless of its type.
     */
    std::string LibrdfNode::str() const {
        if (isNull()) {
            throw RedlandNullPointerException("LibrdfNode::str(): NullPointerException: node");
        }
        std::string value;
        switch (getRaptorTermType()) {
            case RAPTOR_TERM_TYPE_URI: {
                value = (const char *) librdf_uri_as_string(librdf_node_get_uri(getWithoutIncrement()));
                break;
            }
            case RAPTOR_TERM_TYPE_LITERAL: {
                value = (const char *) librdf_node_get_literal_value(getWithoutIncrement());
                break;
            }
            case RAPTOR_TERM_TYPE_BLANK: {
                value = (const char *) librdf_node_get_blank_identifier(getWithoutIncrement());
                break;
            }
            default:
                throw RedlandLibrdfException("RedlandLibrdfException: Librdf::Str() : Unrecognized term type");
        }
        return value;
    }

    raptor_term_type LibrdfNode::getRaptorTermType() const {
        return obj_->type;
    }

    LibrdfUri LibrdfNode::getLiteralDatatype() {
        LibrdfUri uri(librdf_node_get_literal_value_datatype_uri(obj_));
        uri.incrementUsage();
        return uri;
    }

    std::string LibrdfNode::getLiteralLanguage() {
        const char *language = (const char *) obj_->value.literal.language;
        if (!language)
            return std::string();
        return std::string(language);
    }

    std::string LibrdfNode::getBlankIdentifier() {
        return std::string((const char *) obj_->value.blank.string);
    }

    LibrdfUri LibrdfNode::getUri() {
        LibrdfUri uri = LibrdfUri(librdf_node_get_uri(obj_));
        uri.incrementUsage();
        return uri;
    }

    void LibrdfNode::setUri(const std::string &uri) {
        if (obj_->type != RAPTOR_TERM_TYPE_URI)
            throw RedlandLibrdfException(
                    "RedlandLibrdfException: LibrdfNode::setUri(): trying to set a uri on a non-uri node");
        if (obj_ != nullptr) {
            freeNode();
            obj_ = nullptr;
        }

        /*
         * So setters exist for librdf_node so we must create a
         * new one with the new uri.
         */
        obj_ = librdf_new_node_from_uri_string(
                LibrdfWorld::getWorld(), (const unsigned char *) uri.c_str());
    }

    void LibrdfNode::setLiteralDatatype(const std::string &datatype) {
        if (obj_->type != RAPTOR_TERM_TYPE_LITERAL)
            throw RedlandLibrdfException(
                    "RedlandLibrdfException: LibrdfNode::setLiteralDatatype(): trying to set a literal datatype on a non-literal node");
        std::string literal_datatype_ = validateLiteralDatatype(datatype);

        // collect data fields that we wont change before free existing node
        bool language_is_null = false;
        if (obj_->value.literal.language == nullptr) {
            language_is_null = true;
        }
        unsigned char *language_used = nullptr;
        if (!language_is_null) {
            // use std::string to make a copy
            std::string language = (const char *) obj_->value.literal.language;
            language_used = (unsigned char *) language.c_str();
        }
        std::string value = (const char *) obj_->value.literal.string;

        // free existing node
        if (obj_ != nullptr) {
            freeNode();
            obj_ = nullptr;
        }

        // reset node with node information
        obj_ = librdf_new_node_from_typed_literal(
                LibrdfWorld::getWorld(),
                (const unsigned char *) value.c_str(),
                (const char *) language_used,
                librdf_new_uri(LibrdfWorld::getWorld(), (unsigned char *) literal_datatype_.c_str()));
    }

    void LibrdfNode::setBlankIdentifier(const std::string &identifier) {
        if (obj_->type != RAPTOR_TERM_TYPE_BLANK)
            throw RedlandLibrdfException(
                    "RedlandLibrdfException: LibrdfNode::setBlankIdentifier(): trying to set a blank identifer on a non-blank node");
        if (obj_ != nullptr) {
            freeNode();
            obj_ = nullptr;
        }
        obj_ = librdf_new_node_from_blank_identifier(
                LibrdfWorld::getWorld(),
                (const unsigned char *) identifier.c_str());
    }


    void LibrdfNode::freeNode() {
        if (!obj_)
            return;
        unsigned int count = getUsage();
        librdf_free_node(obj_);
        // only set to nullptr if we're sure the pointer
        // is not still in use. librdf_free_node decrements the
        // internal ref counter, but the node may become NULL.
        // If this happens the count is inaccessible for checking.
        // so we do it this way instead.
        if (count - 1 == 0) {
            obj_ = nullptr;
        }
    }

    bool LibrdfNode::operator==(const LibrdfNode &rhs) const {
        return librdf_node_equals(obj_, rhs.getWithoutIncrement());
    }

    bool LibrdfNode::operator!=(const LibrdfNode &rhs) const {
        return !(rhs == *this);
    }

    LibrdfNode LibrdfNode::copyNode(const LibrdfNode &node) {
        return LibrdfNode(librdf_new_node_from_node(node.obj_));
    }

    std::vector<std::string> LibrdfNode::splitStringBy(const std::string &str, char delimiter) {
        std::vector<std::string> tokens;
        if (str.find(delimiter) == std::string::npos) {
            // return the string in the vector
            tokens.push_back(str);
            return tokens;
        }
        std::string token;
        std::istringstream is(str);
        while (std::getline(is, token, delimiter)) {
            if (!token.empty())
                tokens.push_back(token);
        }
        return tokens;
    }

    std::string LibrdfNode::getNamespace() const {
        std::vector<std::string> split = LibrdfNode::splitStringBy(str(), '/');
        std::string last = split[split.size() - 1];
        std::string hash = "#";
        bool hash_on_end = false;
        std::vector<std::string> last_split;
        if (last.find(hash) != std::string::npos) {
            hash_on_end = true;
            last_split = LibrdfNode::splitStringBy(last, '#');
            if (last_split.size() != 2) {
                throw std::logic_error("LibrdfNode::getNamespace(): expected 2 elements");
            }
        }
        std::ostringstream ns;
        for (int i = 0; i < split.size() - 1; i++) {
            if (split[i] == "http:" || split[i] == "https:")
                ns << split[i] << "//";
            else
                ns << split[i] << "/";
        }
        if (hash_on_end) {
            ns << last_split[0] << "#";
        }
        return ns.str();
    }
    bool LibrdfNode::isBlank() {
        return librdf_node_is_blank(obj_);
    }
    bool LibrdfNode::isUri() {
        return librdf_node_is_resource(obj_);
    }
    bool LibrdfNode::isLiteral() {
        return librdf_node_is_literal(obj_);
    }


}// namespace redland
