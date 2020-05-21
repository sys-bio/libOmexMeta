#include "LibrdfStream.h"

namespace semsim {

    LibrdfStream::LibrdfStream(librdf_stream *stream) :
            stream_(stream_ptr(stream, librdf_free_stream)) {

    }

    const stream_ptr &LibrdfStream::getStream() const {
        return stream_;
    }

    bool LibrdfStream::operator!() const {
        return !getStream();
    }

    bool LibrdfStream::operator==(const LibrdfStream &rhs) const {
        return stream_.get() == rhs.stream_.get();
    }

    bool LibrdfStream::operator!=(const LibrdfStream &rhs) const {
        return !(rhs == *this);
    }

    librdf_stream *LibrdfStream::get() {
        return stream_.get();
    }

}
