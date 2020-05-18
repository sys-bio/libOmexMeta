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

    RaptorWorld::RaptorWorld(RaptorWorld &raptorWorld) {
        if (this != &raptorWorld) {
            raptor_world_ = raptorWorld.raptor_world_;
            ref_count_ = raptorWorld.ref_count_;
            increment_ref_count();
            raptorWorld.increment_ref_count();
        }
    }

    RaptorWorld &RaptorWorld::operator=(RaptorWorld &raptorWorld) {
        if (this != &raptorWorld) {
            raptor_world_ = raptorWorld.raptor_world_;
            ref_count_ = raptorWorld.ref_count_;
            increment_ref_count();
            raptorWorld.increment_ref_count();
        }
        return *this;
    }

    RaptorWorld::RaptorWorld(RaptorWorld &&raptorWorld) noexcept {
        if (this != &raptorWorld){
            raptor_world_ = raptorWorld.raptor_world_;
            ref_count_ = raptorWorld.ref_count_;
            raptorWorld.raptor_world_ = nullptr;
        }
    }

    RaptorWorld &RaptorWorld::operator=(RaptorWorld &&raptorWorld) noexcept {
        if (this != &raptorWorld){
            raptor_world_ = raptorWorld.raptor_world_;
            ref_count_ = raptorWorld.ref_count_;
            raptorWorld.raptor_world_ = nullptr;
        }
        return *this;
    }

    raptor_world *RaptorWorld::getRaptorWorld() const {
        return raptor_world_;
    }

    bool RaptorWorld::operator==(const RaptorWorld &rhs) const {
        return getRaptorWorld() == rhs.getRaptorWorld();
    }

    bool RaptorWorld::operator!=(const RaptorWorld &rhs) const {
        return !(rhs == *this);
    }

}