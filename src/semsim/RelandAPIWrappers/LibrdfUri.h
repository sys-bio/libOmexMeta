//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_LIBRDFURI_H
#define LIBSEMSIM_LIBRDFURI_H


#include <librdf.h>
#include <memory>


namespace semsim {
    class LibrdfUri {
        std::shared_ptr<raptor_uri *> raptor_uri_;

    public:
        explicit LibrdfUri(raptor_uri *uri);

        ~LibrdfUri();


        LibrdfUri(const LibrdfUri &raptorUri);

        LibrdfUri(LibrdfUri &&raptorUri) noexcept;

        LibrdfUri &operator=(const LibrdfUri &raptorUri);

        LibrdfUri &operator=(LibrdfUri &&raptorUri) noexcept;

        const std::shared_ptr<raptor_uri *> &getRaptorUri() const;

        std::string str();
    };
}

#endif //LIBSEMSIM_LIBRDFURI_H
