#include "LibrdfSerializer.h"


namespace redland {
    void LibrdfSerializer::deleter::operator()(librdf_serializer *serializer) {
        if (serializer)
            librdf_free_serializer(serializer);
    }

    LibrdfSerializer::LibrdfSerializer(librdf_serializer *serializer) :
            serializer_(std::unique_ptr<librdf_serializer, deleter>(serializer)) {}

    LibrdfSerializer::LibrdfSerializer(const char *format, const char *mime_type, const char *type_uri) {
        librdf_uri *type_uri_ = nullptr;
        if (type_uri)
            type_uri_ = librdf_new_uri(World::getWorld(), (const unsigned char *) type_uri);
        serializer_ = std::unique_ptr<librdf_serializer, deleter>(
                librdf_new_serializer(World::getWorld(),
                                      format, mime_type, type_uri_
                )
        );

    }

    librdf_serializer *LibrdfSerializer::get() const {
        return serializer_.get();
    }


    void LibrdfSerializer::setNamespace(const std::string &ns, const std::string &prefix) const {
        librdf_serializer_set_namespace(serializer_.get(), LibrdfUri(ns).get(), prefix.c_str());
    }

    void LibrdfSerializer::setFeature(const std::string &ns, const std::string &prefix) const {
        librdf_serializer_set_feature(serializer_.get(), LibrdfUri(ns).get(), LibrdfNode::fromLiteral(prefix));
    }

    std::string LibrdfSerializer::toString(const LibrdfUri &uri, const LibrdfModel &model) {
        void *buffer_to_hold_string = nullptr;
        raptor_iostream *ios = raptor_new_iostream_to_string(
                World::getRaptor(), (void **) &buffer_to_hold_string, nullptr, malloc);
        if (!ios)
            throw RedlandNullPointerException("Writer::toString(): raptor_iostream");
        librdf_serializer_serialize_model_to_iostream(
                serializer_.get(), uri.get(), model.get(), ios
        );
        const char *s = (const char *) buffer_to_hold_string;
        std::string output(s);
        free(buffer_to_hold_string);
        return output;
    }

    LibrdfSerializer LibrdfSerializer::fromRawPtr(librdf_serializer *serializer) {
        return LibrdfSerializer(serializer);
    }


    int toIOStream(const LibrdfUri &uri, const LibrdfModel *model, const RaptorIOStream &stream);
}

