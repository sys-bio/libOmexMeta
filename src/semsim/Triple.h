//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBSEMGEN_TRIPLE_H
#define LIBSEMGEN_TRIPLE_H

#include <ostream>
#include "librdf.h"
#include "Subject.h"
#include "Predicate.h"
#include "Resource.h"


namespace semsim {
    class Triple {
    protected:
        librdf_world *world_{};
        Subject subject_;
        PredicatePtr predicate_ptr_;
        Resource resource_;
    public:

        explicit Triple(librdf_world *world);

        Triple(librdf_world *world, Subject subject, PredicatePtr predicate_ptr, Resource resource);

        void setSubject(const Subject &subject);

        void setPredicatePtr(const PredicatePtr &predicatePtr);

        void setResource(const Resource &resource);

        Triple(librdf_world *world, Subject subject, const Predicate &predicate, Resource resource);

        Subject getSubject() const;

        PredicatePtr getPredicatePtr() const;

        Resource getResource() const;

        librdf_statement *toStatement();

        static Triple fromStatement(librdf_world *world, librdf_statement *statement);

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

}

#endif //LIBSEMGEN_TRIPLE_H
