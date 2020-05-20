//
// Created by Ciaran on 5/17/2020.
//

#include "RaptorWorld.h"

namespace semsim {

    RaptorWorld::RaptorWorld(raptor_world *world) {
        raptor_world_ = std::make_shared<raptor_world *>(world);
    }

    RaptorWorld::~RaptorWorld() {
        if (raptor_world_.use_count() == 1) {
            raptor_free_world(*raptor_world_);
        }
    }

    RaptorWorld::RaptorWorld(const RaptorWorld &raptorWorld) {
        if (raptor_world_) {
            raptor_free_world(*raptor_world_);
        }
        raptor_world_ = raptorWorld.raptor_world_;
    }

    RaptorWorld::RaptorWorld(RaptorWorld &&raptorWorld) noexcept {
        if (raptor_world_) {
            raptor_free_world(*raptor_world_);
        }
        raptor_world_ = std::move(raptorWorld.raptor_world_);
    }

    RaptorWorld &RaptorWorld::operator=(const RaptorWorld &raptorWorld) {
        if (this != &raptorWorld) {
            if (raptor_world_) {
                raptor_free_world(*raptor_world_);
            }
            raptor_world_ = raptorWorld.raptor_world_;
        }
        return *this;
    }

    RaptorWorld &RaptorWorld::operator=(RaptorWorld &&raptorWorld) noexcept {
        if (this != &raptorWorld) {
            if (raptor_world_) {
                raptor_free_world(*raptor_world_);
            }
            raptor_world_ = std::move(raptorWorld.raptor_world_);
        }
        return *this;
    }

    std::shared_ptr<raptor_world *> RaptorWorld::getRaptorWorld() const {
        return raptor_world_;
    }

    bool RaptorWorld::operator==(const RaptorWorld &rhs) const {
        return raptor_world_ == rhs.raptor_world_;
    }

    bool RaptorWorld::operator!=(const RaptorWorld &rhs) const {
        return !(rhs == *this);
    }
//
//    LibrdfUri RaptorWorld::newRaptorUri(const std::string &uri_string) {
//        raptor_uri *uri = raptor_new_uri(*raptor_world_, (const unsigned char *) uri_string.c_str());
//        return LibrdfUri(uri);
//    }
//
//    LibrdfUri
//    RaptorWorld::newRaptorUriFromUriOrFileString(const std::string &uri_string, const LibrdfUri &raptor_base_uri,
//                                                 const std::string &file_or_uri) {
//        raptor_uri *uri = raptor_new_uri_from_uri_or_file_string(
//                *raptor_world_, *raptor_base_uri.getUri(), (const unsigned char *) file_or_uri.c_str());
//        return LibrdfUri(uri);
//    }
//
//    LibrdfUri RaptorWorld::newRaptorUriRelativeToBase(const LibrdfUri &raptor_base_uri, const std::string &uri_string) {
//        raptor_uri *uri = raptor_new_uri_relative_to_base(
//                *raptor_world_, *raptor_base_uri.getUri(),
//                (const unsigned char *) uri_string.c_str());
//        return LibrdfUri(uri);
//    }

    bool RaptorWorld::operator!() const {
        return !getRaptorWorld();
    }
}











