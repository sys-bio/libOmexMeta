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


/*
 * Todo librdf_model and librdf_storage are
 * strictly 1:1. Put checks in place to verify that
 * user doesn't try to associate more than one model with
 * a single storage
 */

namespace semsim {
    class LibrdfModel {
        std::shared_ptr<librdf_model *> model_;

    public:
        LibrdfModel() = default;

        explicit LibrdfModel(librdf_model *model);

        ~LibrdfModel();

        LibrdfModel(const LibrdfModel &librdfModel);

        LibrdfModel(LibrdfModel &&librdfModel) noexcept;

        LibrdfModel &operator=(const LibrdfModel &librdfModel);

        LibrdfModel &operator=(LibrdfModel &&librdfModel) noexcept;

        bool operator==(const LibrdfModel &rhs) const;

        bool operator!=(const LibrdfModel &rhs) const;

        const std::shared_ptr<librdf_model *> &getModel() const;

        bool operator!() const;

        void addStatement(const LibrdfStatement &statement);

    };
}

#endif //LIBSEMSIM_LIBRDFMODEL_H
