//
// Created by Ciaran on 5/20/2020.
//

#ifndef LIBSEMSIM_TRIPLEWRITER_H
#define LIBSEMSIM_TRIPLEWRITER_H


#include "semsim/RedlandAPIWrappers/RedlandAPIWrapper.h"
#include "semsim/Writer.h"
#include "semsim/Triple.h"
#include "semsim/Triples.h"

namespace semsim {
    class Triple;

    class Triples;

    class TripleWriter : public Writer {
        LibrdfStorage storage_;
    public:
        using Writer::init;

        explicit TripleWriter(Triple triple,
                              const std::string &base_uri = "file://annotation.rdf",
                              std::string format = "rdfxml-abbrev");

        explicit TripleWriter(Triples triples,
                              const std::string &base_uri = "file://annotation.rdf",
                              std::string format = "rdfxml-abbrev");

    };
}

#endif //LIBSEMSIM_TRIPLEWRITER_H
