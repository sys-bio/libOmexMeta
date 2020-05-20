//
// Created by Ciaran on 5/20/2020.
//

#ifndef LIBSEMSIM_LIBRDFSERIALIZER_H
#define LIBSEMSIM_LIBRDFSERIALIZER_H


#include <librdf.h>
#include <memory>
#include "semsim/Error.h"

namespace semsim {
    class LibrdfSerializer {
        std::shared_ptr<librdf_serializer *> serializer_;
    public:
        const std::shared_ptr<librdf_serializer *> &getSerializer() const;

        LibrdfSerializer() = default;

        explicit LibrdfSerializer(librdf_serializer *query_results);

        ~LibrdfSerializer();

        LibrdfSerializer(const LibrdfSerializer &LibrdfSerializer);

        LibrdfSerializer(LibrdfSerializer &&LibrdfSerializer) noexcept;

        LibrdfSerializer &operator=(const LibrdfSerializer &LibrdfSerializer);

        LibrdfSerializer &operator=(LibrdfSerializer &&LibrdfSerializer) noexcept;

        bool operator!() const;


    };
}
#endif //LIBSEMSIM_LIBRDFSERIALIZER_H
