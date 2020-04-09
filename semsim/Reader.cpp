//
// Created by Ciaran on 4/9/2020.
//

#include "Reader.h"

#include <utility>
#include <stdexcept>
#include <algorithm>
#include <sstream>

semsim::Reader::Reader(librdf_world *world, librdf_model *model, std::string format) {
    this->world_ = world;
    this->raptorWorld_ = librdf_world_get_raptor(this->world_);
    this->model_ = model;
    this->format_ = std::move(format);
    this->baseUri_ = librdf_new_uri(this->world_, (const unsigned char *) "./semsimModel.xml");

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
    if (std::find(valid_parser_names.begin(), valid_parser_names.end(), format) == valid_parser_names.end()){
        std::ostringstream os;
        os << "Format \"" << format << "\" is not a valid option. These are your options: ";
        for (auto &it : valid_parser_names){
            os << it << ", ";
        }
        throw std::invalid_argument(os.str());
    }
    parser_ = librdf_new_parser(world_, (const char *) format.c_str(), nullptr, nullptr);
    if (!parser_) {
        throw std::invalid_argument("Failed to create new parser\n");
    }
    return parser_;
}

std::string semsim::Reader::fromString(const std::string &rdf_string) {
    librdf_parser_parse_string_into_model(parser_, (const unsigned char *) rdf_string.c_str(), baseUri_, model_);
}

void semsim::Reader::fromFile(const std::string& filename) {
    raptor_uri *uri = librdf_new_uri_from_filename(world_, (const char *) filename.c_str());
    if (!uri) {
        fprintf(stderr, "Failed to create URI\n");
    }
    librdf_parser_parse_into_model(parser_, uri, baseUri_, model_);
}

void semsim::Reader::setBaseUri(const std::string& baseUri) {
    this->baseUri_ = librdf_new_uri(world_, (const unsigned char *) baseUri.c_str());
}

librdf_model *semsim::Reader::getModel() const {
    return model_;
}

