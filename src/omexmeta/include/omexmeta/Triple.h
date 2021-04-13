//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBOMEXMETA_Triple22_H
#define LIBOMEXMETA_Triple22_H

#include "redland/librdf.h"
#include "redland/raptor2.h"

#include "redland/LibrdfNode.h"
#include "redland/LibrdfStatement.h"

#include "omexmeta/Predicate.h"
#include "omexmeta/Resource.h"
#include "omexmeta/Subject.h"
#include "omexmeta/Triple.h"
#include "omexmeta/UriHandler.h"

#include <algorithm>
#include <assert.h>
#include <cstring>
#include <ostream>
#include <utility>


using namespace redland;

/**
     * should inherit from librdf_statement?
 */

namespace omexmeta {

    class Triple : public LibrdfStatement {

    public:
        using LibrdfStatement::LibrdfStatement;
        using LibrdfStatement::operator=;

        explicit Triple() = default;

        Triple(const Subject &subject, const PredicatePtr &predicate_ptr, const Resource &resource);

        Triple(librdf_node *subject, librdf_node *predicate, librdf_node *resource);

        static Triple fromRawStatementPtr(librdf_statement *statement);

        const std::string &getLocalUri() const;

        /**
         * @brief set the local_uri_ attribute for this triple
         */
        void setLocalUri(std::string localUri);

        /**
         * @brief set the model_uri_ attribute for this triple
         */
        void setModelUri(const std::string &model_uri);

        /**
         * @brief serialize the triple using a @format serializer.
         *
         * Creates an isolated serializer that does not get added
         * to the users annotations. This method is for visualizing
         * a triple only.
         */
        [[deprecated("Use main RDF class to serialize triple objects")]] std::string str(const std::string &format = "turtle",
                        const std::string &base = (std::filesystem::current_path() /= "annotations.rdf").string(),
                        std::string omex_name = "NewOmex.omex/",
                        std::string model_name = "NewModel.xml") const;

        void freeTriple();

        Triple &about(std::string omex_name, const std::string &model_name, std::string metaid);

        Triple &about(std::string metaid);

        Triple &about(std::string metaid, eUriType uri_type);

        std::string getAbout() const;

        librdf_statement *getStatement() const;

        Triple &setPredicate(const std::string &namespace_, const std::string &term);

        /**
         * @brief alias for setPredicate
         */
        Triple &predicate(const std::string &namespace_, const std::string &term);

        Triple &setResourceLiteral(const std::string &literal);

        Triple &setResourceUri(const std::string &identifiers_uri);

        Triple &setResourceBlank(const std::string &blank_id);

        bool isEmpty();

        Triple &setPredicate(const std::string &uri);

        Triple &predicate(const std::string &uri);

        void freeTripleAndUris();

        //        Triple &about(const std::string &metaid);

        const std::string &getModelUri() const;

        Triple &setResourceWithModelUri(const std::string &metaid);

        Triple &resourceWithModelUri(const std::string &metaid);

        Triple &resourceLiteral(const std::string &literal);

        Triple &resourceUri(const std::string &identifiers_uri);

        Triple &resourceBlank(const std::string &blank_id);

        void setUriHandler(UriHandler& uriHandler);

    private:
        Triple(librdf_statement *statement);

        /**
         * Developers note: This *should* really be a reference. However, in order
         * to construct a Triple with a UriHandler reference we need to inject
         * the UriHandler instance into the constructor. This in turn probably
         * necessitates a "newTriple" method in RDF for creating the Triple object
         * which would pass the UriHandler reference to the Triple behind the scenes.
         * At present, we just use setUriHandler to give this Triple the correct
         * UriHandler when needed, which is a worse solution because of the need to
         * remember to call setUriHandler. However, its already implemented and working ...
         */
        UriHandler uriHandler_;
    };

    typedef Triple SingularAnnotation;
}// namespace omexmeta

#endif//LIBOMEXMETA_Triple22_H
