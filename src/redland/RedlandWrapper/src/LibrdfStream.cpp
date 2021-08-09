//
// Created by Ciaran on 09/08/2021.
//

#include "redland/LibrdfStream.h"
#include "redland/LibrdfStatement.h"

namespace redland {

    LibrdfStream::LibrdfStream(librdf_stream *stream)
        : Redland_librdf_stream(stream, librdf_free_stream){}

    LibrdfStatement LibrdfStream::getStatement(){
        LibrdfStatement s(librdf_stream_get_object(obj_));
        s.incrementUsage();
        return s;
    }

}// namespace redland
