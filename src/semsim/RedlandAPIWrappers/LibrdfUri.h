//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_LIBRDFURI_H
#define LIBSEMSIM_LIBRDFURI_H


#include <memory>
#include <librdf.h>
#include "semsim/Error.h"


namespace semsim {

    typedef std::shared_ptr<librdf_uri> librdf_uri_ptr;

    class LibrdfUri {
        librdf_uri_ptr librdf_uri_;

    public:
        LibrdfUri() = default;

        explicit LibrdfUri(librdf_uri *uri);

        std::string str() const;

        bool operator==(const LibrdfUri &rhs) const;

        bool operator!=(const LibrdfUri &rhs) const;

        bool operator!() const;

        const librdf_uri_ptr &getLibrdfUri() const;

        librdf_uri *get();

    };
}

#endif //LIBSEMSIM_LIBRDFURI_H
