#include "LibrdfStream.h"

namespace semsim {

    LibrdfStream::LibrdfStream(librdf_stream *stream) :
            stream_(std::make_shared<librdf_stream *>(stream)) {

    }

    LibrdfStream::~LibrdfStream() {
        if (stream_.use_count() == 1) {
            librdf_free_stream(*stream_);
        }
    }

    LibrdfStream::LibrdfStream(const LibrdfStream &LibrdfStream) {
        if (stream_)
            librdf_free_stream(*stream_); // Remove prexisting stream before copy
        stream_ = LibrdfStream.stream_;
    }

    LibrdfStream::LibrdfStream(LibrdfStream &&LibrdfStream) noexcept {
        if (stream_) {
            librdf_free_stream(*stream_);
        }
        stream_ = std::move(LibrdfStream.stream_);
    }

    LibrdfStream &LibrdfStream::operator=(const LibrdfStream &LibrdfStream) {
        if (this != &LibrdfStream) {
            if (stream_) {
                librdf_free_stream(*stream_);
            }
            stream_ = LibrdfStream.stream_;
        }
        return *this;
    }

    LibrdfStream &LibrdfStream::operator=(LibrdfStream &&LibrdfStream) noexcept {
        if (this != &LibrdfStream) {
            if (stream_) {
                librdf_free_stream(*stream_);
            }
            stream_ = std::move(LibrdfStream.stream_);
        }
        return *this;
    }

    const std::shared_ptr<librdf_stream *> &LibrdfStream::getStream() const {
        return stream_;
    }

    bool LibrdfStream::operator!() const {
        return !getStream();
    }

}
