#include "LibrdfParser.h"

namespace semsim {

    LibrdfParser::LibrdfParser(librdf_parser *parser) :
            parser_(std::make_shared<librdf_parser *>(parser)) {

    }

    LibrdfParser::~LibrdfParser() {
        if (parser_.use_count() == 1) {
            librdf_free_parser(*parser_);
        }
    }

    LibrdfParser::LibrdfParser(const LibrdfParser &LibrdfParser) {
        if (parser_)
            librdf_free_parser(*parser_); // Remove prexisting parser before copy
        parser_ = LibrdfParser.parser_;
    }

    LibrdfParser::LibrdfParser(LibrdfParser &&LibrdfParser) noexcept {
        if (parser_) {
            librdf_free_parser(*parser_);
        }
        parser_ = std::move(LibrdfParser.parser_);
    }

    LibrdfParser &LibrdfParser::operator=(const LibrdfParser &LibrdfParser) {
        if (this != &LibrdfParser) {
            if (parser_) {
                librdf_free_parser(*parser_);
            }
            parser_ = LibrdfParser.parser_;
        }
        return *this;
    }

    LibrdfParser &LibrdfParser::operator=(LibrdfParser &&LibrdfParser) noexcept {
        if (this != &LibrdfParser) {
            if (parser_) {
                librdf_free_parser(*parser_);
            }
            parser_ = std::move(LibrdfParser.parser_);
        }
        return *this;
    }

    const std::shared_ptr<librdf_parser *> &LibrdfParser::getParser() const {
        return parser_;
    }

    bool LibrdfParser::operator!() const {
        return !getParser();
    }

}
