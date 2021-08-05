//
// Created by Ciaran on 5/31/2020.
//

#ifndef LIBOMEXMETA_RDF_H
#define LIBOMEXMETA_RDF_H

#include "redland/RedlandAPI.h"

#include "omexmeta/OmexMetaXmlType.h"
#include "omexmeta_export.h"

#include <fstream>
#include <streambuf>
#include <unordered_map>
#include <utility>

#include "omexmeta/Editor.h"
#include "omexmeta/IRDF.h"
#include "omexmeta/MarkupIdentifier.h"
#include "omexmeta/OmexMetaUtils.h"
#include "omexmeta/SBMLSemanticExtraction.h"
#include "omexmeta/UriHandler.h"
#include "omexmeta/VCardTranslator.h"
#include "omexmeta/logger.h"


using namespace redland;

namespace omexmeta {

    typedef std::unordered_map<std::string, std::string> NamespaceMap;

    // forward declarations
    class Editor;
    class MarkupIdentifier;
    class OmexMetaUtils;
    class SBMLSemanticExtraction;
    class Predicate;
    class VCardTranslator;
    class PurgeRDFBag;

    class OMEXMETA_EXPORT RDF : public IRDF {

    public:
        /**
         * @brief constructor for RDF class
         * @param storage_type. Defaults to memory. Other options include:
         * "hashes", "file", "mysql", "postgresql", "sqlite", "uri",
         * @param storage_name name used for storage. When storage is not internally
         * held in memory, this becomes the name of the file or database.
         * @param storage_options options that get passed on to storage. Please
         * study http://librdf.org/docs/api/redland-storage-modules.html for
         * more information.
         * @model_options options that get passed to the model. Please see
         * http://librdf.org/docs/api/index.html for more details.
         */
        explicit RDF(const std::string &storage_type = "memory",
                     const std::string &storage_name = "SemsimStore",
                     const char *storage_options = nullptr, const char *model_options = nullptr);

        /**
         * @brief destructor for RDF
         */
        ~RDF();

        /**
         * @brief copy constructor for RDF class
         * @details RDF instances are not copyable
         * due to restrictions within the redland libraries.
         * You must instead move RDF objects.
         */
        RDF(const RDF &rdf) = delete;

        /**
         * @brief move constructor for RDF class
         */
        RDF(RDF &&rdf)
        noexcept;

        /**
         * @brief copy assignment constructor for RDF ojects
         * @details Copy assignment functionality is prohibited for RDF
         * objects. Use move semantics insead.
         */
        RDF &operator=(const RDF &rdf) = delete;

        /**
         * @brief move assignment operator for RDF
         */
        RDF &operator=(RDF &&rdf) noexcept;

        /**
         * @brief returns the number of triples currently present
         * in the RDF graph.
         */
        int size() const override;

        /**
         * @brief indicator for whether the RDF graph is empty
         * @returns true if RDF graph has no triples, false otherwise.
         */
        bool empty() const override;

        /**
         * @brief instantiate an RDF instance and read
         * annotations from a string. This is a static method.
         * @param str a reference to the string containing annotations
         * @param syntax which syntax str is in. Default="guess" : try to guess.
         */
        static RDF fromString(const std::string &str, const std::string &syntax = "guess");

        /**
         * @brief non-static variant of RDF::fromString(). Reads rdf into
         * an RDF instance. See RDF::fromString() for argument requirements.
         */
        void addFromString(const std::string &str, const std::string &syntax = "guess") override;

        /**
         * @brief parse RDF directly from a uri
         * @param uri_string the uri to download containing RDF
         * @param syntax the syntax that the RDF is in
         * @return RDF an instantiated RDF object.
         *
         * @details downloads uri from the internet and creates an RDF graph.
         * See Librdf::parseUri() for more details.
         */
        static RDF fromUri(const std::string &uri_string, const std::string &syntax = "guess");

        /**
         * @brief non-static counterpart of RDF::fromUri. Downloads and
         * parses rdf from a URI.
         *
         * @details See RDF::fromUri for details.
         */
        void addFromUri(const std::string &uri_string, const std::string &syntax = "guess") override;

        /**
         * @brief read rdf from annotations in a file
         * @param filename the filename to read as string
         * @param syntax the syntax of the RDF in filename
         * @return an instantiated RDF object
         * @details Uses LibrdfParser::fromFile under the hood
         */
        static RDF fromFile(const std::string &filename, const std::string &syntax);

