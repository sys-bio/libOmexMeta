//
// Created by Ciaran on 5/17/2020.
//

#include <string>
#include <utility>
#include "LibrdfModel.h"

namespace semsim {

    bool LibrdfModel::operator==(const LibrdfModel &rhs) const {
        return model_ == rhs.model_;
    }

    bool LibrdfModel::operator!=(const LibrdfModel &rhs) const {
        return !(rhs == *this);
    }


    LibrdfModel::LibrdfModel(std::shared_ptr<librdf_model *> model, std::string options)
            : model_(std::move(model)), options_(std::move(options)) {
    }

    const std::string &LibrdfModel::getOptions() const {
        return options_;
    }

    const std::shared_ptr<librdf_model *> &LibrdfModel::getModel() const {
        return model_;
    }

}

