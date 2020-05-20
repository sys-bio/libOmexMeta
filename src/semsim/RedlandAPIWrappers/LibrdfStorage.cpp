#include "LibrdfStorage.h"


namespace semsim {

    LibrdfStorage::LibrdfStorage(librdf_storage *storage)
            : storage_(std::make_shared<librdf_storage *>(storage)) {
    }

    LibrdfStorage::~LibrdfStorage() {
        if (storage_.use_count() == 1) {
            librdf_free_storage(*storage_);
        }
    };

    LibrdfStorage::LibrdfStorage(const LibrdfStorage &storage) {
        this->storage_ = storage.storage_;
    };

    LibrdfStorage &LibrdfStorage::operator=(const LibrdfStorage &storage) {
        if (this != &storage) {
            // if this storage was instantiated with
            // a storage (which it probably was), get rid of
            // it before we take a copy of storage.storage_
            librdf_free_storage(*this->storage_);
            this->storage_ = storage.storage_;
        };
        return *this;
    }

    LibrdfStorage::LibrdfStorage(LibrdfStorage &&storage) noexcept {
        this->storage_ = std::move(storage.storage_);
    }

    LibrdfStorage &LibrdfStorage::operator=(LibrdfStorage &&storage) noexcept {
        if (this != &storage) {
            // if this storage was instantiated with
            // a storage (which it probably was), get rid of
            // it before we move storage.storage_ into this->storage_
            librdf_free_storage(*this->storage_);
            this->storage_ = std::move(storage.storage_);
        };
        return *this;
    }

    bool LibrdfStorage::operator==(const LibrdfStorage &rhs) const {
        return *storage_ == *rhs.storage_;
    }

    std::shared_ptr<librdf_storage *> LibrdfStorage::getStorage() const {
        return storage_;
    }

    bool LibrdfStorage::operator!=(const LibrdfStorage &rhs) const {
        return !(rhs == *this);
    }

    bool LibrdfStorage::operator!() const {
        return !storage_;
    }


}