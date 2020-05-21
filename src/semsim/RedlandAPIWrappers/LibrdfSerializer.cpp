#include "LibrdfSerializer.h"
#include "LibrdfUri.h"

namespace semsim {

    LibrdfSerializer::LibrdfSerializer(librdf_serializer *serializer) :
            serializer_(serializer_ptr(serializer)) {

    }

    const serializer_ptr &LibrdfSerializer::getSerializer() const {
        return serializer_;
    }

    bool LibrdfSerializer::operator!() const {
        return !getSerializer();
    }

    bool LibrdfSerializer::operator==(const LibrdfSerializer &rhs) const {
        return serializer_.get() == rhs.serializer_.get();
    }

    bool LibrdfSerializer::operator!=(const LibrdfSerializer &rhs) const {
        return !(rhs == *this);
    }

    librdf_serializer *LibrdfSerializer::get() {
        return node_.get();
    }

}
