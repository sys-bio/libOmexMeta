//
// Created by Ciaran on 4/9/2020.
//

#include "Reader.h"

#include <utility>
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include "SemSim.h"

using namespace std;

semsim::Reader::Reader(librdf_world *world, librdf_model *model, std::string format, std::string base_uri) {
    this->world_ = world;
    this->raptor_world_ptr_ = librdf_world_get_raptor(this->world_);
    this->model_ = model;
    this->format_ = std::move(format);
    this->base_uri_ = librdf_new_uri(this->world_, (const unsigned char *) base_uri.c_str());

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

librdf_parser *semsim::Reader::makeParser(const std::string& format) {
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
    parser_ = librdf_new_parser(world_, format.c_str(), nullptr, nullptr);
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

std::string semsim::Reader::fromString(const std::string &rdf_string) {
    // use a default base uri?
    librdf_parser_parse_string_into_model(parser_, (const unsigned char *) rdf_string.c_str(), base_uri_, model_);

}

void semsim::Reader::fromFile(const std::string &filename) {
    raptor_uri *uri = librdf_new_uri_from_filename(world_, (const char *) filename.c_str());
    if (!uri) {
        fprintf(stderr, "Failed to create URI\n");
    }
    base_uri_ = uri;
    librdf_parser_parse_into_model(parser_, uri, base_uri_, model_);
}

void semsim::Reader::setOption(const std::string &option, const std::string &value) {
    // prefix for option uri's. Append with desired option for full uri.
    std::string feature_uri_base = "http://feature.librdf.org/raptor-";
    raptor_uri *uri = raptor_new_uri(raptor_world_ptr_, (const unsigned char *) (feature_uri_base + option).c_str());
    librdf_node *node = librdf_new_node_from_literal(world_, (const unsigned char *) value.c_str(), nullptr, 0);
    librdf_parser_set_feature(parser_, uri, node);
}


vector<string> semsim::Reader::getSeenNamespaces() {
    int number_of_prefixes_seen = librdf_parser_get_namespaces_seen_count(parser_);
    std::vector<std::string> namespaces;
    raptor_uri *ns_uri;
    for (int i = 0; i < number_of_prefixes_seen; i++) {
        ns_uri = librdf_parser_get_namespaces_seen_uri(parser_, i);
        if (!ns_uri) {
            throw std::logic_error("couldn't get namespace uri");
        }

        namespaces.emplace_back((const char*)raptor_uri_to_string(ns_uri));
    }
    return namespaces;
}


void semsim::Reader::setBaseUri(const std::string &baseUri) {
    this->base_uri_ = librdf_new_uri(world_, (const unsigned char *) baseUri.c_str());
}

librdf_model *semsim::Reader::getModel() const {
    return model_;
}

librdf_world *semsim::Reader::getWorld() const {
    return world_;
}

raptor_world *semsim::Reader::getRaptorWorld() const {
    return raptor_world_ptr_;
}

const std::string &semsim::Reader::getFormat() const {
    return format_;
}

librdf_parser *semsim::Reader::getParser() const {
    return parser_;
}

librdf_uri *semsim::Reader::getBaseUri() const {
    return base_uri_;
}

const std::vector<std::string> &semsim::Reader::getValidParserNames() const {
    return valid_parser_names;
}

