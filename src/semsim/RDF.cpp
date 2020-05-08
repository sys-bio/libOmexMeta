//
// Created by Ciaran on 4/8/2020.
//
#include <string>
#include <iostream>
#include <cstring>
#include <utility>
#include "RDF.h"
#include "SemSim.h"
#include "Reader.h"
#include "Query.h"

/*******************************************************
 * Constructors
 */

/*
 * Initialiser for librdf/raptor objects. These commands are needed in multiple
 * places so they are pulled out of the RDF constructor into their own function.
 * This method is static so it can be used without instantiating RDF.
 */
semsim::LibRDFObjectsTuple semsim::RDF::init() {
    // init librdf world object
    librdf_world *world_ = librdf_new_world();
    librdf_world_open(world_);

    // init raptor world obj
    raptor_world *raptor_world_ptr_ = librdf_world_get_raptor(world_);
    if (!raptor_world_ptr_) {
        throw std::invalid_argument("failed to create a raptor_world* object from librdf_world");
    }

    // init raptor world obj
    //todo work out and make use of the arguments to librdf_new_storage
    librdf_storage *storage_ = librdf_new_storage(world_, "memory", "semsim_store", nullptr);
    if (!storage_) {
        throw std::invalid_argument("Failed to create new storage\n");
    }
    librdf_model *model_ = librdf_new_model(world_, storage_, nullptr);
    if (!model_) {
        throw std::invalid_argument("Failed to create model\n");
    }
    LibRDFObjectsTuple objectsTuple(world_, raptor_world_ptr_, storage_, model_);

    return objectsTuple;
}


semsim::RDF::RDF() {
    LibRDFObjectsTuple objectsTuple = RDF::init();

    // unpack redland library objects
    world_ = std::get<0>(objectsTuple);
    raptor_world_ = std::get<1>(objectsTuple);
    storage_ = std::get<2>(objectsTuple);
    model_ = std::get<3>(objectsTuple);
    base_uri_ = librdf_new_uri(getWorld(), (const unsigned char *) "file://./semsim_model.rdf");

}

semsim::RDF::RDF(librdf_world *world, raptor_world *raptor_world_, librdf_storage *storage, librdf_model *model) :
        world_(world),
        raptor_world_(raptor_world_),
        storage_(storage),
        model_(model) {
    base_uri_ = librdf_new_uri(getWorld(), (const unsigned char *) "file://./semsim_model.rdf");

    // add some predefined namespaces for the serializer.


}

semsim::RDF::~RDF() {
    // these free functions are not needed since
    // the memory way not allocated with new!
//    librdf_free_model(model_);
//    librdf_free_storage(storage_);
//    librdf_free_world(world_);
}

semsim::RDF::RDF(const semsim::RDF &libRdfModel) {
    this->world_ = libRdfModel.world_;
    this->storage_ = libRdfModel.storage_;
    this->model_ = libRdfModel.model_;
    this->raptor_world_ = libRdfModel.raptor_world_;
    this->base_uri_ = libRdfModel.base_uri_;
}

semsim::RDF::RDF(semsim::RDF &&libRdfModel) noexcept {
    this->world_ = libRdfModel.world_;
    this->storage_ = libRdfModel.storage_;
    this->model_ = libRdfModel.model_;
    this->raptor_world_ = libRdfModel.raptor_world_;
    this->base_uri_ = libRdfModel.base_uri_;
}

semsim::RDF &semsim::RDF::operator=(const semsim::RDF &libRdfModel) {
    if (this != &libRdfModel) {
        this->world_ = libRdfModel.world_;
        this->storage_ = libRdfModel.storage_;
        this->model_ = libRdfModel.model_;
        this->raptor_world_ = libRdfModel.raptor_world_;
        this->base_uri_ = libRdfModel.base_uri_;
    }
    return *this;
}

semsim::RDF &semsim::RDF::operator=(semsim::RDF &&libRdfModel) noexcept {
    if (this != &libRdfModel) {
        this->world_ = libRdfModel.world_;
        this->storage_ = libRdfModel.storage_;
        this->model_ = libRdfModel.model_;
        this->raptor_world_ = libRdfModel.raptor_world_;
        this->base_uri_ = libRdfModel.base_uri_;
    }
    return *this;
}

