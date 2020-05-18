//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_RAPTORURI_H
#define LIBSEMSIM_RAPTORURI_H


#include <librdf.h>
#include "CWrapper.h"

namespace semsim {
    class RaptorUri : private CWrapper {
        librdf_model *model_;

    public:
        RaptorUri(librdf_model *model);

        ~RaptorUri();

        RaptorUri(RaptorUri &RaptorUri);

        RaptorUri(RaptorUri &&RaptorUri) noexcept;

        RaptorUri &operator=(RaptorUri &RaptorUri);

        RaptorUri &operator=(RaptorUri &&RaptorUri) noexcept;

        bool operator==(const RaptorUri &rhs) const;

        bool operator!=(const RaptorUri &rhs) const;

        librdf_model *getModel() const;
    };
}

#endif //LIBSEMSIM_RAPTORURI_H
