//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBOMEXMETA_LIBRDFMODEL_H
#define LIBOMEXMETA_LIBRDFMODEL_H

#include "LibrdfQuery.h"
#include "LibrdfQueryResults.h"
#include "LibrdfStatement.h"
#include "LibrdfStorage.h"
#include "LibrdfStream.h"
#include "LibrdfWorld.h"
#include "librdf.h"
#include <iostream>
#include <memory>
#include <string>


namespace redland {

    class LibrdfModel {

    public:
        ~LibrdfModel();

        /*
         *  librdf_model and librdf_storage have a
         * strictly 1:1 relationship. i.e. a storage cannot
         * be associated with more than one model.
         */
        [[deprecated("Use LibrdfModel(LibrdfStorage storage, const char *options = nullptr);")]]
        explicit LibrdfModel(librdf_storage *storage, const char *options = nullptr);

        explicit LibrdfModel(LibrdfStorage& storage, const char *options = nullptr);

        LibrdfModel(const LibrdfModel &model) = delete;

        LibrdfModel(LibrdfModel &&model) noexcept;

        LibrdfModel &operator=(const LibrdfModel &model) = delete;

        LibrdfModel &operator=(LibrdfModel &&model) noexcept;

        bool operator==(const LibrdfModel &rhs) const;

        bool operator!=(const LibrdfModel &rhs) const;

        LibrdfModel() = default;

        explicit LibrdfModel(librdf_model *model);

        [[nodiscard]] librdf_model *get() const;

//        LibrdfQueryResults query(LibrdfQuery query);
        [[nodiscard]] LibrdfQueryResults query(const LibrdfQuery& query) const;

        librdf_stream* toStream();

        int size() const;

        void addStatement(librdf_statement *statement) const;

        void freeModel();

        void removeStatement(librdf_statement *statement) const;

        void removeStatement(const LibrdfStatement &statement) const;

        librdf_storage* getStorage() const;

        int commitTransaction() const;

        int startTransaction() const;

        void *getTransactionHandle() const;

        int startTransactionWithHandle(void *handle) const;

        int getTransactionRollback() const;

        int supportsContexts() const;

        bool containsStatement(librdf_statement* statement) const;

        bool containsStatement(const LibrdfStatement &statement) const;

        void addStatement(const LibrdfStatement &statement) const;
    private:
        librdf_model *model_ = nullptr;
    };
}

#endif //LIBOMEXMETA_LIBRDFMODEL_H
