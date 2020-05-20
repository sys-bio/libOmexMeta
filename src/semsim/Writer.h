//
// Created by Ciaran on 4/9/2020.
//

#ifndef LIBSEMSIM_WRITER_H
#define LIBSEMSIM_WRITER_H

#include "semsim/RedlandAPIWrappers/LibrdfWorld.h"
#include "Error.h"

#include <librdf.h>
#include <string>
#include <vector>
#include "unordered_map"
#include <stdexcept>
#include <utility>
#include <regex>


namespace semsim {

    class Writer {
        RaptorWorld raptor_world_ptr_;
        std::string format_;
        std::string base_uri_;
        LibrdfSerializer serializer;

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

    protected:
        void init(LibrdfWorld world, LibrdfModel model,
                  const std::string &base_uri,
                  std::string format);

        LibrdfWorld world_;
        LibrdfModel model_;
    public:

        Writer();

        Writer(LibrdfWorld world, LibrdfModel model,
               const std::string &base_uri = "file://annotation.rdf",
               std::string format = "rdfxml-abbrev");

        ~Writer();

        void setFormat(const std::string &format);

        void setWorld(LibrdfWorld world_);

        std::string toString();

        void toFile(std::string format);

        void registerNamespace(const std::string &ns, const std::string &prefix);

        void registerNamespace(const std::unordered_map<std::string, std::string> &ns_map);

        void setOption(const std::string &option, const std::string &value);

    };


}

#endif //LIBSEMSIM_WRITER_H
