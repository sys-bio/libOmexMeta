//
// Created by Ciaran on 5/17/2020.
//

#include "RaptorUri.h"

namespace semsim{
    
    bool RaptorUri::operator==(const RaptorUri &rhs) const {
        return model_ == rhs.model_;
    }

    bool RaptorUri::operator!=(const RaptorUri &rhs) const {
        return !(rhs == *this);
    }

    librdf_model *RaptorUri::getModel() const {
        return model_;
    }

    RaptorUri::RaptorUri(librdf_model *model) {
        this->model_ = model;
        increment_ref_count();
    }

    RaptorUri::~RaptorUri() {
        if (ref_count_ > 0){
            decrement_ref_count();
        }else{
            librdf_free_model(model_);
        }
    }

    RaptorUri::RaptorUri(RaptorUri &RaptorUri) {
        if (this != &RaptorUri){
            model_ = RaptorUri.model_;
            ref_count_ = RaptorUri.ref_count_;
            increment_ref_count();
            RaptorUri.increment_ref_count();
        }
    }

    RaptorUri::RaptorUri(RaptorUri &&RaptorUri) noexcept {
        if (this != &RaptorUri){
            model_ = RaptorUri.model_;
            ref_count_ = RaptorUri.ref_count_;
            RaptorUri.model_ = nullptr;
        }
    }

    RaptorUri &RaptorUri::operator=(RaptorUri &RaptorUri) {
        if (this != &RaptorUri){
            this->model_ = RaptorUri.model_;
            this->ref_count_ = RaptorUri.ref_count_;
            increment_ref_count();
            RaptorUri.increment_ref_count();
        }
        return *this;
    }

    RaptorUri &RaptorUri::operator=(RaptorUri &&RaptorUri) noexcept {
        if (this != &RaptorUri){
            model_ = RaptorUri.model_;
            ref_count_ = RaptorUri.ref_count_;
            RaptorUri.model_ = nullptr;
        }
        return *this;
    }
}
