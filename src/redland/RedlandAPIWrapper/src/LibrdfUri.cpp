//
// Created by Ciaran on 5/17/2020.
//
#include "LibrdfUri.h"
#include "World.h"

namespace semsim {

    void LibrdfUri::deleter::operator()(librdf_uri *ptr) {
        if (ptr)
            librdf_free_uri(ptr);
    }

    LibrdfUri::LibrdfUri(const std::string &uri) {
        librdf_uri_ = std::unique_ptr<librdf_uri, deleter>(
                librdf_new_uri(World::getWorld(), (const unsigned char *) uri.c_str())
        );
    }

    std::string LibrdfUri::str() const {
        auto cstr = (unsigned char *) librdf_uri_as_string(get());
        std::string s = (const char *) cstr;
        return s;
    }

    librdf_uri *LibrdfUri::get() const {
        return librdf_uri_.get();
    }

    LibrdfUri::LibrdfUri(librdf_uri *uri)
            : librdf_uri_(std::unique_ptr<librdf_uri, deleter>(uri)) {}


}
















