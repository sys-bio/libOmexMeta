//
// Created by Ciaran on 4/9/2020.
//

#include <stdexcept>
#include <utility>
#include "Writer.h"
#include "SemSim.h"
#include <regex>
#include "Error.h"

void semsim::Writer::setWorld(librdf_world *w) {
    this->world_ = w;
}

void semsim::Writer::init(librdf_world *world, librdf_model *model,
                          const std::string &base_uri, std::string format) {
    this->world_ = world;

    if (!world) {
        throw std::invalid_argument("World argument invalid");
    }
    this->base_uri_ = librdf_new_uri(world, (const unsigned char *) base_uri.c_str());
    if (!base_uri_) {
        throw std::invalid_argument("base_uri_ argument invalid");
    }
    this->validateBaseUri();

    this->model_ = model;
    if (!model) {
        throw std::invalid_argument("model argument invalid");
    }

    this->format_ = std::move(format);
    if (std::find(valid_writer_names.begin(), valid_writer_names.end(), this->format_) == valid_writer_names.end()) {
        std::ostringstream os;
        os << "Invalid format: \"" << this->format_ << "\". These are valid formats: ";
        for (auto &i : valid_writer_names) {
            os << i << ", ";
        }
        throw std::invalid_argument(os.str());
    }
    serializer = librdf_new_serializer(world, this->format_.c_str(), nullptr, nullptr);
    if (!serializer) {
        throw std::invalid_argument("Failed to create serializer\n");
    }
    this->raptor_world_ptr_ = librdf_world_get_raptor(world);

    if (!raptor_world_ptr_) {
        throw std::invalid_argument("World argument invalid");
    }

    //todo built interface to allow users to set options
    //todo ask about which defaults they want
    //set raptor options
    setOption("relativeURIs", "1");
    setOption("xmlDeclaration", "1");
    setOption("writeBaseURI", "1");

}

semsim::Writer::Writer(librdf_world *world, librdf_model *model,
                       const std::string &base_uri, std::string format) {
    init(world, model, base_uri, format);
}

semsim::Writer::Writer(semsim::Triple triple, const std::string &base_uri, std::string format) {
    // when creating a writer from a Triple, we just create a locally scoped rdf model and storage
    librdf_world *world = librdf_new_world();
    librdf_storage *storage = librdf_new_storage(world, "memory", "triple_store", nullptr);
    if (!storage) {
        throw LibRDFException("Writer::Writer: storage not created");
    }
    librdf_model *model = librdf_new_model(world, storage, nullptr);
    if (!model) {
        throw LibRDFException("Writer::Writer: model not created");
    }

    // add statements to the model
    librdf_model_add_statement(model, triple.toStatement());

    // initialize the writer
    init(world, model, base_uri, format);

    // determine whether we recognize the namespace and add it if we do.
    std::string ns = triple.getPredicatePtr()->getNamespace();
    if (triple.getPredicatePtr()->namespaceKnown(ns)) {
        registerNamespace(ns, Predicate::prefix_map()[ns]);
    }
}

semsim::Writer::Writer(semsim::Triples triples, const std::string &base_uri, std::string format) {
    // when creating a writer from a Triple, we just create a locally scoped rdf model and storage
    librdf_world *world = librdf_new_world();
    librdf_storage *storage = librdf_new_storage(world, "memory", "triples_store", nullptr);
    if (!storage) {
        throw LibRDFException("Writer::Writer: storage not created");
    }
    librdf_model *model = librdf_new_model(world, storage, nullptr);
    if (!model) {
        throw LibRDFException("Writer::Writer: model not created");
    }
    init(world, model, base_uri, format);
    for (auto &triple : triples) {
        librdf_model_add_statement(model, triple.toStatement());
        std::string ns = triple.getPredicatePtr()->getNamespace();
        if (triple.getPredicatePtr()->namespaceKnown(ns)) {
            registerNamespace(ns, Predicate::prefix_map()[triple.getPredicatePtr()->getNamespace()]);
        }
    }
}


void semsim::Writer::registerNamespace(const std::string &ns, const std::string &prefix) {
    librdf_uri *ns_uri = librdf_new_uri(world_, (const unsigned char *) ns.c_str());
    librdf_serializer_set_namespace(serializer, ns_uri, (const char *) prefix.c_str());
    librdf_free_uri(ns_uri);
}

void semsim::Writer::registerNamespace(const std::unordered_map<std::string, std::string> &ns_map) {
    for (auto &i : ns_map) {
        registerNamespace(i.first, i.second);
    }
}

void semsim::Writer::setOption(const std::string &option, const std::string &value) {
    std::string feature_uri_base = "http://feature.librdf.org/raptor-";
    raptor_uri *uri = raptor_new_uri(raptor_world_ptr_, (const unsigned char *) (feature_uri_base + option).c_str());
    librdf_node *node = librdf_new_node_from_literal(world_, (const unsigned char *) value.c_str(), nullptr, 0);
    librdf_serializer_set_feature(serializer, uri, node);
}

std::string semsim::Writer::toString() {
    void *string = nullptr;
    raptor_iostream *iostr = raptor_new_iostream_to_string(raptor_world_ptr_, (void **) &string, nullptr, malloc);
    if (!iostr)
        throw std::invalid_argument("raptor_iostream was not created in semsim::Writer::toString()");

    int failure = librdf_serializer_serialize_model_to_iostream(serializer, base_uri_, model_, iostr);
    if (failure) { // i.e. if non-0
        throw std::logic_error("Could not write model_.");
    }
    std::string output_string((const char *) string);
    return output_string;
}

std::string semsim::Writer::print() {
    raptor_iostream *iostream = raptor_new_iostream_to_file_handle(raptor_world_ptr_, stdout);
    librdf_serializer_serialize_model_to_iostream(serializer, base_uri_, model_, iostream);
}

void semsim::Writer::toFile(std::string format) {

}

void semsim::Writer::setFormat(const std::string &format) {
    Writer::format_ = format;
}

void semsim::Writer::validateBaseUri() {
    std::regex file_regex("^file://");
    std::smatch m;
    std::string uri_str = (const char *) librdf_uri_as_string(base_uri_);
    if (uri_str.rfind("file://", 0) != 0) {
        uri_str = "file://" + uri_str;
        base_uri_ = librdf_new_uri(world_, (const unsigned char *) uri_str.c_str());
    }
}



//todo look into using concept schema part of librdf. This may solve the rdf:Bag problem.
// Might also be able to use sbml/cellml schemas.




















