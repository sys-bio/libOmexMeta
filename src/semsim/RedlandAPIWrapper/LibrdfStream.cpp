#include "LibrdfStream.h"

namespace semsim {

    LibrdfStream::LibrdfStream() :
            stream_(librdf_new_empty_stream(World::getWorld())) {}

    LibrdfStream::LibrdfStream(librdf_stream *stream) :
            stream_(std::unique_ptr<librdf_stream, deleter>(stream)) {}

    librdf_stream *LibrdfStream::get() const {
        return stream_.get();
    }

    void LibrdfStream::deleter::operator()(librdf_stream *stream) {
        librdf_free_stream(stream);
    }

}
