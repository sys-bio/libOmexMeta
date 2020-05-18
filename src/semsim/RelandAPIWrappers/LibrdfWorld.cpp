//
// Created by Ciaran on 5/17/2020.
//

#include <iostream>
#include "LibrdfWorld.h"
#include "LibrdfStorage.h"

namespace semsim {

    LibrdfWorld::LibrdfWorld() : CWrapper() {
        librdf_world *world = librdf_new_world();
        librdf_world_open(world);
        this->world_ = world;
        increment_ref_count();
    }

    LibrdfWorld::~LibrdfWorld() {
        if (ref_count_ > 0) {
            decrement_ref_count();
        } else {
            librdf_free_world(world_);
        }
    }

    LibrdfWorld::LibrdfWorld(LibrdfWorld &librdfWorld)
        : CWrapper(){
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
        if (this != &librdfWorld) {
            world_ = librdfWorld.world_;
            ref_count_ = librdfWorld.ref_count_;
            increment_ref_count();
            librdfWorld.increment_ref_count();
        }
        return (*this);
    }

    LibrdfWorld::LibrdfWorld(LibrdfWorld &&librdfWorld) noexcept {
        if (this != &librdfWorld) {
            world_ = librdfWorld.world_;
            ref_count_ = librdfWorld.ref_count_;
            librdfWorld.world_ = nullptr;
        }
    }

    LibrdfWorld &LibrdfWorld::operator=(LibrdfWorld &&librdfWorld) noexcept {
        if (this != &librdfWorld) {
            world_ = librdfWorld.world_;
            ref_count_ = librdfWorld.ref_count_;
            librdfWorld.world_ = nullptr;
        }
        return (*this);
    }


    RaptorWorld LibrdfWorld::getRaptor() {
        raptor_world *raptor_world_ptr = librdf_world_get_raptor(world_);
        RaptorWorld raptorWorld(raptor_world_ptr);
        return raptorWorld;
    }

    librdf_world *LibrdfWorld::getWorld() const {
        return world_;
    }

    bool LibrdfWorld::operator==(const LibrdfWorld &rhs) const {
        return getWorld() == rhs.getWorld();
    }

    bool LibrdfWorld::operator!=(const LibrdfWorld &rhs) const {
        return !(rhs == *this);
    }

    LibrdfStorage LibrdfWorld::newStorage(const std::string& storage_name, const std::string& name, const std::string& options_string) {
        librdf_storage* storage = librdf_new_storage(world_, storage_name.c_str(), name.c_str(), options_string.c_str());
        LibrdfStorage librdfStorage(storage, storage_name, name, options_string);
        librdf_free_storage(storage);
        return librdfStorage;
    }
    LibrdfModel LibrdfWorld::newModel(const LibrdfStorage& storage, const std::string& options_string) {
        librdf_model* model = librdf_new_model(world_, storage.getStorage(), options_string.c_str());
        LibrdfModel librdfModel(model, options_string);
        librdf_free_model(model);
        return librdfModel;
    }

}
