//
// Created by Ciaran on 09/08/2021.
//

#ifndef LIBOMEXMETA_LIBRDFSTREAM_H
#define LIBOMEXMETA_LIBRDFSTREAM_H

#include "librdf.h"
#include "redland/LibrdfException.h"
#include "redland/LibrdfStatement.h"
#include "redland/RefCountedRedlandType.h"
#include <functional>

namespace redland {

    /**
     * @brief std::function signature of librdf_free_node
     */
    using stream_free_func = std::function<void(librdf_stream *)>;

    /**
     * Instantiation of templated superclass
     */
    using Redland_librdf_stream = RedlandType<librdf_stream, stream_free_func>;

    class LibrdfStream : public Redland_librdf_stream {

    public:
        using Redland_librdf_stream::Redland_librdf_stream;

        explicit LibrdfStream(librdf_stream* stream);

        /**
         * @brief get the current librdf_statement* as a LibrdfStatement
         * @details The returned LibrdfStatement has its internal
         * reference counter incremented by 1 and is therefore
         * managed via RAII.
         */
        LibrdfStatement getStatement();

        /**
         * @brief true when stream has ended
         */
        bool end();

        /**
         * @brief move current statement to the next statement
         */
        bool next();


    };

}// namespace redland

#endif//LIBOMEXMETA_LIBRDFSTREAM_H
