//
// Created by Ciaran on 5/17/2020.
//

#include <string>
#include <utility>
#include "LibrdfModel.h"

namespace semsim{

    bool LibrdfModel::operator==(const LibrdfModel &rhs) const {
        return model_ == rhs.model_;
    }

    bool LibrdfModel::operator!=(const LibrdfModel &rhs) const {
        return !(rhs == *this);
    }

    librdf_model *LibrdfModel::getModel() const {
        return model_;
    }

    LibrdfModel::LibrdfModel(librdf_model *model, std::string options)
        : model_(model), options_(std::move(options)) {
        increment_ref_count();
    }

    LibrdfModel::~LibrdfModel() {
        if (ref_count_ > 0){
            decrement_ref_count();
        }else{
            librdf_free_model(model_);
        }
    }

    LibrdfModel::LibrdfModel(LibrdfModel &librdfModel)  : CWrapper(librdfModel) {
        if (this != &librdfModel){
            model_ = librdfModel.model_;
            options_ = librdfModel.options_;
            ref_count_ = librdfModel.ref_count_;
            increment_ref_count();
            librdfModel.increment_ref_count();
        }
    }

    LibrdfModel::LibrdfModel(LibrdfModel &&librdfModel) noexcept {
        if (this != &librdfModel){
            model_ = librdfModel.model_;
            ref_count_ = librdfModel.ref_count_;
            options_ = librdfModel.options_;
            librdfModel.model_ = nullptr;
        }
    }

    LibrdfModel &LibrdfModel::operator=(LibrdfModel &librdfModel) {
        if (this != &librdfModel){
            this->model_ = librdfModel.model_;
            options_ = librdfModel.options_;
            this->ref_count_ = librdfModel.ref_count_;
            increment_ref_count();
            librdfModel.increment_ref_count();
        }
        return *this;
    }

    LibrdfModel &LibrdfModel::operator=(LibrdfModel &&librdfModel) noexcept {
        if (this != &librdfModel){
            model_ = librdfModel.model_;
            options_ = librdfModel.options_;
            ref_count_ = librdfModel.ref_count_;
            librdfModel.model_ = nullptr;
        }
        return *this;
    }
}