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

}