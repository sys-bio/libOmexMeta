//
// Created by Ciaran on 5/17/2020.
//

#include <iostream>
#include <memory>
#include "LibrdfWorld.h"
#include "LibrdfStorage.h"
#include "semsim/SemsimUtils.h"

namespace semsim {

    LibrdfWorld::LibrdfWorld() {
        librdf_world *world_tmp = librdf_new_world();
        librdf_world_open(world_tmp);
        world_ = std::make_shared<librdf_world *>(world_tmp);
    }

    LibrdfWorld::~LibrdfWorld() = default;

    LibrdfWorld::LibrdfWorld(const LibrdfWorld &librdfWorld) {
        if (this != &librdfWorld) {
            std::cout << "copy constructor: this->world_.use_count(): " << this->world_.use_count() <<
                      "librdfWorld->world_.use_count(): " << librdfWorld.world_.use_count() << std::endl;
            this->world_ = librdfWorld.world_;
        }
    }

    LibrdfWorld::LibrdfWorld(LibrdfWorld &&librdfWorld) noexcept {
        if (this != &librdfWorld) {
            std::cout << "Move constructor: this->world_.use_count(): " << this->world_.use_count() <<
                      "librdfWorld->world_.use_count(): " << librdfWorld.world_.use_count() << std::endl;
            this->world_ = std::move(librdfWorld.world_);
        }
    }

    LibrdfWorld &LibrdfWorld::operator=(const LibrdfWorld &librdfWorld) {
        if (this != &librdfWorld) {
            std::cout << "Copy assignment op: this->world_.use_count(): " << this->world_.use_count() <<
                      "librdfWorld->world_.use_count(): " << librdfWorld.world_.use_count() << std::endl;

            this->world_ = librdfWorld.world_;
        }
        return *this;
    }

    LibrdfWorld &LibrdfWorld::operator=(LibrdfWorld &&librdfWorld) noexcept {
        if (this != &librdfWorld) {
            std::cout << "Move assignment op: before move: this->world_.use_count(): " << this->world_.use_count() <<
                      ", librdfWorld->world_.use_count(): " << librdfWorld.world_.use_count() << std::endl;
            this->world_ = std::move(librdfWorld.world_);
            std::cout << "Move assignment op: after move:  this->world_.use_count(): " << this->world_.use_count() <<
                      ", librdfWorld->world_.use_count(): " << librdfWorld.world_.use_count() << std::endl;
        }
        return *this;
    }


    RaptorWorld LibrdfWorld::getRaptor() {
        raptor_world *raptor_world_ptr = librdf_world_get_raptor(*world_);
        RaptorWorld raptorWorld(raptor_world_ptr);
        return raptorWorld;
    }

    std::shared_ptr<librdf_world *> LibrdfWorld::getWorld() const {
        return world_;
    }

    bool LibrdfWorld::operator==(const LibrdfWorld &rhs) const {
        return getWorld() == rhs.getWorld();
    }

    bool LibrdfWorld::operator!=(const LibrdfWorld &rhs) const {
        return !(rhs == *this);
    }

    LibrdfStorage LibrdfWorld::newStorage(const std::string &storage_name, const std::string &name,
                                          const std::string &options_string) {

        librdf_storage *storage = librdf_new_storage(
                *world_, storage_name.c_str(), name.c_str(), options_string.c_str());
        LibrdfStorage librdfStorage(storage, storage_name, name, options_string);
//        librdf_free_storage(storage);
        return librdfStorage;
    }

    LibrdfModel LibrdfWorld::newModel(const LibrdfStorage &storage, const std::string &options_string) {
        HERE();
        librdf_model *model = librdf_new_model(*world_, *storage.getStorage(), options_string.c_str());
        std::shared_ptr<librdf_model *> m = std::make_shared<librdf_model *>(model);
        HERE();
        LibrdfModel librdfModel(m, options_string);
        HERE();
//        librdf_free_model(model);
        HERE();
        return librdfModel;
    }

}


/*
 * Saved for later: might need it?
 *
 *
 * Since LibrdfWorld is initialized with a world object,
 * We need to free it before we move the world from librdfWorld
 * over this this->world_.
if (world_ != nullptr) { // most of this time world_ will not be nullptr.
    librdf_free_world(*world_);
}
 */