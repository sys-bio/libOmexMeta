//
// Created by Ciaran on 4/9/2020.
//

#include "Writer.h"


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
    serializer = LibrdfSerializer(format_.c_str(), mime_type_, type_uri_);
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
    serializer.setNamespace(ns, prefix);
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
    return serializer.toString(LibrdfUri(base_uri_), model_);
}

void semsim::Writer::toFile(std::string format) {

}

void semsim::Writer::setFormat(const std::string &format) {
    Writer::format_ = format;
}

void semsim::Writer::validateBaseUri() {
    std::regex file_regex("^file://");
    std::smatch m;
    LibrdfUri uri(base_uri_);
    if (uri.str().rfind("file://", 0) != 0) {
        uri.str() = "file://" + uri.str();
        base_uri_ = uri.str();
    }
}





















