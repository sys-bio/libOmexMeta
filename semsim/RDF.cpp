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
    world_ = librdf_new_world();
    librdf_world_open(world_);
    raptor_world_ptr_ = librdf_world_get_raptor(world_);
    storage_ = librdf_new_storage(world_, "memory", "semsim_store", nullptr);
    if (!storage_) {
        throw std::invalid_argument("Failed to create new storage\n");
    }
    model_ = librdf_new_model(world_, storage_, nullptr);
    if (!model_) {
        throw std::invalid_argument("Failed to create model\n");
    }
    parser_ = librdf_new_parser(world_, reinterpret_cast<const char *>("rdfxml"), nullptr,
                                nullptr);
    if (!parser_) {
        throw std::invalid_argument("Failed to create new parser\n");
    }

    uri_ = librdf_new_uri(world_, (const unsigned char *) "./Test.xml");

    // add some predefined namespaces for the serializer.
    namespaces_["dcterms"] = "http://purl.org/dc/terms/";
    namespaces_["bqbiol"] = "http://biomodels.net/biology-qualifers/";
    namespaces_["bqmodel"] = "http://biomodels.net/model-qualifers/";
    namespaces_["semsim"] = "http://www.bhi.washington.edu/semsim#";

}

semsim::RDF::~RDF() {
    librdf_free_model(model_);
    librdf_free_parser(parser_);
    librdf_free_storage(storage_);
    librdf_free_world(world_);
    librdf_free_uri(uri_);
}

semsim::RDF::RDF(const semsim::RDF &libRdfModel) {
    this->world_ = libRdfModel.world_;
    this->storage_ = libRdfModel.storage_;
    this->parser_ = libRdfModel.parser_;
    this->model_ = libRdfModel.model_;
    this->raptor_world_ptr_ = libRdfModel.raptor_world_ptr_;
    this->name_ = libRdfModel.name_;
    this->uri_ = libRdfModel.uri_;
}

semsim::RDF::RDF(semsim::RDF &&libRdfModel) noexcept {
    this->world_ = libRdfModel.world_;
    this->storage_ = libRdfModel.storage_;
    this->parser_ = libRdfModel.parser_;
    this->model_ = libRdfModel.model_;
    this->raptor_world_ptr_ = libRdfModel.raptor_world_ptr_;
    this->name_ = std::move(libRdfModel.name_);
    this->uri_ = libRdfModel.uri_;
}

semsim::RDF &semsim::RDF::operator=(const semsim::RDF &libRdfModel) {
    if (this != &libRdfModel) {
        this->world_ = libRdfModel.world_;
        this->storage_ = libRdfModel.storage_;
        this->parser_ = libRdfModel.parser_;
        this->model_ = libRdfModel.model_;
        this->raptor_world_ptr_ = libRdfModel.raptor_world_ptr_;
        this->name_ = libRdfModel.name_;
        this->uri_ = libRdfModel.uri_;
    }
    return *this;
}

semsim::RDF &semsim::RDF::operator=(semsim::RDF &&libRdfModel) noexcept {
    if (this != &libRdfModel) {
        this->world_ = libRdfModel.world_;
        this->storage_ = libRdfModel.storage_;
        this->parser_ = libRdfModel.parser_;
        this->model_ = libRdfModel.model_;
        this->raptor_world_ptr_ = libRdfModel.raptor_world_ptr_;
        this->name_ = std::move(libRdfModel.name_);
        this->uri_ = libRdfModel.uri_;
    }
    return *this;
}

bool semsim::RDF::operator==(const semsim::RDF &rhs) const {
    return world_ == rhs.world_ &&
           storage_ == rhs.storage_ &&
           parser_ == rhs.parser_ &&
           model_ == rhs.model_ &&
           raptor_world_ptr_ == rhs.raptor_world_ptr_ &&
           name_ == rhs.name_;
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
    librdf_parser_parse_string_into_model(parser_, (const unsigned char *) str.c_str(), uri_, model_);
}

std::string semsim::RDF::toString(std::string format, std::string base_uri) {
    Writer writer = makeWriter(format, base_uri);
    return writer.toString();
}

semsim::Writer semsim::RDF::makeWriter(const std::string &format, const std::string &base_uri) {
    Writer writer(world_, model_, format, base_uri);
    for (auto &it : namespaces_){
        writer.registerNamespace(it.second, it.first);
    }
    return writer;
}

void semsim::RDF::addStatement(std::string subject, std::string predicate, std::string resource) {
    librdf_statement *statement = librdf_new_statement_from_nodes(
            world_,
            librdf_new_node_from_uri_string(world_, (const unsigned char *) "http://www.dajobe.org/"),
            librdf_new_node_from_uri_string(world_, (const unsigned char *) "http://purl.org/dc/elements/1.1/title"),
            librdf_new_node_from_literal(world_, (const unsigned char *) "My Home Page", nullptr, 0)
    );
}

void semsim::RDF::setNamespaces(const std::unordered_map<std::string, std::string> &namespaces) {
    namespaces_ = namespaces;
}

const std::unordered_map<std::string, std::string> &semsim::RDF::getNamespaces() const {
    return namespaces_;
}

semsim::RDF semsim::RDF::fromOmex(std::string filename) {
    return semsim::RDF();
}




















