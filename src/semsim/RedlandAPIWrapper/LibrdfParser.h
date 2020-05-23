//
// Created by Ciaran on 5/20/2020.
//

#ifndef LIBSEMSIM_LIBRDFPARSER_H
#define LIBSEMSIM_LIBRDFPARSER_H


#include <librdf.h>
#include <memory>
#include "semsim/Error.h"
#include "semsim/RedlandAPIWrapper/World.h"
#include "LibrdfUri.h"

namespace semsim {

    class LibrdfParser {

        struct deleter {
            void operator()(librdf_parser *parser);
        };

        std::unique_ptr<librdf_parser, deleter> parser_;
    public:
        LibrdfParser() = default;

        explicit LibrdfParser(librdf_parser *parser);

        LibrdfParser(const char *name, const char *mime_type = nullptr,
                     const char *type_uri = nullptr);

        librdf_parser *get() const;

    };
}


#endif //LIBSEMSIM_LIBRDFPARSER_H
