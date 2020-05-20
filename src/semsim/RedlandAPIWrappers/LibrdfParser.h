//
// Created by Ciaran on 5/20/2020.
//

#ifndef LIBSEMSIM_LIBRDFPARSER_H
#define LIBSEMSIM_LIBRDFPARSER_H


#include <librdf.h>
#include <memory>
#include "semsim/Error.h"

namespace semsim {
    class LibrdfParser {
        std::shared_ptr<librdf_parser *> parser_;
    public:
        const std::shared_ptr<librdf_parser *> &getParser() const;

        LibrdfParser() = default;

        explicit LibrdfParser(librdf_parser *query_results);

        ~LibrdfParser();

        LibrdfParser(const LibrdfParser &LibrdfParser);

        LibrdfParser(LibrdfParser &&LibrdfParser) noexcept;

        LibrdfParser &operator=(const LibrdfParser &LibrdfParser);

        LibrdfParser &operator=(LibrdfParser &&LibrdfParser) noexcept;

        bool operator!() const;


    };
}


#endif //LIBSEMSIM_LIBRDFPARSER_H
