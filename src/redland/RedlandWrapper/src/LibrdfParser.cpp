#include "LibrdfParser.h"

#include <utility>
#include "LibrdfModel.h"

namespace redland {

    LibrdfParser::LibrdfParser(librdf_parser *parser) :
            parser_(parser) {}

    LibrdfParser::LibrdfParser(std::string format, std::string mime_type, const std::string &type_uri) :
            format_(std::move(format)), mime_type_(std::move(mime_type)) {
        setTypeUri(type_uri);
        validateParserName();
        parser_ = makeParser();
    }

    librdf_parser *LibrdfParser::makeParser() {
        if (parser_ != nullptr) {
            librdf_free_parser(parser_);
            parser_ = nullptr;
        }
        const char *name_used = nullptr;
        if (!format_.empty())
            name_used = format_.c_str();

        const char *mime_type_used = nullptr;
        if (!mime_type_.empty())
            mime_type_used = mime_type_.c_str();

        if (!name_used && !mime_type_used && !type_uri_)
            throw std::invalid_argument(
                    "std::invalid_argument: LibrdfParser::makeParser(): Need at "
                    "least one of format, mime_type or type_uri arguments"
            );
        librdf_parser *parser = librdf_new_parser(World::getWorld(), name_used, mime_type_used, type_uri_);
        // must set options each time we create new parser
        // i.e. when we change a parameter, like format
        setOptions(parser);
        return parser;
    }

    librdf_parser *LibrdfParser::get() const {
        return parser_;
    }

    std::string LibrdfParser::getName() const {
        return format_;
    }

    void LibrdfParser::setName(const char *name) {
        format_ = name;
        validateParserName();
        parser_ = makeParser();
    }

    std::string LibrdfParser::getMimeType() const {
        return mime_type_;
    }

    void LibrdfParser::setMimeType(const char *mimeType) {
        mime_type_ = mimeType;
        parser_ = makeParser();
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
        type_uri_ = librdf_new_uri(World::getWorld(), (const unsigned char *) type_uri.c_str());
    }


    void LibrdfParser::setOption(librdf_parser *parser, const std::string &option, const std::string &value) {
        // prefix for option uri's. Append with desired option for full uri.
        std::string feature_uri_base = "http://feature.librdf.org/raptor-";
        LibrdfNode node = LibrdfNode::fromLiteral(value);
        LibrdfUri u(feature_uri_base + option);
        int failed = librdf_parser_set_feature(parser, u.get(), node.get());
        if (failed < 0 ){
            throw std::invalid_argument("No such feature: " + feature_uri_base);
        }
        if (failed) {
            throw std::invalid_argument(
                    "Trying to set parser option " + option + " to value " + value + "but couldn't");
        }
        u.freeUri();
        node.freeNode();
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
        setOption(parser, "allowBagID", "0");
        setOption(parser, "allowRDFtypeRDFlist", "1");
        setOption(parser, "normalizeLanguage", "1");
        setOption(parser, "nonNFCfatal", "0");
        setOption(parser, "warnOtherParseTypes", "1");
        setOption(parser, "checkRdfID", "1");
    }

    int LibrdfParser::numNamespacesSeen() const {
        return librdf_parser_get_namespaces_seen_count(parser_);
    }

    std::string LibrdfParser::getNamespacesSeenUri(int index) const {
        librdf_uri *uri = librdf_parser_get_namespaces_seen_uri(parser_, index);
        return (const char *) librdf_uri_as_string(uri);
    }

    std::string LibrdfParser::getNamespacesSeenPrefix(int index) const {
        return std::string(librdf_parser_get_namespaces_seen_prefix(parser_, index));
    }

    void LibrdfParser::parseString(const std::string &rdf_string, const LibrdfModel &model,
                                   const LibrdfUri &base_uri) const {
        librdf_parser_parse_string_into_model(
                parser_, (const unsigned char *) rdf_string.c_str(),
                base_uri.get(), model.get());
    }

