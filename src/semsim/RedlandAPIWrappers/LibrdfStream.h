//
// Created by Ciaran on 5/20/2020.
//

#ifndef LIBSEMSIM_LIBRDFSTREAM_H
#define LIBSEMSIM_LIBRDFSTREAM_H


#include <librdf.h>
#include <memory>
#include "semsim/Error.h"

namespace semsim {
    typedef std::shared_ptr<librdf_stream> stream_ptr;

    class LibrdfStream {
        stream_ptr stream_;
    public:
        const stream_ptr &getStream() const;

        LibrdfStream() = default;

        explicit LibrdfStream(librdf_stream *stream);

        bool operator!() const;

        bool operator==(const LibrdfStream &rhs) const;

        bool operator!=(const LibrdfStream &rhs) const;

        librdf_stream *get();


    };
}


#endif //LIBSEMSIM_LIBRDFSTREAM_H
