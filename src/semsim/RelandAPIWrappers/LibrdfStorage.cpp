#include <string>
#include "LibrdfStorage.h"

namespace semsim {

    bool LibrdfStorage::operator==(const LibrdfStorage &rhs) const {
        return storage_ == rhs.storage_ &&
               storage_name_ == rhs.storage_name_ &&
               name_ == rhs.name_ &&
               options_ == rhs.options_;
    }

    librdf_storage *LibrdfStorage::getStorage() const {
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

    LibrdfStorage::LibrdfStorage(librdf_storage *storage, std::string storage_name, std::string name,
                                 std::string options)
            : CWrapper(), storage_(storage), storage_name_(storage_name), name_(name),
              options_(options) {
        increment_ref_count();
    }

    LibrdfStorage::~LibrdfStorage() {
        if (ref_count_ > 0) {
            decrement_ref_count();
        } else {
            librdf_free_storage(storage_);
        }
    }

    LibrdfStorage::LibrdfStorage(LibrdfStorage &librdfStorage) {
        if (this != &librdfStorage) {
            storage_ = librdfStorage.storage_;
            storage_name_ = librdfStorage.storage_name_;
            name_ = librdfStorage.name_;
            options_ = librdfStorage.options_;

            ref_count_ = librdfStorage.ref_count_;
            increment_ref_count();
            librdfStorage.increment_ref_count();
        }
    }

    LibrdfStorage::LibrdfStorage(LibrdfStorage &&librdfStorage) noexcept {
        if (this != &librdfStorage) {
            storage_ = librdfStorage.storage_;
            storage_name_ = librdfStorage.storage_name_;
            name_ = librdfStorage.name_;
            options_ = librdfStorage.options_;

            storage_ = librdfStorage.storage_;
            ref_count_ = librdfStorage.ref_count_;
            librdfStorage.storage_ = nullptr;
        }
    }

    LibrdfStorage &LibrdfStorage::operator=(LibrdfStorage &librdfStorage) {
        if (this != &librdfStorage) {
            storage_ = librdfStorage.storage_;
            storage_name_ = librdfStorage.storage_name_;
            name_ = librdfStorage.name_;
            options_ = librdfStorage.options_;

            ref_count_ = librdfStorage.ref_count_;
            increment_ref_count();
            librdfStorage.increment_ref_count();
        }
        return *this;
    }

    LibrdfStorage &LibrdfStorage::operator=(LibrdfStorage &&librdfStorage) noexcept {
        if (this != &librdfStorage) {
            storage_ = librdfStorage.storage_;
            storage_name_ = librdfStorage.storage_name_;
            name_ = librdfStorage.name_;
            options_ = librdfStorage.options_;

            storage_ = librdfStorage.storage_;
            ref_count_ = librdfStorage.ref_count_;
            librdfStorage.storage_ = nullptr;
        }
        return *this;
    }

}