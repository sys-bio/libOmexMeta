//
// Created by Ciaran on 4/9/2020.
//

#ifndef LIBSEMGEN_READER_H
#define LIBSEMGEN_READER_H

#include <librdf.h>
#include <string>
#include <vector>

namespace semsim {
    class Reader {
        librdf_world *world_;
        raptor_world *raptorWorld_;
        std::string format_;
        librdf_model *model_;
        librdf_parser *parser_;
        librdf_uri *baseUri_;

        librdf_parser *makeParser(const std::string &format);

        std::vector<std::string> valid_parser_names = {
                "rdfxml",
                "ntriples",
                "turtle",
                "trig",
                "rss-tag-soup",
                "grddl",
                "guess",
                "rdfa",
                "nquads",
        };

    public:
        librdf_model *getModel() const;

        void setBaseUri(const std::string &baseUri);

        Reader(librdf_world *world, librdf_model *model, std::string format);

        void setFormat(const std::string &f);

        std::string fromString(const std::string &rdf_string);

        void fromFile(const std::string &filename);
    };
}

#endif //LIBSEMGEN_READER_H
