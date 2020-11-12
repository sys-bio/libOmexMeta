//
// Created by Ciaran on 09/11/2020.
//

#ifndef LIBOMEXMETA_URIHANDLER_H
#define LIBOMEXMETA_URIHANDLER_H

#include <iostream>

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
        [[nodiscard]] const std::string &getRepository() const;

        /**
         * @brief setter for repository uri.
         * @details default is "http://omex-library.org/"
         */
        UriHandler &setRepository(const std::string &repository);

        /**
         * @brief getter for archive uri.
         * @details default is"NewOmex.omex" which produces
         * the full uri "http://omex-library.org/NewOmex.omex/"
         * when assembled
         */
        [[nodiscard]] const std::string &getArchive() const;

        /**
         * @brief setter for archive uri.
         * @details default is"NewOmex.omex" which produces
         * the full uri "http://omex-library.org/NewOmex.omex/"
         * when assembled
         */
        UriHandler &setArchive(const std::string &archive);

        /**
         * @brief getter for model uri.
         * @details default is"NewModel.xml" and produces
         * the full uri "http://omex-library.org/NewOmex.omex/NewModel.xml#"
         * when assembled
         */
        [[nodiscard]] const std::string &getModel() const;

        /**
         * @brief setter for model uri.
         * @details default is"NewModel.xml" and produces
         * the full uri "http://omex-library.org/NewOmex.omex/NewModel.xml#"
         * when assembled
         */
        UriHandler &setModel(std::string model);

        /**
         * @brief getter for local uri.
         * @details default is"NewModel.rdf" and produces
         * the full uri "http://omex-library.org/NewOmex.omex/NewModel.rdf#"
         * when assembled. There is no setter for local_uri_ because
         * it'll take on the name of model_uri_ with the "xml" extension
         * replaced with "rdf"
         */
        [[nodiscard]] const std::string &getLocal() const;

        [[nodiscard]] std::string uriModifier(std::string uri_to_modify, eUriType type) const;

        template<class T>
        static std::string uriModifier(T cls, std::string uri_to_modify, eUriType type) {
            std::cout << "uri_to_modify: " << uri_to_modify << std::endl;
            switch (type) {
                case NONE: {
                    return uri_to_modify;
                }
                case LOCAL_URI: {
                    std::cout << "cls.getLocalUri(): " << cls.getLocalUri() << "empty?: " << cls.getLocalUri().empty()  << std::endl;
                    if (cls.getLocalUri().empty()) {
                        throw std::logic_error("UriHandler::uriModifier(): Cannot create local uri for string \"" + uri_to_modify + "\"as local uri is empty");
                    }
                    std::cout << "local uuri: " << cls.getLocalUri() << std::endl;
                    return OmexMetaUtils::concatMetaIdAndUri(uri_to_modify, cls.getLocalUri());
                }
                case MODEL_URI: {
                    if (cls.getModelUri().empty())
                        throw std::logic_error("UriHandler::uriModifier(): Cannot create model uri for string \"" + uri_to_modify + "\"as local uri is empty");
                    return OmexMetaUtils::concatMetaIdAndUri(uri_to_modify, cls.getModelUri());
                }
                case IDENTIFIERS_URI: {
                    return OmexMetaUtils::concatMetaIdAndUri(uri_to_modify, "https://identifiers.org/");
                }
            }
        }


    private:
        /*
         * Users set these values which are built with the getter values.
         * This ensures that when one of these values change, the
         * others get updated.
         */
        std::string repository_ = "http://omex-library.org/";
        std::string archive_ = repository_ + "NewOmex.omex/";
        std::string model_ = archive_ + "NewModel.xml";
        std::string local_ = archive_ + "NewModel.rdf#";
    };


    //    std::string UriFactory();
}// namespace omexmeta

#endif//LIBOMEXMETA_URIHANDLER_H
