#include "redland/LibrdfStorage.h"


namespace redland {
    LibrdfStorage::LibrdfStorage()
        : RefCounted_librdf_storage(
                  librdf_new_storage(LibrdfWorld::getWorld(), "memory", "libOmexMetaStore", nullptr),
                  librdf_free_storage) {}

    LibrdfStorage::LibrdfStorage(librdf_storage *storage)
        : RefCounted_librdf_storage(storage, librdf_free_storage) {}

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
        librdf_storage *storage = librdf_new_storage(
                LibrdfWorld::getWorld(), storage_name.c_str(),
                name.c_str(), options);
        if (storage == nullptr) {
            throw RedlandNullPointerException(
                    "RedlandNullPointerException: LibrdfStorage::LibrdfStorage(): librdf_storage* "
                    "type:\"" +
                    storage_name + "\" was not created. Nullptr.");
        }
        obj_ = storage;
        freeFunc_ = librdf_free_storage;
    }

    int LibrdfStorage::addStatement(const LibrdfStatement &statement) {
        return librdf_storage_add_statement(obj_, statement.getWithoutIncrement());
    }

    int LibrdfStorage::size() {
        return librdf_storage_size(obj_);
    }

    int LibrdfStorage::commit() {
        return librdf_storage_transaction_commit(obj_);
    }

    void LibrdfStorage::printAvailableStorages() {
        print_available_storages(LibrdfWorld::getWorld());
    }


}// namespace redland
