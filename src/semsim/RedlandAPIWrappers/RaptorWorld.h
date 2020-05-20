//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_RAPTORWORLD_H
#define LIBSEMSIM_RAPTORWORLD_H

#include <utility>
#include <memory>
#include "librdf.h"
#include "LibrdfUri.h"


namespace semsim {

    class RaptorWorld {
        std::shared_ptr<raptor_world *> raptor_world_;
    public:
        RaptorWorld() = default;

        explicit RaptorWorld(raptor_world *world);

        ~RaptorWorld();

        RaptorWorld(const RaptorWorld &raptorWorld);

        RaptorWorld(RaptorWorld &&raptorWorld) noexcept;

        RaptorWorld &operator=(const RaptorWorld &raptorWorld);

        RaptorWorld &operator=(RaptorWorld &&raptorWorld) noexcept;

        std::shared_ptr<raptor_world *> getRaptorWorld() const;

        bool operator==(const RaptorWorld &rhs) const;

        bool operator!=(const RaptorWorld &rhs) const;

        bool operator!() const;
//        LibrdfUri newRaptorUri(const std::string &uri_string);
//
//        LibrdfUri newRaptorUriFromUriOrFileString(
//                const std::string &uri_string, const LibrdfUri &raptor_base_uri, const std::string &file_or_uri);
//
//        LibrdfUri newRaptorUriRelativeToBase(
//                const LibrdfUri &raptor_base_uri, const std::string &uri_string);

    };
}

#endif //LIBSEMSIM_RAPTORWORLD_H
