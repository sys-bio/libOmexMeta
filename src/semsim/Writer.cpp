//
// Created by Ciaran on 4/9/2020.
//

#include <stdexcept>
#include <utility>
#include "Writer.h"
#include "SemSim.h"
#include <regex>
#include "Error.h"

void semsim::Writer::setWorld(LibrdfWorld w) {
    this->world_ = w;
}

void semsim::Writer::init(LibrdfWorld world, LibrdfModel model,
                          const std::string &base_uri, std::string format) {
    this->world_ = world;

    if (!world) {
        throw NullPointerException("Writer::init: world");
    }

    this->model_ = model;
    if (!model) {
        throw NullPointerException("Writer::init: model");
    }
    base_uri_ = base_uri;
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
        throw NullPointerException("Writer::init: serializer");
    }
    this->raptor_world_ptr_ = librdf_world_get_raptor(world);

    if (!raptor_world_ptr_) {
        throw NullPointerException("Writer::init: raptor_world_ptr");
    }

    //todo built interface to allow users to set options
    //todo ask about which defaults they want
    //set raptor options
    setOption("relativeURIs", "1");
    setOption("xmlDeclaration", "1");
    setOption("writeBaseURI", "1");

}

semsim::Writer::Writer(LibrdfWorld world, LibrdfModel model,
                       const std::string &base_uri, std::string format) {
    init(world, model, base_uri, format);
}

/*
 * Todo this version of writer contains memory leaks, since RDF is responsuble for
 *  freeing librdf structures yet here we create them again and do not (but cannot) free
 *  I think this design is possible flawed here. Need a way of controlling Writer through RDF
 *  since the model.
 *
 *  I think I need a subclass of Writer so i can create a separate destructor
 */

semsim::Writer::~Writer() {
//    if(serializer)
//        librdf_free_serializer(serializer);
}

void semsim::Writer::registerNamespace(const std::string &ns, const std::string &prefix) {
    LibrdfUri ns_uri = librdf_new_uri(world_, (const unsigned char *) ns.c_str());
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
    LibrdfNode node = librdf_new_node_from_literal(world_, (const unsigned char *) value.c_str(), nullptr, 0);
    librdf_serializer_set_feature(serializer, uri, node);
    librdf_free_uri(uri);
    librdf_free_node(node);
}

std::string semsim::Writer::toString() {
    void *string = nullptr;
    raptor_iostream *iostr = raptor_new_iostream_to_string(raptor_world_ptr_, (void **) &string, nullptr, malloc);
    if (!iostr)
        throw NullPointerException("Writer::toString(): raptor_iostream");

    auto base_uri_cstr = (unsigned char *) base_uri_.c_str();
    LibrdfUri uri = librdf_new_uri(world_, base_uri_cstr);
    if (!uri) {
        throw NullPointerException("Writer::toString: uri");
    }
    this->validateBaseUri();

    int failure = librdf_serializer_serialize_model_to_iostream(serializer, uri, model_, iostr);
    if (failure) { // i.e. if non-0
        throw std::logic_error("Writer::toString(): Failed to serialize model.");
    }
    std::string output_string((const char *) string);
    free(string);
    librdf_free_uri(uri);
    delete base_uri_cstr;

    return output_string;
}

void semsim::Writer::toFile(std::string format) {

}

void semsim::Writer::setFormat(const std::string &format) {
    Writer::format_ = format;
}

void semsim::Writer::validateBaseUri() {
    std::regex file_regex("^file://");
    std::smatch m;
    LibrdfUri uri = librdf_new_uri(world_, reinterpret_cast<const unsigned char *>(base_uri_.c_str()));
    std::string uri_str = (const char *) librdf_uri_as_string(uri);
    if (uri_str.rfind("file://", 0) != 0) {
        uri_str = "file://" + uri_str;
        base_uri_ = uri_str;//librdf_new_uri(world_, (const unsigned char *) uri_str.c_str());
    }
}

semsim::Writer::Writer() = default;


semsim::TripleWriter::TripleWriter(semsim::Triple triple, const std::string &base_uri, std::string format) {
    // when creating a writer from a Triple, we just create a locally scoped rdf model and storage
    LibrdfWorld world = librdf_new_world();
    LibrdfStorage storage = librdf_new_storage(world, "memory", "triple_store", nullptr);
    if (!storage) {
        throw LibRDFException("Writer::Writer: storage not created");
    }
    LibrdfModel model = librdf_new_model(world, storage, nullptr);
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

semsim::TripleWriter::TripleWriter(semsim::Triples triples, const std::string &base_uri, std::string format) {
    // when creating a writer from a Triple, we just create a locally scoped rdf model and storage
    LibrdfWorld world = librdf_new_world();
    storage_ = librdf_new_storage(world, "memory", "triples_store", nullptr);
    if (!storage_) {
        throw LibRDFException("Writer::Writer: storage not created");
    }
    LibrdfModel model = librdf_new_model(world, storage_, nullptr);
    if (!model) {
        throw LibRDFException("Writer::Writer: model not created");
    }
    init(world, model, base_uri, std::move(format));
    for (auto &triple : triples) {
        librdf_model_add_statement(model, triple.toStatement());
        std::string ns = triple.getPredicatePtr()->getNamespace();
        if (triple.getPredicatePtr()->namespaceKnown(ns)) {
            registerNamespace(ns, Predicate::prefix_map()[triple.getPredicatePtr()->getNamespace()]);
        }
    }
}

semsim::TripleWriter::~TripleWriter() {
    librdf_free_storage(storage_);
    librdf_free_model(model_);
    librdf_free_world(world_);

}


















