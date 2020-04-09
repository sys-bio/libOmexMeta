//
// Created by Ciaran on 4/8/2020.
//
#include <string>
#include <iostream>
#include <cstring>
#include <utility>
#include "RDF.h"
#include "semsim/SemSim.h"

/*******************************************************
 * Constructors
 */
semsim::RDF::RDF() {
    world = librdf_new_world();
    librdf_world_open(world);
    raptor_world_ptr = librdf_world_get_raptor(world);
    storage = librdf_new_storage(world, "memory", "semsim_store", nullptr);
    if (!storage) {
        throw std::invalid_argument("Failed to create new storage\n");
    }
    model = librdf_new_model(world, storage, nullptr);
    if (!model) {
        throw std::invalid_argument("Failed to create model\n");
    }
    parser = librdf_new_parser(world, reinterpret_cast<const char *>("rdfxml"), nullptr,
                               nullptr);
    if (!parser) {
        throw std::invalid_argument("Failed to create new parser\n");
    }

    uri = librdf_new_uri(world, (const unsigned char *) "./Test.xml");


}


/*******************************************************
 * Destructor
 */
semsim::RDF::~RDF() {
    librdf_free_model(model);
    librdf_free_parser(parser);
    librdf_free_storage(storage);
    librdf_free_world(world);
    librdf_free_uri(uri);
}

semsim::RDF::RDF(const semsim::RDF &libRdfModel) {
    this->world = libRdfModel.world;
    this->storage = libRdfModel.storage;
    this->parser = libRdfModel.parser;
    this->model = libRdfModel.model;
    this->raptor_world_ptr = libRdfModel.raptor_world_ptr;
    this->name = libRdfModel.name;
    this->uri = libRdfModel.uri;
}

semsim::RDF::RDF(semsim::RDF &&libRdfModel) noexcept {
    this->world = libRdfModel.world;
    this->storage = libRdfModel.storage;
    this->parser = libRdfModel.parser;
    this->model = libRdfModel.model;
    this->raptor_world_ptr = libRdfModel.raptor_world_ptr;
    this->name = std::move(libRdfModel.name);
    this->uri = libRdfModel.uri;
}

semsim::RDF &semsim::RDF::operator=(const semsim::RDF &libRdfModel) {
    if (this != &libRdfModel) {
        this->world = libRdfModel.world;
        this->storage = libRdfModel.storage;
        this->parser = libRdfModel.parser;
        this->model = libRdfModel.model;
        this->raptor_world_ptr = libRdfModel.raptor_world_ptr;
        this->name = libRdfModel.name;
    this->uri = libRdfModel.uri;
    }
    return *this;
}

semsim::RDF &semsim::RDF::operator=(semsim::RDF &&libRdfModel) noexcept {
    if (this != &libRdfModel) {
        this->world = libRdfModel.world;
        this->storage = libRdfModel.storage;
        this->parser = libRdfModel.parser;
        this->model = libRdfModel.model;
        this->raptor_world_ptr = libRdfModel.raptor_world_ptr;
        this->name = std::move(libRdfModel.name);
    this->uri = libRdfModel.uri;
    }
    return *this;
}

bool semsim::RDF::operator==(const semsim::RDF &rhs) const {
    return world == rhs.world &&
           storage == rhs.storage &&
           parser == rhs.parser &&
           model == rhs.model &&
           raptor_world_ptr == rhs.raptor_world_ptr &&
           name == rhs.name;
}

bool semsim::RDF::operator!=(const semsim::RDF &rhs) const {
    return !(rhs == *this);
}

semsim::RDF semsim::RDF::fromUrl(std::string url) {
//        librdf_uri *uri = librdf_new_uri(world,
//                                         (const unsigned char *) "http://www.ebi.ac.uk/biomodels-main/download?mid=BIOMD0000000064");
//
//    raptor_uri *uri = librdf_new_uri_from_filename(world, (const char *) "/mnt/d/libsemsim/tests/Teusink2000.xml");
//    if (!uri) {
//        fprintf(stderr, "Failed to create URI\n");
//    }

    /* PARSE the URI as RDF/XML*/
//    fprintf(stdout, "Parsing URI %s\n", librdf_uri_as_string(uri));
//    librdf_parser_parse_into_model(parser, uri, uri, model);
    return semsim::RDF();
}

semsim::RDF semsim::RDF::fromML(std::string filename) {
    return semsim::RDF();
}

semsim::RDF semsim::RDF::fromRDF(std::string filename) {
    return semsim::RDF();
}


void semsim::RDF::toFile(std::string format) {

}


void semsim::RDF::fromString(std::string str) {
//     todo work out whether this means we need user to specify file on system
    librdf_parser_parse_string_into_model(parser, (const unsigned char *) str.c_str(), uri, model);
}

void semsim::RDF::toString(std::string format, std::string base_uri) {
    Writer writer = makeWriter(format, base_uri);
    writer.toString();
}

librdf_serializer* semsim::RDF::makeSerializer(std::string format){

}

void semsim::RDF::registerNamespace(std::string ns, std::string prefix) {

}

semsim::Writer semsim::RDF::makeWriter(const std::string& format, const std::string &base_uri) {
    Writer writer(world, model, format, base_uri);
}
















