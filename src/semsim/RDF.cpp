//
// Created by Ciaran on 5/31/2020.
//

#include "RDF.h"

#include <utility>


namespace semsim {


    RDF::RDF(const std::string &base_uri, const std::string &storage_type, const std::string &storage_name,
             const char *storage_options,
             const char *model_options) {
        storage_ = LibrdfStorage(storage_type, storage_name, storage_options);
        // model_ now owns storage_
        model_ = LibrdfModel(storage_.get(), model_options);
        setBaseUri(base_uri);
    }

    void RDF::freeRDF() {
        model_.freeModel();
        storage_.freeStorage();
    }

    RDF::~RDF() {
        freeRDF();
    }


    RDF::RDF(RDF &&rdf) noexcept {
        base_uri_ = std::move(rdf.base_uri_);
        namespaces_ = std::move(rdf.namespaces_);
        seen_namespaces_ = std::move(rdf.seen_namespaces_);
        default_namespaces_ = std::move(rdf.default_namespaces_);
        storage_ = std::move(rdf.storage_);
        model_ = std::move(rdf.model_);
    }

    RDF &RDF::operator=(RDF &&rdf) noexcept {
        if (this != &rdf) {
            base_uri_ = std::move(rdf.base_uri_);
            namespaces_ = std::move(rdf.namespaces_);
            seen_namespaces_ = std::move(rdf.seen_namespaces_);
            default_namespaces_ = std::move(rdf.default_namespaces_);
            storage_ = std::move(rdf.storage_);
            model_ = std::move(rdf.model_);
        }
    }

    int RDF::size() const {
        return model_.size();
    }

    void RDF::setBaseUri(std::string baseUri) {
        base_uri_ = SemsimUtils::addFilePrefixToString(std::move(baseUri));
    }

    bool RDF::empty() const {
        return size() == 0;
    }

    RDF RDF::fromString(const std::string &str, const std::string &format, const std::string &base_uri) {
        std::string base_uri_used;
        if (base_uri.empty())
            base_uri_used = SemsimUtils::addFilePrefixToString("Annotations.rdf");
        else
            base_uri_used = base_uri;

        RDF rdf;
        LibrdfParser parser(format);

        LibrdfUri u(base_uri_used);
        parser.parseString(str, rdf.model_, u);
        u.freeUri();

        // update the list of "seen" namespaces
        rdf.seen_namespaces_ = parser.getSeenNamespaces();

        // Compare against predefined set of namespaces: bqbiol etc.
        // This allows us to only use the ones that are needed
        rdf.namespaces_ = rdf.propagateNamespacesFromParser(rdf.seen_namespaces_);

        return rdf;
    }

    void RDF::fromString(RDF *rdf, const std::string &str, const std::string &format, const std::string &base_uri) {
        std::string base_uri_used;
        if (base_uri.empty())
            base_uri_used = SemsimUtils::addFilePrefixToString("Annotations.rdf");
        else
            base_uri_used = base_uri;

        LibrdfParser parser(format);
        parser.parseString(str, rdf->model_, LibrdfUri(base_uri_used));

        // update the list of "seen" namespaces
        rdf->seen_namespaces_ = parser.getSeenNamespaces();

        // Compare against predefined set of namespaces: bqbiol etc.
        // This allows us to only use the ones that are needed
        rdf->namespaces_ = rdf->propagateNamespacesFromParser(rdf->seen_namespaces_);
    }

    void RDF::addFromString(const std::string &str,
                      const std::string &format, const std::string &base_uri) {
        std::string base_uri_used;

        // some logic for allowing users to not need to manually input a base_uri
        // when parsing from a string
        if (base_uri.empty())
            base_uri_used = SemsimUtils::addFilePrefixToString("Annotations.rdf");
        else
            base_uri_used = base_uri;

        LibrdfParser parser(format);

        LibrdfUri u(base_uri_used);
        parser.parseString(str, model_, u);
        u.freeUri();

        // update the list of "seen" namespaces
        seen_namespaces_ = parser.getSeenNamespaces();

        // Compare against predefined set of namespaces: bqbiol etc.
        // This allows us to only use the ones that are needed
        namespaces_ = propagateNamespacesFromParser(seen_namespaces_);

    }

    /*
     * @brief parse RDF directly from a uri
     * @param uri_string the uri to download containing RDF
     * @param format the format that the RDF is in
     * @return RDF an instantiated RDF object.
     *
     * @details downloads uri from the internet and creates an RDF graph.
     * See Librdf::parseUri() for more details.
     */
    RDF RDF::fromUri(const std::string &uri_string, const std::string &format) {
        RDF rdf;
        LibrdfParser parser(format);
        parser.parseUri(uri_string, rdf.model_);
        return rdf;
    }

    /*
     * @brief non-static counterpart of RDF::fromUri. Downloads and
     * parses rdf from a URI.
     *
     * @details See RDF::fromUri for details.
     */
    void RDF::addFromUri(const std::string &uri_string, const std::string &format) {
        LibrdfParser parser(format);
        parser.parseUri(uri_string, model_);
    }

    RDF RDF::fromFile(const std::string &filename, const std::string& format){
        RDF rdf;
        LibrdfParser parser(format);
        parser.parseFile(filename, rdf.model_);
        return rdf;
    }

    void RDF::addFromFile(const std::string &filename, const std::string& format){
        LibrdfParser parser(format);
        parser.parseFile(filename, model_);
    }

    /*
     * @brief compared namespaces seen with namespaces
     * known and ensures models that use a known namespace
     * use that namespace.
     * @param seen_namespaces a vector of strings of namespaces the parser has seen before.
     *
     */
    std::unordered_map<std::string, std::string>
    RDF::propagateNamespacesFromParser(const std::vector<std::string> &seen_namespaces) {
        std::unordered_map<std::string, std::string> keep_map;
        for (auto &seen_namespace : seen_namespaces) {
            auto iter = default_namespaces_.find(seen_namespace);
            if (iter != default_namespaces_.end()) {
                keep_map[seen_namespace] = default_namespaces_[seen_namespace];
            }
        }
        return keep_map;
    }

    std::string RDF::toString(const std::string &format, std::string base_uri,
                              const char *mime_type, const char *type_uri) {
        base_uri = SemsimUtils::addFilePrefixToString(base_uri);
        LibrdfSerializer serializer(format.c_str(), mime_type, type_uri);
        // remember to add namespaces taken from parser
        for (auto &it: namespaces_) {
            serializer.setNamespace(it.first, it.second);
        }
        return serializer.toString(base_uri, model_);
    }

    librdf_model *RDF::getModel() const {
        return model_.get();
    }

    Editor RDF::toEditor(const std::string &xml, SemsimXmlType type) {
        return Editor(xml, type, model_, namespaces_);
    }

    Editor *RDF::toEditorPtr(const std::string &xml, SemsimXmlType type) {
        auto *editor = new Editor(xml, type, model_, namespaces_);
        return editor;
    }

    librdf_storage *RDF::getStorage() const {
        return storage_.get();
    }



}
