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


    LibrdfUri LibrdfUri::fromRawPtr(librdf_uri *uri) {
        return LibrdfUri(uri);
    }


    LibrdfUri::LibrdfUri(librdf_uri *uri)
            : uri_(uri) {}

    LibrdfUri::LibrdfUri(const std::string &uri)
        : uri_(librdf_new_uri(World::getWorld(), (const unsigned char *) uri.c_str())){
    }
//
//    LibrdfUri::LibrdfUri(librdf_uri *uri)
//            : uri_(std::shared_ptr<librdf_uri>(uri, raptor_free_uri)) {}
//
//    LibrdfUri::LibrdfUri(const std::string &uri) {
//        uri_ = std::shared_ptr<librdf_uri>(
//                librdf_new_uri(World::getWorld(), (const unsigned char *) uri.c_str()),
//                raptor_free_uri);
//    }

    std::string LibrdfUri::str() const {
        if (isNull())
            throw RedlandNullPointerException("RedlandNullPointerException: LibrdfUri::str(): uri is null");
        librdf_uri *u = get();
        unsigned char *cstr = librdf_uri_as_string(u);
        std::string s = (const char *) cstr;
        return s;
    }

    librdf_uri *LibrdfUri::get() const {
        return uri_;
    }

    bool LibrdfUri::isNull() const {
        return get() == nullptr;
    }

    bool LibrdfUri::isEmpty() const {
        if (isNull())
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: LibrdfUri::isEmpty(): uri is null on access");
        return str().empty();
    }


}
















