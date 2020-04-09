//
// Created by Ciaran on 4/9/2020.
//

#ifndef LIBSEMGEN_WRITER_H
#define LIBSEMGEN_WRITER_H

#include <librdf.h>
#include <string>
#include <vector>

namespace semsim {
    class Writer {
        librdf_world *world;
        raptor_world *raptor_world_;
        std::string format;
        librdf_uri *base_uri_;
        librdf_model *model;
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
        };

    public:

        Writer(librdf_world *world, librdf_model *model, std::string format,
               const std::string &baseUri = "./semsim_model.xml");

        void setFormat(const std::string &format);

        void setWorld(librdf_world *world);

        std::string toString();

        void toFile(std::string format);

        void registerNamespace(const std::string &ns, const std::string &prefix);

        std::string print();

    };
}

#endif //LIBSEMGEN_WRITER_H
