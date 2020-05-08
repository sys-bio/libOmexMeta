//
// Created by Ciaran on 4/29/2020.
//

#ifndef LIBSEMGEN_TRIPLES_H
#define LIBSEMGEN_TRIPLES_H

#include <vector>
#include "Triple.h"
#include "Subject.h"
#include "Resource.h"
#include "Predicate.h"

namespace semsim {

    class Triples {
    private:

        std::vector<Triple> triples_;

    public:
        Triples();

        Triples(std::initializer_list<Triple> l);

        explicit Triples(std::vector<Triple> triples);

        void push_back(Triple triple);

        void emplace_back(librdf_world *world, librdf_statement *statement);

        void emplace_back(librdf_world *world, Subject subject, PredicatePtr predicatePtr, Resource resource);

        Subjects getSubjects();

        PredicatePtrs getPredicates();

        Resources getResources();

        int size();

        std::vector<semsim::Triple>::iterator begin();

        std::vector<semsim::Triple>::iterator end();

        std::string str(std::string format = "rdfxml-abbrev", std::string base="file://./annotations.rdf");
    };

    typedef std::vector<Triples> NestedTriples;

    //todo implement equality operators
}

#endif //LIBSEMGEN_TRIPLES_H
