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
        /* the URI string */
        std::string string_;
        /* length of string */
        unsigned int length_;
        /* usage count */
        int usage_;

        /*
         * If the deleter of std::unique_ptr is an empty
         * class then it can do some optimizations and
         * not actually store the deleter object.
         * Otherwise it has to accommodate extra space for
         * the deleter, which is unnecessary
         *  https://stackoverflow.com/questions/61969200/what-is-the-purpose-of-wrapping-this-private-deleter-function-in-a-struct/61969274#61969274
         */
        struct deleter {
            void operator()(librdf_uri *ptr) {
                librdf_free_uri(ptr);
            }
        };

        std::unique_ptr<librdf_uri, deleter> librdf_uri_;

    public:
        LibrdfUri() = default;

//        explicit LibrdfUri(librdf_uri *uri);

        explicit LibrdfUri(std::string uri);

        librdf_uri *get();

    };
}

#endif //LIBSEMSIM_LIBRDFURI_H
