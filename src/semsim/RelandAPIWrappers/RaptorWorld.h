//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_RAPTORWORLD_H
#define LIBSEMSIM_RAPTORWORLD_H

#include "librdf.h"
#include "RaptorUri.h"


namespace semsim {

    class RaptorWorld {
        std::shared_ptr<raptor_world *> raptor_world_;
    public:
        explicit RaptorWorld(raptor_world *world);

        std::shared_ptr<raptor_world *> getRaptorWorld() const;

        bool operator==(const RaptorWorld &rhs) const;

        bool operator!=(const RaptorWorld &rhs) const;

        RaptorUri newRaptorUri();

        RaptorUri newRaptorUri(std::string uri_string);

        RaptorUri
        newRaptorUriFromUriOrFileString(std::string uri_string, RaptorUri raptor_base_uri, std::string file_or_uri);

        RaptorUri newRaptorUriRelativeToBase(RaptorUri raptor_base_uri, std::string uri_string);
    };
}

#endif //LIBSEMSIM_RAPTORWORLD_H
