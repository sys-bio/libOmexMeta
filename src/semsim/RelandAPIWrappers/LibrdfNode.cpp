//
// Created by Ciaran on 5/17/2020.
//

#include "LibrdfNode.h"

namespace semsim{
    
    bool LibrdfNode::operator==(const LibrdfNode &rhs) const {
        return model_ == rhs.model_;
    }

    bool LibrdfNode::operator!=(const LibrdfNode &rhs) const {
        return !(rhs == *this);
    }

    librdf_model *LibrdfNode::getModel() const {
        return model_;
    }

    LibrdfNode::LibrdfNode(librdf_model *model) {
        this->model_ = model;
        increment_ref_count();
    }

    LibrdfNode::~LibrdfNode() {
        if (ref_count_ > 0){
            decrement_ref_count();
        }else{
            librdf_free_model(model_);
        }
    }

    LibrdfNode::LibrdfNode(LibrdfNode &LibrdfNode) {
        if (this != &LibrdfNode){
            model_ = LibrdfNode.model_;
            ref_count_ = LibrdfNode.ref_count_;
            increment_ref_count();
            LibrdfNode.increment_ref_count();
        }
    }

    LibrdfNode::LibrdfNode(LibrdfNode &&LibrdfNode) noexcept {
        if (this != &LibrdfNode){
            model_ = LibrdfNode.model_;
            ref_count_ = LibrdfNode.ref_count_;
            LibrdfNode.model_ = nullptr;
        }
    }

    LibrdfNode &LibrdfNode::operator=(LibrdfNode &LibrdfNode) {
        if (this != &LibrdfNode){
            this->model_ = LibrdfNode.model_;
            this->ref_count_ = LibrdfNode.ref_count_;
            increment_ref_count();
            LibrdfNode.increment_ref_count();
        }
        return *this;
    }

    LibrdfNode &LibrdfNode::operator=(LibrdfNode &&LibrdfNode) noexcept {
        if (this != &LibrdfNode){
            model_ = LibrdfNode.model_;
            ref_count_ = LibrdfNode.ref_count_;
            LibrdfNode.model_ = nullptr;
        }
        return *this;
    }
}