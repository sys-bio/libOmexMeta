//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_LIBRDFMODEL_H
#define LIBSEMSIM_LIBRDFMODEL_H

#include <librdf.h>
#include <memory>
#include <string>
#include <iostream>
#include "LibrdfStatement.h"
#include "LibrdfQueryResults.h"
#include "LibrdfQuery.h"
#include "LibrdfStorage.h"
#include "World.h"
#include "LibrdfStream.h"


namespace redland {

    class LibrdfModel {

        librdf_model *model_ = nullptr;

    public:
//        ~LibrdfModel();

        LibrdfModel(const LibrdfModel &model) = delete;

        LibrdfModel(LibrdfModel &&model) noexcept;

        LibrdfModel &operator=(const LibrdfModel &model) = delete;

        LibrdfModel &operator=(LibrdfModel &&model) noexcept;

        LibrdfModel() = default;

        explicit LibrdfModel(librdf_model *model);

        /*
         *  librdf_model and librdf_storage have a
         * strictly 1:1 relationship. i.e. a storage cannot
         * be associated with more than one model.
         */
        explicit LibrdfModel(librdf_storage *storage, const char *options = nullptr);

        [[nodiscard]] librdf_model *get() const;

        LibrdfQueryResults query(LibrdfQuery query);

        LibrdfStream toStream();

        int size() const;

        void addStatement(const LibrdfStatement &statement) const;

        void addStatement(librdf_statement *statement) const;

        void freeModel();

        void removeStatement(librdf_statement *statement) const;

        void removeStatement(const LibrdfStatement &statement) const;
    };
}

#endif //LIBSEMSIM_LIBRDFMODEL_H
