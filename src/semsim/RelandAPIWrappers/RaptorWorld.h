//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_RAPTORWORLD_H
#define LIBSEMSIM_RAPTORWORLD_H

#include "librdf.h"


namespace semsim {

    class RaptorWorld {
        std::shared_ptr<raptor_world *> raptor_world_;
    public:
        explicit RaptorWorld(raptor_world *world);

        std::shared_ptr<raptor_world *> getRaptorWorld() const;

        bool operator==(const RaptorWorld &rhs) const;

        bool operator!=(const RaptorWorld &rhs) const;
    };
}

#endif //LIBSEMSIM_RAPTORWORLD_H
