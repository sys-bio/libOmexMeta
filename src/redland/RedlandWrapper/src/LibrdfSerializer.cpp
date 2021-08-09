#include "redland/LibrdfSerializer.h"


namespace redland {
    LibrdfSerializer::LibrdfSerializer(librdf_serializer *serializer) 
        : RedlandType_librdf_serializer(serializer, librdf_free_serializer) {}


    LibrdfSerializer::LibrdfSerializer(const char *format, const char *mime_type, const char *type_uri) {
        freeFunc_ = librdf_free_serializer;
        validateSerializerName(format);
        librdf_uri *type_uri_ = nullptr;
        if (type_uri)
            type_uri_ = librdf_new_uri(LibrdfWorld::getWorld(), (const unsigned char *) type_uri);
        obj_ = librdf_new_serializer(LibrdfWorld::getWorld(),
                                            format, mime_type, type_uri_
        );
        setOptions();
    }

    void LibrdfSerializer::setNamespace(const std::string &ns, const std::string &prefix) const {
        LibrdfUri u(ns);
        librdf_serializer_set_namespace(obj_, u.get(), prefix.c_str());
        u.freeObj();
    }

    void LibrdfSerializer::setFeature(const std::string &ns, const std::string &prefix) const {
        LibrdfUri u(ns);
        LibrdfNode node = LibrdfNode::fromLiteral(prefix);
        librdf_serializer_set_feature(obj_, u.getWithoutIncrement(), node.getWithoutIncrement());
    }

    std::string LibrdfSerializer::toString(const std::string &uri, const LibrdfModel &model) {
        void *buffer_to_hold_string = nullptr;
        raptor_iostream *ios = raptor_new_iostream_to_string(
                LibrdfWorld::getRaptor(), (void **) &buffer_to_hold_string, nullptr, malloc);
        if (!ios)
            throw RedlandNullPointerException("Writer::toString(): raptor_iostream");
        LibrdfUri u(uri);
        librdf_serializer_serialize_model_to_iostream(
                obj_, u.getWithoutIncrement(), model.getWithoutIncrement(), ios
        );
        const char *s = (const char *) buffer_to_hold_string;
        std::string output(s);
        free(buffer_to_hold_string);
        return output;
    }

    void LibrdfSerializer::validateSerializerName(std::string name) {
        std::vector<std::string> v = {
                "ntriples",
                "turtle",
                "rdfxml-abbrev",
                "rdfxml",
                "dot",
                "json-triples",
                "json",
                "nquads",
                "html",
                // unsupported by libOmexMeta
//                "rdfxml-xmp",
//                "rss-1.0",
//                "atom",
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
        std::string feature_uri_base = "http://feature.librdf.org/raptor-";
        LibrdfUri feature_uri(feature_uri_base + option);
        LibrdfNode node = LibrdfNode::fromLiteral(value);
        int failure = librdf_serializer_set_feature(get(), feature_uri.getWithoutIncrement(), node.getWithoutIncrement());
        if (failure < 0) {
            throw std::invalid_argument(
                    "std::invalid_argument: LibrdfSerializer::setOption: Invalid feature: " + option);
        }
        if (failure) {
            throw std::logic_error(
                    "std::logic_error: LibrdfSerializer::setOption. Failed to set serializer option: " + option);
        }
    }

    void LibrdfSerializer::setOptions() const {
        setOption("relativeURIs", "1");
        setOption("writeBaseURI", "0");
        setOption("xmlDeclaration", "1");
        setOption("xmlVersion", "1.1");
    }


    int toIOStream(const LibrdfUri &uri, const LibrdfModel *model, const RaptorIOStream &stream);

}

