//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBSEMSIM_Triple22_H
#define LIBSEMSIM_Triple22_H

#include "LibrdfNode.h"
#include "LibrdfStatement.h"
#include "semsim/Predicate.h"
#include "semsim/Subject.h"
#include "semsim/Resource.h"
#include "semsim/Triple.h"
//#include "semsim/Triple2Writer.h"
#include "librdf.h"
#include "raptor2.h"

#include <ostream>
#include <utility>
#include <algorithm>
#include <cstring>

using namespace redland;

/*
 * should inherit from librdf_statement?
 */

namespace semsim {

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
        std::string
        str(const std::string &format = "rdfxml-abbrev", const std::string &base = "file://./annotations.rdf");

        Triple &setAbout(const std::string &about);

        std::string getAbout() const;

        librdf_statement *getStatement() const;

        Triple &setPredicate(const std::string &namespace_, const std::string &term);

        Triple &setResourceLiteral(const std::string &literal);

        Triple &setResourceUri(const std::string &identifiers_uri);

        Triple &setResourceBlank(const std::string &blank_id);

        bool isEmpty();

        Triple &setPredicate(const std::string &uri);
    };

    typedef Triple SingularAnnotation;
}

#endif //LIBSEMSIM_Triple22_H
