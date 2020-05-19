//
// Created by Ciaran on 5/17/2020.
//
#include "semsim/Error.h"
#include "LibrdfUri.h"

namespace semsim {

    LibrdfUri::LibrdfUri(librdf_uri *uri)
            : raptor_uri_(std::make_shared<raptor_uri *>(uri)) {

    }

    LibrdfUri::~LibrdfUri() {
        if (raptor_uri_.use_count() == 1) {
            raptor_free_uri(*raptor_uri_);
        }
    }

    LibrdfUri::LibrdfUri(const LibrdfUri &raptorUri) {
        if (raptor_uri_ != nullptr) {
            raptor_free_uri(*raptor_uri_);
        }
        raptor_uri_ = raptorUri.getRaptorUri();
    }

    LibrdfUri::LibrdfUri(LibrdfUri &&raptorUri) noexcept {
        if (raptor_uri_ != nullptr) {
            raptor_free_uri(*raptor_uri_);
        }
        raptor_uri_ = std::move(raptorUri.raptor_uri_);
    }

    LibrdfUri &LibrdfUri::operator=(const LibrdfUri &raptorUri) {
        if (this != &raptorUri) {
            if (raptor_uri_ != nullptr) {
                raptor_free_uri(*raptor_uri_);
            }
            raptor_uri_ = raptorUri.raptor_uri_;
        }
        return *this;
    }

    LibrdfUri &LibrdfUri::operator=(LibrdfUri &&raptorUri) noexcept {
        if (this != &raptorUri) {
            if (raptor_uri_ != nullptr) {
                raptor_free_uri(*raptor_uri_);
            }
            raptor_uri_ = std::move(raptorUri.raptor_uri_);
        }
        return *this;
    }

    const std::shared_ptr<raptor_uri *> &LibrdfUri::getRaptorUri() const {
        return raptor_uri_;
    }

    std::string LibrdfUri::str() {
        if (raptor_uri_ == nullptr) {
            throw NullPointerException("LibrdfUri::str(): raptor_uri_ ");
        }
        unsigned char *cstr = raptor_uri_to_string(*getRaptorUri());
        std::string str = (const char *) cstr;
        free(cstr);
        return str;
    }

}
