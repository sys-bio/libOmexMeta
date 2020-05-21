//
// Created by Ciaran on 5/17/2020.
//

#include "RaptorWorld.h"

namespace semsim {

    RaptorWorld::RaptorWorld(raptor_world *world) :
            raptor_world_(raptor_world_ptr(world)) {
    }

    raptor_world_ptr RaptorWorld::getRaptorWorld() const {
        return raptor_world_;
    }

    bool RaptorWorld::operator==(const RaptorWorld &rhs) const {
        return raptor_world_.get() == rhs.raptor_world_.get();
    }

    bool RaptorWorld::operator!=(const RaptorWorld &rhs) const {
        return !(rhs == *this);
    }

    bool RaptorWorld::operator!() const {
        return !getRaptorWorld();
    }

    raptor_world *RaptorWorld::get() {
        return raptor_world_.get();
    }
}











