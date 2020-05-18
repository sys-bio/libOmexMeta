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

        RaptorWorld(RaptorWorld &raptorWorld);

        RaptorWorld &operator=(RaptorWorld &raptorWorld);

        RaptorWorld(RaptorWorld &&raptorWorld) noexcept;

        RaptorWorld &operator=(RaptorWorld &&raptorWorld) noexcept ;

        raptor_world *getRaptorWorld() const;

        bool operator==(const RaptorWorld &rhs) const;

        bool operator!=(const RaptorWorld &rhs) const;
    };
}

#endif //LIBSEMSIM_RAPTORWORLD_H
