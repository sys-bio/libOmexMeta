//
// Created by Ciaran on 5/31/2020.
//

#ifndef LIBSEMSIM_RDF_H
#define LIBSEMSIM_RDF_H

#include <unordered_map>
#include "RedlandAPIWrapper.h"
#include "semsim/SemsimUtils.h"
#include "Editor.h"

using namespace redland;

namespace semsim {


    class RDF {
        LibrdfStorage storage_;
        LibrdfModel model_;

        typedef std::unordered_map<std::string, std::string> NamespaceMap;

    public:
        std::string base_uri_;
        NamespaceMap namespaces_;
        std::vector<std::string> seen_namespaces_;
        NamespaceMap default_namespaces_ = {
                {"http://purl.org/dc/terms/",                "dcterms"},
                {"http://biomodels.net/biology-qualifiers/", "bqbiol"},
                {"http://biomodels.net/model-qualifiers/",   "bqmodel"},
                {"http://www.bhi.washington.edu/semsim#",    "semsim"},
        };

        explicit RDF(const std::string &base_uri = "./Annotations.rdf", const std::string &storage_type = "memory",
                     const std::string &storage_name = "SemsimStore",
                     const char *storage_options = nullptr, const char *model_options = nullptr);

        int size() const;

        void setBaseUri(std::string baseUri);

        bool empty();

        static RDF fromString(const std::string &str,
                              const std::string &format = "guess",
                              const std::string &base_uri = std::string());

        std::unordered_map<std::string, std::string>
        propagateNamespacesFromParser(std::vector<std::string> seen_namespaces);

        std::string toString(const std::string &format = "rdfxml-abbrev", const std::string &base_uri = std::string(),
                             const char *mime_type = nullptr, const char *type_uri = nullptr);

        Editor toEditor(std::string xml, SemsimXmlType type);

        librdf_model* getModel() const;
    };
}

#endif //LIBSEMSIM_RDF_H
