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

    // add some predefined namespaces for the serializer.


}

semsim::RDF::RDF(librdf_world *world, raptor_world *raptor_world_, librdf_storage *storage, librdf_model *model) :
        world_(world),
        raptor_world_(raptor_world_),
        storage_(storage),
        model_(model) {

    // add some predefined namespaces for the serializer.


}

semsim::RDF::~RDF() {
    librdf_free_model(model_);
    librdf_free_storage(storage_);
    librdf_free_world(world_);
}

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
    Reader reader(rdf.getWorld(), rdf.getModel(), std::move(format));
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
    Reader reader(world, model, std::move(format));
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

semsim::RDF semsim::RDF::fromOmex(std::string filename_or_url) {
    return semsim::RDF();
}

std::string semsim::RDF::toString(std::string format, std::string base_uri) {
    Writer writer = makeWriter(format, base_uri);
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

semsim::Writer semsim::RDF::makeWriter(const std::string &format, const std::string &base_uri) {
    Writer writer(world_, model_, format, base_uri);
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

semsim::RDF semsim::RDF::query(std::string query_str, std::string query_format, std::string results_mime_type) {
    RDF rdf;
    std::string format = "turtle";
    unsigned char *string;
    size_t length;

    librdf_query *query = librdf_new_query(
            world_, query_format.c_str(), nullptr,
            (const unsigned char *) query_str.c_str(), nullptr
    );

    librdf_query_results *results = librdf_model_query_execute(model_, query);
    if (!results) {
        throw LibRDFException("No results");
    }

    std::cout << librdf_query_results_is_bindings(results) << std::endl;
    std::cout << librdf_query_results_is_boolean(results) << std::endl;
    string = librdf_query_results_to_counted_string2(
            results, format.c_str(), results_mime_type.c_str(), nullptr, nullptr, &length);
    if (!string) {
        throw LibRDFException("No workey");
    }
    std::cout << string << "\n\n\n\n\n" << std::endl;


//    if (librdf_query_results_is_bindings(results) ||
//        librdf_query_results_is_boolean(results)) {
//        HERE();

//    } else {
//    HERE();
    /* triples */
//    librdf_serializer *serializer;
//    librdf_stream *stream;

//    serializer = librdf_new_serializer(world_, format.c_str(), nullptr, nullptr);
//    if (!serializer) {
//        throw LibRDFException("No workey");
//    }

    librdf_stream *stream = librdf_query_results_as_stream(results);
    if (!stream) {
        throw LibRDFException("Stream no workey");
    }
//    librdf_query_res
//    string = librdf_serializer_serialize_stream_to_counted_string(
//            serializer, nullptr, stream, &length);
//    if (!string) {
//        throw LibRDFException("No workey");
//
//    }
    int x = librdf_model_add_statements(rdf.getModel(), stream);
    std::cout << "x is :" << x << std::endl;
    librdf_free_stream(stream);
    std::cout << rdf.toString("rdfxml") << std::endl;

    raptor_uri *u = librdf_get_concept_schema_namespace(world_);
    raptor_uri *u2 = librdf_get_concept_ms_namespace(world_);

    std::cout << librdf_uri_as_string(u) << std::endl;
    std::cout << librdf_uri_as_string(u2) << std::endl;

    std::vector<raptor_uri *> j = {
            librdf_get_concept_uri_by_index(world_, LIBRDF_CONCEPT_MS_Alt),
            librdf_get_concept_uri_by_index(world_, LIBRDF_CONCEPT_MS_Bag),
            librdf_get_concept_uri_by_index(world_, LIBRDF_CONCEPT_MS_Property),
            librdf_get_concept_uri_by_index(world_, LIBRDF_CONCEPT_MS_Seq),
            librdf_get_concept_uri_by_index(world_, LIBRDF_CONCEPT_MS_Statement),
            librdf_get_concept_uri_by_index(world_, LIBRDF_CONCEPT_MS_object),
            librdf_get_concept_uri_by_index(world_, LIBRDF_CONCEPT_MS_predicate),
            librdf_get_concept_uri_by_index(world_, LIBRDF_CONCEPT_MS_subject),
            librdf_get_concept_uri_by_index(world_, LIBRDF_CONCEPT_MS_type),
            librdf_get_concept_uri_by_index(world_, LIBRDF_CONCEPT_MS_value),
            librdf_get_concept_uri_by_index(world_, LIBRDF_CONCEPT_MS_li),
            librdf_get_concept_uri_by_index(world_, LIBRDF_CONCEPT_MS_RDF),
            librdf_get_concept_uri_by_index(world_, LIBRDF_CONCEPT_MS_Description),
            librdf_get_concept_uri_by_index(world_, LIBRDF_CONCEPT_MS_aboutEach),
            librdf_get_concept_uri_by_index(world_, LIBRDF_CONCEPT_MS_aboutEachPrefix),
            librdf_get_concept_uri_by_index(world_, LIBRDF_CONCEPT_RS_nodeID),
            librdf_get_concept_uri_by_index(world_, LIBRDF_CONCEPT_RS_List),
            librdf_get_concept_uri_by_index(world_, LIBRDF_CONCEPT_RS_first),
            librdf_get_concept_uri_by_index(world_, LIBRDF_CONCEPT_RS_rest),
            librdf_get_concept_uri_by_index(world_, LIBRDF_CONCEPT_RS_nil),
            librdf_get_concept_uri_by_index(world_, LIBRDF_CONCEPT_RS_XMLLiteral)
    };
    std::vector<librdf_node *> asresources = {
            librdf_get_concept_resource_by_index(world_, LIBRDF_CONCEPT_MS_Alt),
            librdf_get_concept_resource_by_index(world_, LIBRDF_CONCEPT_MS_Bag),
            librdf_get_concept_resource_by_index(world_, LIBRDF_CONCEPT_MS_Property),
            librdf_get_concept_resource_by_index(world_, LIBRDF_CONCEPT_MS_Seq),
            librdf_get_concept_resource_by_index(world_, LIBRDF_CONCEPT_MS_Statement),
            librdf_get_concept_resource_by_index(world_, LIBRDF_CONCEPT_MS_object),
            librdf_get_concept_resource_by_index(world_, LIBRDF_CONCEPT_MS_predicate),
            librdf_get_concept_resource_by_index(world_, LIBRDF_CONCEPT_MS_subject),
            librdf_get_concept_resource_by_index(world_, LIBRDF_CONCEPT_MS_type),
            librdf_get_concept_resource_by_index(world_, LIBRDF_CONCEPT_MS_value),
            librdf_get_concept_resource_by_index(world_, LIBRDF_CONCEPT_MS_li),
            librdf_get_concept_resource_by_index(world_, LIBRDF_CONCEPT_MS_RDF),
            librdf_get_concept_resource_by_index(world_, LIBRDF_CONCEPT_MS_Description),
            librdf_get_concept_resource_by_index(world_, LIBRDF_CONCEPT_MS_aboutEach),
            librdf_get_concept_resource_by_index(world_, LIBRDF_CONCEPT_MS_aboutEachPrefix),
            librdf_get_concept_resource_by_index(world_, LIBRDF_CONCEPT_RS_nodeID),
            librdf_get_concept_resource_by_index(world_, LIBRDF_CONCEPT_RS_List),
            librdf_get_concept_resource_by_index(world_, LIBRDF_CONCEPT_RS_first),
            librdf_get_concept_resource_by_index(world_, LIBRDF_CONCEPT_RS_rest),
            librdf_get_concept_resource_by_index(world_, LIBRDF_CONCEPT_RS_nil),
            librdf_get_concept_resource_by_index(world_, LIBRDF_CONCEPT_RS_XMLLiteral)
    };
    int count = 0;
    for (auto &i : j) {
        std::cout << count << " " << librdf_uri_as_string(i) << std::endl;
        count++;
    }
    size_t len;

//    int y = librdf_conce(model_, asresources[1]);
//    std::cout << "y: " << y << std::endl;
//    }

//    std::cout << string << std::endl;
//
//
//    free(string);


    librdf_free_query_results(results);
    librdf_free_query(query);
    return rdf;

}























