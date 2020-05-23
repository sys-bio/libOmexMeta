#include "LibrdfStorage.h"


namespace semsim {

    LibrdfStorage::LibrdfStorage(librdf_storage *storage)
            : storage_(storage_ptr(storage, librdf_free_storage)) {
    }

    bool LibrdfStorage::operator==(const LibrdfStorage &rhs) const {
        return storage_.get() == rhs.storage_.get();
    }

    bool LibrdfStorage::operator!=(const LibrdfStorage &rhs) const {
        return !(rhs == *this);
    }

    bool LibrdfStorage::operator!() const {
        return !storage_;
    }

    storage_ptr LibrdfStorage::getStorage() const {
        return storage_;
    }

    librdf_storage *LibrdfStorage::get() {
        return storage_.get();
    }


}