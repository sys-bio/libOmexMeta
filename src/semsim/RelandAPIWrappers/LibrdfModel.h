//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_LIBRDFMODEL_H
#define LIBSEMSIM_LIBRDFMODEL_H

#include <librdf.h>
#include <memory>


namespace semsim {
    class LibrdfModel {
        std::shared_ptr<librdf_model *> model_;
        std::string options_;

    public:
        explicit LibrdfModel(std::shared_ptr<librdf_model *> model, std::string options = "");

        bool operator==(const LibrdfModel &rhs) const;

        bool operator!=(const LibrdfModel &rhs) const;

        const std::string &getOptions() const;

        const std::shared_ptr<librdf_model *> &getModel() const;
    };
}

#endif //LIBSEMSIM_LIBRDFMODEL_H