    void LibrdfParser::parseString(const std::string &rdf_string, const LibrdfModel &model,
                                   const std::string &base_uri) const {
        LibrdfUri u(base_uri);
        librdf_parser_parse_string_into_model(
                parser_, (const unsigned char *) rdf_string.c_str(),
                u.get(), model.get());
        u.freeUri();
    }

    void LibrdfParser::parseUri(const std::string &uri_string, const LibrdfModel &model) const {
        LibrdfUri uri(uri_string);
        librdf_parser_parse_into_model(
                parser_, uri.get(), uri.get(), model.get());
        uri.freeUri();
    }

    void LibrdfParser::parseFile(const std::string &filename_uri, const LibrdfModel &model) const {
        LibrdfUri filename_uri_ = LibrdfUri::fromFilename(filename_uri);
        LibrdfUri base_uri = LibrdfUri::fromFilename(filename_uri);
        librdf_parser_parse_into_model(
                parser_, filename_uri_.get(), base_uri.get(), model.get()
        );
    }

    void LibrdfParser::parseFile(const std::string &filename_uri, const LibrdfModel &model, const std::string &local_uri) const {
        LibrdfUri filename_uri_ = LibrdfUri::fromFilename(filename_uri);
        LibrdfUri base_uri(local_uri);
        librdf_parser_parse_into_model(
                parser_, filename_uri_.get(), base_uri.get(), model.get()
        );
    }

    void LibrdfParser::validateParserName() const {
        std::vector<std::string> v = {"rdfxml",
                                      "ntriples",
                                      "turtle",
                                      "trig",
                                      "rss-tag-soup",
                                      "grddl",
                                      "guess",
                                      "rdfa",
                                      "nquads",
                                      "guess",
                                      "", // empty string is allowed
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

    LibrdfParser::~LibrdfParser() {
        if (parser_ != nullptr) {
            librdf_free_parser(parser_);
            parser_ = nullptr;
        }
    }

    std::vector<std::string> LibrdfParser::getSeenNamespaces(std::vector<std::string> namespaces) const {
        for (int i = 0; i < numNamespacesSeen(); i++) {
            std::string nsref = getNamespacesSeenUri(i);
            if (std::find(namespaces.begin(), namespaces.end(), nsref) == namespaces.end())
                namespaces.push_back(nsref);
        }
        return namespaces;
    }

    LibrdfParser::LibrdfParser(LibrdfParser &&parser) noexcept {
        format_ = std::move(parser.format_);
        mime_type_ = std::move(parser.mime_type_);
        if (parser.type_uri_ != nullptr) {
            if (type_uri_ != nullptr) {
                librdf_free_uri(type_uri_);
            }
            type_uri_ = parser.type_uri_;
            parser.type_uri_ = nullptr;
        }
        if (parser.parser_ != nullptr) {
            if (parser_ != nullptr) {
                // ensure we don't create leak from
                // forgetting to free the original parser
                librdf_free_parser(parser_);
            }
            parser_ = parser.parser_;
            parser.parser_ = nullptr;
        }

    }

    LibrdfParser &LibrdfParser::operator=(LibrdfParser &&parser) noexcept {
        if (this != &parser) {
            format_ = std::move(parser.format_);
            mime_type_ = std::move(parser.mime_type_);
            if (parser.type_uri_ != nullptr) {
                if (type_uri_ != nullptr) {
                    librdf_free_uri(type_uri_);
                }
                type_uri_ = parser.type_uri_;
                parser.type_uri_ = nullptr;
            }
            if (parser.parser_ != nullptr) {
                // ensure we don't create leak from
                // forgetting to free the original parser
                if (parser_ != nullptr) {
                    librdf_free_parser(parser_);
                }
                parser_ = parser.parser_;
                parser.parser_ = nullptr;
            }
        }
        return *this;
    }
}