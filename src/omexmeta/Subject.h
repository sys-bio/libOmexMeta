//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBOMEXMETA_SUBJECT_H
#define LIBOMEXMETA_SUBJECT_H

#include "World.h"
#include "LibrdfNode.h"
#include "omexmeta/Error.h"


#include "iostream"
#include <vector>
#include "omexmeta/HERE.h"

using namespace redland;


namespace omexmeta {

    class Subject {
    private:
        librdf_node *node_ = nullptr;

        explicit Subject(librdf_node *node);

    public:
        explicit Subject(LibrdfNode node);

        Subject() = default;

        [[nodiscard]] librdf_node *getNode() const;

        void setNode(librdf_node *node);

        static Subject fromRawPtr(librdf_node *node);

        static Subject fromUri(const std::string &uri);

        static Subject fromBlank(const std::string &blank);

        bool operator==(const Subject &rhs) const;

        bool operator!=(const Subject &rhs) const;
//        ~Subject();

        [[nodiscard]] std::string str() const;

        [[nodiscard]] bool isSet() const;

        void free();

    };

    typedef std::vector<Subject> Subjects;


}

#endif //LIBOMEXMETA_SUBJECT_H
