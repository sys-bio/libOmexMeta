//
// Created by Ciaran on 4/9/2020.
//

#include "Reader.h"



using namespace std;

semsim::Reader::Reader(LibrdfWorld world, LibrdfModel model, std::string format, std::string base_uri) {
    this->world_ = world;
    this->raptor_world_ptr_ = world.getRaptor();
    this->model_ = model;
    this->format_ = std::move(format);
    this->base_uri_ = world_.newUri(base_uri);

    // generate new parsesr
    this->parser_ = makeParser(this->format_);
}

/*
 * Set the format of parser to @parameter f
 */
void semsim::Reader::setFormat(const std::string &f) {
    librdf_free_parser(parser_);
    this->parser_ = makeParser(f);
}

librdf_parser *semsim::Reader::makeParser(const std::string &format) {
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
    parser_ = librdf_new_parser(*world_.getWorld(), format.c_str(), nullptr, nullptr);
    if (!parser_) {
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

    return parser_;
}

void semsim::Reader::fromString(const std::string &rdf_string) {
    librdf_parser_parse_string_into_model(parser_, (const unsigned char *) rdf_string.c_str(), *base_uri_.getUri(),
                                          *model_.getModel());
}

void semsim::Reader::fromFile(const std::string &filename) {
    LibrdfUri uri = world_.newUri(filename);
    if (!uri) {
        fprintf(stderr, "Failed to create URI\n");
    }
    base_uri_ = uri;
    librdf_parser_parse_into_model(parser_, *uri.getUri(), *base_uri_.getUri(), *model_.getModel());
}

void semsim::Reader::setOption(const std::string &option, const std::string &value) {
    // prefix for option uri's. Append with desired option for full uri.
    std::string feature_uri_base = "http://feature.librdf.org/raptor-";
    raptor_uri *uri = raptor_new_uri(
            *raptor_world_ptr_.getRaptorWorld(), (const unsigned char *) (feature_uri_base + option).c_str());
    LibrdfNode node = world_.newNodeLiteral(value, nullptr, 0);
    librdf_parser_set_feature(parser_, uri, *node.getNode());
}


vector<string> semsim::Reader::getSeenNamespaces() {
    int number_of_prefixes_seen = librdf_parser_get_namespaces_seen_count(parser_);
    std::vector<std::string> namespaces;
    raptor_uri *ns_uri;
    const char* uri_string;
    for (int i = 0; i < number_of_prefixes_seen; i++) {
        ns_uri = librdf_parser_get_namespaces_seen_uri(parser_, i);
        if (!ns_uri) {
            throw std::logic_error("semsim::Reader::getSeenNamespaces(): can't get namespace uri");
        }
        /*
         * Note: the command:
         *     const char* uri_string = (const char*) raptor_uri_to_string(ns_uri)
         * is a memory leak because the unsigned char* returned by raptor_uri_to_string
         * is unreachable and thus cannot be freed.
         *
         * Solution:
         *      split the command into two lines.
         */
        unsigned char* s = raptor_uri_to_string(ns_uri);
        uri_string = (const char *) s;
        namespaces.push_back(std::string(uri_string));
        free(s);
        librdf_free_uri(ns_uri);
    }

    return namespaces;
}


void semsim::Reader::setBaseUri(const std::string &baseUri) {
    this->base_uri_ = world_.newUri(baseUri);
}


const std::vector<std::string> &semsim::Reader::getValidParserNames() const {
    return valid_parser_names;
}

const semsim::LibrdfWorld &semsim::Reader::getWorld() const {
    return world_;
}

const semsim::RaptorWorld &semsim::Reader::getRaptorWorldPtr() const {
    return raptor_world_ptr_;
}

const string &semsim::Reader::getFormat() const {
    return format_;
}

const semsim::LibrdfModel &semsim::Reader::getModel() const {
    return model_;
}

librdf_parser *semsim::Reader::getParser() const {
    return parser_;
}

const semsim::LibrdfUri &semsim::Reader::getBaseUri() const {
    return base_uri_;
}

