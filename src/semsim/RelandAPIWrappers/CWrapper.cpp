//
// Created by Ciaran on 5/17/2020.
//

#include <stdexcept>
#include "CWrapper.h"

namespace semsim {

    unsigned int CWrapper::getRefCount() const {
        return ref_count_;
    }

    void CWrapper::increment_ref_count() {
        ref_count_++;
    }

    void CWrapper::decrement_ref_count() {
        if (ref_count_ == 0) {
            throw std::logic_error("CWrapper::decrement: Trying to decrement reference count of 0.");
        }
        ref_count_--;
    }

    CWrapper::CWrapper() = default;


}