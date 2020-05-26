//
// Created by Ciaran on 5/20/2020.
//

#ifndef LIBSEMSIM_LIBRDFSERIALIZER_H
#define LIBSEMSIM_LIBRDFSERIALIZER_H


#include <librdf.h>
#include <memory>
#include "semsim/Error.h"
#include "semsim/RedlandAPIWrapper/World.h"
#include "LibrdfUri.h"
#include "LibrdfModel.h"
#include "RaptorIOStream.h"
#include "LibrdfNode.h"
#include "LibrdfModel.h"
#include "semsim/Error.h"

namespace semsim {

    class LibrdfSerializer {

        struct deleter {
            void operator()(librdf_serializer *serializer);
        };

        std::unique_ptr<librdf_serializer, deleter> serializer_;
    public:
        LibrdfSerializer() = default;

        explicit LibrdfSerializer(librdf_serializer *serializer);

        explicit LibrdfSerializer(const char *name, const char *mime_type = nullptr,
                                  const char *type_uri = nullptr);

        [[nodiscard]] librdf_serializer *get() const;

        void setNamespace(const std::string &ns, const std::string &prefix) const;

        void setFeature(const std::string &ns, const std::string &prefix) const;

        std::string toString(const LibrdfUri &uri, const LibrdfModel &model);
    };
}


#endif //LIBSEMSIM_LIBRDFSERIALIZER_H
