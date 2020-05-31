//
// Created by Ciaran on 4/9/2020.
//

#include "Reader.h"

namespace semsim {

    Reader::Reader(const LibrdfModel &model, std::string format,
                   const std::string &base_uri,
                   const char *mime_type, const char *type_uri)
            :
            model_(model),
            format_(std::move(format)),
            base_uri_(base_uri),
            mime_type_(mime_type),
            type_uri_(type_uri) {
        // generate new parsesr
        this->parser_ = makeParser(this->format_, mime_type_, type_uri_);
    }

/*
 * Set the format of parser to @parameter f
 */
    void Reader::setFormat(const std::string &f) {
        this->parser_ = makeParser(f, mime_type_, type_uri_);
    }

    LibrdfParser Reader::makeParser(const std::string &format, const char *mime_type, const char *type_uri) {
        if (std::find(valid_parser_names.begin(), valid_parser_names.end(), format) == valid_parser_names.end()) {
            std::ostringstream os;
            os << __FILE__ << ":" << __LINE__ << ": Format \"" << format
               << "\" is not a valid option. These are your options: ";
            for (auto &it : valid_parser_names) {
                os << it << ", ";
            }
            throw std::invalid_argument(os.str());
        }
        //todo read in  mime type from omex manifest, if you can
        parser_ = LibrdfParser(format.c_str(), mime_type, type_uri);
        if (!parser_.get()) {
            throw std::invalid_argument("Failed to create new parser\n");
        }

        // set parser options
        setOption("scanForRDF", "1");
        setOption("allowNonNsAttributes", "0");
        setOption("allowOtherParsetypes", "1");
        setOption("allowBagID", "1");
        setOption("allowRDFtypeRDFlist", "1");
        setOption("normalizeLanguage", "1");
        setOption("nonNFCfatal", "0");
        setOption("warnOtherParseTypes", "1");
        setOption("checkRdfID", "1");

        return std::move(parser_);
    }

    void Reader::fromString(const std::string &rdf_string) {
        parser_.parseString(rdf_string, model_, std::move(base_uri_));
    }


    void Reader::fromFile(const std::string &filepath) {
        LibrdfUri uri = LibrdfUri(filepath); // the filepath is the uri
        base_uri_ = LibrdfUri(filepath); // we also use filepath for base uri
        parser_.parseFilenameUriIntoModel(uri, base_uri_, model_);
    }

    void Reader::fromUri(const std::string &uri) {
        LibrdfUri uri_ = LibrdfUri(uri);
        base_uri_ = LibrdfUri(uri);
        parser_.parseUriIntoModel(uri_, base_uri_, model_);
    }

    void Reader::setOption(const std::string &option, const std::string &value) {
        // prefix for option uri's. Append with desired option for full uri.
        std::string feature_uri_base = "http://feature.librdf.org/raptor-";
        librdf_node* node = LibrdfNode::fromLiteral(value);
        parser_.setFeature(feature_uri_base + option, node);
    }


    std::vector<std::string> Reader::getSeenNamespaces() {
        int number_of_prefixes_seen = parser_.numNamespacesSeen();
        std::vector<std::string> namespaces;
        for (int i = 0; i < number_of_prefixes_seen; i++) {
            std::string nsref = parser_.getNamespacesSeenUri(i);
            namespaces.push_back(nsref);
        }
        return namespaces;
    }

    void Reader::setBaseUri(const std::string &baseUri) {
        this->base_uri_ = LibrdfUri(baseUri);
    }

    const std::vector<std::string> &Reader::getValidParserNames() const {
        return valid_parser_names;
    }

    const std::string &Reader::getFormat() const {
        return format_;
    }

    const LibrdfModel &Reader::getModel() const {
        return model_;
    }

    const LibrdfUri &Reader::getBaseUri() const {
        return base_uri_;
    }

    const LibrdfParser &Reader::getParser() const {
        return parser_;
    }

}