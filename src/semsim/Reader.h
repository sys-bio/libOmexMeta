//
// Created by Ciaran on 4/9/2020.
//

#ifndef LIBSEMGEN_READER_H
#define LIBSEMGEN_READER_H

#include <librdf.h>
#include <string>
#include <vector>
#include "unordered_map"

#include <utility>
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <unordered_map>


namespace semsim {
    class Reader {
        LibrdfWorld world_;
        raptor_world *raptor_world_ptr_;
        std::string format_;
        LibrdfModel model_;
        librdf_parser *parser_;
        librdf_uri *base_uri_;

        // create a parser object
        librdf_parser *makeParser(const std::string& format = "guess");

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
        LibrdfModel getModel() const;

        void setBaseUri(const std::string &baseUri);

        Reader(LibrdfWorld world, LibrdfModel model,
               std::string format = "guess", std::string base_uri = "file://./annotations.rdf");

        void setFormat(const std::string &f);

        void fromString(const std::string &rdf_string);

        void fromFile(const std::string &filename);

        LibrdfWorld getWorld() const;

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
