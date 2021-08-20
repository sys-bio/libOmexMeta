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
#include "redland/RedlandType.h"
#include <stdlib.h>

namespace redland {


    /**
     * @brief std::function signature of librdf_free_parser
     */
    using serializer_free_func = std::function<void(librdf_serializer *)>;

    /**
     * Instantiation of templated superclass
     */
    using RedlandType_librdf_serializer = RedlandType<librdf_serializer, serializer_free_func>;


    class LibrdfSerializer : public RedlandType_librdf_serializer {

    public:
        using RedlandType_librdf_serializer::RedlandType_librdf_serializer;

        explicit LibrdfSerializer(librdf_serializer *serializer);

        explicit LibrdfSerializer(const char *format, const char *mime_type = nullptr,
                                  const char *type_uri = nullptr);

        void setNamespace(const std::string &ns, const std::string &prefix) const;

        void setFeature(const std::string &ns, const std::string &prefix) const;

        std::string toString(const std::string &uri, const LibrdfModel &model);

        void validateSerializerName(std::string name);

        void setOption(const std::string &option, const std::string &value) const;

        void setOptions() const;

    };
}// namespace redland


#endif//LIBOMEXMETA_LIBRDFSERIALIZER_H
