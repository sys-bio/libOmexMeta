//
// Created by Ciaran on 5/17/2020.
//
#include "LibrdfUri.h"
#include "World.h"

/*
 * developer notes. Do not try to implement a deep copy/clone
 * method for librdf objects. There is a mechanism that exists, presumably for
 * efficiency, that stores Uri's in a avl tree and checks for existing
 * uri before creating a new one. Therefore, it is impossible to have multiple
 * copies of a librdf_uri at different memory locations.
 */

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
            : uri_(librdf_new_uri(World::getWorld(), (const unsigned char *) uri.c_str())) {
    }

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

    void LibrdfUri::freeUri() {
        if (uri_ != nullptr) {
            librdf_free_uri(uri_);
            uri_ = nullptr;
        }

    }

    LibrdfUri LibrdfUri::fromFilename(const std::string &filename) {
        librdf_uri *uri = librdf_new_uri_from_filename(World::getWorld(), filename.c_str());
        return LibrdfUri(uri);
    }

    LibrdfUri LibrdfUri::concatonate(librdf_uri *old_name, const std::string &local_name) {
        librdf_uri *uri = librdf_new_uri_from_uri_local_name(old_name, (const unsigned char *) local_name.c_str());
        return LibrdfUri(uri);
    }

    LibrdfUri LibrdfUri::concatonate(const std::string &local_name) const {
        librdf_uri *uri = librdf_new_uri_from_uri_local_name(get(), (const unsigned char *) local_name.c_str());
        return LibrdfUri(uri);
    }


    bool LibrdfUri::isFileUri() const {
        return librdf_uri_is_file_uri(get());

    }

    std::string LibrdfUri::toFilenameString() const {
        if (!isFileUri()) {
            throw std::logic_error("std::logic_error: LibrdfUri::toFilenameString(): Uri is not a Filename type uri. ");
        }
        char *string = (char *) librdf_uri_to_filename(get());
        std::string s = (const char *) string;
        free(string);
        return s;
    }

    bool LibrdfUri::operator==(const LibrdfUri &rhs) const {
        return librdf_uri_equals(get(), rhs.get());
    }

    bool LibrdfUri::operator!=(const LibrdfUri &rhs) const {
        return !(rhs == *this);
    }


}
















