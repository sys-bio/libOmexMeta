//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_LIBRDFSTORAGE_H
#define LIBSEMSIM_LIBRDFSTORAGE_H

#include <librdf.h>
#include <string>
#include <memory>
#include "semsim/RedlandAPIWrapper/World.h"

namespace semsim {

    class LibrdfStorage {

        struct deleter {
            void operator()(librdf_storage *storage);
        };

        std::unique_ptr<librdf_storage, deleter> storage_;

    public:
        explicit LibrdfStorage(librdf_storage *storage);

        explicit LibrdfStorage(std::string storage_name = "memory", std::string name = "SemsimStore",
                               std::string options = std::string());

        librdf_storage *get() const;

    };
}


#endif //LIBSEMSIM_LIBRDFSTORAGE_H
