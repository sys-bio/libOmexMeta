//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBSEMGEN_SUBJECT_H
#define LIBSEMGEN_SUBJECT_H

#include "iostream"
#include "RDFNode.h"
#include <vector>

#include <utility>
#include "semsim/Error.h"
#include "semsim/RedlandAPIWrappers/LibrdfWorld.h"

namespace semsim {

    class Subject {
    private:
        RDFNodePtr rdf_node_ptr_;

    public:
        Subject() = default;

        explicit Subject(const RDFBlankNode &node);

        explicit Subject(const RDFURINode &node);

        explicit Subject(const RDFNode &node);

        static Subject uri(LibrdfWorld world, const std::string &uri);

        static Subject blank(LibrdfWorld world, const std::string &blank);

        ~Subject();

        LibrdfNode getNode() const;

        std::string str() const;

    };

    typedef std::vector<Subject> Subjects;

}

#endif //LIBSEMGEN_SUBJECT_H
