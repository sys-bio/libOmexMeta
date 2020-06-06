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

/*
 * Todo librdf_model and librdf_storage are
 * strictly 1:1. Put checks in place to verify that
 * user doesn't try to associate more than one model with
 * a single storage
 */

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

        explicit LibrdfModel(librdf_storage *storage, const char *options = nullptr);

        [[nodiscard]] librdf_model *get() const;

        LibrdfQueryResults query(LibrdfQuery query);

        LibrdfStream toStream();

        int size() const;

        void addStatement(const LibrdfStatement &statement) const;

        void addStatement(librdf_statement *statement) const;

        void freeModel();
    };
}

#endif //LIBSEMSIM_LIBRDFMODEL_H
