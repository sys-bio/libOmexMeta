//
// Created by Ciaran on 5/20/2020.
//

#ifndef LIBSEMSIM_LIBRDFSTREAM_H
#define LIBSEMSIM_LIBRDFSTREAM_H


#include <librdf.h>
#include <memory>

#include "World.h"

namespace redland {

    class LibrdfStream {
        struct deleter {
            void operator()(librdf_stream *stream);
        };

        std::unique_ptr<librdf_stream, deleter> stream_;
    public:
        LibrdfStream();

        explicit LibrdfStream(librdf_stream *stream);

        [[nodiscard]] librdf_stream *get() const;

    };
}


#endif //LIBSEMSIM_LIBRDFSTREAM_H
