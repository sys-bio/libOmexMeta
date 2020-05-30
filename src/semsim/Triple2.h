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
#include "semsim/Triple2.h"
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

    class Triple2 : public LibrdfStatement{
    protected:
//        Subject subject_;
//        PredicatePtr predicate_ptr_;
//        Resource resource_;
    public:

        explicit Triple2() = default;

        Triple2(const Subject& subject,const Predicate& predicate, const Resource& resource);

        Triple2(const Subject &subject, const PredicatePtr &predicate_ptr, const Resource &resource);


//        std::string str(std::string format = "rdfxml-abbrev", std::string base = "file://./annotations.rdf");


        Triple2 &setAbout(const std::string &about);

        std::string getAbout() const;
//
//        /*
//         * Factory returning Prdicate of type namespace_ and
//         * term of type term.
//         */
////        Triple2 &setPredicate(const std::string &namespace_, const std::string &term);
////
////        Triple2 &setPredicateNew(
////                const std::string &namespace_, const std::string &term, const std::string &prefix);
////
////        Triple2 &setResourceLiteral(const std::string &literal);
////
////        Triple2 &setResourceUri(const std::string &identifiers_uri);
////
////        Triple2 &setResourceBlank(const std::string &blank_id);
////
//
//        void checkForNull();
    };

    typedef Triple2 SingularAnnotation;
}

#endif //LIBSEMSIM_Triple22_H
