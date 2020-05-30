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

#include "World.h"
#include "LibrdfModel.h"
#include "LibrdfUri.h"
#include "RedlandAPIWrapper.h"

using namespace redland;


namespace semsim {
    class Reader {
        std::string format_;
        const char *mime_type_;
        const char *type_uri_;
        const LibrdfModel &model_;
        LibrdfParser parser_;
        LibrdfUri base_uri_;

        // create a parser object
        LibrdfParser makeParser(const std::string &format, const char *mime_type, const char *type_uri);

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

        Reader(const LibrdfModel &model, std::string format = "guess",
               const std::string &base_uri = "file://./annotations.rdf",
               const char *mime_type = nullptr, const char *type_uri = nullptr);

        void setFormat(const std::string &f);

        /*
         * @brief read rdf from a string
         * @parameter the rdf string to read
         */
        void fromString(const std::string &rdf_string);

        /*
         * @brief read rdf from a file.
         * @parameter filepath location of file to read. Used for base uri of rdf graph.
         *
         */
        void fromFile(const std::string &filepath);

        void fromUri(const std::string &uri);

        [[nodiscard]] const std::string &getFormat() const;

        [[nodiscard]] const LibrdfModel &getModel() const;

        [[nodiscard]] const LibrdfParser &getParser() const;

        [[nodiscard]] const LibrdfUri &getBaseUri() const;

        [[nodiscard]] const std::vector<std::string> &getValidParserNames() const;

        void setOption(const std::string &option, const std::string &value);

        std::vector<std::string> getSeenNamespaces();

    };
}

#endif //LIBSEMSIM_READER_H
