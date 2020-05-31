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

    class Triple : public LibrdfStatement{
    protected:
//        Subject subject_;
//        PredicatePtr predicate_ptr_;
//        Resource resource_;
    public:

        explicit Triple() = default;

        Triple(const Subject& subject, const Predicate& predicate, const Resource& resource);

        Triple(const Subject &subject, const PredicatePtr &predicate_ptr, const Resource &resource);


//        std::string str(std::string format = "rdfxml-abbrev", std::string base = "file://./annotations.rdf");


        Triple &setAbout(const std::string &about);

        std::string getAbout() const;
//
//        /*
//         * Factory returning Prdicate of type namespace_ and
//         * term of type term.
//         */
////        Triple &setPredicate(const std::string &namespace_, const std::string &term);
////
////        Triple &setPredicateNew(
////                const std::string &namespace_, const std::string &term, const std::string &prefix);
////
////        Triple &setResourceLiteral(const std::string &literal);
////
////        Triple &setResourceUri(const std::string &identifiers_uri);
////
////        Triple &setResourceBlank(const std::string &blank_id);
////
//
//        void checkForNull();
    };

    typedef Triple SingularAnnotation;
}

#endif //LIBSEMSIM_Triple22_H
