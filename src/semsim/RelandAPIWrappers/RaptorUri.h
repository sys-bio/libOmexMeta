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

        ~RaptorUri();


        RaptorUri(const RaptorUri &raptorUri);

        RaptorUri(RaptorUri &&raptorUri) noexcept;

        RaptorUri &operator=(const RaptorUri &raptorUri);

        RaptorUri &operator=(RaptorUri &&raptorUri) noexcept;

        const std::shared_ptr<raptor_uri *> &getRaptorUri() const;

        std::string str();
    };
}

#endif //LIBSEMSIM_RAPTORURI_H
