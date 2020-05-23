//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBSEMSIM_SUBJECT_H
#define LIBSEMSIM_SUBJECT_H

#include "iostream"
#include "semsim/RedlandAPIWrapper/World.h"
#include "RDFNode.h"
#include <vector>

#include <utility>
#include "semsim/Error.h"


namespace semsim {

    class Subject {
    private:
        RDFNodePtr rdf_node_ptr_;

    public:
        Subject() = default;

        explicit Subject(LibrdfWorld world, const RDFBlankNode &node);

        explicit Subject(LibrdfWorld world, const RDFURINode &node);

        explicit Subject(const RDFNode &node);

        static Subject fromUri(LibrdfWorld world, const std::string &uri);

        static Subject fromBlank(LibrdfWorld world, const std::string &blank);

        ~Subject();

        LibrdfNode getNode() const;

        std::string str() const;


        bool isSet() const;

    };

    typedef std::vector<Subject> Subjects;

}

#endif //LIBSEMSIM_SUBJECT_H
