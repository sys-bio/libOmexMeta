//
// Created by Ciaran on 09/11/2020.
//

#ifndef LIBOMEXMETA_URIHANDLER_H
#define LIBOMEXMETA_URIHANDLER_H

#include "OmexMetaUtils.h"
#include <iostream>
#include "omexmeta/Error.h"
#include <exception>

namespace omexmeta {
    enum eUriType {
        NONE,
        LOCAL_URI,
        MODEL_URI,
        IDENTIFIERS_URI
    };

    class UriHandler {
    public:
        UriHandler() = default;

        /**
         * @brief getter for repository uri.
         * @details default is "http://omex-library.org/"
         */
        [[nodiscard]] const std::string &getRepositoryUri() const;

        /**
         * @brief setter for repository uri.
         * @details default is "http://omex-library.org/"
         */
        UriHandler &setRepositoryUri(const std::string &repository);

        /**
         * @brief getter for archive uri.
         * @details default is"NewOmex.omex" which produces
         * the full uri "http://omex-library.org/NewOmex.omex/"
         * when assembled
         */
        [[nodiscard]] const std::string &getArchiveUri() const;

        /**
         * @brief setter for archive uri.
         * @details default is"NewOmex.omex" which produces
         * the full uri "http://omex-library.org/NewOmex.omex/"
         * when assembled
         */
        UriHandler &setArchiveUri(const std::string &archive);

        /**
         * @brief getter for model uri.
         * @details default is"NewModel.xml" and produces
         * the full uri "http://omex-library.org/NewOmex.omex/NewModel.xml#"
         * when assembled
         */
        [[nodiscard]] const std::string &getModelUri() const;

        /**
         * @brief setter for model uri.
         * @details default is"NewModel.xml" and produces
         * the full uri "http://omex-library.org/NewOmex.omex/NewModel.xml"
         * when assembled
         */
        UriHandler &setModelUri(std::string model);

        /**
         * @brief getter for local uri.
         * @details default is"NewModel.rdf" and produces
         * the full uri "http://omex-library.org/NewOmex.omex/NewModel.rdf#"
         * when assembled. There is no setter for local_uri_ because
         * it'll take on the name of model_uri_ with the "xml" extension
         * replaced with "rdf"
         */
        [[nodiscard]] const std::string &getLocalUri() const;

        /**
         * @brief getter for model metaid. This is used in model level annotations
         */
        const std::string &getModelMetaid() const;

        /**
         * @brief get the full uri for model level annotations.
         * @details the modelUri concatonated with the model metaid fragment
         */
         std::string getModelLevelAnnotationUri();

        /**
         * @brief setting for model metaid. This is used in model level annotations
         */
        UriHandler& setModelMetaid(const std::string &modelMetaid);

        [[nodiscard]] std::string uriModifier(std::string uri_to_modify, eUriType type) const;

        template<class T>
        static std::string uriModifier(T &cls, std::string uri_to_modify, eUriType type) {
            // When uri_to_modify equals model or local uri, we throw.
            if (
                    uri_to_modify == cls.getLocalUri() ||
                    uri_to_modify == cls.getLocalUri() + "#" ||
                    uri_to_modify == cls.getModelUri() ||
                    uri_to_modify == cls.getModelUri() + "#") {
                throw std::logic_error("std::string uriModifier: Cannot modify input string: \"" + uri_to_modify + "\"");
            }
            // When we already have a uri that is not local or model uri, we just return
            if (OmexMetaUtils::startsWith(uri_to_modify, "http")) {
                return uri_to_modify;
            }
            switch (type) {
                case NONE: {
                    return uri_to_modify;
                }
                case LOCAL_URI: {
                    if (cls.getLocalUri().empty()) {
                        throw std::logic_error("UriHandler::uriModifier(): Cannot create local uri for string \"" + uri_to_modify + "\"as local uri is empty");
                    }
                    return OmexMetaUtils::concatMetaIdAndUri(uri_to_modify, cls.getLocalUri());
                }
                case MODEL_URI: {
                    if (cls.getModelUri().empty())
                        throw std::logic_error("UriHandler::uriModifier(): Cannot create model uri for string \"" + uri_to_modify + "\"as local uri is empty");
                    return OmexMetaUtils::concatMetaIdAndUri(uri_to_modify, cls.getModelUri());
                }
                case IDENTIFIERS_URI: {
                    return "https://identifiers.org/" + uri_to_modify;
                }
                default: {
                    throw std::invalid_argument("std::string uriModifier: Unrecognized eUriType");
                }
            }
        }
        bool operator==(const UriHandler &rhs) const;

        bool operator!=(const UriHandler &rhs) const;

    private:
        /*
         * Users set these values which are built with the getter values.
         * This ensures that when one of these values change, the
         * others get updated.
         */
        std::string repository_uri_ = "http://omex-library.org/";
        std::string archive_uri_ = repository_uri_ + "NewOmex.omex/";
        std::string model_uri_ = archive_uri_ + "NewModel.xml";
        std::string local_uri_ = archive_uri_ + "NewModel.rdf#";
        std::string model_metaid_ = "NewModel"; // should be changed by client code.

    };


}// namespace omexmeta

#endif//LIBOMEXMETA_URIHANDLER_H
