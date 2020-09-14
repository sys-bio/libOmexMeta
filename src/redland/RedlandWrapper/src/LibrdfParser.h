//
// Created by Ciaran on 5/20/2020.
//

#ifndef LIBOMEXMETA_LIBRDFPARSER_H
#define LIBOMEXMETA_LIBRDFPARSER_H


#include "librdf.h"
#include <memory>

#include "World.h"
#include "LibrdfNode.h"
#include "LibrdfUri.h"
#include "LibrdfModel.h"

namespace redland {

    class LibrdfParser {

        librdf_parser *parser_ = nullptr;

        void validateParserName() const;

        std::string format_ = std::string();
        std::string mime_type_ = std::string();
        librdf_uri *type_uri_ = nullptr;

    public:
        LibrdfParser() = default;

        ~LibrdfParser();

        LibrdfParser(const LibrdfParser &parser) = delete;

        LibrdfParser(LibrdfParser &&parser) noexcept;

        LibrdfParser &operator=(const LibrdfParser &parser) = delete;

        LibrdfParser &operator=(LibrdfParser &&parser) noexcept;

        explicit LibrdfParser(librdf_parser *parser);

        explicit LibrdfParser(std::string format, std::string mime_type = std::string(),
                              const std::string& type_uri = std::string());

        [[nodiscard]] librdf_parser *get() const;

        [[nodiscard]] int numNamespacesSeen() const;

        [[nodiscard]] std::string getNamespacesSeenUri(int index) const;

        /*
         *
         * For developers. This method should be deprecated
         * and replaced with the other signature for this function. It is
         * better because the user does not need to remember to free the Uri used.
         */
        void parseString(const std::string &rdf_string, const LibrdfModel &model, const LibrdfUri &base_uri) const;

        void parseString(const std::string &rdf_string, const LibrdfModel &model, const std::string &base_uri) const;

        /*
         * @brief parse a file into rdf graph. Use local_uri as base uri.
         * @param filename_uri location of filename on disk
         * @param model the current LibrdfModel
         */
        void parseFile(const std::string &filename_uri, const LibrdfModel &model, const std::string &local_uri) const;

        /*
         * @brief parse a file into rdf graph. Use filename as base url
         * @param filename_uri location of filename on disk
         * @param model the current LibrdfModel
         * @param local_uri the uri to use for base.
         * @details This version of parse file is preferred as it will take
         * the local uri from RDF object and use it for the base.
         */
        void parseFile(const std::string &filename_uri, const LibrdfModel &model) const;

        void parseUri(const std::string &uri_string, const LibrdfModel &model) const;

        [[nodiscard]] std::string getNamespacesSeenPrefix(int index) const;

        [[nodiscard]] std::string getName() const;

        void setName(const char *name);

        [[nodiscard]] std::string getMimeType() const;

        void setMimeType(const char *mimeType);

        [[nodiscard]] librdf_uri *getTypeUri() const;

        void setTypeUri(librdf_uri *typeUri);

        void setTypeUri(const std::string &type_uri);

        librdf_parser *makeParser();

        static void setFeature(librdf_parser *parser, const std::string &feature_uri, librdf_node *node);

        static void setOption(librdf_parser *parser, const std::string &option, const std::string &value);

        static void setOptions(librdf_parser *parser);

        [[nodiscard]] std::vector<std::string> getSeenNamespaces(std::vector<std::string> namespaces) const;


    };
}


#endif //LIBOMEXMETA_LIBRDFPARSER_H
