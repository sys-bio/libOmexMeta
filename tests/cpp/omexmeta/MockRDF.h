//
// Created by Ciaran Welsh on 04/06/2021.
//

#ifndef LIBOMEXMETA_MOCKRDF_H
#define LIBOMEXMETA_MOCKRDF_H

#include "gmock/gmock.h"
#include "omexmeta/IRDF.h"

using namespace omexmeta;
using namespace redland;

class MockRDF : public IRDF {
public:
    MOCK_METHOD(OmexMetaXmlType, getXmlType, (), (const, override));
    MOCK_METHOD(void, setXmlType, (OmexMetaXmlType xmlType), (override));
    MOCK_METHOD(const std::string &,getRepositoryUri, (), (const, override));
    MOCK_METHOD(void, setRepositoryUri, (const std::string &repositoryName), (override));
    MOCK_METHOD(const std::string &,getArchiveUri, (), (const, override));
    MOCK_METHOD(void, setArchiveUri, (const std::string &archiveName), (override));
    MOCK_METHOD(const std::string &,getModelUri, (), (const, override));
    MOCK_METHOD(void, setModelUri, (std::string modelName), (override));
    MOCK_METHOD(const std::string &,getLocalUri, (), (const, override));
    MOCK_METHOD(int, size, (), (const, override));
    MOCK_METHOD(bool, empty, (), (const, override));
    MOCK_METHOD(void, addFromString, (const std::string &str, const std::string &syntax), (override));
    MOCK_METHOD(void, addFromUri, (const std::string &uri_string, const std::string &syntax), (override));
    MOCK_METHOD(void, addFromFile, (const std::string &filename, const std::string &syntax), (override));
    MOCK_METHOD((std::unordered_map<std::string, std::string>), propagateNamespacesFromParser, (const std::vector<std::string> &seen_namespaces), (override));
    MOCK_METHOD(std::string, toString, (const std::string &syntax, const char *mime_type, const char *type_uri), (override));
    MOCK_METHOD(void, toFile, (const std::string &filename, const std::string &syntax, const char *mime_type, const char *type_uri), (override));
    MOCK_METHOD(Editor, toEditor, (const std::string &xml, bool generate_new_metaids, bool sbml_semantic_extraction), (override));
    MOCK_METHOD(Editor*, toEditorPtr, (const std::string &xml, bool generate_new_metaids, bool sbml_semantic_extraction), (override));
    MOCK_METHOD(librdf_model*, getModel, (), (const, override));
    MOCK_METHOD(librdf_storage*, getStorage, (), (const, override));
    MOCK_METHOD(int, commitTransaction, (), (const, override));
    MOCK_METHOD(int, startTransaction, (), (const, override));
    MOCK_METHOD(void *, getTransactionHandle, (), (const, override));
    MOCK_METHOD(int, startTransactionWithHandle, (void *handle), (const, override));
    MOCK_METHOD(int, getTransactionRollback, (), (const, override));
    MOCK_METHOD(std::string, queryResultsAsString, (const std::string &query_str, const std::string &results_syntax), (const, override));
    MOCK_METHOD(ResultsMap , queryResultsAsMap, (const std::string &query_str), (const, override));
    MOCK_METHOD(void, addTriple, (const Triple &triple), (override));
    MOCK_METHOD(void, addTriples, (Triples & triples), (override));
    MOCK_METHOD(UriHandler&, getUriHandler, (), (override));
};

#endif//LIBOMEXMETA_MOCKRDF_H
