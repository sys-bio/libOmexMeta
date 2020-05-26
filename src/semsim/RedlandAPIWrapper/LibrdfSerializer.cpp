#include "LibrdfSerializer.h"
#include "LibrdfNode.h"
#include "LibrdfModel.h"

namespace semsim {

    LibrdfSerializer::LibrdfSerializer(librdf_serializer *serializer) :
            serializer_(std::unique_ptr<librdf_serializer, deleter>(serializer)) {}

    LibrdfSerializer::LibrdfSerializer(const char *name, const char *mime_type, const char *type_uri) {
        librdf_uri *type_uri_ = nullptr;
        if (type_uri)
            type_uri_ = librdf_new_uri(World::getWorld(), (const unsigned char *) type_uri);
        serializer_ = std::unique_ptr<librdf_serializer, deleter>(
                librdf_new_serializer(World::getWorld(),
                                      name, mime_type, type_uri_
                )
        );

    }

    librdf_serializer *LibrdfSerializer::get() const {
        return serializer_.get();
    }


    void *LibrdfSerializer::setNamespace(const std::string &ns, const std::string &prefix) const {
        librdf_serializer_set_namespace(serializer_.get(), LibrdfUri(ns).get(), prefix.c_str());
    }

    void *LibrdfSerializer::setFeature(const std::string &ns, const std::string &prefix) const {
        librdf_serializer_set_feature(serializer_.get(), LibrdfUri(ns).get(), LibrdfNode::fromLiteral(prefix).get());
    }

    void LibrdfSerializer::deleter::operator()(librdf_serializer *serializer) {
        librdf_free_serializer(serializer);
    }

    int toIOStream(const LibrdfUri &uri, const LibrdfModel *model,);
}

