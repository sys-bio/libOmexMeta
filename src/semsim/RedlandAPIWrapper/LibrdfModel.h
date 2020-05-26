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
/*
 * Todo librdf_model and librdf_storage are
 * strictly 1:1. Put checks in place to verify that
 * user doesn't try to associate more than one model with
 * a single storage
 */

namespace semsim {

    class LibrdfModel {
        struct deleter {
            void operator()(librdf_model *model);
        };

        std::unique_ptr<librdf_model, deleter> model_;

    public:
        LibrdfModel() = default;

        explicit LibrdfModel(librdf_model *model);

        explicit LibrdfModel(const LibrdfStorage &storage, const char *options = nullptr);

        [[nodiscard]] librdf_model *get() const;

        LibrdfQueryResults query(LibrdfQuery query);

        void addStatement(const LibrdfStatement &statement) const;

        int size() const;
    };
}

#endif //LIBSEMSIM_LIBRDFMODEL_H
