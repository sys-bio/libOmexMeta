//
// Created by Ciaran on 5/26/2020.
//

#include "RaptorIOStream.h"

namespace semsim {
    RaptorIOStream::RaptorIOStream(raptor_iostream *iostream)
            : iostream_(std::unique_ptr<raptor_iostream, deleter>(iostream)) {

    }

    raptor_iostream *RaptorIOStream::get() const {
        return iostream_.get();
    }

    void RaptorIOStream::deleter::operator()(raptor_iostream *iostream) {
        raptor_free_iostream(iostream);
    }
}