        /**
         * @brief non-static counter part of RDF::fromFile. Reads rdf from annotations in a file
         * @param filename the filename to read as string
         * @param syntax the syntax of the RDF in filename
         * @return an instantiated RDF object
         * @details Uses LibrdfParser::fromFile under the hood
         */
        void addFromFile(const std::string &filename, const std::string &syntax) override;

        /**
         * @brief serialize RDF graph to string
         * @param syntax the expected output syntax. Options include:
         * "ntriples", "turtle", "rdfxml-xmp", "rdfxml-abbrev",
         * "rdfxml", "dot", "json-triples", "json", "nquads", "html".
         */
        std::string toString(const std::string &syntax = "turtle",
                             const char *mime_type = nullptr, const char *type_uri = nullptr) override;

        /**
         * @brief Write annotations to file
         * @param syntax the expected output syntax. Options include:
         * "ntriples", "turtle", "rdfxml-xmp", "rdfxml-abbrev",
         * "rdfxml", "dot", "json-triples", "json", "nquads", "html".
         * @param filename full path of file to write
         * @param mime_type optional valid mime
         * @param type_uri optional type uri
         *
         */
        void toFile(const std::string &filename, const std::string &syntax = "turtle", const char *mime_type = nullptr,
                    const char *type_uri = nullptr) override;

        /**
         * @brief instantiate an Editor object.
         * @param xml the xml you want to open for editing. This can be any type of xml document, but SBML and CellML are most common.
         * @param generate_new_metaids When true, will add metaids onto a copy of the xml source code for annotation. Default = false.
         * @param OmexMetaXmlType an indicator enum specifying whether the xml is sbml, cellml or unknown. Default is "OMEXMETA_TYPE_NOTSET"
         * @details
         */
        Editor toEditor(const std::string &xml, bool generate_new_metaids = false, bool sbml_semantic_extraction = true) override;

        /**
         * @brief instantiate an Editor object and return a new pointer to it. Memory
         * returned is owned by the caller and needs deleting.
         * @param xml the xml you want to open for editing. This can be any type of xml document, but SBML and CellML are most common.
         * @param generate_new_metaids When true, will add metaids onto a copy of the xml source code for annotation. Default = false.
         * @param OmexMetaXmlType an indicator enum specifying whether the xml is sbml, cellml or unknown. Default is "OMEXMETA_TYPE_NOTSET"
         * @details
         */
         Editor *toEditorPtr(const std::string &xml, bool generate_new_metaids = false, bool sbml_semantic_extraction = true) override;

        librdf_model *getModel() const override;

        librdf_storage *getStorage() const override;

        int commitTransaction() const override;

        int startTransaction() const override;

        void *getTransactionHandle() const override;

        int startTransactionWithHandle(void *handle) const override;

        int getTransactionRollback() const override;

        static std::ostringstream listOptions();

        std::string queryResultsAsString(const std::string &query_str, const std::string &results_syntax) const override;

        ResultsMap queryResultsAsMap(const std::string &query_str) const override;

        /**
         * @brief compared namespaces seen with namespaces
         * known and ensures models that use a known namespace
         * use that namespace.
         * @param seen_namespaces a vector of strings of namespaces the parser has seen before.
         *
         */
        std::unordered_map<std::string, std::string>
        propagateNamespacesFromParser(const std::vector<std::string> &seen_namespaces) override;

        /**
         * @brief getter for xmlType attribue.
         * @details when the rdf graph is sbml, it
         * will return OMEXMETA_TYPE_SBML. When cellML
         * it will return OMEXMETA_TYPE_CELLML. Otherwise
         * it is OMEXMETA_TYPE_UNKNOWN.
         */
        OmexMetaXmlType getXmlType() const override;
        bool operator==(const RDF &rhs) const;
        bool operator!=(const RDF &rhs) const;

        /**
         * @brief set the xml type for the current graph.
         * @details If you have been reading from an SBML you cannot
         * then read from another syntax (such as cellml).
         */
        void setXmlType(OmexMetaXmlType xmlType) override;

        /**
         * @brief getter for repository uri which defaults
         * to "http://omex-library.org/"
         */
        const std::string &getRepositoryUri() const override;

        /**
         * @brief setter for the repository uri which
         * defaults to "http://omex-library.org/".
         * @param repositoryName the repository uri.
         */
        void setRepositoryUri(const std::string &repositoryName) override;

