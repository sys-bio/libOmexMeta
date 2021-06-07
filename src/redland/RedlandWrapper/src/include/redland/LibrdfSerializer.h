//
// Created by Ciaran on 5/20/2020.
//

#ifndef LIBOMEXMETA_LIBRDFSERIALIZER_H
#define LIBOMEXMETA_LIBRDFSERIALIZER_H


#include "librdf.h"
#include <memory>

#include "LibrdfModel.h"
#include "LibrdfNode.h"
#include "LibrdfUri.h"
#include "LibrdfWorld.h"
#include "RaptorIOStream.h"
#include <stdlib.h>

namespace redland {

    class LibrdfSerializer {

    public:
        LibrdfSerializer() = default;

        ~LibrdfSerializer();

        LibrdfSerializer(const LibrdfSerializer &serializer) = delete;

        LibrdfSerializer(LibrdfSerializer &&serializer) noexcept;

        LibrdfSerializer &operator=(const LibrdfSerializer &serializer) = delete;

        LibrdfSerializer &operator=(LibrdfSerializer &&serializer) noexcept;

        static LibrdfSerializer fromRawPtr(librdf_serializer *serializer);

        explicit LibrdfSerializer(const char *format, const char *mime_type = nullptr,
                                  const char *type_uri = nullptr);

        [[nodiscard]] librdf_serializer *get() const;

        void setNamespace(const std::string &ns, const std::string &prefix) const;

        void setFeature(const std::string &ns, const std::string &prefix) const;

        std::string toString(const std::string &uri, const LibrdfModel &model);

        void freeSerializer();

        void validateSerializerName(std::string name);

        void setOption(const std::string &option, const std::string &value) const;

        void setOptions() const;

    private:
        librdf_serializer *serializer_ = nullptr;

        explicit LibrdfSerializer(librdf_serializer *serializer);
    };
}// namespace redland


#endif//LIBOMEXMETA_LIBRDFSERIALIZER_H
