//
// Created by Ciaran on 5/20/2020.
//

#ifndef LIBSEMSIM_LIBRDFQUERY_H
#define LIBSEMSIM_LIBRDFQUERY_H


#include <librdf.h>
#include <memory>
#include "semsim/Error.h"

namespace semsim {
    typedef std::shared_ptr<librdf_query> query_ptr;

    class LibrdfQuery {
        query_ptr query_;
    public:
        const query_ptr &getQuery() const;

        LibrdfQuery() = default;

        explicit LibrdfQuery(librdf_query *query);

        bool operator!() const;

        bool operator==(const LibrdfQuery &rhs) const;

        bool operator!=(const LibrdfQuery &rhs) const;

        librdf_query *get();

    };
}

#endif //LIBSEMSIM_LIBRDFQUERY_H
