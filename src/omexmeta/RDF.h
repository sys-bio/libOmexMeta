//
// Created by Ciaran on 5/31/2020.
//

#ifndef LIBOMEXMETA_RDF_H
#define LIBOMEXMETA_RDF_H

#include <unordered_map>
#include "RedlandAPIWrapper.h"
#include "omexmeta/SemsimUtils.h"
#include "Editor.h"

using namespace redland;

namespace omexmeta {

    class RDF {
        LibrdfStorage storage_;
        LibrdfModel model_;

        typedef std::unordered_map<std::string, std::string> NamespaceMap;

    public:
        NamespaceMap namespaces_;
        std::vector<std::string> seen_namespaces_;
        const std::string myomexlib_ = "http://myOmexLibrary.org/";

        // todo remove this field and replace with the one
        //  in Predicate. Should be a simple swap.
        NamespaceMap default_namespaces_ = Predicate::namespaceMap();

        explicit RDF(const std::string &storage_type = "memory",
                     const std::string &storage_name = "SemsimStore",
                     const char *storage_options = nullptr, const char *model_options = nullptr);

        void freeRDF();

        ~RDF();

        RDF(const RDF &rdf) = delete;

        RDF(RDF &&rdf) noexcept;

        RDF &operator=(const RDF &rdf) = delete;

        RDF &operator=(RDF &&rdf) noexcept;

        int size() const;

        bool empty() const;

        /*
         * @brief instantiate an RDF instance and read
         * annotations from a string. This is a static method.
         * @param str a reference to the string containing annotations
         * @param format which format str is in. Default="guess" : try to guess.
         * @param base_uri the uri that all subject uri's are relative to. Defaults to ./Annotations.rdf.
         *
         * @details The base_uri argument is required when parsing from a string
         * because there is nothing to find one automatically (like there is
         * when parsing from filename or uri).
         */
        static RDF fromString(const std::string &str,
                              const std::string &format = "guess",
                              const std::string &base_uri = "Annotations.rdf");

        /*
         * @brief non-static variant of RDF::fromString(). Reads rdf into
         * an RDF instance. See RDF::fromString() for argument requirements.
         */
        void addFromString(const std::string &str,
                           const std::string &format = "guess",
                           const std::string &base_uri = "Annotations.rdf");

        /*
         * @brief parse RDF directly from a uri
         * @param uri_string the uri to download containing RDF
         * @param format the format that the RDF is in
         * @return RDF an instantiated RDF object.
         *
         * @details downloads uri from the internet and creates an RDF graph.
         * See Librdf::parseUri() for more details.
         */
        static RDF fromUri(const std::string &uri_string, const std::string &format = "guess");

        /*
         * @brief non-static counterpart of RDF::fromUri. Downloads and
         * parses rdf from a URI.
         *
         * @details See RDF::fromUri for details.
         */
        void addFromUri(const std::string &uri_string, const std::string &format = "guess");

        /*
         * @brief read rdf from annotations in a file
         * @param filename the filename to read as string
         * @param format the format of the RDF in filename
         * @return an instantiated RDF object
         * @details Uses LibrdfParser::fromFile under the hood
         */
        static RDF fromFile(const std::string &filename, const std::string &format);

        /*
         * @brief non-static counter part of RDF::fromFile. Reads rdf from annotations in a file
         * @param filename the filename to read as string
         * @param format the format of the RDF in filename
         * @return an instantiated RDF object
         * @details Uses LibrdfParser::fromFile under the hood
         */
        void addFromFile(const std::string &filename, const std::string &format);

        /*
         * @brief non static version of RDF::fromString that takes
         * a * RDF pointer object and modifies in place.
         *
         * @details Primarily used for C API
         * For developers: look into replacing this function
         * fully with RDF::addFromString() method.
         *
         */
        static void
        fromString(RDF *rdf, const std::string &str, const std::string &format,
                   std::string base_uri = "Annotations.rdf");

        /*
         * @brief compared namespaces seen with namespaces
         * known and ensures models that use a known namespace
         * use that namespace.
         * @param seen_namespaces a vector of strings of namespaces the parser has seen before.
         *
         */
        std::unordered_map<std::string, std::string>
        propagateNamespacesFromParser(const std::vector<std::string> &seen_namespaces);

//        std::string toString(const std::string &format = "rdfxml-abbrev", std::string base_uri = std::string(),
//                             const char *mime_type = nullptr, const char *type_uri = nullptr);

        std::string toString(const std::string &format = "rdfxml-abbrev", const std::string& model_name = "MyModel",
                             std::string base_uri = std::string(),
                             const char *mime_type = nullptr, const char *type_uri = nullptr);


        Editor toEditor(const std::string &xml, SemsimXmlType type);

        Editor *toEditorPtr(const std::string &xml, SemsimXmlType type);

        librdf_model *getModel() const;

        librdf_storage *getStorage() const;

        int commitTransaction() const;

        int startTransaction() const;

        void *getTransactionHandle() const;

        int startTransactionWithHandle(void *handle) const;

        int getTransactionRollback() const;

        static std::ostringstream listOptions();
    };
}

#endif //LIBOMEXMETA_RDF_H
