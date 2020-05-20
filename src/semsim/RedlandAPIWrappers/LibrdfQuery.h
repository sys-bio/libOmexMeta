//
// Created by Ciaran on 5/20/2020.
//

#ifndef LIBSEMSIM_LIBRDFQUERY_H
#define LIBSEMSIM_LIBRDFQUERY_H


#include <librdf.h>
#include <memory>
#include "semsim/Error.h"

namespace semsim {
    class LibrdfQuery {
        std::shared_ptr<librdf_query *> query_;
    public:
        const std::shared_ptr<librdf_query *> &getQueryResults() const;

        LibrdfQuery() = default;

        explicit LibrdfQuery(librdf_query *query_results);

        ~LibrdfQuery();

        LibrdfQuery(const LibrdfQuery &LibrdfQuery);

        LibrdfQuery(LibrdfQuery &&LibrdfQuery) noexcept;

        LibrdfQuery &operator=(const LibrdfQuery &LibrdfQuery);

        LibrdfQuery &operator=(LibrdfQuery &&LibrdfQuery) noexcept;

        bool operator!() const;


    };
}

#endif //LIBSEMSIM_LIBRDFQUERY_H
