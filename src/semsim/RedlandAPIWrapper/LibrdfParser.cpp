#include "LibrdfParser.h"
#include "LibrdfModel.h"

namespace semsim {

    LibrdfParser::LibrdfParser(librdf_parser *parser) :
            parser_(std::unique_ptr<librdf_parser, deleter>(parser)) {}

    LibrdfParser::LibrdfParser(const char *name, const char *mime_type, const char *type_uri) {
        librdf_uri *type_uri_ = nullptr;
        if (type_uri)
            type_uri_ = librdf_new_uri(World::getWorld(), (const unsigned char *) type_uri);
        parser_ = std::unique_ptr<librdf_parser, deleter>(
                librdf_new_parser(World::getWorld(),
                                  name, mime_type, type_uri_
                )
        );

    }

    librdf_parser *LibrdfParser::get() const {
        return parser_.get();
    }

    void LibrdfParser::setFeature(std::string feature_uri, LibrdfNode node) const {
        librdf_parser_set_feature(parser_.get(), LibrdfUri(feature_uri).get(), node.get());
    }

    int LibrdfParser::numNamespacesSeen() const {
        return librdf_parser_get_namespaces_seen_count(parser_.get());
    }

    LibrdfUri LibrdfParser::getNamespacesSeenUri(int index) const {
        return LibrdfUri(librdf_parser_get_namespaces_seen_uri(parser_.get(), index));
    }

    std::string LibrdfParser::getNamespacesSeenPrefix(int index) const {
        return std::string(librdf_parser_get_namespaces_seen_prefix(parser_.get(), index));
    }

    void LibrdfParser::parseString(const std::string &rdf_string, const LibrdfModel &model, LibrdfUri base_uri) const {
        librdf_parser_parse_string_into_model(
                parser_.get(), (const unsigned char *) rdf_string.c_str(),
                base_uri.get(), model.get());
    }

    void
    LibrdfParser::parseUriIntoModel(const LibrdfUri &uri, const LibrdfUri &base_uri, const LibrdfModel &model) const {
        librdf_parser_parse_into_model(
                parser_.get(), uri.get(), base_uri.get(), model.get());
    }

    void LibrdfParser::parseFilenameUriIntoModel(const LibrdfUri &filename_uri, const LibrdfUri &base_uri,
                                                 const LibrdfModel &model) const {
        librdf_parser_parse_into_model(
                parser_.get(), filename_uri.get(), base_uri.get(), model.get());
    }


    void LibrdfParser::deleter::operator()(librdf_parser *parser) {
        librdf_free_parser(parser);
    }
}

