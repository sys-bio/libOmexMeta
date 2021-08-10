//
// Created by Ciaran on 09/08/2021.
//

#include "redland/LibrdfStream.h"
#include "redland/LibrdfStatement.h"
#include "redland/Logger.h"

namespace redland {

    LibrdfStream::LibrdfStream(librdf_stream *stream)
        : Redland_librdf_stream(stream, librdf_free_stream){}

    LibrdfStatement LibrdfStream::getStatement(){
        LibrdfStatement s(librdf_stream_get_object(obj_));
        if (s.isNull()){
            std::ostringstream err;
            err << "statement is null";
            REDLAND_WARN(err.str());
            throw std::invalid_argument(err.str());
        }
        s.incrementUsage();
        return s;
    }

    bool LibrdfStream::end() {
        return librdf_stream_end(obj_);
    }

    bool LibrdfStream::next() {
        return librdf_stream_next(obj_);
    }

}// namespace redland
