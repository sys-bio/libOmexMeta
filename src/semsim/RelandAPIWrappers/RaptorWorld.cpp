//
// Created by Ciaran on 5/17/2020.
//

#include <utility>
#include "RaptorWorld.h"

namespace semsim {

    RaptorWorld::RaptorWorld(raptor_world *world) {
        this->raptor_world_ = world;
        increment_ref_count();
    }

    RaptorWorld::~RaptorWorld() {
        if (ref_count_ > 0)
            decrement_ref_count();
        else
            raptor_free_world(raptor_world_);
    }

    RaptorWorld::RaptorWorld(const RaptorWorld &raptorWorld) {
        if (this != &raptorWorld) {
            raptor_world_ = raptorWorld.raptor_world_;
            increment_ref_count();
        }
    }

    RaptorWorld::RaptorWorld(RaptorWorld &&raptorWorld) noexcept {
        if (this != &raptorWorld) {
            raptor_world_ = std::move(raptorWorld.raptor_world_);
            increment_ref_count();
        }
    }

    RaptorWorld &RaptorWorld::operator=(const RaptorWorld &raptorWorld) {
        if (this != &raptorWorld) {
            raptor_world_ = raptorWorld.raptor_world_;
            increment_ref_count();
        }
        return *this;
    }

    RaptorWorld &RaptorWorld::operator=(RaptorWorld &&raptorWorld) noexcept {
        if (this != &raptorWorld) {
            raptor_world_ = std::move(raptorWorld.raptor_world_);
            increment_ref_count();
        }
        return *this;
    }
}