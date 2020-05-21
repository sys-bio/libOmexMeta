//
// Created by Ciaran on 5/17/2020.
//
#include "LibrdfUri.h"

namespace semsim {

    LibrdfUri::LibrdfUri(librdf_uri *uri)
            : librdf_uri_(librdf_uri_ptr(uri)) {

    }

    std::string LibrdfUri::str() const {
        if (librdf_uri_ == nullptr) {
            throw NullPointerException("LibrdfUri::str(): librdf_uri_ ");
        }
        unsigned char *cstr = raptor_uri_to_string(librdf_uri_.get());
        std::string str = (const char *) cstr;
        free(cstr);
        return str;
    }

    const librdf_uri_ptr &LibrdfUri::getLibrdfUri() const {
        return librdf_uri_;
    }

    bool LibrdfUri::operator!() const {
        return !librdf_uri_;
    }

    bool LibrdfUri::operator==(const LibrdfUri &rhs) const {
        return librdf_uri_.get() == rhs.librdf_uri_.get();
    }

    bool LibrdfUri::operator!=(const LibrdfUri &rhs) const {
        return !(rhs == *this);
    }

    librdf_uri *LibrdfUri::get() {
        return librdf_uri_.get();
    }

}
