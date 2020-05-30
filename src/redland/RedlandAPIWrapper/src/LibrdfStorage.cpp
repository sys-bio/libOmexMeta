#include "LibrdfStorage.h"


namespace redland {

    void LibrdfStorage::deleter::operator()(librdf_storage *storage) {
        if (storage)
            librdf_free_storage(storage);
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
        storage_ = std::unique_ptr<librdf_storage, deleter>(librdf_new_storage(
                World::getWorld(), storage_name.c_str(),
                name.c_str(), options)
        );
    }


    librdf_storage *LibrdfStorage::get() const {
        return storage_.get();
    }


}