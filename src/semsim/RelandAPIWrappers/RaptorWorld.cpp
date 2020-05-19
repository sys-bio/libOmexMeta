//
// Created by Ciaran on 5/17/2020.
//

#include <utility>
#include <memory>
#include "RaptorWorld.h"

namespace semsim {

    RaptorWorld::RaptorWorld(raptor_world *world) {
        raptor_world_ = std::make_shared<raptor_world *>(world);
    }

    std::shared_ptr<raptor_world *> RaptorWorld::getRaptorWorld() const {
        return raptor_world_;
    }

    bool RaptorWorld::operator==(const RaptorWorld &rhs) const {
        return getRaptorWorld() == rhs.getRaptorWorld();
    }

    bool RaptorWorld::operator!=(const RaptorWorld &rhs) const {
        return !(rhs == *this);
    }

    RaptorUri RaptorWorld::newRaptorUri(std::string uri_string) {
        raptor_uri *uri = raptor_new_uri(*raptor_world_, (const unsigned char *) uri_string.c_str());
        return RaptorUri(uri);
    }

    RaptorUri RaptorWorld::newRaptorUriFromUriOrFileString(std::string uri_string, RaptorUri raptor_base_uri,
                                                           std::string file_or_uri) {
        raptor_uri *uri = raptor_new_uri_from_uri_or_file_string(
                *raptor_world_, *raptor_base_uri.getRaptorUri(), (const unsigned char *) file_or_uri.c_str());
        return RaptorUri(uri);
    }

    RaptorUri RaptorWorld::newRaptorUriRelativeToBase(RaptorUri raptor_base_uri, std::string uri_string) {
        raptor_uri *uri = raptor_new_uri_relative_to_base(
                *raptor_world_, *raptor_base_uri.getRaptorUri(),
                (const unsigned char *) uri_string.c_str());
        return RaptorUri(uri);
    }
}