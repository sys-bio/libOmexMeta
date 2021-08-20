#include "redland/LibrdfParser.h"

#include "redland/LibrdfModel.h"
#include <utility>
#include "redland/Logger.h"

namespace redland {

    LibrdfParser::LibrdfParser(librdf_parser *parser)
        : RedlandType_librdf_parser(parser, librdf_free_parser) {
        REDLAND_DEBUG("Instantiated a LibrdfParser instance");
    }

    LibrdfParser::LibrdfParser(std::string syntax, std::string mime_type, const std::string &type_uri)
        : syntax_(std::move(syntax)), mime_type_(std::move(mime_type)) {
        freeFunc_ = librdf_free_parser;
        setTypeUri(type_uri);
        validateParserName();
        obj_ = makeParser();
        REDLAND_DEBUG("Instantiated a LibrdfParser instance");
    }

    librdf_parser *LibrdfParser::makeParser() {
        if (obj_ != nullptr) {
            librdf_free_parser(obj_);
            obj_ = nullptr;
        }
        const char *name_used = nullptr;
        if (!syntax_.empty())
            name_used = syntax_.c_str();

        const char *mime_type_used = nullptr;
        if (!mime_type_.empty())
            mime_type_used = mime_type_.c_str();

        if (!name_used && !mime_type_used && !type_uri_)
            throw std::invalid_argument(
                    "std::invalid_argument: LibrdfParser::makeParser(): Need at "
                    "least one of format, mime_type or type_uri arguments");
        librdf_parser *parser = librdf_new_parser(LibrdfWorld::getWorld(), name_used, mime_type_used, type_uri_);
        // must set options each time we create new parser
        // i.e. when we change a parameter, like format
        setOptions(parser);
        return parser;
    }

    //    LibrdfParser::LibrdfParser(LibrdfParser &&parser) noexcept {
    //        format_ = std::move(parser.format_);
    //        mime_type_ = std::move(parser.mime_type_);
    //        if (parser.type_uri_ != nullptr) {
    //            if (type_uri_ != nullptr) {
    //                librdf_free_uri(type_uri_);
    //            }
    //            type_uri_ = parser.type_uri_;
    //            parser.type_uri_ = nullptr;
    //        }
    //        if (parser.obj_ != nullptr) {
    //            if (obj_ != nullptr) {
    //                // ensure we don't create leak from
    //                // forgetting to free the original parser
    //                librdf_free_parser(obj_);
    //            }
    //            obj_ = parser.obj_;
    //            parser.obj_ = nullptr;
    //        }
    //    }
    //
    //    LibrdfParser &LibrdfParser::operator=(LibrdfParser &&parser) noexcept {
    //        if (this != &parser) {
    //            format_ = std::move(parser.format_);
    //            mime_type_ = std::move(parser.mime_type_);
    //            if (parser.type_uri_ != nullptr) {
    //                if (type_uri_ != nullptr) {
    //                    librdf_free_uri(type_uri_);
    //                }
    //                type_uri_ = parser.type_uri_;
    //                parser.type_uri_ = nullptr;
    //            }
    //            if (parser.obj_ != nullptr) {
    //                // ensure we don't create leak from
    //                // forgetting to free the original parser
    //                if (obj_ != nullptr) {
    //                    librdf_free_parser(obj_);
    //                }
    //                obj_ = parser.obj_;
    //                parser.obj_ = nullptr;
    //            }
    //        }
    //        return *this;
    //    }
    std::string LibrdfParser::getName() const {
        return syntax_;
    }

    void LibrdfParser::setName(const char *name) {
        syntax_ = name;
        validateParserName();
        obj_ = makeParser();
    }

    std::string LibrdfParser::getMimeType() const {
        return mime_type_;
    }

    void LibrdfParser::setMimeType(const char *mimeType) {
        mime_type_ = mimeType;
        obj_ = makeParser();
    }

    librdf_uri *LibrdfParser::getTypeUri() const {
        return type_uri_;
    }

    void LibrdfParser::setTypeUri(librdf_uri *typeUri) {
        if (!typeUri)
            throw RedlandNullPointerException("RedlandNullPointerException: LibrdfParser::setTypeUri: typeUri");
        if (type_uri_) {
            librdf_free_uri(type_uri_);
            type_uri_ = nullptr;
        }
        type_uri_ = typeUri;
    }


    void LibrdfParser::setTypeUri(const std::string &type_uri) {
        if (type_uri_) {
            librdf_free_uri(type_uri_);
            type_uri_ = nullptr;
        }
        type_uri_ = librdf_new_uri(LibrdfWorld::getWorld(), (const unsigned char *) type_uri.c_str());
    }


