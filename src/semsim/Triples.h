//
// Created by Ciaran on 4/29/2020.
//

#ifndef LIBSEMSIM_TRIPLES_H
#define LIBSEMSIM_TRIPLES_H

#include "semsim/Triple.h"
#include "semsim/Predicate.h"
#include "semsim/Subject.h"
#include "semsim/Resource.h"
#include "semsim/RedlandAPIWrapper/RedlandAPIWrapper.h"
#include "semsim/Error.h"
#include "semsim/TripleWriter.h"

#include <vector>

namespace semsim {

    class Triple;

    class Triples {
    private:

        std::vector<Triple> triples_;

    public:
        Triples();

        Triples(std::initializer_list<Triple> l);

        explicit Triples(std::vector<Triple> triples);

        void push_back(Triple triple);

        void emplace_back(LibrdfWorld world, LibrdfStatement statement);

        void emplace_back(LibrdfWorld world, Subject subject, PredicatePtr predicatePtr, Resource resource);

        Subjects getSubjects();

        PredicatePtrs getPredicates();

        Resources getResources();

        int size();

        std::vector<Triple>::iterator begin();

        std::vector<Triple>::iterator end();

        std::string str(std::string format = "rdfxml-abbrev", std::string base="file://./annotations.rdf");
    };

    typedef std::vector<Triples> NestedTriples;

    //todo implement equality operators
}

#endif //LIBSEMSIM_TRIPLES_H
