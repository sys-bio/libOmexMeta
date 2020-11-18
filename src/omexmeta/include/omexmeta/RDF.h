//
// Created by Ciaran on 5/31/2020.
//

#ifndef LIBOMEXMETA_RDF_H
#define LIBOMEXMETA_RDF_H

#include "redland/RedlandAPI.h"


#include "omexmeta_export.h"
#include "omexmeta/OmexMetaXmlType.h"

#include <streambuf>
#include <unordered_map>
#include <utility>
#include <fstream>

#include "omexmeta/Editor.h"
#include "omexmeta/MarkupIdentifier.h"
#include "omexmeta/OmexMetaUtils.h"
#include "omexmeta/SBMLSemanticExtraction.h"
#include "omexmeta/logger.h"
#include "omexmeta/UriHandler.h"


using namespace redland;

namespace omexmeta {

    // forward declarations
    class Editor;
    class MarkupIdentifier;
    class OmexMetaUtils;
    class SBMLSemanticExtraction;
    class Predicate;


    class OMEXMETA_EXPORT RDF {
        LibrdfStorage storage_;
        LibrdfModel model_;

        OmexMetaXmlType xmlType = OMEXMETA_TYPE_NOTSET;

        typedef std::unordered_map<std::string, std::string> NamespaceMap;

        UriHandler uriHandler_;

//        std::string repository_uri_ = "http://omex-library.org/";
//        std::string archive_uri_ = repository_uri_ + "NewOmex.omex/";
//        std::string model_uri_ = archive_uri_ + "NewModel.xml";
//        std::string local_uri_ = archive_uri_ + "NewModel.rdf#";

        /**
         * @brief autoset the xmlType variable based on xml content.
         */
        void classifyXmlType(const std::string& xml, const std::string& input_format);

        /**
         * @brief reads xml from file before calling classifyXmlType
         */
        void classifyXmlTypeFromFile(const std::string &xml_file, const std::string &input_format);

        /**
         * @brief pull semantic information out of the sbml
         *  int the RDF graph
         */
        void extractSemanticInformationFromSBML(const std::string& sbml);

        /**
         * @brief release memory consumed by RDF.
         * @details Memory consumed by RDF is destructed using RAII
         * so users normally do not need this function.
         */
        void freeRDF();

    public:
        NamespaceMap namespaces_;
        std::vector<std::string> seen_namespaces_;
        const std::string OMEXlib_ = "http://OMEXlibrary.org/";

        /**
         * @brief getter for xmlType attribue.
         * @details when the rdf graph is sbml, it
         * will return OMEXMETA_TYPE_SBML. When cellML
         * it will return OMEXMETA_TYPE_CELLML. Otherwise
         * it is OMEXMETA_TYPE_UNKNOWN.
         */
        OmexMetaXmlType getXmlType() const;
        bool operator==(const RDF &rhs) const;
        bool operator!=(const RDF &rhs) const;
        /**
         * @brief set the xml type for the current graph.
         * @details If you have been reading from an SBML you cannot
         * then read from another format (such as cellml).
         */
        void setXmlType(OmexMetaXmlType xmlType);

        /**
         * @brief getter for repository uri which defaults
         * to "http://omex-library.org/"
         */
        const std::string &getRepositoryUri() const;

        /**
         * @brief setter for the repository uri which
         * defaults to "http://omex-library.org/".
         * @param repositoryName the repository uri.
         */
        void setRepositoryUri(const std::string& repositoryName);

        /**
         * @brief getter for archiveUri attribute.
         * @details default to http://omex-library.org/NewOmex.omex/
         */
        const std::string &getArchiveUri() const;

        /**
         * @brief setter for archiveUri attribute.
         * @param archiveName the new name for archive uri attribute
         * @details default to http://omex-library.org/NewOmex.omex/
         */
        void setArchiveUri(const std::string& archiveName);

        /**
         * @brief getter for model uri.
         * @details defaults to http://omex-library.org/NewOmex.omex/NewModel.xml
         */
        const std::string &getModelUri() const;

        /**
         * @brief setter for model uri.
         * @param modelName string for new model uri.
         * @details defaults to http://omex-library.org/NewOmex.omex/NewModel.xml
         */
        void setModelUri(std::string modelName);

        /**
         * @brief getter for local uri attribute.
         * @details defaults to http://omex-library.org/NewOmex.omex/NewModel.rdf#
         */
        const std::string &getLocalUri() const;
//
//        // todo remove this field and replace with the one
//        //  in Predicate. Should be a simple swap.
//        NamespaceMap default_namespaces_ = Predicate::namespaceMap();

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
        RDF(RDF &&rdf) noexcept;

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
        int size() const;

        /**
         * @brief indicator for whether the RDF graph is empty
         * @returns true if RDF graph has no triples, false otherwise.
         */
        bool empty() const;

        /**
         * @brief instantiate an RDF instance and read
         * annotations from a string. This is a static method.
         * @param str a reference to the string containing annotations
         * @param format which format str is in. Default="guess" : try to guess.
         */
        static RDF fromString(const std::string &str,
                              const std::string &format = "guess");

