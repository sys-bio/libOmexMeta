//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_RAPTORWORLD_H
#define LIBSEMSIM_RAPTORWORLD_H

#include "librdf.h"
#include "CWrapper.h"

namespace semsim {

    class RaptorWorld : public CWrapper {
        raptor_world *raptor_world_;
    public:
        RaptorWorld(raptor_world *world);

        ~RaptorWorld();

        RaptorWorld(const RaptorWorld &raptorWorld);

        RaptorWorld(RaptorWorld &&raptorWorld) noexcept;

        RaptorWorld &operator=(const RaptorWorld &raptorWorld);

        RaptorWorld &operator=(RaptorWorld &&raptorWorld) noexcept;

    };
}

#endif //LIBSEMSIM_RAPTORWORLD_H
