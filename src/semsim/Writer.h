//
// Created by Ciaran on 4/9/2020.
//

#ifndef LIBSEMGEN_WRITER_H
#define LIBSEMGEN_WRITER_H

#include <librdf.h>
#include <string>
#include <vector>
#include "unordered_map"
#include "Triple.h"
#include "Triples.h"

namespace semsim {
    class Writer {
        raptor_world *raptor_world_ptr_;
        std::string format_;
        std::string base_uri_;
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

        void validateBaseUri();

    protected:
        void init(librdf_world *world, librdf_model *model,
                  const std::string &base_uri,
                  std::string format);

        librdf_world *world_;
        librdf_model *model_;
    public:

        Writer();

        Writer(librdf_world *world, librdf_model *model,
               const std::string &base_uri = "file://annotation.rdf",
               std::string format = "rdfxml-abbrev");

        ~Writer();

        void setFormat(const std::string &format);

        void setWorld(librdf_world *world_);

        std::string toString();

        void toFile(std::string format);

        void registerNamespace(const std::string &ns, const std::string &prefix);

        void registerNamespace(const std::unordered_map<std::string, std::string> &ns_map);

        void setOption(const std::string &option, const std::string &value);

    };

    class TripleWriter : public Writer {
        librdf_storage *storage_;
    public:
        using Writer::init;

        TripleWriter(Triple triple,
                     const std::string &base_uri = "file://annotation.rdf",
                     std::string format = "rdfxml-abbrev");

        TripleWriter(Triples triples,
                     const std::string &base_uri = "file://annotation.rdf",
                     std::string format = "rdfxml-abbrev");

        ~TripleWriter();

    };

}

#endif //LIBSEMGEN_WRITER_H
