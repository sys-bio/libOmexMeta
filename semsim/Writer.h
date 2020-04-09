//
// Created by Ciaran on 4/9/2020.
//

#ifndef LIBSEMGEN_WRITER_H
#define LIBSEMGEN_WRITER_H

#include <librdf.h>
#include <string>

namespace semsim {
    class Writer {
        librdf_world *world;
        raptor_world *raptorWorld;
        std::string format;
        librdf_uri* baseUri;
        librdf_model* model;
        librdf_serializer *serializer;

    public:

        Writer(librdf_world *world, librdf_model* model, std::string format, const std::string& baseUri="./semsim_model.xml");

        void setFormat(const std::string &format);

        void setWorld(librdf_world *world);

        std::string toString();

        void toFile(std::string format);

        void registerNamespace(const std::string& ns, const std::string& prefix);
    };
}

#endif //LIBSEMGEN_WRITER_H
