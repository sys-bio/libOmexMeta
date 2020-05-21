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
    typedef std::shared_ptr<librdf_model> model_ptr;

    class LibrdfModel {
        model_ptr model_;

    public:
        LibrdfModel() = default;

        explicit LibrdfModel(librdf_model *model);

        bool operator==(const LibrdfModel &rhs) const;

        bool operator!=(const LibrdfModel &rhs) const;

        const model_ptr &getModel() const;

        bool operator!() const;

        void addStatement(LibrdfStatement statement);

        librdf_model *get();

    };
}

#endif //LIBSEMSIM_LIBRDFMODEL_H
