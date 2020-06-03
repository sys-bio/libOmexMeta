//
// Created by Ciaran on 5/31/2020.
//

#include "RDF.h"


namespace semsim {

    RDF::RDF(const std::string &base_uri, const std::string &storage_type, const std::string &storage_name,
             const char *storage_options,
             const char *model_options) {
        storage_ = LibrdfStorage(storage_type, storage_name, storage_options);
        model_ = LibrdfModel(storage_, model_options);
        setBaseUri(base_uri);
    }

    int RDF::size() const {
        return model_.size();
    }

    void RDF::setBaseUri(std::string baseUri) {
        base_uri_ = SemsimUtils::addFilePrefixToString(baseUri);
    }

    bool RDF::empty() {
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
        parser.parseString(str, rdf.model_, LibrdfUri(base_uri_used));

        // update the list of "seen" namespaces
        rdf.seen_namespaces_ = parser.getSeenNamespaces();

        // Compare against predefined set of namespaces: bqbiol etc.
        // This allows us to only use the ones that are needed
        rdf.namespaces_ = rdf.propagateNamespacesFromParser(rdf.seen_namespaces_);

        return rdf;
    }

    std::unordered_map<std::string, std::string>
    RDF::propagateNamespacesFromParser(std::vector<std::string> seen_namespaces) {
        std::unordered_map<std::string, std::string> keep_map;
        for (auto &seen_namespace : seen_namespaces) {
            auto iter = default_namespaces_.find(seen_namespace);
            if (iter != default_namespaces_.end()) {
                keep_map[seen_namespace] = default_namespaces_[seen_namespace];
            }
        }
        return keep_map;
    }

    std::string RDF::toString(const std::string &format, const std::string &base_uri,
                              const char *mime_type, const char *type_uri) {
        LibrdfSerializer serializer(format.c_str(), mime_type, type_uri);
        // remember to add namespaces taken from parser
        for (auto &it: namespaces_){
            serializer.setNamespace(it.first, it.second);
        }
        return serializer.toString(LibrdfUri(base_uri), model_);
    }


    Editor RDF::toEditor(std::string xml, SemsimXmlType type) {
        return Editor(xml, type, model_, namespaces_);
    }

    librdf_model *RDF::getModel() const {
        return model_.get();
    }


}
