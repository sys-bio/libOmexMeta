//
// Created by Ciaran on 4/8/2020.
//
#include <string>
#include <iostream>
#include <cstring>
#include "LibRDFModel.h"
#include "semsim/SemSim.h"


semsim::LibRDFModel::LibRDFModel(const semsim::LibRDFModel &libRdfModel) {
    this->world = libRdfModel.world;
    this->storage = libRdfModel.storage;
    this->parser = libRdfModel.parser;
    this->serializer = libRdfModel.serializer;
    this->model = libRdfModel.model;
    this->raptor_world_ptr = libRdfModel.raptor_world_ptr;
    this->name = libRdfModel.name;
}

semsim::LibRDFModel::LibRDFModel(semsim::LibRDFModel &&libRdfModel) noexcept {
    this->world = libRdfModel.world;
    this->storage = libRdfModel.storage;
    this->parser = libRdfModel.parser;
    this->serializer = libRdfModel.serializer;
    this->model = libRdfModel.model;
    this->raptor_world_ptr = libRdfModel.raptor_world_ptr;
    this->name = std::move(libRdfModel.name);
}

semsim::LibRDFModel::LibRDFModel() {
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

    serializer = librdf_new_serializer(world, "rdfxml", nullptr, nullptr);

    if (!serializer) {
        throw std::invalid_argument("Failed to create serializer\n");
    }

    uri = librdf_new_uri(world, (const unsigned char *) "./Test.xml");


}

semsim::LibRDFModel::~LibRDFModel() {
    librdf_free_model(model);
    librdf_free_parser(parser);
    librdf_free_serializer(serializer);
    librdf_free_storage(storage);
    librdf_free_world(world);
    librdf_free_uri(uri);
}

semsim::LibRDFModel &semsim::LibRDFModel::operator=(const semsim::LibRDFModel &libRdfModel) {
    if (this != &libRdfModel) {
        this->world = libRdfModel.world;
        this->storage = libRdfModel.storage;
        this->parser = libRdfModel.parser;
        this->serializer = libRdfModel.serializer;
        this->model = libRdfModel.model;
        this->raptor_world_ptr = libRdfModel.raptor_world_ptr;
        this->name = libRdfModel.name;
    }
    return *this;
}

semsim::LibRDFModel &semsim::LibRDFModel::operator=(semsim::LibRDFModel &&libRdfModel) noexcept {
    if (this != &libRdfModel) {
        this->world = libRdfModel.world;
        this->storage = libRdfModel.storage;
        this->parser = libRdfModel.parser;
        this->serializer = libRdfModel.serializer;
        this->model = libRdfModel.model;
        this->raptor_world_ptr = libRdfModel.raptor_world_ptr;
        this->name = std::move(libRdfModel.name);
    }
    return *this;
}

bool semsim::LibRDFModel::operator==(const semsim::LibRDFModel &rhs) const {
    return world == rhs.world &&
           storage == rhs.storage &&
           parser == rhs.parser &&
           serializer == rhs.serializer &&
           model == rhs.model &&
           raptor_world_ptr == rhs.raptor_world_ptr &&
           name == rhs.name;
}

bool semsim::LibRDFModel::operator!=(const semsim::LibRDFModel &rhs) const {
    return !(rhs == *this);
}

semsim::LibRDFModel semsim::LibRDFModel::fromUrl(std::string url) {
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
    return semsim::LibRDFModel();
}

semsim::LibRDFModel semsim::LibRDFModel::fromML(std::string filename) {
    return semsim::LibRDFModel();
}

semsim::LibRDFModel semsim::LibRDFModel::fromRDF(std::string filename) {
    return semsim::LibRDFModel();
}


void semsim::LibRDFModel::toFile(std::string format) {

}


void semsim::LibRDFModel::fromString(std::string str) {
    // todo work out whether this means we need user to specify file on system
    librdf_parser_parse_string_into_model(parser, (const unsigned char *) str.c_str(), uri, model);
}

void semsim::LibRDFModel::toString(std::string format) {
    HERE();
    raptor_iostream *iostream = raptor_new_iostream_to_file_handle(raptor_world_ptr, stdout);
    HERE();
    const char* bqb_str = "http://biomodels.net/biology-qualifiers/";
    HERE();
    librdf_uri *bqb = librdf_new_uri(world, (const unsigned char*)bqb_str);
    HERE();
    librdf_serializer_set_namespace(serializer, bqb, (const char*)"bqbiol");
    HERE();
    librdf_serializer_serialize_model_to_iostream(serializer, uri, model, iostream);
    HERE();
//    raptor_free_iostream(iostream);
    HERE();
}
















