//
// Created by Ciaran on 5/17/2020.
//
#include "redland/LibrdfUri.h"
#include "librdf.h"
#include "raptor2.h"
#include "redland/LibrdfWorld.h"
#include "redland/Logger.h"
/*
 * developer notes. Do not try to implement a deep copy/clone
 * method for librdf objects. There is a mechanism that exists, presumably for
 * efficiency, that stores Uri's in a avl tree and checks for existing
 * uri before creating a new one. Therefore, it is impossible to have multiple
 * copies of a librdf_uri at different memory locations.
 */

namespace redland {

    LibrdfUri::LibrdfUri(const std::string &uri)
        : RefCountedRedlandType<librdf_uri, uri_free_func>(
                  librdf_new_uri(LibrdfWorld::getWorld(), (const unsigned char *) uri.c_str()),
                  librdf_free_uri) {
        REDLAND_DEBUG("Instantiated a LibrdfUri instance");
    }

    LibrdfUri::LibrdfUri(librdf_uri *uri)
        : RefCounted_librdf_uri(uri, librdf_free_uri) {
        REDLAND_DEBUG("Instantiated a LibrdfUri instance");
    }
    std::string LibrdfUri::str() const {
        if (!obj_)
            throw RedlandNullPointerException("RedlandNullPointerException: LibrdfUri::str(): uri is null");
        unsigned char *cstr = librdf_uri_as_string(obj_);
        // note from librdf_uri_as_string doc:
        //  * Note: does not allocate a new string so the caller must not free it.
        std::string s = (const char *) cstr;
        return s;
    }

    bool LibrdfUri::isEmpty() const {
        if (!obj_)
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: LibrdfUri::isEmpty(): uri is null on access");
        return str().empty();
    }

    //    void LibrdfUri::freeUri() {
    //        if (!obj_)
    //            return;
    //        // need to collect the usage count before
    //        // the call to librdf_free_uri, or the
    //        // count will have gone
    //        int usageCount = getUsage();
    //        librdf_free_uri(obj_);
    //
    //        // set to null if uri was freed and not decremented
    //        if (usageCount - 1 == 0) {
    //            obj_ = nullptr;
    //        }
    //    }

    LibrdfUri LibrdfUri::fromFilename(const std::string &filename) {
        librdf_uri *uri = librdf_new_uri_from_filename(LibrdfWorld::getWorld(), filename.c_str());
        return {uri, librdf_free_uri};// brace initializer, automatically calls the constructor
    }

    LibrdfUri LibrdfUri::concatonate(librdf_uri *old_name, const std::string &local_name) {
        librdf_uri *uri = librdf_new_uri_from_uri_local_name(old_name, (const unsigned char *) local_name.c_str());
        return {uri, librdf_free_uri};
    }

    LibrdfUri LibrdfUri::concatonate(const std::string &local_name) const {
        librdf_uri *uri = librdf_new_uri_from_uri_local_name(obj_, (const unsigned char *) local_name.c_str());
        return {uri, librdf_free_uri};
    }


    bool LibrdfUri::isFileUri() const {
        return librdf_uri_is_file_uri(obj_);
    }

    std::string LibrdfUri::toFilenameString() const {
        if (!isFileUri()) {
            throw std::logic_error("std::logic_error: LibrdfUri::toFilenameString(): Uri is not a Filename type uri. ");
        }
        char *string = (char *) librdf_uri_to_filename(obj_);
        std::string s = (const char *) string;
        free(string);
        return s;
    }

    bool LibrdfUri::operator==(const LibrdfUri &rhs) const {
        if (!obj_ || !rhs.getWithoutIncrement()) {
            return false;
        }
        return librdf_uri_equals(obj_, rhs.getWithoutIncrement());
    }

    bool LibrdfUri::operator!=(const LibrdfUri &rhs) const {
        return !(rhs == *this);
    }


}// namespace redland
