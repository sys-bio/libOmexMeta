//
// Created by Ciaran on 5/17/2020.
//

#include <iostream>
#include "LibrdfWorld.h"


namespace semsim {

    LibrdfWorld::LibrdfWorld() : CWrapper() {
        std::cout << "constructor" << std::endl;
        librdf_world *world = librdf_new_world();
        librdf_world_open(world);
        this->world_ = world;
        increment_ref_count();
    }

    LibrdfWorld::~LibrdfWorld() {
        std::cout << "destructor" << std::endl;
        if (ref_count_ > 0) {
            decrement_ref_count();
        } else {
            librdf_free_world(world_);
        }
    }

    LibrdfWorld::LibrdfWorld(LibrdfWorld &librdfWorld) {
        std::cout << "Copy constructor" << std::endl;
        if (this != &librdfWorld) {
            this->world_ = librdfWorld.world_;
            // copy the current reference count
            ref_count_ = librdfWorld.ref_count_;
            // increment count of this object
            increment_ref_count();
            // increment count of that object
            librdfWorld.increment_ref_count();
        }
    }

    LibrdfWorld &LibrdfWorld::operator=(LibrdfWorld &librdfWorld) {
        std::cout << "copy assignment constructor" << std::endl;
        if (this != &librdfWorld) {
            world_ = librdfWorld.world_;
            ref_count_ = librdfWorld.ref_count_;
            increment_ref_count();
            librdfWorld.increment_ref_count();
        }
        return (*this);
    }

    librdf_world *LibrdfWorld::getWorld() const {
        return world_;
    }

    RaptorWorld LibrdfWorld::getRaptor() {
        raptor_world *raptor_world_ptr = librdf_world_get_raptor(world_);
        RaptorWorld raptorWorld(raptor_world_ptr);
        return raptorWorld;
    }

}
