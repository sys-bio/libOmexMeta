//
// Created by Ciaran on 5/20/2020.
//

#ifndef LIBSEMSIM_LIBRDFQUERYRESULTS_H
#define LIBSEMSIM_LIBRDFQUERYRESULTS_H

#include <librdf.h>
#include <memory>
#include "semsim/Error.h"

namespace semsim {
    typedef std::shared_ptr<librdf_query_results> query_results_ptr;

    class LibrdfQueryResults {
        query_results_ptr query_results_;

    public:
        const query_results_ptr &getQueryResults() const;

        LibrdfQueryResults() = default;

        explicit LibrdfQueryResults(librdf_query_results *query_results);

        bool operator!() const;

        bool operator==(const LibrdfQueryResults &rhs) const;

        bool operator!=(const LibrdfQueryResults &rhs) const;

        librdf_query_results *get();

    };
}


#endif //LIBSEMSIM_LIBRDFQUERYRESULTS_H
