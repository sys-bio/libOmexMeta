#include "LibrdfSerializer.h"


namespace redland {
    void LibrdfSerializer::deleter::operator()(librdf_serializer *serializer) {
        if (serializer)
            librdf_free_serializer(serializer);
    }

    LibrdfSerializer::LibrdfSerializer(librdf_serializer *serializer) :
            serializer_(serializer) {}

    LibrdfSerializer::LibrdfSerializer(const char *format, const char *mime_type, const char *type_uri) {
        validateSerializerName(format);
        librdf_uri *type_uri_ = nullptr;
        if (type_uri)
            type_uri_ = librdf_new_uri(World::getWorld(), (const unsigned char *) type_uri);
        serializer_ = librdf_new_serializer(World::getWorld(),
                                            format, mime_type, type_uri_
        );
    }

    void LibrdfSerializer::freeSerializer() {
        if (serializer_ != nullptr) {
            librdf_free_serializer(serializer_);
            serializer_ = nullptr;
        }
    }

    LibrdfSerializer::~LibrdfSerializer() {
        freeSerializer();
    }

    LibrdfSerializer::LibrdfSerializer(LibrdfSerializer &&serializer) noexcept {
        if (serializer.serializer_ != nullptr) {
            if (serializer_ != nullptr)
                freeSerializer();
            serializer_ = serializer.serializer_;
            serializer.serializer_ = nullptr;
        }
    }

    LibrdfSerializer &LibrdfSerializer::operator=(LibrdfSerializer &&serializer) noexcept {
        if (this != &serializer) {
            if (serializer.serializer_ != nullptr) {
                if (serializer_ != nullptr)
                    freeSerializer();
                serializer_ = serializer.serializer_;
                serializer.serializer_ = nullptr;
            }
        }
        return *this;
    }

    librdf_serializer *LibrdfSerializer::get() const {
        return serializer_;
    }


    void LibrdfSerializer::setNamespace(const std::string &ns, const std::string &prefix) const {
        LibrdfUri u(ns);
        librdf_serializer_set_namespace(serializer_, u.get(), prefix.c_str());
        u.freeUri();
    }

    void LibrdfSerializer::setFeature(const std::string &ns, const std::string &prefix) const {
        LibrdfUri u(ns);
        LibrdfNode node = LibrdfNode::fromLiteral(prefix);
        librdf_serializer_set_feature(serializer_, u.get(), node.get());
        u.freeUri();
        node.freeNode();
    }

    std::string LibrdfSerializer::toString(const std::string &uri, const LibrdfModel &model) {
        void *buffer_to_hold_string = nullptr;
        raptor_iostream *ios = raptor_new_iostream_to_string(
                World::getRaptor(), (void **) &buffer_to_hold_string, nullptr, malloc);
        if (!ios)
            throw RedlandNullPointerException("Writer::toString(): raptor_iostream");
        librdf_uri *u = librdf_new_uri(World::getWorld(), (const unsigned char *) uri.c_str());
        librdf_serializer_serialize_model_to_iostream(
                serializer_, u, model.get(), ios
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

    void LibrdfSerializer::validateSerializerName(std::string name) {
        std::vector<std::string> v = {
                "ntriples",
                "turtle",
                "rdfxml-xmp",
                "rdfxml-abbrev",
                "rdfxml",
                "rss-1.0",
                "atom",
                "dot",
                "json-triples",
                "json",
                "nquads",
                "html",
        };
        if (std::find(v.begin(), v.end(), name) != v.end()) {
            // string accepted return
            return;
        }
        // error
        std::ostringstream os;
        os << "std::invalid_argument: Serializer Format \"" << name
           << "\" is not a valid option. These are your options: ";
        for (auto &it : v) {
            os << it << ", ";
        }
        throw std::invalid_argument(os.str());
    }

    int toIOStream(const LibrdfUri &uri, const LibrdfModel *model, const RaptorIOStream &stream);
}

