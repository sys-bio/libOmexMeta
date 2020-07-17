//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBOMEXMETA_LIBRDFSTORAGE_H
#define LIBOMEXMETA_LIBRDFSTORAGE_H

#include <librdf.h>
#include <string>
#include <memory>
#include "World.h"
#include "sstream"
#include "LibrdfStatement.h"

namespace redland {

    class LibrdfStorage {

        std::vector<std::string> valid_stores_ = {
                "hashes",
                "memory",
                "file",
                "mysql",
                "postgresql",
                "sqlite",
                "tstore",
                "uri",
                "virtuoso",
        };

        struct deleter {
            void operator()(librdf_storage *storage);
        };

        librdf_storage *storage_ = nullptr;

    public:
        explicit LibrdfStorage(librdf_storage *storage);

        explicit LibrdfStorage(const std::string &storage_name = "memory", const std::string &name = "SemsimStore",
                               const char *options = nullptr);

        [[nodiscard]] librdf_storage *get() const;

        void freeStorage();

        LibrdfStorage(const LibrdfStorage &storage) = delete;

        LibrdfStorage(LibrdfStorage &&storage) noexcept;

        LibrdfStorage &operator=(LibrdfStorage &&storage) noexcept;

        int addStatement(librdf_statement *statement);

        int addStatement(const LibrdfStatement &statement);

        int size();

        int commit();

        void printAvailableStorages();
    };
}

/*
 *
//  /* Get storage configuration */
//  storage_type=getenv("REDLAND_TEST_STORAGE_TYPE");
//  storage_name=getenv("REDLAND_TEST_STORAGE_NAME");
//  storage_options=getenv("REDLAND_TEST_STORAGE_OPTIONS");
//  if(!(storage_type && storage_name && storage_options)) {
//    /* test all storages */
//    const char* const storages[] = {
//      "memory", NULL, "write='yes',new='yes',contexts='yes'",
//#ifdef STORAGE_HASHES
//#ifdef HAVE_BDB_HASH
//      "hashes", "test", "hash-type='bdb',dir='.',write='yes',new='yes',contexts='yes'",
//#else
//      "hashes", "test", "hash-type='memory',write='yes',new='yes',contexts='yes'",
//#endif
//#endif
//#ifdef STORAGE_TREES
//      "trees", "test", "contexts='yes'",
//#endif
//#ifdef STORAGE_FILE
//      "file", "test.rdf", NULL,
//#endif
//#ifdef STORAGE_MYSQL
//      "mysql", "test", "host='localhost',database='test'",
//#endif
//#ifdef STORAGE_POSTGRESQL
//      "postgresql", "test", "host='localhost',database='test'",
//#endif
//#ifdef STORAGE_TSTORE
//      "tstore", "test", "host='localhost',database='test'",
//#endif
//#ifdef STORAGE_SQLITE
//      "sqlite", "test", "new='yes'",
//#endif
//       NULL, NULL, NULL
//    };
//
// */
#endif //LIBOMEXMETA_LIBRDFSTORAGE_H
