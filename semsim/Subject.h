//
// Created by Ciaran on 4/4/2020.
//

#ifndef LIBSEMGEN_SUBJECT_H
#define LIBSEMGEN_SUBJECT_H

#include "iostream"
#include "uri.h"

namespace semsim {
    class Subject {
    private:
        std::string metaId;

    public:

        explicit Subject(std::string metaId) : metaId(std::move(metaId)) {};

        const std::string &getMetaId() const;

        bool operator==(const Subject &rhs) const;

        bool operator!=(const Subject &rhs) const;

        friend std::ostream &operator<<(std::ostream &os, const Subject &subject);
    };

}

#endif //LIBSEMGEN_SUBJECT_H
