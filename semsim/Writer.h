//
// Created by Ciaran on 4/9/2020.
//

#ifndef LIBSEMGEN_WRITER_H
#define LIBSEMGEN_WRITER_H

#include <librdf.h>
#include <string>
#include <vector>
#include "unordered_map"

namespace semsim {
    class Writer {
        librdf_world *world_;
        raptor_world *raptor_world_ptr_;
        std::string format_;
        librdf_uri *base_uri_;
        librdf_model *model_;
        librdf_serializer *serializer;

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

    public:

        Writer(librdf_world *world_, librdf_model *model_, std::string format = "rdfxml-abbrev",
               const std::string &base_uri = "./semsim_model.xml");

        void setFormat(const std::string &format);

        void setWorld(librdf_world *world_);

        std::string toString();

        void toFile(std::string format);

        void registerNamespace(const std::string &ns, const std::string &prefix);

        void registerNamespace(const std::unordered_map<std::string, std::string> &ns_map);

        std::string print();

        void setOption(const std::string &option, const std::string &value);

    };
}

#endif //LIBSEMGEN_WRITER_H
