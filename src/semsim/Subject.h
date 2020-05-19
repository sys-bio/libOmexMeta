//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBSEMGEN_SUBJECT_H
#define LIBSEMGEN_SUBJECT_H

#include "iostream"
#include "RDFNode.h"
#include <vector>


namespace semsim {
    class Subject {
    private:
        RDFNodePtr rdf_node_ptr_;

    public:
        Subject() = default;

        explicit Subject(const RDFBlankNode &node);

        explicit Subject(const RDFURINode &node);

        explicit Subject(const RDFNode &node);

//        Subject(LibrdfWorld world, const RDFBlankNode &node);
//
//        Subject(LibrdfWorld world, const RDFURINode &node);
//
//        Subject(LibrdfWorld world, LibrdfNode node);
//
        ~Subject();

        LibrdfNode getNode() const;

        std::string str() const;

        bool isSet() const;

    };
    typedef std::vector<Subject> Subjects;

}

#endif //LIBSEMGEN_SUBJECT_H
