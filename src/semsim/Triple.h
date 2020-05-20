//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBSEMSIM_TRIPLE_H
#define LIBSEMSIM_TRIPLE_H

#include "semsim/RedlandAPIWrappers/LibrdfNode.h"
#include "semsim/RedlandAPIWrappers/LibrdfStatement.h"
#include "semsim/Predicate.h"
#include "semsim/Subject.h"
#include "semsim/Resource.h"
//#include "semsim/Writer.h"
#include "semsim/Triple.h"
#include "librdf.h"
#include "raptor2.h"

#include <ostream>
#include <utility>
#include <algorithm>
#include <cstring>


namespace semsim {

    class Triple {
    protected:
        LibrdfWorld world_{};
        Subject subject_;
        PredicatePtr predicate_ptr_;
        Resource resource_;
    public:

        explicit Triple(LibrdfWorld world);

        Triple(LibrdfWorld world, Subject subject, PredicatePtr predicate_ptr, Resource resource);

        void setSubject(const Subject &subject);

        void setPredicatePtr(const PredicatePtr &predicatePtr);

        void setResource(const Resource &resource);

        Triple(LibrdfWorld world, Subject subject, const Predicate &predicate, Resource resource);

        Subject getSubject() const;

        PredicatePtr getPredicatePtr() const;

        Resource getResource() const;

        LibrdfStatement toStatement();

        static Triple fromStatement(LibrdfWorld world, LibrdfStatement statement);

        std::string str(std::string format = "rdfxml-abbrev", std::string base = "file://./annotations.rdf");


        Triple &setAbout(const std::string &about);

        /*
         * Factory returning Prdicate of type namespace_ and
         * term of type term.
         */
        Triple &setPredicate(const std::string &namespace_, const std::string &term);

        Triple &setPredicateNew(
                const std::string &namespace_, const std::string &term, const std::string &prefix);

        Triple &setResourceLiteral(const std::string &literal);

        Triple &setResourceUri(const std::string &identifiers_uri);

        Triple &setResourceBlank(const std::string &blank_id);

        std::string getAbout() const;

    };

    typedef Triple SingularAnnotation;
}

#endif //LIBSEMSIM_TRIPLE_H
