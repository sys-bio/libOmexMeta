#include "LibrdfSerializer.h"


namespace redland {
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
        setOptions();
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
        LibrdfUri u(uri);
        librdf_serializer_serialize_model_to_iostream(
                serializer_, u.get(), model.get(), ios
        );
        u.freeUri();
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

    void LibrdfSerializer::setOption(const std::string &option, const std::string &value) const {
        // valid options : http://librdf.org/raptor/api-1.4/raptor-section-feature.html
        std::cout << "setting option: " << option << " to: " << value << std::endl;
        std::string feature_uri_base = "http://feature.librdf.org/raptor-";
        LibrdfUri feature_uri(feature_uri_base + option);
        LibrdfNode node = LibrdfNode::fromUriString(value);
        int failure = librdf_serializer_set_feature(get(), feature_uri.get(), node.get());
        std::cout << failure << std::endl;
        if (failure < 0) {
            throw std::invalid_argument(
                    "std::invalid_argument: LibrdfSerializer::setOption: Invalid feature: " + option);
        }
        if (failure) {
            throw std::logic_error(
                    "std::logic_error: LibrdfSerializer::setOption. Failed to set serializer option: " + option);
        }
        node.freeNode();
        feature_uri.freeUri();
    }

    void LibrdfSerializer::setOptions() const {
        // These options do not work and I do not know
        // how to find the names of the options that do work
        // for turning off serialization of the base uri.
        // This is a low priority problem - fix later.
//        setOption("RAPTOR_FEATURE_WRITER_AUTO_INDENT", "1");
//        setOption("RAPTOR_FEATURE_WRITER_AUTO_EMPTY", "1");
//        setOption("RAPTOR_FEATURE_WRITE_BASE_URI", "0");
//        setOption("writerAutoIndent", "1");
//        setOption("writerAutoEmpty", "1");
//        setOption("writeBaseUri", "0");
    }


    int toIOStream(const LibrdfUri &uri, const LibrdfModel *model, const RaptorIOStream &stream);

}

