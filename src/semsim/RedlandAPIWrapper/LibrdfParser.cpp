#include "LibrdfParser.h"

namespace semsim {

    LibrdfParser::LibrdfParser(librdf_parser *parser) :
            parser_(parser_ptr(parser, librdf_free_parser)) {

    }

    const parser_ptr &LibrdfParser::getParser() const {
        return parser_;
    }

    bool LibrdfParser::operator!() const {
        return !getParser();
    }

    bool LibrdfParser::operator==(const LibrdfParser &rhs) const {
        return parser_.get() == rhs.parser_.get();
    }

    bool LibrdfParser::operator!=(const LibrdfParser &rhs) const {
        return !(rhs == *this);
    }

    librdf_parser *LibrdfParser::get() {
        return parser_.get();
    }

}
