//
// Created by Ciaran on 5/17/2020.
//
#include "semsim/Error.h"
#include "RaptorUri.h"

namespace semsim {

    RaptorUri::RaptorUri(raptor_uri *uri)
            : raptor_uri_(std::make_shared<raptor_uri *>(uri)) {

    }

    RaptorUri::~RaptorUri() {
        if (raptor_uri_.use_count() == 1) {
            raptor_free_uri(*raptor_uri_);
        }
    }

    RaptorUri::RaptorUri(const RaptorUri &raptorUri) {
        if (raptor_uri_ != nullptr) {
            raptor_free_uri(*raptor_uri_);
        }
        raptor_uri_ = raptorUri.getRaptorUri();
    }

    RaptorUri::RaptorUri(RaptorUri &&raptorUri) noexcept {
        if (raptor_uri_ != nullptr) {
            raptor_free_uri(*raptor_uri_);
        }
        raptor_uri_ = std::move(raptorUri.raptor_uri_);
    }

    RaptorUri &RaptorUri::operator=(const RaptorUri &raptorUri) {
        if (this != &raptorUri) {
            if (raptor_uri_ != nullptr) {
                raptor_free_uri(*raptor_uri_);
            }
            raptor_uri_ = raptorUri.raptor_uri_;
        }
        return *this;
    }

    RaptorUri &RaptorUri::operator=(RaptorUri &&raptorUri) noexcept {
        if (this != &raptorUri) {
            if (raptor_uri_ != nullptr) {
                raptor_free_uri(*raptor_uri_);
            }
            raptor_uri_ = std::move(raptorUri.raptor_uri_);
        }
        return *this;
    }

    const std::shared_ptr<raptor_uri *> &RaptorUri::getRaptorUri() const {
        return raptor_uri_;
    }

    std::string RaptorUri::str() {
        if (raptor_uri_ == nullptr){
            throw NullPointerException("RaptorUri::str(): raptor_uri_ ");
        }
        unsigned char * cstr = raptor_uri_to_string(*getRaptorUri());
        std::string str = (const char*)cstr;
        free(cstr);
        return str;
    }

}