        /**
         * @brief non-static variant of RDF::fromString(). Reads rdf into
         * an RDF instance. See RDF::fromString() for argument requirements.
         */
        void addFromString(const std::string &str,
                           const std::string &format = "guess");

        /**
         * @brief parse RDF directly from a uri
         * @param uri_string the uri to download containing RDF
         * @param format the format that the RDF is in
         * @return RDF an instantiated RDF object.
         *
         * @details downloads uri from the internet and creates an RDF graph.
         * See Librdf::parseUri() for more details.
         */
        static RDF fromUri(const std::string &uri_string, const std::string &format = "guess");

        /**
         * @brief non-static counterpart of RDF::fromUri. Downloads and
         * parses rdf from a URI.
         *
         * @details See RDF::fromUri for details.
         */
        void addFromUri(const std::string &uri_string, const std::string &format = "guess");

        /**
         * @brief read rdf from annotations in a file
         * @param filename the filename to read as string
         * @param format the format of the RDF in filename
         * @return an instantiated RDF object
         * @details Uses LibrdfParser::fromFile under the hood
         */
        static RDF fromFile(const std::string &filename, const std::string &format);

        /**
         * @brief non-static counter part of RDF::fromFile. Reads rdf from annotations in a file
         * @param filename the filename to read as string
         * @param format the format of the RDF in filename
         * @return an instantiated RDF object
         * @details Uses LibrdfParser::fromFile under the hood
         */
        void addFromFile(const std::string &filename, const std::string &format);

        /**
         * @brief non static version of RDF::fromString that takes
         * a * RDF pointer object and modifies in place.
         *
         * @details Primarily used for C API
         * For developers: look into replacing this function
         * fully with RDF::addFromString() method.
         *
         */
        [[maybe_unused]] static void
        fromString(RDF *rdf, const std::string &str, const std::string &format,
                   std::string base_uri = "Annotations.rdf");

        /**
         * @brief compared namespaces seen with namespaces
         * known and ensures models that use a known namespace
         * use that namespace.
         * @param seen_namespaces a vector of strings of namespaces the parser has seen before.
         *
         */
        std::unordered_map<std::string, std::string>
        propagateNamespacesFromParser(const std::vector<std::string> &seen_namespaces);

        /**
         * @brief serialize RDF graph to string
         * @param format the expected output format. Options include:
         * "ntriples", "turtle", "rdfxml-xmp", "rdfxml-abbrev",
         * "rdfxml", "dot", "json-triples", "json", "nquads", "html".
         */
        std::string toString(const std::string &format = "turtle",
                             const char *mime_type = nullptr, const char *type_uri = nullptr);

        /**
         * @brief Write annotations to file
         * @param format the expected output format. Options include:
         * "ntriples", "turtle", "rdfxml-xmp", "rdfxml-abbrev",
         * "rdfxml", "dot", "json-triples", "json", "nquads", "html".
         * @param filename full path of file to write
         * @param mime_type optional valid mime
         * @param type_uri optional type uri
         *
         */
        void toFile(const std::string &filename, const std::string &format = "turtle", const char *mime_type = nullptr,
                    const char *type_uri = nullptr);

        /**
         * @brief instantiate an Editor object.
         * @param xml the xml you want to open for editing. This can be any type of xml document, but SBML and CellML are most common.
         * @param generate_new_metaids When true, will add metaids onto a copy of the xml source code for annotation. Default = false.
         * @param OmexMetaXmlType an indicator enum specifying whether the xml is sbml, cellml or unknown. Default is "OMEXMETA_TYPE_NOTSET"
         * @details
         */
        Editor toEditor(const std::string &xml, bool generate_new_metaids = false, bool sbml_semantic_extraction = true);

        Editor *toEditorPtr(const std::string &xml, bool generate_new_metaids = false, bool sbml_semantic_extraction = true);

        librdf_model *getModel() const;

        librdf_storage *getStorage() const;

        int commitTransaction() const;

        int startTransaction() const;

        void *getTransactionHandle() const;

        int startTransactionWithHandle(void *handle) const;

        int getTransactionRollback() const;

        static std::ostringstream listOptions();

        std::string query(const std::string &query_str, const std::string &results_format) const;

        /**
         * @brief add a Triple to the current model
         */
        void addTriple(const Triple &triple);

        /**
         * @brief add a set of Triples to the current model
         */
        void addTriples(const Triples &triples) ;

        /**
         * @brief test for equality between @param actual and @param expected
         */
        static bool equals(RDF *actual, const std::string &expected, const std::string &format = "turtle");

        /**
         * @brief test for equality between @param actual and @param expected
         */
        static bool equals(const Triple &actual, const std::string &expected, const std::string &format = "turtle");

        /**
         * @brief test for equality between @param actual and @param expected
         */
        static bool equals(const Triples &actual, const std::string &expected, const std::string &format = "turtle");

        /**
         * @brief test for equality between @param actual and @param expected
         */
        static bool equals(RDF *actual, RDF *expected, const std::string &format = "turtle");

        /**
         * @brief test for equality between @param first and @param second
         */
        static bool equals(const std::string &first, const std::string &second, const std::string &first_format = "turtle", const std::string &second_format = "turtle");

    };
}

#endif //LIBOMEXMETA_RDF_H
