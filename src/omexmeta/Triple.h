//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBOMEXMETA_Triple22_H
#define LIBOMEXMETA_Triple22_H

#include "LibrdfNode.h"
#include "LibrdfStatement.h"
#include "omexmeta/Predicate.h"
#include "omexmeta/Subject.h"
#include "omexmeta/Resource.h"
#include "omexmeta/Triple.h"
//#include "omexmeta/Triple2Writer.h"
#include "librdf.h"
#include "raptor2.h"

#include <ostream>
#include <utility>
#include <algorithm>
#include <cstring>
#include <assert.h>


using namespace redland;

/*
 * should inherit from librdf_statement?
 */

namespace omexmeta {

    class Triple : public LibrdfStatement {

        Triple(librdf_statement *statement);


    public:

        using LibrdfStatement::LibrdfStatement;
        using LibrdfStatement::operator=;

        explicit Triple() = default;

        Triple(const Subject &subject, const PredicatePtr &predicate_ptr, const Resource &resource);

        Triple(librdf_node *subject, librdf_node *predicate, librdf_node *resource);

        static Triple fromRawStatementPtr(librdf_statement *statement);

        /*
         * @brief serialize the triple using a @format serializer.
         *
         * Creates an isolated serializer that does not get added
         * to the users annotations. This method is for visualizing
         * a triple only.
         */
        std::string str(const std::string &format = "rdfxml-abbrev",
                const std::string &base = (std::filesystem::current_path() /=  "annotations.rdf").string(),
                std::string omex_name = "myOmex.omex",
                std::string model_name = "myOmexModel.xml") const;

        void freeTriple();

        Triple &setAbout(const std::string& omex_name, const std::string& model_name, const std::string &metaid);

        std::string getAbout() const;

        librdf_statement *getStatement() const;

        Triple &setPredicate(const std::string &namespace_, const std::string &term);

        Triple &setResourceLiteral(const std::string &literal);

        Triple &setResourceUri(const std::string &identifiers_uri);

        Triple &setResourceBlank(const std::string &blank_id);

        bool isEmpty();

        Triple &setPredicate(const std::string &uri);

        void freeTripleAndUris();

        Triple &setAbout(const std::string &metaid);
    };

    typedef Triple SingularAnnotation;
}

#endif //LIBOMEXMETA_Triple22_H
