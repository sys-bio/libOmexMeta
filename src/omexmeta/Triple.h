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
#include "omexmeta/Subject.h"
#include "omexmeta/Resource.h"
#include "omexmeta/Triple.h"

#include <ostream>
#include <utility>
#include <algorithm>
#include <cstring>
#include <assert.h>
#include <utility>


using namespace redland;

/*
 * should inherit from librdf_statement?
 */

namespace omexmeta {

    class Triple : public LibrdfStatement {

        Triple(librdf_statement *statement);
        std::string local_uri_; // like http:/omex-library.org/omex-archive.omex/model.rdf
        std::string model_uri_;

    public:

        using LibrdfStatement::LibrdfStatement;
        using LibrdfStatement::operator=;

        explicit Triple() = default;

        Triple(const Subject &subject, const PredicatePtr &predicate_ptr, const Resource &resource);

        Triple(librdf_node *subject, librdf_node *predicate, librdf_node *resource);

        static Triple fromRawStatementPtr(librdf_statement *statement);

        const std::string &getLocalUri() const;

        /*
         * @brief set the local_uri_ attribute for this triple
         */
        void setLocalUri(std::string localUri);

        /*
         * @brief set the model_uri_ attribute for this triple
         */
        void setModelUri(const std::string& model_uri);

        /*
         * @brief serialize the triple using a @format serializer.
         *
         * Creates an isolated serializer that does not get added
         * to the users annotations. This method is for visualizing
         * a triple only.
         */
        std::string str(const std::string &format = "turtle",
                const std::string &base = (std::filesystem::current_path() /=  "annotations.rdf").string(),
                std::string omex_name = "NewOmex.omex/",
                std::string model_name = "NewModel.xml#") const;

        void freeTriple();

        Triple &setAbout(std::string omex_name, const std::string& model_name, std::string metaid);

        Triple &setAbout(std::string metaid);

        std::string getAbout() const;

        librdf_statement *getStatement() const;

        Triple &setPredicate(const std::string &namespace_, const std::string &term);

        Triple &setResourceLiteral(const std::string &literal);

        Triple &setResourceUri(const std::string &identifiers_uri);

        Triple &setResourceBlank(const std::string &blank_id);

        bool isEmpty();

        Triple &setPredicate(const std::string &uri);

        void freeTripleAndUris();

//        Triple &setAbout(const std::string &metaid);

        const std::string &getModelUri() const;
    };

    typedef Triple SingularAnnotation;
}

#endif //LIBOMEXMETA_Triple22_H
