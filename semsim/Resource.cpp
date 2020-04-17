//
// Created by Ciaran on 4/4/2020.
//

#include "semsim/Resource.h"

#include <utility>
#include <regex>
#include "uri.h"
#include "sstream"
#include "iterator"
#include "SemsimUtils.h"

namespace semsim {

    Resource::Resource(RDFTerm *rdf_term_ptr) {
        this->rdf_term_ptr_ = rdf_term_ptr->clone();
    }

    Resource::Resource(const RDFTerm *rdf_term_ptr) {
        this->rdf_term_ptr_ = rdf_term_ptr->clone();
    }

    Resource::~Resource() {
        delete this->rdf_term_ptr_;
    }

    Resource::Resource(const Resource &resource) {
        this->rdf_term_ptr_ = resource.rdf_term_ptr_;
        delete resource.rdf_term_ptr_;
    }

    Resource::Resource(const Resource &&resource) noexcept {
        this->rdf_term_ptr_ = resource.rdf_term_ptr_;
        delete resource.rdf_term_ptr_;
    }

    Resource &Resource::operator=(const Resource &resource) {
        if (this != &resource) {
            this->rdf_term_ptr_ = resource.rdf_term_ptr_;
        }
        return *this;
    }

    Resource &Resource::operator=(Resource &&resource) noexcept {
        if (this != &resource) {
            this->rdf_term_ptr_ = resource.rdf_term_ptr_;
        }
        return *this;
    };


    std::string Resource::str() {
        return this->rdf_term_ptr_->str();
    }


}






