//
// Created by Ciaran on 5/17/2020.
//

#include "LibrdfModel.h"

namespace semsim {

    LibrdfModel::LibrdfModel(librdf_model *model)
            : model_(model_ptr(model)) {
    }

    bool LibrdfModel::operator==(const LibrdfModel &rhs) const {
        return model_ == rhs.model_;
    }

    bool LibrdfModel::operator!=(const LibrdfModel &rhs) const {
        return !(rhs == *this);
    }

    const model_ptr &LibrdfModel::getModel() const {
        return model_;
    }

    bool LibrdfModel::operator!() const {
        return !model_;
    }

    void LibrdfModel::addStatement(const LibrdfStatement &statement) {
        librdf_model_add_statement(get(), statement.get());
    }

    librdf_model *LibrdfModel::get() {
        return model_.get();
    }

    // todo add wrapper around librdf_model_add_statement

}

