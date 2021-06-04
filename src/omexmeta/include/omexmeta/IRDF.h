//
// Created by Ciaran on 5/31/2020.
//

#ifndef LIBOMEXMETA_IRDF_H
#define LIBOMEXMETA_IRDF_H

#include "omexmeta/Editor.h"
#include "redland/RedlandAPI.h"

using namespace redland;

namespace omexmeta {

    class Editor; // fwd

    /**
     * @brief public interface for RDF types.
     *
     * @details for developers. This interface was introduced ad-hoc for the
     * sake of being able to mock RDF in test classes. It is therefore
     * expected that the interface segregation principle is broken here.
     * However, it is unlikely that we'll have need for another RDF class - if we
     * do, then we'll rethink the design of this interface.
     */
    class IRDF {

    public:
        virtual OmexMetaXmlType getXmlType() const = 0;
        virtual void setXmlType(OmexMetaXmlType xmlType) = 0;
        virtual const std::string &getRepositoryUri() const = 0;
        virtual void setRepositoryUri(const std::string &repositoryName) = 0;
        virtual const std::string &getArchiveUri() const = 0;
        virtual void setArchiveUri(const std::string &archiveName) = 0;
        virtual const std::string &getModelUri() const = 0;
        virtual void setModelUri(std::string modelName) = 0;
        virtual const std::string &getLocalUri() const = 0;
        virtual int size() const = 0;
        virtual bool empty() const = 0;
        virtual void addFromString(const std::string &str, const std::string &syntax = "guess") = 0;
        virtual void addFromUri(const std::string &uri_string, const std::string &syntax = "guess") = 0;
        virtual void addFromFile(const std::string &filename, const std::string &syntax) = 0;
        virtual std::unordered_map<std::string, std::string> propagateNamespacesFromParser(const std::vector<std::string> &seen_namespaces) = 0;
        virtual std::string toString(const std::string &syntax = "turtle", const char *mime_type = nullptr, const char *type_uri = nullptr) = 0;
        virtual void toFile(const std::string &filename, const std::string &syntax = "turtle", const char *mime_type = nullptr, const char *type_uri = nullptr) = 0;
        virtual Editor toEditor(const std::string &xml, bool generate_new_metaids = false, bool sbml_semantic_extraction = true) = 0;
        virtual Editor *toEditorPtr(const std::string &xml, bool generate_new_metaids = false, bool sbml_semantic_extraction = true) = 0;
        virtual librdf_model *getModel() const = 0;
        virtual librdf_storage *getStorage() const = 0;
        virtual int commitTransaction() const = 0;
        virtual int startTransaction() const = 0;
        virtual void *getTransactionHandle() const = 0;
        virtual int startTransactionWithHandle(void *handle) const = 0;
        virtual int getTransactionRollback() const = 0;
        virtual std::string queryResultsAsString(const std::string &query_str, const std::string &results_syntax) const = 0;
        virtual ResultsMap queryResultsAsMap(const std::string &query_str) const = 0;
        virtual void addTriple(const Triple &triple) = 0;
        virtual void addTriples(Triples &triples) = 0;
        virtual UriHandler &getUriHandler() = 0;
    };
}// namespace omexmeta

#endif//LIBOMEXMETA_IRDF_H
