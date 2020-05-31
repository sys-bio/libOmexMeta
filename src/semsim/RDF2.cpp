//
// Created by Ciaran on 5/31/2020.
//

#include "RDF2.h"


namespace semsim {

    RDF2::RDF2(const std::string &base_uri, const std::string &storage_type, const std::string &storage_name,
               const char *storage_options,
               const char *model_options) {
        storage_ = LibrdfStorage(storage_type, storage_name, storage_options);
        model_ = LibrdfModel(storage_, model_options);
        setBaseUri(base_uri);
    }

    int RDF2::size() const {
        return model_.size();
    }

    void RDF2::setBaseUri(std::string baseUri) {
        base_uri_ = SemsimUtils::addFilePrefixToString(baseUri);
    }

    bool RDF2::empty() {
        return size() == 0;
    }

    RDF2 RDF2::fromString(const std::string &str, const std::string &format, const std::string &base_uri) {
        std::string base_uri_used;
        if (base_uri.empty())
            base_uri_used = SemsimUtils::addFilePrefixToString("Annotations.rdf");
        else
            base_uri_used = base_uri;

        RDF2 rdf;
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
    RDF2::propagateNamespacesFromParser(std::vector<std::string> seen_namespaces) {
        std::unordered_map<std::string, std::string> keep_map;
        for (auto &seen_namespace : seen_namespaces) {
            auto iter = default_namespaces_.find(seen_namespace);
            if (iter != default_namespaces_.end()) {
                keep_map[seen_namespace] = default_namespaces_[seen_namespace];
            }
        }
        return keep_map;
    }

}
