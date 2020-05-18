//
// Created by Ciaran on 5/17/2020.
//

#ifndef LIBSEMSIM_CWRAPPER_H
#define LIBSEMSIM_CWRAPPER_H

namespace semsim {
    class CWrapper {
    protected:
        unsigned int ref_count_ = 0;
    public:

        CWrapper();

        unsigned int getRefCount() const;

    protected:
        void increment_ref_count();

        void decrement_ref_count();

    };
}

#endif //LIBSEMSIM_CWRAPPER_H
