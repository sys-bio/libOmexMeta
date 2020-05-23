#include "LibrdfStorage.h"


namespace semsim {

    LibrdfStorage::LibrdfStorage(librdf_storage *storage)
            : storage_(storage) {}

    LibrdfStorage::LibrdfStorage(std::string storage_name, std::string name, std::string options) :
            storage_(
                    librdf_new_storage(
                            World::getWorld(), storage_name.c_str(),
                            name.c_str(), options.c_str()
                    )
            ) {}


    librdf_storage *LibrdfStorage::get() const {
        return storage_.get();
    }


    void LibrdfStorage::deleter::operator()(librdf_storage *storage) {
        librdf_free_storage(storage);
    }
}