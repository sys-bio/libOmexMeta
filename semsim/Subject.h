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
        Uri uri;

    public:
        Subject(std::string metaId, Uri uri) : metaId(std::move(metaId)), uri(std::move(uri)) {};

        Subject(std::string metaId, std::string uri) : metaId(std::move(metaId)), uri(Uri(std::move(uri))) {};

        std::string &getMetaId();

        Uri &getUri();

        bool operator==(const Subject &rhs) const;

        bool operator!=(const Subject &rhs) const;

        friend std::ostream &operator<<(std::ostream &os, Subject &subject);
    };

}

#endif //LIBSEMGEN_SUBJECT_H
