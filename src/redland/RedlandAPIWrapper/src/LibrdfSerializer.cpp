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
        LibrdfUri u(ns);
        librdf_serializer_set_namespace(serializer_.get(), u.get(), prefix.c_str());
        u.free();
    }

    void LibrdfSerializer::setFeature(const std::string &ns, const std::string &prefix) const {
        LibrdfUri u(ns);
        librdf_serializer_set_feature(serializer_.get(), u.get(), LibrdfNode::fromLiteral(prefix));
        u.free();
    }

    std::string LibrdfSerializer::toString(std::string uri, const LibrdfModel &model) {
        void *buffer_to_hold_string = nullptr;
        raptor_iostream *ios = raptor_new_iostream_to_string(
                World::getRaptor(), (void **) &buffer_to_hold_string, nullptr, malloc);
        if (!ios)
            throw RedlandNullPointerException("Writer::toString(): raptor_iostream");
        librdf_uri* u = librdf_new_uri(World::getWorld(), (const unsigned char*) uri.c_str());
        librdf_serializer_serialize_model_to_iostream(
                serializer_.get(), u, model.get(), ios
        );
        librdf_free_uri(u);
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

