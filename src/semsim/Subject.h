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
        librdf_world *world_;
        RDFNodePtr rdf_node_ptr_;

    public:
        Subject() = default;

        Subject(librdf_world *world, const RDFBlankNode &node);

        Subject(librdf_world *world, const RDFURINode &node);

        Subject(librdf_world *world, librdf_node *node);

        ~Subject();

        librdf_node *toRdfNode() const;

        std::string str() const;

        bool isSet() const;

    };
    typedef std::vector<Subject> Subjects;

}

#endif //LIBSEMGEN_SUBJECT_H
