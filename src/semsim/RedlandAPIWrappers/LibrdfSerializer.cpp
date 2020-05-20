#include "LibrdfSerializer.h"
#include "LibrdfUri.h"

namespace semsim {

    LibrdfSerializer::LibrdfSerializer(librdf_serializer *serializer) :
            serializer_(std::make_shared<librdf_serializer *>(serializer)) {

    }

    LibrdfSerializer::~LibrdfSerializer() {
        if (serializer_.use_count() == 1) {
            librdf_free_serializer(*serializer_);
        }
    }

    LibrdfSerializer::LibrdfSerializer(const LibrdfSerializer &LibrdfSerializer) {
        if (serializer_)
            librdf_free_serializer(*serializer_); // Remove prexisting serializer before copy
        serializer_ = LibrdfSerializer.serializer_;
    }

    LibrdfSerializer::LibrdfSerializer(LibrdfSerializer &&LibrdfSerializer) noexcept {
        if (serializer_) {
            librdf_free_serializer(*serializer_);
        }
        serializer_ = std::move(LibrdfSerializer.serializer_);
    }

    LibrdfSerializer &LibrdfSerializer::operator=(const LibrdfSerializer &LibrdfSerializer) {
        if (this != &LibrdfSerializer) {
            if (serializer_) {
                librdf_free_serializer(*serializer_);
            }
            serializer_ = LibrdfSerializer.serializer_;
        }
        return *this;
    }

    LibrdfSerializer &LibrdfSerializer::operator=(LibrdfSerializer &&LibrdfSerializer) noexcept {
        if (this != &LibrdfSerializer) {
            if (serializer_) {
                librdf_free_serializer(*serializer_);
            }
            serializer_ = std::move(LibrdfSerializer.serializer_);
        }
        return *this;
    }

    const std::shared_ptr<librdf_serializer *> &LibrdfSerializer::getSerializer() const {
        return serializer_;
    }

    bool LibrdfSerializer::operator!() const {
        return !getSerializer();
    }


}
