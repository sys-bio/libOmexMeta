//
// Created by Ciaran on 5/17/2020.
//

#include "RaptorUri.h"

namespace semsim {

    RaptorUri::RaptorUri(raptor_uri *uri)
            : raptor_uri_(std::make_shared<raptor_uri *>(uri)) {

    }

    const std::shared_ptr<raptor_uri *> &RaptorUri::getRaptorUri() const {
        return raptor_uri_;
    }
}
