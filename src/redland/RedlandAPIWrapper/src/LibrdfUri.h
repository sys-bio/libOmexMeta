//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_LIBRDFURI_H
#define LIBSEMSIM_LIBRDFURI_H


#include <memory>
#include <librdf.h>
#include "LibrdfException.h"


namespace redland {

    class LibrdfUri {

        /*
         * If the deleter of std::unique_ptr is an empty
         * class then it can do some optimizations and
         * not actually store the deleter object.
         * Otherwise it has to accommodate extra space for
         * the deleter, which is unnecessary
         *  https://stackoverflow.com/questions/61969200/what-is-the-purpose-of-wrapping-this-private-deleter-function-in-a-struct/61969274#61969274
         */
        struct deleter {
            void operator()(librdf_uri *ptr);
        };

        std::shared_ptr<librdf_uri> librdf_uri_;

    public:
        LibrdfUri() = default;

//        LibrdfUri(const LibrdfUri& librdfUri);

        [[nodiscard]] std::string str() const;

        explicit LibrdfUri(const std::string &uri);

        explicit LibrdfUri(librdf_uri *uri);

        [[nodiscard]] librdf_uri *get() const;

        bool isNull() const;

        bool isEmpty() const;
    };
}

#endif //LIBSEMSIM_LIBRDFURI_H