bool semsim::RDF::operator==(const semsim::RDF &rhs) const {
    return world_ == rhs.world_ &&
           storage_ == rhs.storage_ &&
           model_ == rhs.model_ &&
           raptor_world_ == rhs.raptor_world_ &&
           base_uri_ == rhs.base_uri_;
}

bool semsim::RDF::operator!=(const semsim::RDF &rhs) const {
    return !(rhs == *this);
}


/***************************************************************
 *  getters and setters
 */
librdf_world *semsim::RDF::getWorld() const {
    return world_;
}

librdf_storage *semsim::RDF::getStorage() const {
    return storage_;
}


const std::unordered_map<std::string, std::string> &semsim::RDF::getNamespaces() const {
    return namespaces_;
}

void semsim::RDF::setNamespaces(const std::unordered_map<std::string, std::string> &namespaces) {
    namespaces_ = namespaces;
}


librdf_model *semsim::RDF::getModel() const {
    return model_;
}

raptor_world *semsim::RDF::getRaptorWorld() const {
    return raptor_world_;
}

semsim::RDF semsim::RDF::fromUrl(std::string url, std::string filename) {
    SemsimUtils::download(url, filename);
    return semsim::RDF::fromFile(filename);
}

void semsim::RDF::setWorld(librdf_world *world) {
    world_ = world;
}

void semsim::RDF::setStorage(librdf_storage *storage) {
    storage_ = storage;
}

void semsim::RDF::setModel(librdf_model *model) {
    model_ = model;
}

void semsim::RDF::setRaptorWorld(raptor_world *raptorWorldPtr) {
    raptor_world_ = raptorWorldPtr;
}


/*************************************************
 * to/from operations
 */

semsim::RDF semsim::RDF::fromFile(std::string filename) {
    return semsim::RDF();
}

semsim::RDF semsim::RDF::fromString(const std::string &str, std::string format) {
    RDF rdf;
    Reader reader(rdf.getWorld(), rdf.getModel(), std::move(format), "file://./annotations.rdf");
    reader.fromString(str);

    // pull "seen" namespaces out of the parser and pass them to RDF class
    rdf.seen_namespaces_ = reader.getSeenNamespaces();

    // Compare against predefined set of namespaces: keep ones we've seen
    rdf.namespaces_ = rdf.propagateNamespacesFromParser(rdf.seen_namespaces_);

    return rdf;
}

semsim::RDF semsim::RDF::fromXML(const std::string &filename, std::string format) {
    LibRDFObjectsTuple objectsTuple = RDF::init();

    // unpack redland library objects
    librdf_world *world = std::get<0>(objectsTuple);
    raptor_world *raptor_world_ptr = std::get<1>(objectsTuple);
    librdf_storage *storage = std::get<2>(objectsTuple);
    librdf_model *model = std::get<3>(objectsTuple);

    // Read the xml
    Reader reader(world, model, std::move(format), "file://./annotations.rdf");
    reader.fromFile(filename);

    // construct an RDF object
    semsim::RDF rdf(world, raptor_world_ptr, storage, model);

    // pull "seen" namespaces out of the parser and pass them to RDF class
    rdf.seen_namespaces_ = reader.getSeenNamespaces();

    // Compare against predefined set of namespaces: keep ones we've seen
    rdf.namespaces_ = rdf.propagateNamespacesFromParser(rdf.seen_namespaces_);

    return rdf;
}

semsim::RDF semsim::RDF::fromStream(librdf_stream *stream) {
    RDF rdf;
    librdf_model_add_statements(rdf.model_, stream);

    return rdf;
}

semsim::RDF semsim::RDF::fromOmex(const std::string &filename_or_url) {
    return semsim::RDF();
}

std::string semsim::RDF::toString(const std::string &format="rdfxml-abbrev",
        const std::string &base_uri="file://./annotations.rdf") {
    setBaseUri(base_uri);
    Writer writer = makeWriter(format);
    return writer.toString();
}


librdf_stream *semsim::RDF::toStream() {
    return librdf_model_as_stream(model_);
}


void semsim::RDF::toFile(std::string format) {

}


/********************************************************************
 * Other methods
 */

