//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_RAPTORURI_H
#define LIBSEMSIM_RAPTORURI_H


#include <librdf.h>
#include <memory>


namespace semsim {
    class RaptorUri {
        std::shared_ptr<raptor_uri *> raptor_uri_;

    public:
        explicit RaptorUri(raptor_uri *uri);

        const std::shared_ptr<raptor_uri *> &getRaptorUri() const;

    };
}

#endif //LIBSEMSIM_RAPTORURI_H
