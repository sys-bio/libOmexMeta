//
// Created by Ciaran on 4/9/2020.
//

#include "Writer.h"

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
    serializer = librdf_new_serializer(*world.getWorld(), this->format_.c_str(), nullptr, nullptr);
    if (!serializer) {
        throw NullPointerException("Writer::init: serializer");
    }
    this->raptor_world_ptr_ = world.getRaptor();

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
    LibrdfUri ns_uri = world_.newUri(ns);
    librdf_serializer_set_namespace(serializer, *ns_uri.getUri(), (const char *) prefix.c_str());
}

void semsim::Writer::registerNamespace(const std::unordered_map<std::string, std::string> &ns_map) {
    for (auto &i : ns_map) {
        registerNamespace(i.first, i.second);
    }
}

void semsim::Writer::setOption(const std::string &option, const std::string &value) {
    std::string feature_uri_base = "http://feature.librdf.org/raptor-";
    LibrdfUri uri = world_.newUri(feature_uri_base + option);
    LibrdfNode node = world_.newNodeLiteral(value);
    librdf_serializer_set_feature(serializer, *uri.getUri(), *node.getNode());
}

std::string semsim::Writer::toString() {
    void *string = nullptr;
    raptor_iostream *iostr = raptor_new_iostream_to_string(
            *raptor_world_ptr_.getRaptorWorld(), (void **) &string, nullptr, malloc);
    if (!iostr)
        throw NullPointerException("Writer::toString(): raptor_iostream");

    LibrdfUri uri = world_.newUri(base_uri_);
    this->validateBaseUri();

    int failure = librdf_serializer_serialize_model_to_iostream(
            serializer, *uri.getUri(), *model_.getModel(), iostr);
    if (failure) { // i.e. if non-0
        throw std::logic_error("Writer::toString(): Failed to serialize model.");
    }
    std::string output_string((const char *) string);
    free(string);
    raptor_free_iostream(iostr);
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
    LibrdfUri uri = world_.newUri(base_uri_);
    if (uri.str().rfind("file://", 0) != 0) {
        uri.str() = "file://" + uri.str();
        base_uri_ = uri.str();
    }
}

semsim::Writer::Writer() = default;


semsim::TripleWriter::TripleWriter(semsim::Triple triple, const std::string &base_uri, std::string format) {
    // when creating a writer from a Triple, we just create a locally scoped rdf model and storage
    LibrdfWorld world;
    LibrdfStorage storage = world.newStorage("memory", "triple_store");
    if (!storage) {
        throw LibRDFException("Writer::Writer: storage not created");
    }
    LibrdfModel model = world.newModel(storage);
    if (!model) {
        throw LibRDFException("Writer::Writer: model not created");
    }

    // add statements to the model
    model.addStatement(triple.toStatement());

    // initialize the writer
    init(world, model, base_uri, std::move(format));

    // determine whether we recognize the namespace and add it if we do.
    std::string ns = triple.getPredicatePtr()->getNamespace();
    if (triple.getPredicatePtr()->namespaceKnown(ns)) {
        registerNamespace(ns, Predicate::prefix_map()[ns]);
    }
}

semsim::TripleWriter::TripleWriter(semsim::Triples triples, const std::string &base_uri, std::string format) {
    // when creating a writer from a Triple, we just create a locally scoped rdf model and storage
    LibrdfWorld world;
    LibrdfStorage storage = world.newStorage("memory", "triple_store");
    if (!storage) {
        throw LibRDFException("Writer::Writer: storage not created");
    }
    LibrdfModel model = world.newModel(storage);
    if (!model) {
        throw LibRDFException("Writer::Writer: model not created");
    }

    init(world, model, base_uri, std::move(format));
    for (auto &triple : triples) {
        model.addStatement(triple.toStatement());
        std::string ns = triple.getPredicatePtr()->getNamespace();
        if (triple.getPredicatePtr()->namespaceKnown(ns)) {
            registerNamespace(ns, Predicate::prefix_map()[triple.getPredicatePtr()->getNamespace()]);
        }
    }
}



















