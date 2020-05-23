//
// Created by Ciaran on 4/9/2020.
//

#ifndef LIBSEMSIM_READER_H
#define LIBSEMSIM_READER_H

#include <librdf.h>
#include <string>
#include <vector>
#include "unordered_map"

#include <utility>
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <unordered_map>

#include "semsim/RedlandAPIWrapper/World.h"
#include "semsim/RedlandAPIWrapper/LibrdfModel.h"
#include "semsim/RedlandAPIWrapper/RaptorWorld.h"
#include "semsim/RedlandAPIWrapper/LibrdfUri.h"


namespace semsim {
    class Reader {
        LibrdfWorld world_;
        RaptorWorld raptor_world_ptr_;
        std::string format_;
        LibrdfModel model_;
        librdf_parser *parser_;
        LibrdfUri base_uri_;

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

        void setBaseUri(const std::string &baseUri);

        Reader(LibrdfWorld world, LibrdfModel model,
               std::string format = "guess", std::string base_uri = "file://./annotations.rdf");

        void setFormat(const std::string &f);

        void fromString(const std::string &rdf_string);

        void fromFile(const std::string &filename);

        const LibrdfWorld &getWorld() const;

        const RaptorWorld &getRaptorWorldPtr() const;

        const std::string &getFormat() const;

        const LibrdfModel &getModel() const;

        librdf_parser *getParser() const;

        const LibrdfUri &getBaseUri() const;

        const std::vector<std::string> &getValidParserNames() const;

        void setOption(const std::string &option, const std::string &value);

        std::vector<std::string> getSeenNamespaces();
    };
}

#endif //LIBSEMSIM_READER_H
