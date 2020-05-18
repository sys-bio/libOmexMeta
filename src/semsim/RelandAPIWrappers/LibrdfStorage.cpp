#include <string>
#include <memory>
#include <utility>
#include <iostream>
#include "LibrdfStorage.h"

namespace semsim {

    LibrdfStorage::LibrdfStorage(librdf_storage *storage, std::string storage_name, std::string name,
                                 std::string options)
            : storage_(std::make_shared<librdf_storage *>(storage)), storage_name_(std::move(storage_name)),
              name_(std::move(name)),
              options_(std::move(options)) {
    }

    LibrdfStorage::~LibrdfStorage() {
        if (storage_.use_count() == 1) {
            librdf_free_storage(*storage_);
        }
    };

    LibrdfStorage::LibrdfStorage(const LibrdfStorage &storage) {
        this->storage_ = storage.storage_;
        this->storage_name_ = storage.storage_name_;
        this->name_ = storage.name_;
        this->options_ = storage.options_;
    };

    LibrdfStorage &LibrdfStorage::operator=(const LibrdfStorage &storage) {
        if (this != &storage) {
            if (this->storage_ != nullptr) {
                // if this storage was instantiated with
                // a storage (which it probably was), get rid of
                // it before we take a copy of storage.storage_
                librdf_free_storage(*this->storage_);
            }
            this->storage_ = storage.storage_;
            this->storage_name_ = storage.storage_name_;
            this->name_ = storage.name_;
            this->options_ = storage.options_;
        };
        return *this;
    }

    LibrdfStorage::LibrdfStorage(LibrdfStorage &&storage) noexcept {
        this->storage_ = std::move(storage.storage_);
        this->storage_name_ = std::move(storage.storage_name_);
        this->name_ = std::move(storage.name_);
        this->options_ = std::move(storage.options_);
    }

    LibrdfStorage &LibrdfStorage::operator=(LibrdfStorage &&storage) noexcept {
        if (this != &storage) {
            if (this->storage_ != nullptr) {
                // if this storage was instantiated with
                // a storage (which it probably was), get rid of
                // it before we move storage.storage_ into this->storage_
                librdf_free_storage(*this->storage_);
            }
            this->storage_ = std::move(storage.storage_);
            this->storage_name_ = std::move(storage.storage_name_);
            this->name_ = std::move(storage.name_);
            this->options_ = std::move(storage.options_);
        };
        return *this;
    }

    bool LibrdfStorage::operator==(const LibrdfStorage &rhs) const {
        return *storage_ == *rhs.storage_ &&
               storage_name_ == rhs.storage_name_ &&
               name_ == rhs.name_ &&
               options_ == rhs.options_;
    }

    std::shared_ptr<librdf_storage *> LibrdfStorage::getStorage() const {
        return storage_;
    }

    const std::string &LibrdfStorage::getStorageName() const {
        return storage_name_;
    }

    const std::string &LibrdfStorage::getName() const {
        return name_;
    }

    const std::string &LibrdfStorage::getOptions() const {
        return options_;
    }

    const std::vector<std::string> &LibrdfStorage::getValidStorageNames() const {
        return valid_storage_names;
    }

    const std::vector<std::string> &LibrdfStorage::getValidStorage() const {
        return valid_storage;
    }

    const std::vector<std::string> &LibrdfStorage::getValidOptions() const {
        return valid_options;
    }

    bool LibrdfStorage::operator!=(const LibrdfStorage &rhs) const {
        return !(rhs == *this);
    }


}