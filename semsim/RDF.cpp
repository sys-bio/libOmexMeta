//
// Created by Ciaran on 4/8/2020.
//
#include <string>
#include <iostream>
#include <cstring>
#include <utility>
#include "RDF.h"
#include "semsim/SemSim.h"
#include "Reader.h"

/*******************************************************
 * Constructors
 */

/*
 * Initialiser for librdf/raptor objects. These commands are needed in multiple
 * places so they are pulled out of the RDF constructor into their own function.
 * This method is static so it can be used without instantiating RDF.
 */
semsim::LibrdfObjectsTuple semsim::RDF::init() {
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
    LibrdfObjectsTuple objectsTuple(world_, raptor_world_ptr_, storage_, model_);

    return objectsTuple;
}


semsim::RDF::RDF() {
    LibrdfObjectsTuple objectsTuple = RDF::init();

    // unpack redland library objects
    world_ = std::get<0>(objectsTuple);
    raptor_world_ = std::get<1>(objectsTuple);
    storage_ = std::get<2>(objectsTuple);
    model_ = std::get<3>(objectsTuple);

    // add some predefined namespaces for the serializer.
    declareNamespaces();

}

semsim::RDF::RDF(librdf_world *world, raptor_world *raptor_world_, librdf_storage *storage, librdf_model *model) :
        world_(world),
        raptor_world_(raptor_world_),
        storage_(storage),
        model_(model) {

    // add some predefined namespaces for the serializer.
    declareNamespaces();

}

semsim::RDF::~RDF() {
    librdf_free_model(model_);
    librdf_free_storage(storage_);
    librdf_free_world(world_);
}

void semsim::RDF::declareNamespaces() {
    // add some predefined namespaces for the serializer.
    namespaces_["dcterms"] = "http://purl.org/dc/terms/";
    namespaces_["bqbiol"] = "http://biomodels.net/biology-qualifiers/";
    namespaces_["bqmodel"] = "http://biomodels.net/model-qualifiers/";
    namespaces_["semsim"] = "http://www.bhi.washington.edu/semsim#";
}

semsim::RDF::RDF(const semsim::RDF &libRdfModel) {
    this->world_ = libRdfModel.world_;
    this->storage_ = libRdfModel.storage_;
    this->model_ = libRdfModel.model_;
    this->raptor_world_ = libRdfModel.raptor_world_;
}

semsim::RDF::RDF(semsim::RDF &&libRdfModel) noexcept {
    this->world_ = libRdfModel.world_;
    this->storage_ = libRdfModel.storage_;
    this->model_ = libRdfModel.model_;
    this->raptor_world_ = libRdfModel.raptor_world_;
}

semsim::RDF &semsim::RDF::operator=(const semsim::RDF &libRdfModel) {
    if (this != &libRdfModel) {
        this->world_ = libRdfModel.world_;
        this->storage_ = libRdfModel.storage_;
        this->model_ = libRdfModel.model_;
        this->raptor_world_ = libRdfModel.raptor_world_;
    }
    return *this;
}

semsim::RDF &semsim::RDF::operator=(semsim::RDF &&libRdfModel) noexcept {
    if (this != &libRdfModel) {
        this->world_ = libRdfModel.world_;
        this->storage_ = libRdfModel.storage_;
        this->model_ = libRdfModel.model_;
        this->raptor_world_ = libRdfModel.raptor_world_;
    }
    return *this;
}

bool semsim::RDF::operator==(const semsim::RDF &rhs) const {
    return world_ == rhs.world_ &&
           storage_ == rhs.storage_ &&
           model_ == rhs.model_ &&
           raptor_world_ == rhs.raptor_world_;
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

librdf_model *semsim::RDF::getModel() const {
    return model_;
}

raptor_world *semsim::RDF::getRaptorWorld() const {
    return raptor_world_;
}


const std::unordered_map<const char*, const char*> &semsim::RDF::getNamespaces() const {
    return namespaces_;
}

void semsim::RDF::setNamespaces(const std::unordered_map<const char*, const char*> &namespaces) {
    namespaces_ = namespaces;
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

semsim::RDF semsim::RDF::fromXML(const std::string &filename, std::string format) {
    LibrdfObjectsTuple objectsTuple = RDF::init();

    // unpack redland library objects
    librdf_world *world = std::get<0>(objectsTuple);
    raptor_world *raptor_world_ptr = std::get<1>(objectsTuple);
    librdf_storage *storage = std::get<2>(objectsTuple);
    librdf_model *model = std::get<3>(objectsTuple);

    // Read the xml
    Reader reader(world, model, std::move(format));
    reader.fromFile(filename);

    // construct an RDF object
    semsim::RDF rdf(world, raptor_world_ptr, storage, model);

    // pull "seen" namespaces out of the parser and pass them to RDF class
    rdf.namespaces_ = reader.parseNamespacesWithPrefix();

    return rdf;
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

semsim::RDF semsim::RDF::fromRDF(std::string filename) {
    return semsim::RDF();
}

void semsim::RDF::fromString(const std::string &str, std::string format) {
    Reader reader(world_, model_, std::move(format));
    reader.fromString(str);
    namespaces_ = reader.parseNamespacesWithPrefix();
}

std::string semsim::RDF::toString(std::string format, std::string base_uri) {
    Writer writer = makeWriter(format, base_uri);
    return writer.toString();
}

void semsim::RDF::toFile(std::string format) {

}


semsim::RDF semsim::RDF::fromOmex(std::string filename_or_url) {
    return semsim::RDF();
}

/********************************************************************
 * Other methods
 */



semsim::Writer semsim::RDF::makeWriter(const std::string &format, const std::string &base_uri) {
    Writer writer(world_, model_, format, base_uri);
    for (auto &it : namespaces_) {
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


std::ostringstream semsim::RDF::listOptions() {
    raptor_world *raptor_world_ptr = raptor_new_world();
    int num_raptor_options = (int) raptor_option_get_count() - 1;
    std::ostringstream os;
    os << "option, name, label, domain, value type, url" << std::endl;
    int i = 0;
    while (i != num_raptor_options) {
        raptor_option_description *parser_opt = raptor_world_get_option_description(raptor_world_ptr,
                                                                                    RAPTOR_DOMAIN_PARSER,
                                                                                    (raptor_option) i);
        if (parser_opt) {

            os << parser_opt->option << "," << parser_opt->name << "," << parser_opt->label << ","
               << parser_opt->domain
               << "," << parser_opt->value_type << "," << raptor_uri_to_string(parser_opt->uri) << std::endl;
        } else {
            raptor_option_description *serializer_opt = raptor_world_get_option_description(raptor_world_ptr,
                                                                                            RAPTOR_DOMAIN_SERIALIZER,
                                                                                            (raptor_option) i);
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
    return Editor(xml, type, world_, model_);
}























