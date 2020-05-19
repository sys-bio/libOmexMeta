//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_LIBRDFMODEL_H
#define LIBSEMSIM_LIBRDFMODEL_H

#include <librdf.h>
#include <memory>


/*
 * Todo librdf_model and librdf_storage are
 * strictly 1:1. Put checks in place to verify that
 * user doesn't try to associate more than one model with
 * a single storage
 */

namespace semsim {
    class LibrdfModel {
        std::shared_ptr<librdf_model *> model_;
        std::string options_;

    public:
        explicit LibrdfModel(librdf_model *model, std::string options = "");

        ~LibrdfModel();

        LibrdfModel(const LibrdfModel &librdfModel);

        LibrdfModel(LibrdfModel &&librdfModel) noexcept;

        LibrdfModel &operator=(const LibrdfModel &librdfModel);

        LibrdfModel &operator=(LibrdfModel &&librdfModel) noexcept;

        bool operator==(const LibrdfModel &rhs) const;

        bool operator!=(const LibrdfModel &rhs) const;

        const std::string &getOptions() const;

        const std::shared_ptr<librdf_model *> &getModel() const;
    };
}

#endif //LIBSEMSIM_LIBRDFMODEL_H
