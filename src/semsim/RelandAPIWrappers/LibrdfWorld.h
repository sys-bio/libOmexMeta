//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_LIBRDFWORLD_H
#define LIBSEMSIM_LIBRDFWORLD_H

#include "librdf.h"
#include "CWrapper.h"
#include "RaptorWorld.h"


namespace semsim {

    class LibrdfWorld : public CWrapper {
        librdf_world *world_;

    public:
        LibrdfWorld();

        ~LibrdfWorld();

        LibrdfWorld(LibrdfWorld &librdfWorld);

        /*
         * operator= cannot be implemented because if we
         * copy assign, we need to increment the reference
         * counts of both *this and *rhs, which with the const
         * modifier, we cannot. We also cannot remove the
         * const modifier, because it is a part of the
         * copy assignment operator.
         */
        LibrdfWorld &operator=(LibrdfWorld &librdfWorld);

        LibrdfWorld(LibrdfWorld &&librdfWorld) noexcept = delete;

        LibrdfWorld &operator=(LibrdfWorld &&librdfWorld) noexcept = delete;

        librdf_world *getWorld() const;

        RaptorWorld getRaptor();

    };
}

#endif //LIBSEMSIM_LIBRDFWORLD_H
