//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBSEMSIM__TRIPLE_H
#define LIBSEMSIM__TRIPLE_H

#include "LibrdfNode.h"
#include "LibrdfStatement.h"
#include "semsim/Predicate.h"
#include "semsim/Subject.h"
#include "semsim/Resource.h"
#include "semsim/_Triple.h"
//#include "semsim/TripleWriter.h"
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

    class _Triple {
    protected:
        Subject subject_;
        PredicatePtr predicate_ptr_;
        Resource resource_;
    public:

        explicit _Triple() = default;

        _Triple(Subject subject, PredicatePtr predicate_ptr, Resource resource);

        _Triple(Subject subject, Predicate predicate, Resource resource);

//        void setSubject(const Subject &subject);
//
//        void setPredicatePtr(const PredicatePtr &predicatePtr);
//
//        void setResource(const Resource &resource);

        std::string getSubjectStr() const;

        std::string getPredicateStr() const;

        std::string getResourceStr() const;

        librdf_statement * toStatement();

        static _Triple fromStatement(LibrdfStatement statement);

//        std::string str(std::string format = "rdfxml-abbrev", std::string base = "file://./annotations.rdf");


//        _Triple &setAbout(const std::string &about);

        /*
         * Factory returning Prdicate of type namespace_ and
         * term of type term.
         */
//        _Triple &setPredicate(const std::string &namespace_, const std::string &term);
//
//        _Triple &setPredicateNew(
//                const std::string &namespace_, const std::string &term, const std::string &prefix);
//
//        _Triple &setResourceLiteral(const std::string &literal);
//
//        _Triple &setResourceUri(const std::string &identifiers_uri);
//
//        _Triple &setResourceBlank(const std::string &blank_id);
//
//        std::string getAbout() const;

        void checkForNull();
    };

    typedef _Triple SingularAnnotation;
}

#endif //LIBSEMSIM__TRIPLE_H
