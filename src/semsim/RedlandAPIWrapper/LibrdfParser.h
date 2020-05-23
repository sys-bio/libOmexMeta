//
// Created by Ciaran on 5/20/2020.
//

#ifndef LIBSEMSIM_LIBRDFPARSER_H
#define LIBSEMSIM_LIBRDFPARSER_H


#include <librdf.h>
#include <memory>
#include "semsim/Error.h"

namespace semsim {
    typedef std::shared_ptr<librdf_parser> parser_ptr;

    class LibrdfParser {
        parser_ptr parser_;
    public:
        const parser_ptr &getParser() const;

        LibrdfParser() = default;

        explicit LibrdfParser(librdf_parser *query_results);

        bool operator!() const;

        bool operator==(const LibrdfParser &rhs) const;

        bool operator!=(const LibrdfParser &rhs) const;

        librdf_parser *get();

    };
}


#endif //LIBSEMSIM_LIBRDFPARSER_H
