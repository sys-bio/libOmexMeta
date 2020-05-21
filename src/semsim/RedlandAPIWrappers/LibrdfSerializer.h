//
// Created by Ciaran on 5/20/2020.
//

#ifndef LIBSEMSIM_LIBRDFSERIALIZER_H
#define LIBSEMSIM_LIBRDFSERIALIZER_H


#include <librdf.h>
#include <memory>
#include "semsim/Error.h"

namespace semsim {
    typedef std::shared_ptr<librdf_serializer> serializer_ptr;

    class LibrdfSerializer {
        serializer_ptr serializer_;
    public:
        const serializer_ptr &getSerializer() const;

        LibrdfSerializer() = default;

        explicit LibrdfSerializer(librdf_serializer *serializer);

        bool operator!() const;

        bool operator==(const LibrdfSerializer &rhs) const;

        bool operator!=(const LibrdfSerializer &rhs) const;

        librdf_serializer *get();

    };
}
#endif //LIBSEMSIM_LIBRDFSERIALIZER_H
