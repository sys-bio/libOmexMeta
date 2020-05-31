//
// Created by Ciaran on 4/9/2020.
//

#ifndef LIBSEMSIM_WRITER_H
#define LIBSEMSIM_WRITER_H

#include <librdf.h>
#include "RedlandAPIWrapper.h"

#include "Error.h"
//#include "semsim/SemsimUtils.h"

#include <string>
#include <vector>
#include "unordered_map"
#include <stdexcept>
#include <utility>
#include <regex>

using namespace redland;

/*
 * Perhaps Reader and Writer
 * should inherit from LibrdfSerializer and
 * LibrdfParser?
 */

namespace semsim {

    class Writer : LibrdfSerializer{
        std::string format_;
        std::string base_uri_;
        const char *mime_type_;
        const char *type_uri_;
        const LibrdfModel &model_;

        std::vector<std::string> valid_writer_names = {
                "ntriples",
                "turtle",
                "rdfxml-xmp",
                "rdfxml-abbrev",
                "rdfxml",
                "rss-1.0",
                "atom",
                "dot",
                "json-triples",
                "json",
                "nquads",
                "html",
        };

        void validateBaseUri();

    public:

        explicit Writer(const LibrdfModel &model,
                        std::string base_uri = "file://./annotation.rdf",
                        std::string format = "rdfxml-abbrev",
                        const char *mime_type = nullptr, const char *type_uri = nullptr);

        ~Writer();

        void setFormat(const std::string &format);

        std::string toString();

        void toFile(std::string format);

        void registerNamespace(const std::string &ns, const std::string &prefix);

        void registerNamespace(const std::unordered_map<std::string, std::string> &ns_map);

        void setOption(const std::string &option, const std::string &value);

    };


}

#endif //LIBSEMSIM_WRITER_H
