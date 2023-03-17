//
// Created by Ciaran on 5/17/2020.
//


#include "redland/LibrdfWorld.h"
#include "redland/Logger.h"
#include <sstream>

namespace redland {


    int librdfLogHandler(void *user_data, librdf_log_message *message) {
        // make sure logger has been called so we set default logger to
        // the ones we've built if this is the first time we've called
        // getLogger.
        Logger();

        std::ostringstream log;
        log << message->message;
        switch (message->level) {
            case LIBRDF_LOG_INFO: {
                Logger().info(log.str());
                break;
            }
            case LIBRDF_LOG_DEBUG: {
                Logger().debug(log.str());
                break;
            }
            case LIBRDF_LOG_WARN: {
                Logger().warn(log.str());
                break;
            }
            case LIBRDF_LOG_ERROR: {
                Logger().error(log.str());
                break;
            }
            case LIBRDF_LOG_FATAL: {
                Logger().critical(log.str());
                break;
            }
            case LIBRDF_LOG_NONE: {
                break;
            }
        }
        return 1;
    }

    void raptorLogHandler(void *user_data, raptor_log_message *message) {
        // make sure logger has been called so we set default logger to
        // the ones we've built if this is the first time we've called
        // getLogger.
        Logger();

        std::ostringstream log;
        log << message->text;

        switch (message->level) {
            case RAPTOR_LOG_LEVEL_INFO: {
                Logger().info(log.str());
                break;
            }
            case RAPTOR_LOG_LEVEL_TRACE: {
                Logger().trace(log.str());
                break;
            }
            case RAPTOR_LOG_LEVEL_DEBUG: {
                Logger().debug(log.str());
                break;
            }
            case RAPTOR_LOG_LEVEL_WARN: {
                Logger().warn(log.str());
                break;
            }
            case RAPTOR_LOG_LEVEL_ERROR: {
                Logger().error(log.str());
                break;
            }
            case RAPTOR_LOG_LEVEL_FATAL: {
                Logger().critical(log.str());
                break;
            }
            case RAPTOR_LOG_LEVEL_NONE: {
                break;
            }
        }
    }


    void LibrdfWorld::deleter::operator()(librdf_world *world) {
        if (world)
            librdf_free_world(world);
    }

    librdf_world *LibrdfWorld::world_ = nullptr;

    librdf_world *LibrdfWorld::getWorld() {
        if (world_ == nullptr) {
            world_ = librdf_new_world();
            librdf_world_open(world_);

            // initialize loggers
            initLoggers();
            REDLAND_DEBUG("Instantiated LibrdfWorld object");
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
    void LibrdfWorld::initLoggers() {
        Logger logger;
        setLogHandler((void*)&logger, librdfLogHandler);
        setRaptorLogHandler((void*)&logger, raptorLogHandler);
        setRasqalLogHandler((void*)&logger, raptorLogHandler);
    }

    LibrdfWorld::LibrdfWorld() = default;


}// namespace redland
