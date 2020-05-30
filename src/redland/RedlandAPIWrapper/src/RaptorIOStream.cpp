//
// Created by Ciaran on 5/26/2020.
//

#include "RaptorIOStream.h"


namespace redland {

    void RaptorIOStream::deleter::operator()(raptor_iostream *iostream) {
        if (iostream)
            raptor_free_iostream(iostream);
    }

    RaptorIOStream::RaptorIOStream(raptor_iostream *iostream)
            : iostream_(std::unique_ptr<raptor_iostream, deleter>(iostream)) {

    }

    raptor_iostream *RaptorIOStream::get() const {
        return iostream_.get();
    }

    std::pair<RaptorIOStream, void *> RaptorIOStream::newIOToString() {
        void *buffer_to_hold_string = nullptr;
        RaptorIOStream ios(raptor_new_iostream_to_string(
                World::getRaptor(), (void **) &buffer_to_hold_string, nullptr, malloc)
        );
        if (!ios.get())
            throw RedlandNullPointerException("Writer::toString(): raptor_iostream");
        std::pair<RaptorIOStream, void *> pair(std::move(ios), buffer_to_hold_string);
        return pair;
    }



}