    void LibrdfParser::setOption(librdf_parser *parser, const std::string &option, const std::string &value) {
        // prefix for option uri's. Append with desired option for full uri.
        std::string feature_uri_base = "http://feature.librdf.org/raptor-";
        LibrdfNode node = LibrdfNode::fromLiteral(value);
        LibrdfUri u(feature_uri_base + option);
        int failed = librdf_parser_set_feature(parser, u.getWithoutIncrement(), node.getWithoutIncrement());
        if (failed < 0) {
            throw std::invalid_argument("No such feature: " + feature_uri_base);
        }
        if (failed) {
            throw std::invalid_argument(
                    "Trying to set parser option " + option + " to value " + value + "but couldn't");
        }
    }

    void LibrdfParser::setOptions(librdf_parser *parser) {
        // set some parser options. These are things
        // that we always want - like support for
        // scanning xml documents for RDF
        // or enabling the Bag ID.
        // features docs: http://librdf.org/raptor/api-1.4/raptor-section-feature.html
        setOption(parser, "scanForRDF", "1");
        setOption(parser, "allowNonNsAttributes", "0");
        setOption(parser, "allowOtherParsetypes", "1");
        setOption(parser, "allowBagID", "0");// does nae work
        setOption(parser, "allowRDFtypeRDFlist", "1");
        setOption(parser, "normalizeLanguage", "1");
        setOption(parser, "nonNFCfatal", "0");
        setOption(parser, "warnOtherParseTypes", "1");
        setOption(parser, "checkRdfID", "1");
    }

    int LibrdfParser::numNamespacesSeen() const {
        return librdf_parser_get_namespaces_seen_count(obj_);
    }

    std::string LibrdfParser::getNamespacesSeenUri(int index) const {
        librdf_uri *uri = librdf_parser_get_namespaces_seen_uri(obj_, index);
        return (const char *) librdf_uri_as_string(uri);
    }

    std::string LibrdfParser::getNamespacesSeenPrefix(int index) const {
        return std::string(librdf_parser_get_namespaces_seen_prefix(obj_, index));
    }

    void LibrdfParser::parseString(const std::string &rdf_string, const LibrdfModel &model,
                                   const LibrdfUri &base_uri) const {
        librdf_parser_parse_string_into_model(
                obj_, (const unsigned char *) rdf_string.c_str(),
                base_uri.get(), model.getWithoutIncrement());
    }

    void LibrdfParser::parseString(const std::string &rdf_string, const LibrdfModel &model,
                                   const std::string &base_uri) const {
        LibrdfUri u(base_uri);
        librdf_parser_parse_string_into_model(
                obj_, (const unsigned char *) rdf_string.c_str(),
                u.getWithoutIncrement(), model.getWithoutIncrement());
    }

    void LibrdfParser::parseUri(const std::string &uri_string, const LibrdfModel &model) const {
        LibrdfUri uri(uri_string);
        librdf_parser_parse_into_model(
                obj_, uri.getWithoutIncrement(), uri.getWithoutIncrement(), model.getWithoutIncrement());
    }

    void LibrdfParser::parseFile(const std::string &filename_uri, const LibrdfModel &model, const std::string& baseUriString) const {
        LibrdfUri filename_uri_ = LibrdfUri::fromFilename(filename_uri);
        LibrdfUri base_uri = LibrdfUri(baseUriString);
        librdf_parser_parse_into_model(
                obj_, filename_uri_.getWithoutIncrement(), base_uri.getWithoutIncrement(), model.getWithoutIncrement());
    }

    void LibrdfParser::validateParserName() const {
        std::vector<std::string> v = {
                "rdfxml",
                "ntriples",
                "turtle",
                "nquads",
                "guess",
                "",// empty string is allowed
        };
        if (std::find(v.begin(), v.end(), getName()) != v.end()) {
            // string accepted return
            return;
        }
        // error
        std::ostringstream os;
        os << "Invalid Argument Exception: RDF::fromString: Format \"" << getName()
           << "\" is not a valid option. These are your options: ";
        for (auto &it : v) {
            os << it << ", ";
        }
        throw std::invalid_argument(os.str());
    }

    std::vector<std::string> LibrdfParser::getSeenNamespaces(std::vector<std::string> namespaces) const {
        for (int i = 0; i < numNamespacesSeen(); i++) {
            std::string nsref = getNamespacesSeenUri(i);
            if (std::find(namespaces.begin(), namespaces.end(), nsref) == namespaces.end())
                namespaces.push_back(nsref);
        }
        return namespaces;
    }

}// namespace redland