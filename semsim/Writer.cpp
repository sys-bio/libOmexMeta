//
// Created by Ciaran on 4/9/2020.
//

#include <stdexcept>
#include <utility>
#include "Writer.h"

void semsim::Writer::setWorld(librdf_world *w) {
    this->world = w;
}

semsim::Writer::Writer(librdf_world *world, librdf_model *model, std::string format, const std::string &baseUri) {
    this->world = world;
    this->raptorWorld = librdf_world_get_raptor(world);
    this->format = std::move(format);
    this->baseUri = librdf_new_uri(world, (const unsigned char *) baseUri.c_str());
    this->model = model;

    librdf_serializer_check_name(world, (const char *) this->format.c_str());
    serializer = librdf_new_serializer(world, this->format.c_str(), nullptr, nullptr);
    if (!serializer) {
        throw std::invalid_argument("Failed to create serializer\n");
    }
}

void semsim::Writer::registerNamespace(const std::string &ns, const std::string &prefix) {
    librdf_uri *ns_uri = librdf_new_uri(world, (const unsigned char *) ns.c_str());
    librdf_serializer_set_namespace(serializer, ns_uri, (const char *) prefix.c_str());
    librdf_free_uri(ns_uri);
}

std::string semsim::Writer::toString() {
    raptor_iostream *iostream = raptor_new_iostream_to_file_handle(raptorWorld, stdout);
    registerNamespace("http://biomodels.net/biology-qualifiers/", "bqbiol");
    librdf_serializer_serialize_model_to_iostream(serializer, baseUri, model, iostream);
}

void semsim::Writer::toFile(std::string format) {

}

void semsim::Writer::setFormat(const std::string &format) {
    Writer::format = format;
}
