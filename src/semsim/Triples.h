//
// Created by Ciaran on 4/29/2020.
//

#ifndef LIBSEMSIM_TRIPLES_H
#define LIBSEMSIM_TRIPLES_H

#include "semsim/Triple.h"
#include "semsim/Predicate.h"
#include "semsim/Subject.h"
#include "semsim/Resource.h"
#include "RedlandAPIWrapper.h"
#include "semsim/Error.h"
//#include "semsim/TripleWriter.h"

#include <vector>

using namespace redland;

namespace semsim {

//    class Triple;

    typedef std::vector<std::shared_ptr<Triple>> UniqueTripleVector;
    typedef std::vector<Triple> TripleVector;

    class Triples {
    private:

        UniqueTripleVector triples_;

    public:
        Triples();

        explicit Triples(Triple triple);

        explicit Triples(std::vector<Triple> triples);

        void push_back(Triple triple);

        void emplace_back(LibrdfStatement statement);

        void emplace_back(Subject subject, PredicatePtr predicatePtr, Resource resource);

        void emplace_back(Subject subject, Predicate predicate, Resource resource);

        void emplace_back(Subject subject, BiomodelsBiologyQualifier predicate, Resource resource);

        void emplace_back(Subject subject, BiomodelsModelQualifier predicate, Resource resource);

        void emplace_back(Subject subject, DCTerm predicate, Resource resource);

        void emplace_back(Subject subject, SemSim predicate, Resource resource);

        std::vector<std::string> getSubjectsStr();

        std::vector<std::string> getPredicates();

        std::vector<std::string> getResources();

        int size();

        UniqueTripleVector::iterator begin();

        UniqueTripleVector::iterator end();

        std::string str(std::string format = "rdfxml-abbrev", std::string base = "file://./annotations.rdf");

    };

    typedef std::vector<Triples> NestedTriples;

    //todo implement equality operators
}

#endif //LIBSEMSIM_TRIPLES_H