        /**
         * @brief getter for archiveUri attribute.
         * @details default to http://omex-library.org/NewOmex.omex/
         */
        const std::string &getArchiveUri() const override;

        /**
         * @brief setter for archiveUri attribute.
         * @param archiveName the new name for archive uri attribute
         * @details default to http://omex-library.org/NewOmex.omex/
         */
        void setArchiveUri(const std::string &archiveName) override;

        /**
         * @brief getter for model uri.
         * @details defaults to http://omex-library.org/NewOmex.omex/NewModel.xml
         */
        const std::string &getModelUri() const override;

        /**
         * @brief setter for model uri.
         * @param modelName string for new model uri.
         * @details defaults to http://omex-library.org/NewOmex.omex/NewModel.xml
         */
        void setModelUri(std::string modelName) override;

        /**
         * @brief gets the uri fragment used for model level annotations. This must
         * be a valid metaid in your model and should be attached to a "model" element
         */
        const std::string &getModelMetaid() override;

        /**
         * @brief sets the uri fragment used for model level annotations. This must
         * be a valid metaid in your model and should be attached to a "model" element
         */
        void setModelMetaid(const std::string& modelMetaid) override;

        /**
         * @brief get the full uri for model level annotations.
         * @details the modelUri concatonated with the model metaid fragment
         */
        std::string getModelLevelAnnotationUri() override;
        /**
         * @brief getter for local uri attribute.
         * @details defaults to http://omex-library.org/NewOmex.omex/NewModel.rdf#
         */
        const std::string &getLocalUri() const override;

        /**
         * @brief add a Triple to the current model
         */
        void addTriple(const Triple &triple) override;

        /**
         * @brief add a set of Triples to the current model
         */
        void addTriples(Triples &triples) override;

        /**
         * @brief test for equality between @param actual and @param expected
         */
        static bool equals(RDF *actual, const std::string &expected, const std::string &syntax = "turtle", bool verbose = false);

        /**
         * @brief test for equality between @param actual and @param expected
         */
        static bool equals(const Triple &actual, const std::string &expected, const std::string &syntax = "turtle", bool verbose = false);

        /**
         * @brief test for equality between @param actual and @param expected
         */
        static bool equals(Triples &actual, const std::string &expected, const std::string &syntax = "turtle", bool verbose = false);

        /**
         * @brief test for equality between @param actual and @param expected
         */
        static bool equals(RDF *actual, RDF *expected, const std::string &syntax = "turtle", bool verbose = false);

        /**
         * @brief test for equality between @param first and @param second
         */
        static bool equals(const std::string &first, const std::string &second, const std::string &first_syntax = "turtle", const std::string &second_syntax = "turtle", bool verbose = false);

        UriHandler &getUriHandler() override;

        /**
         * @brief remove rdf:Bag constructs from the current rdf graph
         */
        void purgeRDFBag();

        /**
         * Translate VCARD into foaf
         */
        void translateVcard();

        /**
         * Storage for namespaces and prefixes
         */
        NamespaceMap namespaces_;

        /**
         * Part of the mechanism that propogates namespaces
         * through to serializer.
         *
         * todo observer pattern might make for more elegant design.
         */
        std::vector<std::string> seen_namespaces_;

        /**
         * Default repository uri
         */
        const std::string OMEXlib_ = "http://OMEXlibrary.org/";

    private:
        /**
         * @brief autoset the xmlType variable based on xml content.
         */
        void classifyXmlType(const std::string &xml, const std::string &input_syntax);

        /**
         * @brief reads xml from file before calling classifyXmlType
         */
        void classifyXmlTypeFromFile(const std::string &xml_file, const std::string &input_syntax);

        /**
         * @brief pull semantic information out of the sbml
         *  int the RDF graph
         */
        void extractSemanticInformationFromSBML(const std::string &sbml);

        /**
         * @brief release memory consumed by RDF.
         * @details Memory consumed by RDF is destructed using RAII
         * so users normally do not need this function.
         */
        void freeRDF();

        LibrdfStorage storage_;
        LibrdfModel model_;
        OmexMetaXmlType xmlType = OMEXMETA_TYPE_NOTSET;
        UriHandler uriHandler_;
    };
}// namespace omexmeta

#endif//LIBOMEXMETA_RDF_H
