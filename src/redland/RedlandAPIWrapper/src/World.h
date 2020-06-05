//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_WORLD_H
#define LIBSEMSIM_WORLD_H

#include "librdf.h"

#include <iostream>
#include <memory>
#include <regex>

//#include "LibrdfStorage.h"
//#include "RaptorWorld.h"
//#include "LibrdfModel.h"
//#include "LibrdfNode.h"
//#include "LibrdfUri.h"
//#include "LibrdfSerializer.h"
//#include "LibrdfParser.h"
//#include "LibrdfQuery.h"


//#include "redland/SemsimUtils.h"
//#include "redland/Subject.h"
//#include "redland/Predicate.h"

/*
 * A useful comment made by a stackoverflow wizard in a question
 * I asked:
 *  https://stackoverflow.com/questions/61972493/how-to-generalize-this-c-wrapper-around-a-c-class?noredirect=1#comment109609206_61972493
 *
 * A thunk is a small function used to basically call another
 * function and pass along the parameters as arguments to the
 * actual implementation function. It's a glue function.
 * The approach you're taking will help with object ownership
 * and life-cycle management and allow for RAII (so the destructor
 * can do the clean up), which I like. I've wrapped C libraries
 * before, it starts out a bother, but gets easier as you go.
 */

namespace redland {

    typedef std::shared_ptr<librdf_world> librdf_world_ptr;

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
    class World {

        static librdf_world *world_;

        /*
         * Private constructor prevents instancing
         */
        World();

        struct deleter {
            void operator()(librdf_world *world);
        };

    public:

        static librdf_world *getWorld();

        static raptor_world *getRaptor();

        static void free(librdf_world *world);

    };


}

#endif //LIBSEMSIM_WORLD_H


















