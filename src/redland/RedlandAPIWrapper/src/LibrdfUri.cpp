//
// Created by Ciaran on 5/17/2020.
//
#include "LibrdfUri.h"
#include "World.h"

namespace redland {

    void LibrdfUri::deleter::operator()(librdf_uri *ptr) {
        if (ptr)
            raptor_free_uri_wrapper(ptr);
    }

    LibrdfUri::LibrdfUri(librdf_uri *uri)
            : librdf_uri_(std::shared_ptr<librdf_uri>(uri, raptor_free_uri_wrapper)) {}

    LibrdfUri::LibrdfUri(const std::string &uri) {
        librdf_uri_ = std::shared_ptr<librdf_uri>(
                librdf_new_uri(World::getWorld(), (const unsigned char *) uri.c_str()),
                raptor_free_uri_wrapper);
    }

    std::string LibrdfUri::str() const {
        auto cstr = (unsigned char *) librdf_uri_as_string(get());
        std::string s = (const char *) cstr;
        return s;
    }

    librdf_uri *LibrdfUri::get() const {
        return librdf_uri_.get();
    }


}
















