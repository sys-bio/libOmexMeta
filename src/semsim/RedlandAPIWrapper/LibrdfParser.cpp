#include "LibrdfParser.h"

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


    void LibrdfParser::deleter::operator()(librdf_parser *parser) {
        librdf_free_parser(parser);
    }
}

