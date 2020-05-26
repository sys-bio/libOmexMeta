//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBSEMSIM_SUBJECT_H
#define LIBSEMSIM_SUBJECT_H

#include "semsim/RedlandAPIWrapper/World.h"
#include "semsim/RedlandAPIWrapper/LibrdfNode.h"
#include "semsim/Error.h"

#include "iostream"
#include <vector>


namespace semsim {

    class Subject {
    private:
        LibrdfNode node_;

    public:
        Subject() = default;

        [[nodiscard]] const LibrdfNode &getNode() const;

        explicit Subject(LibrdfNode node);

        static Subject fromUri(const std::string &uri);

        static Subject fromBlank(const std::string &blank);

//        ~Subject();

        [[nodiscard]] std::string str() const;

        [[nodiscard]] bool isSet() const;

    };

    typedef std::vector<Subject> Subjects;

}

#endif //LIBSEMSIM_SUBJECT_H
