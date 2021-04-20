//
// Created by Ciaran on 5/17/2020.
//
#include "redland/LibrdfUri.h"
#include "librdf.h"
#include "redland/World.h"

/*
 * developer notes. Do not try to implement a deep copy/clone
 * method for librdf objects. There is a mechanism that exists, presumably for
 * efficiency, that stores Uri's in a avl tree and checks for existing
 * uri before creating a new one. Therefore, it is impossible to have multiple
 * copies of a librdf_uri at different memory locations.
 */

namespace redland {

    LibrdfUri::LibrdfUri(const LibrdfUri &librdfUri) {
        if (uri_) {
            librdf_free_uri(uri_);
            uri_ = nullptr;
        }
        uri_ = librdfUri.get();// automatically increments the ref count for us
    }

    LibrdfUri::LibrdfUri(LibrdfUri &&librdfUri) noexcept {
        if (*this != librdfUri) {
            if (uri_) {
                librdf_free_uri(uri_);
                uri_ = nullptr;
            }
            uri_ = librdfUri.getWithoutIncrement();
            librdfUri.uri_ = nullptr;
        }
    }

    LibrdfUri &LibrdfUri::operator=(const LibrdfUri &librdfUri) {
        if (uri_) {
            librdf_free_uri(uri_);
            uri_ = nullptr;
        }
        uri_ = librdfUri.get();// automatically increments the ref count for us
        return *this;
    }

    LibrdfUri &LibrdfUri::operator=(LibrdfUri &&librdfUri) noexcept {
        if (*this != librdfUri) {
            if (uri_) {
                librdf_free_uri(uri_);
                uri_ = nullptr;
            }
            uri_ = librdfUri.getWithoutIncrement();
            librdfUri.uri_ = nullptr;
        }
        return *this;
    }

    LibrdfUri::~LibrdfUri() {
        freeUri();
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
        if (!uri_)
            throw RedlandNullPointerException("RedlandNullPointerException: LibrdfUri::str(): uri is null");
        unsigned char *cstr = librdf_uri_as_string(uri_);
        // note from librdf_uri_as_string doc:
        //  * Note: does not allocate a new string so the caller must not free it.
        std::string s = (const char *) cstr;
        return s;
    }

    librdf_uri *LibrdfUri::get() const {
        incrementUsage();
        return uri_;
    }

    librdf_uri *LibrdfUri::getWithoutIncrement() const {
        return uri_;
    }

    bool LibrdfUri::isEmpty() const {
        if (!uri_)
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: LibrdfUri::isEmpty(): uri is null on access");
        return str().empty();
    }

    void LibrdfUri::freeUri() {
        if (!uri_)
            return;
        // need to collect the usage count before
        // the call to librdf_free_uri, or the
        // count will have gone
        int usageCount = getUsage();
        librdf_free_uri(uri_);

        // set to null if uri was freed and not decremented
        if (usageCount - 1 == 0) {
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
        librdf_uri *uri = librdf_new_uri_from_uri_local_name(uri_, (const unsigned char *) local_name.c_str());
        return LibrdfUri(uri);
    }


    bool LibrdfUri::isFileUri() const {
        return librdf_uri_is_file_uri(uri_);
    }

    std::string LibrdfUri::toFilenameString() const {
        if (!isFileUri()) {
            throw std::logic_error("std::logic_error: LibrdfUri::toFilenameString(): Uri is not a Filename type uri. ");
        }
        char *string = (char *) librdf_uri_to_filename(uri_);
        std::string s = (const char *) string;
        free(string);
        return s;
    }

    bool LibrdfUri::operator==(const LibrdfUri &rhs) const {
        if (!uri_ || !rhs.getWithoutIncrement()) {
            return false;
        }
        return librdf_uri_equals(uri_, rhs.getWithoutIncrement());
    }

    bool LibrdfUri::operator!=(const LibrdfUri &rhs) const {
        return !(rhs == *this);
    }

    int LibrdfUri::getUsage() {
        return librdf_uri_get_usage(uri_);
    }

    void LibrdfUri::incrementUsage() const {
        librdf_uri_increment_usage(uri_);
    }


}// namespace redland
