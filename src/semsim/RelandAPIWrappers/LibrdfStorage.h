//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_LIBRDFSTORAGE_H
#define LIBSEMSIM_LIBRDFSTORAGE_H

#include <librdf.h>
#include <vector>

namespace semsim {
    class LibrdfStorage {
        std::shared_ptr<librdf_storage *> storage_;

    public:

        LibrdfStorage(librdf_storage *storage);

        ~LibrdfStorage();

        LibrdfStorage(const LibrdfStorage &storage);

        LibrdfStorage &operator=(const LibrdfStorage &storage);

        LibrdfStorage(LibrdfStorage &&storage) noexcept;

        LibrdfStorage &operator=(LibrdfStorage &&storage) noexcept;

        bool operator==(const LibrdfStorage &rhs) const;

        bool operator!=(const LibrdfStorage &rhs) const;

        std::shared_ptr<LibrdfStorage> getStorage() const;

        const std::string &getStorageName() const;

        const std::string &getName() const;

        const std::string &getOptions() const;

        const std::vector<std::string> &getValidStorageNames() const;

        const std::vector<std::string> &getValidStorage() const;

        const std::vector<std::string> &getValidOptions() const;

    };
}


#endif //LIBSEMSIM_LIBRDFSTORAGE_H
