//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBSEMSIM_SUBJECT_H
#define LIBSEMSIM_SUBJECT_H

#include "World.h"
#include "LibrdfNode.h"
#include "semsim/Error.h"


#include "iostream"
#include <vector>

using namespace redland;


namespace semsim {

    class Subject {
    private:
        librdf_node* node_;

        explicit Subject(librdf_node* node);

    public:
        Subject() = default;

        [[nodiscard]] librdf_node* getNode() const;

        static Subject fromRawPtr(librdf_node* node);

        static Subject fromUri(const std::string &uri);

        static Subject fromBlank(const std::string &blank);

//        ~Subject();

        [[nodiscard]] std::string str() const;

        [[nodiscard]] bool isSet() const;

    };

    typedef std::vector<Subject> Subjects;

}

#endif //LIBSEMSIM_SUBJECT_H
