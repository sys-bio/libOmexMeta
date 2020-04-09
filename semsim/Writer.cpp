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

semsim::Writer::Writer(librdf_world *world, librdf_model *model, std::string format, const std::string &base_uri) {
    this->world = world;

    if (!world){
        throw std::invalid_argument("World argument invalid");
    }


    this->base_uri_ = librdf_new_uri(world, (const unsigned char *) base_uri.c_str());
    if (!base_uri_){
        throw std::invalid_argument("base_uri argument invalid");
    }

    this->model = model;
    if (!model){
        throw std::invalid_argument("model argument invalid");
    }

    this->format = std::move(format);
    if (std::find(valid_writer_names.begin(), valid_writer_names.end(), format) != valid_writer_names.end()) {
        std::ostringstream os;
        os << "Invalid format: \"" << format << "\". These are valid formats: ";
        for (auto &i : valid_writer_names) {
            os << i << ", ";
        }
        throw std::invalid_argument(os.str());
    }
    serializer = librdf_new_serializer(world, this->format.c_str(), nullptr, nullptr);
    if (!serializer) {
        throw std::invalid_argument("Failed to create serializer\n");
    }
    this->raptor_world_ptr_ = librdf_world_get_raptor(world);

    if (!raptor_world_ptr_){
        throw std::invalid_argument("World argument invalid");
    }
}

void semsim::Writer::registerNamespace(const std::string &ns, const std::string &prefix) {
    librdf_uri *ns_uri = librdf_new_uri(world, (const unsigned char *) ns.c_str());
    librdf_serializer_set_namespace(serializer, ns_uri, (const char *) prefix.c_str());
    librdf_free_uri(ns_uri);
}

std::string semsim::Writer::toString() {
    void *string = nullptr;
    raptor_world *r = librdf_world_get_raptor(world);
    raptor_iostream *iostr = raptor_new_iostream_to_string(raptor_world_ptr_, (void **) &string, nullptr, malloc);
    if (!iostr)
        throw std::invalid_argument("You did a baad");

    int failure = librdf_serializer_serialize_model_to_iostream(serializer, base_uri_, model, iostr);
    if (failure) { // i.e. if non-0
        throw std::logic_error("Could not write model.");
    }
    std::string output_string((const char *) string);
    return output_string;
}

std::string semsim::Writer::print() {
    raptor_iostream *iostream = raptor_new_iostream_to_file_handle(raptor_world_ptr_, stdout);
    registerNamespace("http://biomodels.net/biology-qualifiers/", "bqbiol");
    librdf_serializer_serialize_model_to_iostream(serializer, base_uri_, model, iostream);
}

void semsim::Writer::toFile(std::string format) {

}

void semsim::Writer::setFormat(const std::string &format) {
    Writer::format = format;
}


