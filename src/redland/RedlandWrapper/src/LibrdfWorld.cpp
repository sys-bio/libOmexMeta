//
// Created by Ciaran on 5/17/2020.
//


#include "redland/LibrdfWorld.h"

namespace redland {

    void LibrdfWorld::deleter::operator()(librdf_world *world) {
        if (world)
            librdf_free_world(world);
    }

    librdf_world *LibrdfWorld::world_ = nullptr;

    librdf_world *LibrdfWorld::getWorld() {
        if (world_ == nullptr) {
            world_ = librdf_new_world();
            librdf_world_open(world_);
        }
        return world_;
    }

    raptor_world *LibrdfWorld::getRaptor() {
        return librdf_world_get_raptor(LibrdfWorld::getWorld());
    }

    rasqal_world *LibrdfWorld::getRasqal() {
        return librdf_world_get_rasqal(LibrdfWorld::getWorld());
    }

    void LibrdfWorld::free(librdf_world *world) {
        if (world) {
            librdf_free_world(world);
            world_ = nullptr;
        }
    }

    void LibrdfWorld::setLogHandler(void *userData, librdf_log_func logging_func) {
        librdf_world_set_logger(world_, userData, logging_func);
    }

    void LibrdfWorld::setRaptorLogHandler(void *userData, raptor_log_handler logging_func) {
        // int raptor_world_set_log_handler(raptor_world *world, void *user_data, raptor_log_handler handler);
        raptor_world_set_log_handler(LibrdfWorld::getRaptor(), userData, logging_func);
    }

    void LibrdfWorld::setRasqalLogHandler(void *userData, raptor_log_handler logging_func) {
        rasqal_world_set_log_handler(LibrdfWorld::getRasqal(), userData, logging_func);
    }

    LibrdfWorld::LibrdfWorld() = default;


}// namespace redland
