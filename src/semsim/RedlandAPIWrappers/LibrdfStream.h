//
// Created by Ciaran on 5/20/2020.
//

#ifndef LIBSEMSIM_LIBRDFSTREAM_H
#define LIBSEMSIM_LIBRDFSTREAM_H


#include <librdf.h>
#include <memory>
#include "semsim/Error.h"

namespace semsim {
    class LibrdfStream {
        std::shared_ptr<librdf_stream *> stream_;
    public:
        const std::shared_ptr<librdf_stream *> &getStream() const;

        LibrdfStream() = default;

        explicit LibrdfStream(librdf_stream *stream);

        ~LibrdfStream();

        LibrdfStream(const LibrdfStream &LibrdfStream);

        LibrdfStream(LibrdfStream &&LibrdfStream) noexcept;

        LibrdfStream &operator=(const LibrdfStream &LibrdfStream);

        LibrdfStream &operator=(LibrdfStream &&LibrdfStream) noexcept;

        bool operator!() const;


    };
}


#endif //LIBSEMSIM_LIBRDFSTREAM_H
