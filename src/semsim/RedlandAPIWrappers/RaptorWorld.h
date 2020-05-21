//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_RAPTORWORLD_H
#define LIBSEMSIM_RAPTORWORLD_H

#include <utility>
#include <memory>
#include "librdf.h"


namespace semsim {

    typedef std::shared_ptr<raptor_world> raptor_world_ptr;

    class RaptorWorld {
        raptor_world_ptr raptor_world_;
    public:
        RaptorWorld() = default;

        explicit RaptorWorld(raptor_world *world);

        raptor_world_ptr getRaptorWorld() const;

        bool operator==(const RaptorWorld &rhs) const;

        bool operator!=(const RaptorWorld &rhs) const;

        bool operator!() const;

        raptor_world *get();

    };
}

#endif //LIBSEMSIM_RAPTORWORLD_H