std::unordered_map<std::string, std::string>
semsim::RDF::propagateNamespacesFromParser(std::vector<std::string> seen_namespaces) {
    std::unordered_map<std::string, std::string> keep_map;
    for (auto &seen_namespace : seen_namespaces) {
        auto iter = default_namespaces_.find(seen_namespace);
        if (iter != default_namespaces_.end()) {
            keep_map[seen_namespace] = default_namespaces_[seen_namespace];
        }
    }
    return keep_map;
}


semsim::Writer semsim::RDF::makeWriter(const std::string &format) {
    Writer writer(world_, model_, getBaseUriAsString(), format);
    writer.registerNamespace(namespaces_);
    return writer;
}

std::ostringstream semsim::RDF::listOptions() {
    raptor_world *raptor_world_ptr = raptor_new_world();
    int num_raptor_options = (int) raptor_option_get_count() - 1;
    std::ostringstream os;
    os << "option, name, label, domain, value type, url" << std::endl;
    int i = 0;
    while (i != num_raptor_options) {
        raptor_option_description *parser_opt = raptor_world_get_option_description(
                raptor_world_ptr,
                RAPTOR_DOMAIN_PARSER,
                (raptor_option) i
        );
        if (parser_opt) {
            os << parser_opt->option << "," << parser_opt->name << "," << parser_opt->label << ","
               << parser_opt->domain
               << "," << parser_opt->value_type << "," << raptor_uri_to_string(parser_opt->uri) << std::endl;
        } else {
            raptor_option_description *serializer_opt = raptor_world_get_option_description(
                    raptor_world_ptr,

                    RAPTOR_DOMAIN_SERIALIZER,
                    (raptor_option) i
            );
            if (serializer_opt) {
                os << serializer_opt->option << "," << serializer_opt->name << "," << serializer_opt->label
                   << ","
                   << serializer_opt->domain
                   << "," << serializer_opt->value_type << "," << raptor_uri_to_string(serializer_opt->uri)
                   << std::endl;
            }
        }
        i++;
    };
    return os;
}

semsim::Editor semsim::RDF::toEditor(std::string xml, semsim::XmlAssistantType type) {
    return Editor(xml, type, world_, model_, namespaces_);
}

librdf_uri *semsim::RDF::getBaseUri() const {
    return base_uri_;
}

std::string semsim::RDF::getBaseUriAsString() const {
    return std::string((const char *) librdf_uri_as_string(base_uri_));
}

void semsim::RDF::setBaseUri(const std::string &baseUri) {
    base_uri_ = librdf_new_uri(world_, (const unsigned char *) baseUri.c_str());
}

void semsim::RDF::setBaseUri(librdf_uri *baseUri) {
    base_uri_ = baseUri;
}

int semsim::RDF::size() const {
    librdf_stream *stream = librdf_model_as_stream(getModel());
    if (!stream) {
        throw LibRDFException("Query::resultsAsTriples: stream object null");
    }
    int count = 0;
    while (!librdf_stream_end(stream)) {
        count++;
        librdf_stream_next(stream);
    }
    return count;
}

semsim::Triples semsim::RDF::toTriples() {
    librdf_stream *stream = librdf_model_as_stream(getModel());
    if (!stream) {
        throw LibRDFException("RDF::toTriples: stream object null");
    }
    Triples triples;
    while (!librdf_stream_end(stream)) {
        librdf_statement *statement = librdf_stream_get_object(stream);
        if (!statement) {
            throw LibRDFException("RDF::toTriples(): statement is null");
        }
        triples.emplace_back(world_, statement);
        librdf_stream_next(stream);
    }
    return triples;
}

std::string semsim::RDF::queryResultsAsStr(const std::string &query_str, const std::string& results_format) {
    return semsim::Query(world_, model_, query_str).resultsAsStr(results_format);
}

semsim::ResultsMap semsim::RDF::queryResultsAsMap(const std::string &query_str) {
    return semsim::Query(world_, model_, query_str).resultsAsMap();
}

semsim::Triples semsim::RDF::queryResultsAsTriples(const std::string &query_str) {
    return queryResultsAsRDF(query_str).toTriples();
}

semsim::RDF semsim::RDF::queryResultsAsRDF(const std::string &query_str) {
    return RDF::fromString(queryResultsAsStr(query_str, "rdfxml"), "rdfxml");
}























