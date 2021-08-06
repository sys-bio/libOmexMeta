//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBOMEXMETA_LIBRDFWORLD_H
#define LIBOMEXMETA_LIBRDFWORLD_H

#include "librdf.h"

#include <iostream>
#include <memory>
#include <regex>
#include <functional>

//#include "LibrdfStorage.h"
//#include "RaptorWorld.h"
//#include "LibrdfModel.h"
//#include "LibrdfNode.h"
//#include "LibrdfUri.h"
//#include "LibrdfSerializer.h"
//#include "LibrdfParser.h"
//#include "LibrdfQuery.h"


//#include "redland/OmexMetaUtils.h"
//#include "redland/Subject.h"
//#include "redland/Predicate.h"

namespace redland {


    /*
     * @brief C++ wrapper around librdf_world.
     *
     * World is a singleton
     * class. Other classes can use the World
     * by call to World::getWorld(). To implement
     * the singleton, librdf_world* is allocated statically
     * and therefore does not need to be destructed in the
     * way that the other wrapper classes need to be
     * (i.e. stack not heap)
     */
    class LibrdfWorld {

        static librdf_world *world_;


        /*
         * Private constructor prevents instancing
         */
        LibrdfWorld();

        struct deleter {
            void operator()(librdf_world *world);
        };

    public:
        static void setLogHandler(void* userData, librdf_log_func logging_func);

        static void setRaptorLogHandler(void* userData, raptor_log_handler logging_func);

        static void setRasqalLogHandler(void* userData, raptor_log_handler logging_func);

        static librdf_world *getWorld();

        static raptor_world *getRaptor();

        static rasqal_world *getRasqal();

        static void free(librdf_world *world);

    };


}

#endif//LIBOMEXMETA_LIBRDFWORLD_H
