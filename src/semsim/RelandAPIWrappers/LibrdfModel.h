//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_LIBRDFMODEL_H
#define LIBSEMSIM_LIBRDFMODEL_H

#include <librdf.h>
#include "CWrapper.h"

namespace semsim {
    class LibrdfModel : private CWrapper {
        librdf_model *model_;
        std::string options_;

    public:
        LibrdfModel(librdf_model *model, std::string options="");

        ~LibrdfModel();

        LibrdfModel(LibrdfModel &librdfModel);

        LibrdfModel(LibrdfModel &&librdfModel) noexcept;

        LibrdfModel &operator=(LibrdfModel &librdfModel);

        LibrdfModel &operator=(LibrdfModel &&librdfModel) noexcept;

        bool operator==(const LibrdfModel &rhs) const;

        bool operator!=(const LibrdfModel &rhs) const;

        librdf_model *getModel() const;
    };
}

#endif //LIBSEMSIM_LIBRDFMODEL_H
