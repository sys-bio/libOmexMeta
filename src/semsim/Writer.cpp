//
// Created by Ciaran on 4/9/2020.
//

#include "Writer.h"
#include "semsim/SemsimUtils.h"


semsim::Writer::Writer(
        const LibrdfModel &model, std::string base_uri, std::string format,
        const char *mime_type, const char *type_uri)
        : model_(model), base_uri_(std::move(base_uri)), format_(std::move(format)),
          mime_type_(mime_type), type_uri_(type_uri) {
    if (std::find(valid_writer_names.begin(), valid_writer_names.end(), this->format_) == valid_writer_names.end()) {
        std::ostringstream os;
        os << "Invalid format: \"" << this->format_ << "\". These are valid formats: ";
        for (auto &i : valid_writer_names) {
            os << i << ", ";
        }
        throw std::invalid_argument(os.str());
    }
    serializer = LibrdfSerializer(format.c_str(), mime_type, type_uri);
    if (!serializer.get()) {
        throw NullPointerException("NullPointerException: Writer::init: serializer");
    }
    //set raptor options
    setOption("relativeURIs", "1");
    setOption("xmlDeclaration", "1");
    setOption("writeBaseURI", "1");
}

semsim::Writer::~Writer() = default;

void semsim::Writer::registerNamespace(const std::string &ns, const std::string &prefix) {
    serializer.setNamespace(LibrdfUri(ns), prefix);
}

void semsim::Writer::registerNamespace(const std::unordered_map<std::string, std::string> &ns_map) {
    for (auto &i : ns_map) {
        registerNamespace(i.first, i.second);
    }
}

void semsim::Writer::setOption(const std::string &option, const std::string &value) {
    std::string feature_uri_base = "http://feature.librdf.org/raptor-";
    serializer.setFeature(feature_uri_base + option, value);
}

std::string semsim::Writer::toString() {
    void *string = nullptr;
    raptor_iostream *iostr = raptor_new_iostream_to_string(
            World::getRaptor(), (void **) &string, nullptr, malloc);
    if (!iostr)
        throw NullPointerException("Writer::toString(): raptor_iostream");

    LibrdfUri uri = LibrdfUri(base_uri_);
    validateBaseUri();

    int failure = librdf_serializer_serialize_model_to_iostream(
            *serializer.getSerializer(), *uri.getUri(), *model_.getModel(), iostr);
    if (failure) { // i.e. if non-0
        throw std::logic_error("Writer::toString(): Failed to serialize model.");
    }
    std::string output_string((const char *) string);
    free(string);
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




















