//
// Created by Ciaran on 4/9/2020.
//

#include <stdexcept>
#include <utility>
#include "Writer.h"
#include "semsim/SemSim.h"


void semsim::Writer::setWorld(librdf_world *w) {
    this->world = w;
}

semsim::Writer::Writer(librdf_world *world, librdf_model *model, std::string format, const std::string &baseUri) {
    this->world = world;
    this->raptor_world_ = librdf_world_get_raptor(world);
    this->format = std::move(format);
    this->base_uri_ = librdf_new_uri(world, (const unsigned char *) baseUri.c_str());
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
    void *string = nullptr;
    raptor_iostream *iostr = raptor_new_iostream_to_string(raptor_world_, (void **) &string, nullptr, malloc);
    if (!iostr)
        throw std::invalid_argument("You did a baad");

    int failure = librdf_serializer_serialize_model_to_iostream(serializer, base_uri_, model, iostr);
    if (failure){ // i.e. if non-0
        throw std::logic_error("Could not write model.");
    }
    std::string output_string((const char*)string);
    return output_string;
}

std::string semsim::Writer::print() {
    raptor_iostream *iostream = raptor_new_iostream_to_file_handle(raptor_world_, stdout);
    registerNamespace("http://biomodels.net/biology-qualifiers/", "bqbiol");
    librdf_serializer_serialize_model_to_iostream(serializer, base_uri_, model, iostream);
}

void semsim::Writer::toFile(std::string format) {

}

void semsim::Writer::setFormat(const std::string &format) {
    Writer::format = format;
}


