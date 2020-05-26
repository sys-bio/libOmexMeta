//
// Created by Ciaran on 5/26/2020.
//

#ifndef LIBSEMSIM_SUPERBUILD_RAPTORIOSTREAM_H
#define LIBSEMSIM_SUPERBUILD_RAPTORIOSTREAM_H

#include <memory>
#include "librdf.h"
#include "World.h"
#include "semsim/Error.h"

#include "utility"

namespace semsim {
    class RaptorIOStream {
        struct deleter {
            void operator()(raptor_iostream *iostream);
        };

        std::unique_ptr<raptor_iostream, deleter> iostream_;
    public:
        RaptorIOStream() = default;

        explicit RaptorIOStream(raptor_iostream *iostream);

        [[nodiscard]] raptor_iostream *get() const;

        static std::pair<RaptorIOStream, void *> newIOToString();
    };
}

#endif //LIBSEMSIM_SUPERBUILD_RAPTORIOSTREAM_H
