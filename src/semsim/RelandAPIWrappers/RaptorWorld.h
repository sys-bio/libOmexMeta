//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_RAPTORWORLD_H
#define LIBSEMSIM_RAPTORWORLD_H

#include "librdf.h"
#include "LibrdfUri.h"


namespace semsim {

    class RaptorWorld {
        std::shared_ptr<raptor_world *> raptor_world_;
    public:
        explicit RaptorWorld(raptor_world *world);

        ~RaptorWorld();

        RaptorWorld(const RaptorWorld &raptorWorld);

        RaptorWorld(RaptorWorld &&raptorWorld) noexcept;

        RaptorWorld &operator=(const RaptorWorld &raptorWorld);

        RaptorWorld &operator=(RaptorWorld &&raptorWorld) noexcept;

        std::shared_ptr<raptor_world *> getRaptorWorld() const;

        bool operator==(const RaptorWorld &rhs) const;

        bool operator!=(const RaptorWorld &rhs) const;

        LibrdfUri newRaptorUri(std::string uri_string);

        LibrdfUri newRaptorUriFromUriOrFileString(
                std::string uri_string, LibrdfUri raptor_base_uri, std::string file_or_uri);

        LibrdfUri newRaptorUriRelativeToBase(
                LibrdfUri raptor_base_uri, std::string uri_string);
    };
}

#endif //LIBSEMSIM_RAPTORWORLD_H
