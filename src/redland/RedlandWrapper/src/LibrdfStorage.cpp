#include "redland/LibrdfStorage.h"


namespace redland {

    LibrdfStorage::~LibrdfStorage() {
        freeStorage();
    }

    LibrdfStorage::LibrdfStorage(librdf_storage *storage)
        : storage_(storage) {}

    LibrdfStorage::LibrdfStorage(const std::string &storage_name, const std::string &name, const char *options) {
        if (std::find(valid_stores_.begin(), valid_stores_.end(), storage_name) == valid_stores_.end()) {
            std::ostringstream err;
            err << "\"" << storage_name << "\" is not a valid storage name. These are your options ";
            for (auto &it : valid_stores_) {
                err << it << ", ";
            }
            err << std::endl;
            throw std::invalid_argument(err.str());
        }
        storage_ = librdf_new_storage(
                LibrdfWorld::getWorld(), storage_name.c_str(),
                name.c_str(), options);
        if (storage_ == nullptr) {
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: LibrdfStorage::LibrdfStorage(): librdf_storage* "
                    "type:\"" +
                    storage_name + "\" was not created. Nullptr.");
        }
    }

    LibrdfStorage::LibrdfStorage(LibrdfStorage &&storage) noexcept {
        if (storage.storage_ != nullptr) {
            if (storage_ != nullptr)
                freeStorage();
            storage_ = storage.storage_;
            storage.storage_ = nullptr;
        }
    }

    LibrdfStorage &LibrdfStorage::operator=(LibrdfStorage &&storage) noexcept {
        if (this != &storage) {
            if (storage.storage_ != nullptr) {
                if (storage_ != nullptr)
                    freeStorage();
                storage_ = storage.storage_;
                storage.storage_ = nullptr;
            }
        }
        return *this;
    }

    librdf_storage *LibrdfStorage::get() const {
        return storage_;
    }

    void LibrdfStorage::freeStorage() {
        if (!storage_)
            return;

        librdf_free_storage(storage_);
        storage_ = nullptr;
    }

    int LibrdfStorage::addStatement(librdf_statement *statement) {
        return librdf_storage_add_statement(storage_, statement);
    }

    int LibrdfStorage::addStatement(const LibrdfStatement &statement) {
        return librdf_storage_add_statement(storage_, statement.getWithoutIncrement());
    }

    int LibrdfStorage::size() {
        return librdf_storage_size(storage_);
    }

    int LibrdfStorage::commit() {
        return librdf_storage_transaction_commit(storage_);
    }

    void LibrdfStorage::printAvailableStorages() {
        print_available_storages(LibrdfWorld::getWorld());
    }


}// namespace redland
