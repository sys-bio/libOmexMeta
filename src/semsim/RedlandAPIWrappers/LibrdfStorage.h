//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_LIBRDFSTORAGE_H
#define LIBSEMSIM_LIBRDFSTORAGE_H

#include <librdf.h>
#include <string>
#include <memory>

namespace semsim {
    typedef std::shared_ptr<librdf_storage> storage_ptr;

    class LibrdfStorage {

        storage_ptr storage_;

    public:
        LibrdfStorage() = default;

        explicit LibrdfStorage(librdf_storage *storage);

        bool operator==(const LibrdfStorage &rhs) const;

        bool operator!=(const LibrdfStorage &rhs) const;

        storage_ptr getStorage() const;

        bool operator!() const;

        librdf_storage *get();

    };
}


#endif //LIBSEMSIM_LIBRDFSTORAGE_H
