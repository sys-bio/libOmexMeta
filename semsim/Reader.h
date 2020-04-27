//
// Created by Ciaran on 4/9/2020.
//

#ifndef LIBSEMGEN_READER_H
#define LIBSEMGEN_READER_H

#include <librdf.h>
#include <string>
#include <vector>
#include "unordered_map"

namespace semsim {
    class Reader {
        librdf_world *world_;
        raptor_world *raptor_world_ptr_;
        std::string format_;
        librdf_model *model_;
        librdf_parser *parser_;
        librdf_uri* base_uri_;

        // create a parser object
        librdf_parser *makeParser(std::string format = "guess");

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

        Reader(librdf_world *world, librdf_model *model, std::string format = "guess");

        void setFormat(const std::string &f);

        std::string fromString(const std::string &rdf_string);

        void fromFile(const std::string &filename);

        librdf_world *getWorld() const;

        raptor_world *getRaptorWorld() const;

        const std::string &getFormat() const;

        librdf_parser *getParser() const;

        librdf_uri* getBaseUri() const;

        const std::vector<std::string> &getValidParserNames() const;

        void setOption(const std::string &option, const std::string& value);

        std::vector<std::string> getSeenNamespaces();
    };
}

#endif //LIBSEMGEN_READER_H
